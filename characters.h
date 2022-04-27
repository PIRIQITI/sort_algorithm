/**
 *  This portion of the program takes care of sorting characters
 *  it models input into dynamically allocated array and sorts it
 */

#ifndef D2FABA92_6031_44A0_A732_B5893BE57232
#define D2FABA92_6031_44A0_A732_B5893BE57232

#include <string.h>
#include "structures.h"
#include "abort.h"

// you can modify this constant to sort input however you'd like
#define ALPHABET "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789"
#define ALPHABET_SIZE 63 // make sure to change this constant if you change ALPHABET

typedef int (*char_compare_template) (int first, int second, int *check);

int check_character(const unsigned char ch);
void free_memory(struct Array_2d *arr);
void swap(struct Array *array1, struct Array *array2, char_compare_template cmp);

int cmp_char_ascending(int first, int second, int *check)
{
    *check = 0;
    return first > second;
}

int cmp_char_descending(int first, int second, int *check)
{
    *check = 1;
    return second > first;
}

int cmp_size(int index, int size)
{
    return index == size;
}

/* 
    this function creates an array of integer arrays
    it models command line input as arrays of integers and checks characters if they are in ALPHABET constant
    here are many checks to prevent errors (function is tested in various ways using valgrind)
    if errors happen program frees up all allocated memory and aborts with an error message
*/
struct Array_2d *make_char_array(char *argv[], const int count)
{
    struct Array_2d *array_of_int_arrays = (struct Array_2d *)malloc(sizeof(struct Array_2d));

    if (!array_of_int_arrays)
        die(MEMORY_ERROR);

    array_of_int_arrays->size = 0;

    struct Array *array_of_ints = (struct Array *)malloc(count * sizeof(struct Array));

    if (!array_of_ints) {
        free(array_of_int_arrays);
        die(MEMORY_ERROR);
    }

    array_of_int_arrays->cell = array_of_ints;

    int i = 0;
    int j = 0;
    for (i = 0; i < count; i++) {
        array_of_ints[i].size = strlen(argv[i + 2]);

        int *elements = (int *)malloc(strlen(argv[i + 2]) * sizeof(int));

        if (!elements) { // This if statement frees up all allocated memory if any of the allocations fail
            free_memory(array_of_int_arrays);
            die(MEMORY_ERROR);
        }
        array_of_ints[i].elements = elements;
        array_of_int_arrays->size++;

        for (j = 0; j < array_of_ints[i].size; j++) {
            if (!check_character(argv[i + 2][j])) {
                free_memory(array_of_int_arrays);
                die(INVALID_ARGS_ERROR);
            }
            array_of_ints[i].elements[j] = argv[i + 2][j];
        }

    }

    return array_of_int_arrays;
}

/*
    this function takes pointer to data allocated by make_char_array()
    it copies memory into newly allocated space leaving original data intact
    lastly it calls swap() function to sort input as needed
    function is well tested and there are no leaks its tested with valgrind
*/
struct Array_2d *sort_characters(struct Array_2d *arr, char_compare_template cmp)
{
    struct Array_2d *sorted_words = (struct Array_2d *)malloc(sizeof(struct Array_2d));

    if (!sorted_words)
        die(MEMORY_ERROR);

    sorted_words->size = 0;

    struct Array *words = (struct Array *)malloc(arr->size * sizeof(struct Array));

    if (!words) {
        free(sorted_words);
        die(MEMORY_ERROR);
    }
    sorted_words->cell = words;

    int i = 0;
    for (i = 0; i < arr->size; i++) {

        int *word = malloc(arr->cell[i].size * sizeof(int));

        if (!word) { // This if frees up all allocated memory if any of the allocations fail
            free_memory(sorted_words);
            free_memory(arr);
            die(MEMORY_ERROR);
        }

        memcpy(word, arr->cell[i].elements, arr->cell[i].size * sizeof(int)); // find out what happens if this fails
        
        words[i].elements = word;
        words[i].size = arr->cell[i].size;

        sorted_words->size++;
    }

    int j = 0;
    for (i = 0; i < sorted_words->size; i++) {
        struct Array *array1 = &(sorted_words->cell[i]);
        for (j = i + 1; j < sorted_words->size; j++) {
            struct Array *array2 = &(sorted_words->cell[j]);
            swap(array1, array2, cmp);
        }
    }

    return sorted_words;
}

int check_character(const unsigned char ch)
{
    int i = 0;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        if (ALPHABET[i] == ch)
            return 1;
    }
    return 0;
}

void free_memory(struct Array_2d *arr)
{
    int i = 0;
    for (i = 0; i < arr->size; i++)
        free(arr->cell[i].elements);
    free(arr->cell);
    free(arr);
}

void swap(struct Array *array1, struct Array *array2, char_compare_template cmp)
{
    int l = 0;
    int k = 0;
    for (l = 0; l < array1->size; l++) {
        unsigned char ch1 = array1->elements[l];
        unsigned char ch2 = array2->elements[l];
        // printf("\narray1: ");
        // print_word(array1);
        // printf("\narray2: ");                                        // printfs for initial testing
        // print_word(array2);
        // printf("\n%d\nch1 %c\nch2 %c\n", array1->size, ch1, ch2);
        int first = 0;
        int second = 0;
        for (k = 0; k < ALPHABET_SIZE; k++) { // 63 being length of the ALPHABET defined at the beginning of the file
            if (ALPHABET[k] == ch1)
                first = k + 1; // + 1 for the last if (first && second) to work in case ch1 or ch2 or both are A
            if (ALPHABET[k] == ch2)
                second = k + 1;

            if (first && second)
                break; // this if exists to optimize algorithm. end the for loop immediately after both values are found
        }
        // if first character comes after the second one swap them
        int check = 0; // this variable tells how we are sorting, ascending or descending
        if (cmp(first, second, &check)) {
            struct Array temp = *array1;
            *array1 = *array2;
            *array2 = temp;
            break;
        } else if (cmp(second, first, &check)) {
            // if first character is already before the second character no swap needed so break out of the for loop
            break;
        }
        // this is if statement to swap if the swap hasnt happened since the scope of the for loop began
        if (l == array1->size - 1 && !check) {
            struct Array temp = *array1;
            *array1 = *array2;
            *array2 = temp;
            break;
        } else if (l == array2->size - 1 && check) {
            struct Array temp = *array1;
            *array1 = *array2;
            *array2 = temp;
        }
        // this is if statement to prevent out of bounds read of memory
        if (l == array1->size - 1 || l == array2->size - 1)
            break;
    }
}

void print_words(struct Array_2d *array_of_arrays)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < array_of_arrays->size; i++) {
        for (j = 0; j < array_of_arrays->cell[i].size; j++) {
            unsigned char ch = array_of_arrays->cell[i].elements[j];
            printf("%c", ch);
        }
        printf(" ");
    }
}

/*
void print_word(struct Array *arr)
{
    int i = 0;
    for (i = 0; i < arr->size; i++)             // this function is for testing
        printf("%c", arr->elements[i]);
    printf("\n");
}
*/

#endif /* D2FABA92_6031_44A0_A732_B5893BE57232 */

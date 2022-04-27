/**
 *  This portion of the program takes care of sorting integers
 *  it models input into dynamically allocated array and sorts it
*/

#ifndef DA433472_C2E9_423E_B90D_C76E83E708DB
#define DA433472_C2E9_423E_B90D_C76E83E708DB

#include <string.h>
#include "structures.h"
#include "abort.h"

typedef int (*int_compare_template) (int a, int b);

int cmp_int_ascending(int a, int b)
{
    return a > b;
}

int cmp_int_descending(int a, int b)
{
    return a < b;
}

/*
    this function creates array of integers and tests input to be numbers only
    function is well tested with valgrind and has no leaks
*/
struct Array *make_int_array(char *argv[], const int count)
{
    int *numbers = (int *)malloc(count * sizeof(int));

    if (!numbers)
        die(MEMORY_ERROR);

    // Check for invalid inputs, if there are characters abort, if not add them to the array
    int i = 0;
    int j = 0;
    int unary_minus_count = 0;
    for (i = 0; i < count; i++) {
        for (j = 0; j < strlen(argv[i + 2]); j++) {
            if (argv[i + 2][j] == 45)
                unary_minus_count++;
            if ((argv[i + 2][j] < 48 || argv[i + 2][j] > 57) && argv[i + 2][j] != 45) {
                free(numbers);
                die(INVALID_ARGS_ERROR);
            }
            if (unary_minus_count > 1) {
                free(numbers);
                die(INVALID_ARGS_ERROR);
            } else if (unary_minus_count == 1 && strlen(argv[i + 2]) == 1) {
                free(numbers);
                die(INVALID_ARGS_ERROR);
            }
        }
        numbers[i] = atoi(argv[i + 2]);
        unary_minus_count = 0;
    }

    struct Array *array = (struct Array *)malloc(sizeof(struct Array));

    if (!array) {
        free(numbers);
        die(MEMORY_ERROR);
    }

    array->elements = numbers;
    array->size = count;

    return array;
}

/*
    this function takes pointer to data allocated by make_int_array()
    it copies memory into newly allocated space leaving original data intact
    lastly it sorts integers
*/
struct Array *sort_integers(struct Array *arr, int_compare_template cmp)
{
    int *ordered_arr = (int *)malloc(arr->size * sizeof(int));

    if (!ordered_arr) {
        free(arr->elements);
        free(arr);
        die(MEMORY_ERROR);
    }

    struct Array *array = (struct Array *)malloc(sizeof(struct Array));

    if (!array) {
        free(arr->elements);
        free(arr);
        free(ordered_arr);
        die(MEMORY_ERROR);
    }

    array->elements = ordered_arr;
    array->size = arr->size;

    memcpy(array->elements, arr->elements, arr->size * sizeof(int));

    int i = 0;
    int j = 0;
    int temp = 0;
    for (i = 0; i < array->size; i++) {
        temp = array->elements[i];
        for (j = i + 1; j < array->size; j++) {
            if (cmp(temp, array->elements[j])) {
                temp = array->elements[j];
                array->elements[j] = array->elements[i];
                array->elements[i] = temp;
            }
        }
    }

    return array;
}

void print_int_array(const struct Array *const arr)
{
    int i = 0;
    for (i = 0; i < arr->size; i++)
        printf(" %d ", arr->elements[i]);
}


#endif /* DA433472_C2E9_423E_B90D_C76E83E708DB */

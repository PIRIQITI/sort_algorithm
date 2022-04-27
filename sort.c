/**
 * @file sort.c
 * @author PIRIQITI
 * @brief sort input in different ways
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CD8A9D4B_389D_420C_B976_A97F86ACC4F2
#define CD8A9D4B_389D_420C_B976_A97F86ACC4F2

#include "integers.h"
#include "characters.h"
#include "parsing_args.h"

int main(int argc, char *argv[])
{
    enum Options { INT, CHAR, HELP, ERROR };

    int option = examine_args(argc, argv);

    const int count = argc - 2;

    switch (option) {
        case INT:
            {   // this data "array" stays intact and gets freed lastly
                struct Array *array = make_int_array(argv, count);

                struct Array *sorted_array = sort_integers(array, cmp_int_ascending);
                printf("ascending: ");
                print_int_array(sorted_array);
                printf("\n");
                free(sorted_array->elements);
                free(sorted_array);

                sorted_array = sort_integers(array, cmp_int_descending);
                printf("descending: ");
                print_int_array(sorted_array);
                printf("\n");
                free(sorted_array->elements);
                free(sorted_array);


                free(array->elements);
                free(array);
            }
            break;

        case CHAR:
            {   // this data "array_of_arrays" stays intact and gets freed lastly
                struct Array_2d *array_of_arrays = make_char_array(argv, count);
                
                struct Array_2d *sorted_array = sort_characters(array_of_arrays, cmp_char_ascending);
                printf("\nascending: ");
                print_words(sorted_array);
                printf("\n");

                free_memory(sorted_array);

                sorted_array = sort_characters(array_of_arrays, cmp_char_descending);
                printf("\ndescending: ");
                print_words(sorted_array);
                printf("\n");

                free_memory(sorted_array);


                free_memory(array_of_arrays);
            }
            break;

        case HELP:
            printf("%s\n", USAGE);
            break;

        default:
            die(USAGE);
    }

    return 0;
}


#endif /* CD8A9D4B_389D_420C_B976_A97F86ACC4F2 */

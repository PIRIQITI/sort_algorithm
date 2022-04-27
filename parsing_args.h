/**
 *  This part takes care of command line arguments
 */

#ifndef D8F8180C_443B_43BA_834A_6671CCE672D4
#define D8F8180C_443B_43BA_834A_6671CCE672D4

#include <string.h>

int compare(const char *const arg, const char *option)
{
    if (strlen(arg) != strlen(option))
        return 0;

    int i = 0;
    for (i = 0; i < strlen(arg); i++) {
        if (arg[i] != option[i])
            return 0;
    }

    return 1;
}

int examine_args(const int argc, char *argv[])
{
    if (argc == 2) {
        if (compare(argv[1], "--help"))
            return 2;
        else
            return 3;
    } else if (argc >= 3) {
        if (compare(argv[1], "--integers"))
            return 0;
        else if (compare(argv[1], "--characters"))
            return 1;
        else
            return 3;
    } else {
        return 3;
    }
}


#endif /* D8F8180C_443B_43BA_834A_6671CCE672D4 */

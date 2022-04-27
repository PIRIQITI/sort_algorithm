#ifndef F135B0AD_31F7_4607_ABFF_D2756F404DDE
#define F135B0AD_31F7_4607_ABFF_D2756F404DDE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define USAGE "USAGE: sort [--integers] or [--characters], [integers or characters(words or chars) separated by the whitespaces]."
#define MEMORY_ERROR "memory error."
#define INVALID_ARGS_ERROR "provided arguments are invalid."

void die(const char *message)
{
    if (errno)
        perror(message);
    else
        printf("ERROR: %s", message);

    printf("\n");
    exit(1);
}


#endif /* F135B0AD_31F7_4607_ABFF_D2756F404DDE */

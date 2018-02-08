/*
    this file should include function definitions

    include any libraries needed by your functions
*/

#include <stdio.h>
#include <stdlib.h>
#include "hw09-lib.h"


char ** grow(char ** array, int newSize)
{
    char ** temp;
    temp = realloc(array, newSize * sizeof(char *));
    if (temp != NULL)
        return temp;
    printf("Error reallocating.\n");
    exit(1);
}

void freeArray(char ** array, int size)
{
    for (size--; size >= 0; size--)
        free(array[size]);
    free(array);
}

char ** sortArray(char ** array, int size)
{

}

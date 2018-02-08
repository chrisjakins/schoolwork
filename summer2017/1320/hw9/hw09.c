/*
    to compile, type
      make
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw09-lib.h"

int main(void)
{
    FILE * inFile;
    char * filename = "data09.txt", buffer[21],
         ** nameArray;
    Node * root;
    int maxSize = 2, currentSize = 0;

    if ((inFile = fopen(filename, "r")) == NULL)
    {
        printf("problem opening %s\n", filename);
        return EXIT_FAILURE;
    }

    nameArray = malloc(maxSize * sizeof(char *));

    while (fgets(buffer, sizeof(buffer), inFile) != NULL)
    {
        if (currentSize == maxSize)
        {
            maxSize *= 2;
            nameArray = grow(nameArray, maxSize);
        } 
        nameArray[currentSize] = malloc(strlen(buffer) + 1);
        currentSize++;
    }
    
    /* sort array */
    freeArray(nameArray, currentSize);
    return EXIT_SUCCESS;
}

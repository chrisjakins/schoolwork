/* Chris Jakins */
/* HW6 */
/* CSE1320 */
/* 7/26 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char ** readFile(char *, int *);
char ** grow(char **, int);
void printLines(char **, int, int);
void sort(char **, int);
void swap(char **, char **);
void freeMem(char ** array, int size);

int main(int argc, char * argv[])
{
    char ** lines;
    int count = 0, argNum;

    if (argc != 4)
    {
        printf("  usage: executable [h/t/b/s] number filename\n");
        printf("example: ./jakins-hw06 h 10 somefile.txt\n");
        return EXIT_FAILURE;
    }
    lines = readFile(argv[3], &count); 

    argNum = atoi(argv[2]);
    if (argNum >= count) /* user-specified number is greater than lines in file */
        printLines(lines, 0, count);
    else                /* user-specified number is valid */
        switch(*argv[1])
        {
            case 'h': printLines(lines, 0, argNum); break;
            case 't': printLines(lines, count - argNum, count); break;
            case 'b': 
                if (argNum >= count / 2) /* user number is greater than half lines in file*/
                    printLines(lines, 0, count);
                else
                {
                    printLines(lines, 0, argNum);
                    printLines(lines, count - argNum, count);
                }
                break;
            case 's': sort(lines, count);
                      printLines(lines, 0, count); break;
            default:
                printf("%s is not a valid option\n", argv[1]);
                break;
        }

    freeMem(lines, count);
    return EXIT_SUCCESS;
}

/*  this function opens the file, stores each line in a dynamically-allocated
    array, reallocating memory as necessary, and returns the array */
char ** readFile(char * filename, int * count)
{
    FILE * fp;
    char ** lines, buffer[1001];
    int maxLines = 4;

    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("unable to open %s\n", filename);
        exit(1);
    }

    lines = malloc(maxLines * sizeof(char *)); 
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (*count == maxLines)
        {
            maxLines *= 2;
            lines = grow(lines, maxLines);
            printf("reached limit...increasing potential strings to %d\n", maxLines);
        }
        lines[*count] = malloc(strlen(buffer) + 1);
        strcpy(lines[*count], buffer);
        (*count)++; 
    }
    fclose(fp);
    return lines;
}

/*  this function checks if able to reallocate memory for the argument array,
    and exits the program on failure */
char ** grow(char ** array, int size)
{
    char ** temp = realloc(array, size * sizeof(char *));
    if (temp != NULL)
        return temp;
    
    printf("unable to reallocate memory.\n");
    exit(1);
}

/*  this function prints all lines of argument list, from argument start
    to argument end */
void printLines(char ** list, int start, int end)
{
    int i;
    for (i = start; i < end; i++)
        printf("%s", list[i]);
}

/*  this function implements selection sort on argument list and sorts in
    ascending order by the ascii table */
void sort(char ** list, int size)
{
    int current, minimum, i;
   
    for (current = 0; current < size - 1; current++)
    {
        minimum = current;
        for (i = current + 1; i < size; i++)
            if (strcmp(list[i], list[minimum]) < 0)
                minimum = i;

        swap(&list[current], &list[minimum]);
    }
}

/*  this function swaps the values in arguments one and two */
void swap(char ** one, char ** two)
{
    char * temp = *one;
    *one = *two;
    *two = temp;
}

/*  this function frees all memory dynamically-allocated to 
    argument array */
void freeMem(char ** array, int size)
{
    for (size--; size >= 0; size--)
        free(array[size]);
    free(array);
}

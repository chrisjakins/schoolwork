#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grow(char***, int);
char** readFile(FILE*, char**, int*, int);
void search(char**, char*, int);
int hasNeedle(char*, char*);
void destroyArray(char**, int);

int main(int argc, char* argv[])
{
    char* filename = "books.csv";
    int maxBooks = 10, bookCount = 0;
    FILE* inFile;
    char** books = malloc(maxBooks * sizeof(char*)); 

    if (argc != 2)
    {
        printf("usage: ./exe genreName\n");
        exit(1);
    }

    if ((inFile = fopen(filename, "r")) == NULL)
    {
        printf("Could not open %s\n", filename);
        exit(1);
    }
    books = readFile(inFile, books, &bookCount, maxBooks);
    fclose(inFile);

    search(books, argv[1], bookCount);
    destroyArray(books, bookCount);

    return EXIT_SUCCESS;
}

/* this function populates and returns the array with every
        line in the file excluding the first (column headers)
    it also will grow the array if necessary */
char** readFile(FILE* fp, char** array, int* count, int max)
{
    char line[1001];

    fgets(line, sizeof(line), fp);
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (*count == max)
        {
            max *= 2;
            grow(&array, max);
            printf("reallocating to %d\n", max);
        }
        array[*count] = malloc(strlen(line) + 1);
        strcpy(array[*count], line);

        (*count)++;
    }

    return array;
}

/* this function takes a pointer to a dynamically allocated
        array of strings
    it attempts to double the size of the array and on
        success: the original pointer will point to the (new) 
            address on the heap
        failure: the program will exit */
void grow(char*** arrPtr, int maxSize)
{
    char** temp = realloc(*arrPtr, maxSize * sizeof(char*));
    if (temp != NULL)
    {
        *arrPtr = temp;
    }
    else
    {
        printf("unable to reallocate.\n");
        exit(1);
    }
}

/* this function searches 'books' for 'genre'
    it tokenizes each line (starting at the last array element),
        saving the title, and printing it if the 'bookshelf' 
        column has the specified genre */
void search(char** books, char* genre, int count)
{
    char* title;
    char* token, *delim = ",";
    int i, column;

    for (i = count - 1; i >= 0; i--)
    {
        column = 2; /* starts at 2 because we read first two columns
                        before loop */
        token = strtok(books[i], delim);
        title = strtok(NULL, delim);
        while (token != NULL)
        {   /* 16 = bookshelf column */
            if (column == 16 && hasNeedle(token, genre))
                printf("%s\n", title);

            token = strtok(NULL, delim);
            column++;
        }
    }
}

/* this function returns 1 if needle is found in
        the haystack and 0 otherwise */ 
int hasNeedle(char* haystack, char* needle)
{
    char* token, *delim = "|";
    
    token = strtok(haystack, delim);
    while (token != NULL)
    {
        if (strcmp(token, needle) == 0)
            return 1;
        token = strtok(NULL, delim);
    }
    return 0;
}

/* this function takes an array and frees up every element
        then frees the array itself */
void destroyArray(char** array, int count)
{
    for (count--; count >= 0; count--)
        free(array[count]);
    free(array);
}

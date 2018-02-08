/* Chris Jakins */
/* HW4 */
/* 7/12 */
/* CSE1320 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char dateRead[16];
    char title[501];
    char bookshelf[101];
} Book;

int readFile(char* filename, Book* books);
void searchBooks(Book* books, char* answer, int size);
void bubbleSort2(Book* books, int size);
void swap(Book* one, Book* two);
char* hasRead(Book* book);

int main(void)
{
    char* filename = "books.csv";
    Book books[2000];
    int totalBooks = readFile(filename, books);
    char answer[101];
   
    bubbleSort2(books, totalBooks);

    printf("enter genre: ");
    scanf("%s", answer);
    while (strcmp(answer, "stop") != 0)
    {
        searchBooks(books, answer, totalBooks);
        printf("enter genre: ");
        scanf("%s", answer);
    }
    return EXIT_SUCCESS;
}

/* this function attempts to open the file, and, upon success, will tokenize
        every line for the title/date read/bookshelves
    the total number of books stored is returned */
int readFile(char* filename, Book* books)
{
    FILE* inFile;
    int colCount, total = 0;
    char *token, *delim = ",", line[1001];

    if ((inFile = fopen(filename, "r")) == NULL)
    {
        printf("Could not open file.\n");
        exit(1);
    }
    
    /* clear first line with columns */
    fgets(line, sizeof(line), inFile);
    while (fgets(line, sizeof(line), inFile) != NULL)
    {
        colCount = 1;
        token = strtok(line, delim);
        while (token != NULL)
        {
            if (colCount == 2)          /* title column */
                strcpy(books[total].title, token);
            else if (colCount == 14)    /* date read column */
                strcpy(books[total].dateRead, token);
            else if (colCount == 16)    /* bookshelves column */
                strcpy(books[total].bookshelf, token);
            token = strtok(NULL, delim);
            colCount++;
        }
        total++;
    }
    fclose(inFile);
    return total;
}

void bubbleSort2(Book* books, int size)
{
    int sorted, i;
    Book temp;

    do 
    {
        sorted = 1;
        for (i = 0; i < size - 1; i++)
        {
            /* swap if:
                    title1 > title2 alphabetically OR
                    (title1 == title2 AND date1 > date2) */
            if (strcmp(books[i].title, books[i + 1].title) > 0  ||
               (strcmp(books[i].title, books[i + 1].title) == 0 && 
                strcmp(books[i].dateRead, books[i + 1].dateRead) > 0))
            {
                swap(&books[i], &books[i + 1]);
                sorted = 0;
            }
        } 
    } while(!sorted);
}

void swap(Book* one, Book* two)
{
    Book temp = *one;
    *one = *two;
    *two = temp;
}

/* linear search */
void searchBooks(Book* books, char* term, int size)
{
    char* token, *delim = "|";
    char shelf[101];
    int i;
    
    for (i = 0; i < size; i++)
    {
        strcpy(shelf, books[i].bookshelf);
        token = strtok(shelf, delim);
        while (token != NULL)
        {
            if (strcmp(token, term) == 0)
                printf("%s, %s\n", books[i].title, hasRead(&books[i]));
            token = strtok(NULL, delim);
        }
    }
}

char* hasRead(Book* book)
{
    if (strcmp(book->dateRead, "empty") == 0)
        return "unread";
    return book->dateRead;
}

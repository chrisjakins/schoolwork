/*
  this file should include things like
    structure definitions
    #define statements
    function declarations
*/

typedef struct Person {
    struct Person * left;
    struct Person * right;
    char name[21];
} Node;

char ** grow(char **, int);
void freeArray(char **, int);
char ** sortArray(char **, int);

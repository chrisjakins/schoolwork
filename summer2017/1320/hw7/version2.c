#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct LinkedNode
{
    char * name;
    double totalCost;
    struct LinkedNode * next;
    struct LinkedNode * prev;
} Node;

/* think about params with these */
Node * addNode(Node *);
Node * updateNode(Node *);
Node * constructList(Node *);
void printList(Node *);
void destroyList();
int search(Node *);

/* optional */
void tokenize(); /* tokenize string and populate node? */

int main(void)
{
    Node * head;
    char buffer[51], * name;
    int cost;

    constructList(head);

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        tokenize(buffer, &name, &cost);
        printf("%s, %d\n", name, cost);
    }

    free(head);
}

Node * constructList(Node * head)
{
    head = malloc(sizeof(Node));
    head->next = NULL;
    head->prev = NULL;
    return head;
}

void tokenize(char * line, char ** name, int * cost)
{
    char * token, * delim = " $.";

    *name = strtok(line, delim);
    token = strtok(NULL, delim);
    while (token != NULL)
    {   /* consider returning after getting cost */
        if (token[0] >= '1' && token[0] <= '9')
        {
            *cost = atoi(token);    
            printf("In function: %s %d\n", *name, *cost);
        }
        token = strtok(NULL, delim);
    }
}

/*
construct list
loop through all lines
        tokenize line
        if name is found in list, update node
        otherwise, add node in correct position
print list
destroy list
*/

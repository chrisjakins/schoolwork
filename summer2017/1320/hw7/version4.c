#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct LinkedNode
{
    char * name;
    int totalCost;
    struct LinkedNode * next;
    struct LinkedNode * prev;
} Node;

/* think about params with these */
Node * addNode(Node *, char *, int);
Node * updateNode(Node *);
Node * constructList(Node *, char *, int);
void printList(Node *);
void tokenize(char *, char **, int *);
void destroyList();
int search(Node *);

int main(void)
{
    Node * head = NULL;
    char buffer[101], * name;
    int cost;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        tokenize(buffer, &name, &cost);
        if (head != NULL)
        {
            /* printf("%s, %d\n", name, cost); */
            head = addNode(head, name, cost);
        }
        else 
            head = constructList(head, name, cost);

        printList(head);
        printf("\n\n");
    }

    printList(head);

    destroyList(head);
}

void tokenize(char * line, char ** name, int * cost)
{
    char * token, * delim = " $.";

    *name = strtok(line, delim);
    token = strtok(NULL, delim);
    while (token != NULL)
    {
        if (token[0] >= '1' && token[0] <= '9')
            *cost = atoi(token);
        token = strtok(NULL, delim);
    }
}

Node * constructList(Node * head, char * name, int cost)
{
    head = malloc(sizeof(Node));
    head->name = malloc(strlen(name) + 1);
    /* head->name = name; */
    strcpy(head->name, name);
    head->totalCost = cost;
    head->prev = NULL;
    head->next = NULL;
    return head;
}

/* strcmp
    insert if next one is greater than o/w
    add to end
    */
Node * addNode(Node * head, char * name, int cost)
{
    Node * temp, * new = malloc(sizeof(Node));
    /* printf("malloc ok"); */
    new->name = malloc(strlen(name) + 1);
    strcpy(new->name, name);
    /* new->name = name; */
    new->totalCost = cost;

    if (strcmp(new->name, head->name) < 0)
    {
        /* printf("in here"); */
        new->next = head;
        new->prev = NULL;
        head->prev = new;
        head = new;
        return head;
    }
    /* printf("out here"); */

    /* temp != NULL breaks adding nodes to the end 
        figure out a new way 
        maybe add a second traversing pointer??? */
    for (temp = head; temp != NULL; temp = temp->next) 
    {
        if (strcmp(new->name, temp->name) < 0)
        {
            new->next = temp;
            new->prev = temp->prev;
            temp->prev->next = new;
            temp->prev = new;
            return head;
        }
        else if (strcmp(new->name, temp->name) == 0)
        {
            temp->totalCost += cost;
            free(new->name);
            free(new);
            return head;
        }
    }

    /* if we get here, we know node belongs at end of list */
    new->prev = temp;
    new->next = NULL;
    temp->next = new;
    return head; 
}

void destroyList(Node * head)
{
    Node * temp;
    for (temp = head; temp != NULL; temp = head)
    {
        head = temp->next;
        free(temp->name);
        free(temp);
    }
}

void printList(Node * head)
{
    Node * temp;

    for (temp = head; temp != NULL; temp = temp->next)
        printf("%s, %d\n", temp->name, temp->totalCost);
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

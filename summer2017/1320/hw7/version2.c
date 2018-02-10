#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct LinkedNode
{
    char * name;
    int cost;
    struct LinkedNode * next;
    struct LinkedNode * prev;
} Node;

Node * constructList(Node *, char *, int);
Node * addNode(Node *, char *, int);
void printList(Node *);
void tokenize();
void destroyList(Node *);
void freeNode(Node *);

int main(void)
{
    Node * head = NULL;
    char buffer[51], * name;
    int cost;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        tokenize(buffer, &name, &cost);
        head = addNode(head, name, cost);
    }
    
    printList(head);
    destroyList(head);

    return EXIT_SUCCESS;
}

Node * addNode(Node * head, char * name, int cost)
{
    Node * temp, * prev, * new;
    
    if (head == NULL)   /* if list does not yet exit */
        return constructList(head, name, cost);
   
    /* If a list DOES exist, set up the new node */
    new = malloc(sizeof(Node));
    new->name = malloc(strlen(name) + 1); 
    strcpy(new->name, name);
    new->cost = cost;

    for (temp = head, prev = head; temp != NULL; prev = temp, temp = temp->next)
    {
        if (strcmp(new->name, temp->name) < 0)  /* if new node goes BEFORE node */
        {                                       /* currently pointed to by temp */
            if (temp == head)   
            {   /* new node becomes head */
                new->next = head;
                head->prev = new;
                head = new;
                return head;
            }
            else  
            {   /* inserting in middle of list */
                new->next = temp;
                new->prev = prev;
                prev->next = new;
                temp->prev = new;
                return head;
            }
        }
        else if (strcmp(new->name, temp->name) == 0) /* updating node */
        {
            freeNode(new);
            temp->cost += cost;
            return head;
        }
    }
    /*end of list */
    new->prev = prev;
    prev->next = new;
    new->next = NULL;
    return head;
}

Node * allocNode(char * name, int cost)
{
    Node * node = malloc(sizeof(Node));
    node->name = malloc(strlen(name) + 1);
    strcpy(node->name, name);
    node->cost = cost;
}

Node * constructList(Node * head, char * name, int cost)
{
    head = malloc(sizeof(Node));
    head->name = malloc(strlen(name) + 1);
    head->next = NULL;
    head->prev = NULL;
    strcpy(head->name, name);
    head->cost = cost;
    return head;
}

void tokenize(char * line, char ** name, int * cost)
{
    char * token, * delim = " $.";

    *name = strtok(line, delim);
    token = strtok(NULL, delim);
    while (token != NULL)
    {   
        if (token[0] >= '1' && token[0] <= '9')
        {
            *cost = atoi(token);    
            return;
        }
        token = strtok(NULL, delim);
    }
}

void printList(Node * head)
{
    Node * temp;
    for (temp = head; temp != NULL; temp = temp->next)
        printf("%s, %d\n", temp->name, temp->cost);
}

void destroyList(Node * head)
{
    Node * temp, * next;
    for (temp = head; temp != NULL; temp = next)
    {
        next = temp->next;
        freeNode(temp);
    }
}

void freeNode(Node * node)
{
    free(node->name);
    free(node);    
}

/* Chris Jakins */
/* HW7 */
/* CSE1320 */
/* 7/26 */
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

Node * allocNode(Node *, char *, int, Node *, Node *);
Node * updateList(Node *, char *, int);
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
        head = updateList(head, name, cost);
    }
    
    printList(head);
    destroyList(head);
    return EXIT_SUCCESS;
}

/*  this function inserts a new node into the proper location
    of the linked list pointed to by argument head:
    if head is null (list does not yet exit)
        initialize the list with arguments name and cost
    otherwise loop through the linked list
        if argument name goes before the node currently on
            if that is the first/head node 
                create new node at head of list
            else (argument goes somewhere in middle of list)
                insert new node and make proper connections
        else if argument name is EQUAL to current node name
            update node
    end loop
    if control flow reaches here, argument name goes at end of list
        so we add new node to tail */
Node * updateList(Node * head, char * name, int cost)
{
    Node * temp, * prev, * new;
    
    if (head == NULL)   /* if list does not yet exit */
        return allocNode(head, name, cost, NULL, NULL);

    for (temp = head, prev = head; temp != NULL; prev = temp, temp = temp->next)
    {
        if (strcmp(name, temp->name) < 0)  /* if new node goes BEFORE node */
        {                                  /* currently pointed to by temp */
            if (temp == head)   
            {   /* new node becomes head */
                new = allocNode(new, name, cost, NULL, head);
                head->prev = new;
                head = new;
                return head;
            }
            else  
            {   /* inserting in middle of list */
                new = allocNode(new, name, cost, prev, temp);
                prev->next = new;
                temp->prev = new;
                return head;
            }
        }
        else if (strcmp(name, temp->name) == 0) /* updating node */
        {
            temp->cost += cost;
            return head;
        }
    }
    /*end of list */
    new = allocNode(new, name, cost, prev, NULL);
    prev->next = new;
    return head;
}

/*  this function handles creation of new nodes */
Node * allocNode(Node * node, char * name, int cost, Node * prev, Node * next)
{
    node = malloc(sizeof(Node));
    node->name = malloc(strlen(name) + 1);
    strcpy(node->name, name);
    node->cost = cost;
    node->next = next;
    node->prev = prev;
    return node;
}

/*  this function tokenizes the line for the
        name (first token of line)
        cost (immediately preceded by $) */
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

/*  prints linked list pointed to by argument head */
void printList(Node * head)
{
    Node * temp;
    for (temp = head; temp != NULL; temp = temp->next)
        printf("%s, %d\n", temp->name, temp->cost);
}

/*  frees all memory associated with linked list */
void destroyList(Node * head)
{
    Node * temp, * next;
    for (temp = head; temp != NULL; temp = next)
    {
        next = temp->next;
        freeNode(temp);
    }
}

/*  frees the memory of a node */
void freeNode(Node * node)
{
    free(node->name);
    free(node);    
}

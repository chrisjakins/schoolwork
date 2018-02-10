/* Chris Jakins */
/* CSE 1320 */
/* HW 10 */ 
/* 8/9 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glob.h>

#define NUM_DATES 14
const int DATES[NUM_DATES] = {601, 608, 615, 622, 629, 706, 713,
                               720, 727, 803, 810, 817, 824, 1231};

const char * DATES_STRING[NUM_DATES] = {"06/01", "06/08", "06/15", "06/22", "06/29",
                                        "07/06", "07/13", "07/20", "07/27", "08/03",
                                        "08/10", "08/17", "08/24", "12/31"};

typedef struct LinkedNode
{
    struct LinkedNode * next;
    char * courseName;
    int enrollByDate[14];
    char year[5];
} Node;

Node * readFiles(char **);
void tokenizeFilename(char *, char **, char **, char **);
Node * isInList(Node*, char *, char *);
int compareNodes(char *, char *, char *, char *);
Node * addNode(Node **, char *, char *);
Node * allocNode(char *, char *);
void updateNode(FILE *, Node *);

void printList(Node *);
void freeList(Node *);

int main()
{
    glob_t paths;
    Node * head;

    if (glob("*.csv", 0, NULL, &paths) == 0)
    {
        head = readFiles(paths.gl_pathv); 
        globfree(&paths);
        printList(head);
        freeList(head);
    }

    return EXIT_SUCCESS;
}

Node * readFiles(char ** files)
{
    Node * head = NULL, * temp;
    FILE * fp;
    char ** filename, * year, * course, * section;
    int date;
   
    for (filename = files; *filename != NULL; filename++)
    {
        if ((fp = fopen(*filename, "r")) == NULL)
        {
            printf("unable to open %s\n", *filename);
            exit(1);
        } /* don't need filename anymore */
        tokenizeFilename(*filename, &year, &course, &section);
        
        if ((temp = isInList(head, year, course)) == NULL)
            temp = addNode(&head, course, year);

        updateNode(fp, temp);
        fclose(fp);
    }
    /* fix arrays to accumulate based off previous numbers */
    for (temp = head; temp != NULL; temp = temp->next)
        for (date = 1; date < NUM_DATES; date++)
            temp->enrollByDate[date] += temp->enrollByDate[date - 1];

    return head;
}

void tokenizeFilename(char * filename, char ** year, char ** course, char ** section)
{
    char * del1 = "-", * del2 = ".";

    *year = strtok(filename, del1);
    *course = strtok(NULL, del2);
    *section = strtok(NULL, del2);
}

Node * isInList(Node * head, char * year, char * course)
{
    for (/*no init*/; head != NULL; head = head->next)
        if (strcmp(head->courseName, course) == 0 && strcmp(head->year, year) == 0)
            return head;
    return NULL;
}

Node * allocNode(char * course, char * year)
{
    int i;
    Node * new = malloc(sizeof(Node));
    new->courseName = malloc(strlen(course) + 1);

    strcpy(new->courseName, course);
    strcpy(new->year, year);
    for (i = 0; i < NUM_DATES; i++)
        new->enrollByDate[i] = 0;

    new->next = NULL;
    return new;
}

/* helper function */
int compareNodes(char * course1, char * course2, char * year1, char * year2)
{
    if (strcmp(course1, course2) > 0 ||
       (strcmp(course1, course2) == 0 &&
        strcmp(year1, year2) > 0))
       return 1;
    return 0;
}

Node * addNode(Node ** head, char * course, char * year)
{
    Node * trav, * prev, * node;

    /* list is empty */
    if (*head == NULL)
    {
        *head = allocNode(course, year);
        return *head;
    }

    /* beginning of list */
    if (compareNodes((*head)->courseName, course, (*head)->year, year))
    {
        node = allocNode(course, year);
        node->next = *head;
        return node;
    }

    /* middle of list */
    for (trav = *head, prev = *head; trav != NULL; prev = trav, trav = trav->next)
    {
        if (compareNodes(trav->courseName, course, trav->year, year))
        {
            node = allocNode(course, year); 
            node->next = prev->next;
            prev->next = node;
            return node;
        } 
    }

    prev->next = allocNode(course, year);
    prev->next->next = NULL; 
    return prev->next;
}

void updateNode(FILE * fp, Node * node)
{
    char buffer[301];
    char * token, * dateTok;
    char * del = ",", * delDate = "/";
    int i, date, found, day;

    /* clear first line of column headings */
    fgets(buffer, sizeof(buffer), fp);
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        token = strtok(buffer, ",");
        while (token != NULL)
        {
            dateTok = token;
            token = strtok(NULL, ",");
        }
        
        /* converts string date into MMDD integer format */ 
        day = atoi(strtok(dateTok, delDate)) * 100;
        day += atoi(strtok(NULL, delDate)); 
        for (date = 0, found = 0; !found && date < NUM_DATES; date++)
        {
            if (day <= DATES[date])
            {
                found = 1;
                node->enrollByDate[date] += 1;
            }
        }
    }
}

void printList(Node * head)
{
    int i;

    printf("course,year");
    for (i = 0; i < NUM_DATES; i++)
        printf(",%s", DATES_STRING[i]);
    printf("\n");
    for (/*no init*/; head != NULL; head = head->next)
    {
        for (i = 0; i < strlen(head->courseName); i++)
            if (head->courseName[i] >= '0' && head->courseName[i] <= '9')
                printf("%c", head->courseName[i]);
        printf(",%s", head->year);
        for (i = 0; i < NUM_DATES; i++)
            printf(",%d", head->enrollByDate[i]);
        printf("\n");
    }
}

void freeList(Node * head)
{
    Node * temp;
    for (temp = head; temp != NULL; temp = head)
    {
        free(temp->courseName);
        head = temp->next; 
        free(temp);
    }
}

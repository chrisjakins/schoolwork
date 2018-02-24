/* 
    Chris Jakins
    1000802309
    CSE3320 
    Shell Assignment
    2/26
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#define WHITESPACE " \t\n"
#define MAX_COMMAND_SIZE 255
#define MAX_NUM_ARGUMENTS 11

char * stringBuiltin[] = {"cd", "history", "showpids"};

#define PATH_NUM 4
char paths[PATH_NUM][MAX_COMMAND_SIZE] = {"/bin/", "/usr/bin/", "/usr/local/bin/", "./"};

/******
        DATA STRUCTURES
******/

#define HISTORY_NUM 15
#define SHOWPIDS_NUM 10

typedef struct HistoryNode {
    struct HistoryNode * next;
    char * command;
} HistoryNode;

typedef struct PidNode {
    struct PidNode * next;
    pid_t pid;
} PidNode;

/**** Initialize data structures ****/
HistoryNode * historyHead = NULL;
PidNode * pidHead = NULL;

/******
        FUNCTIONS
******/

/* data structure maintainence functions */
void addHistoryNode(char *);
void cleanHistoryList();

void addPidNode(pid_t);
void cleanPidList();

/* high-level shell operations */
int readInput(char **);
int parseInput(char *, char **);
int execute(char **);

/* signal handling functions */
void handleSIGTSTP(int sig);

/* built-in functions */
int cd(char **);
int history(char **);
int showpids(char **);
int repeatCommand(char **);

/*******
        MAIN
*******/

int main() {
    char ** token = malloc(MAX_NUM_ARGUMENTS);
    int status;

    /* init handler for ctrl-z */
    struct sigaction tstop;
    memset(&tstop, '\0', sizeof(tstop));
    tstop.sa_handler = &handleSIGTSTP;
    sigaction(SIGTSTP, &tstop, NULL);

    do {
        printf("msh> ");
        memset(token, '\0', MAX_NUM_ARGUMENTS * sizeof(token));
        readInput(token);
        status = execute(token);

    } while (status);

    free(token);
    cleanHistoryList();
    cleanPidList();
    return 0;
}

/******
        HIGH-LEVEL SHELL OPERATIONS
******/

/*
    token -> array of strings ending in (null) are stored here after function returns
    number of tokens is returned

    this code taken from Trevor Bakker :
    https://github.com/CSE3320/Shell-Assignment/blob/master/mfs.c
*/
int readInput(char ** token) {
    char * cmdStr = malloc(MAX_COMMAND_SIZE);

    while (!fgets(cmdStr, MAX_COMMAND_SIZE, stdin)) ;

    addHistoryNode(cmdStr);
/*
    int tokenCount = 0;
    char * argPtr;
    char * workingStr = strdup(cmdStr);


    while (((argPtr = strsep(&workingStr, WHITESPACE)) != NULL) &&
              (tokenCount < MAX_NUM_ARGUMENTS)) {

        token[tokenCount] = strndup(argPtr, MAX_COMMAND_SIZE);

        if (strlen(token[tokenCount]) == 0) {
            token[tokenCount] = NULL;
        }
        tokenCount++;
    }

    free(cmdStr);
    free(workingStr);
    return tokenCount; */

    return parseInput(cmdStr, token);
}

int parseInput(char * input, char ** token) {
    int tokenCount = 0;
    char * workingStr = strdup(input);
    char * argPtr;

    while (((argPtr = strsep(&workingStr, WHITESPACE)) != NULL) &&
              (tokenCount < MAX_NUM_ARGUMENTS)) {

        token[tokenCount] = strndup(argPtr, MAX_COMMAND_SIZE);

        if (strlen(token[tokenCount]) == 0) {
            token[tokenCount] = NULL;
        }
        tokenCount++;
    }

    free(input);
    free(workingStr);
    return tokenCount;
}

int execute(char ** params) {
    int status, execErr = 0;

    /* if the user entered exit or quit, return 0 to end main */
    if (params[0] != NULL && 
       (strcmp(params[0], "exit") == 0 || strcmp(params[0], "quit") == 0)) {

        return 0;

    } else if (strcmp(params[0], stringBuiltin[0]) == 0) {

        execErr = cd(params);

    } else if (strcmp(params[0], stringBuiltin[1]) == 0) {

        execErr = history(params);

    } else if (strcmp(params[0], stringBuiltin[2]) == 0) {

        execErr = showpids(params);

    } else if (params[0][0] == '!') {

        execErr = repeatCommand(params);

    } else {

        pid_t pid = fork();

        if (pid != 0) {

            addPidNode(pid);
            waitpid(pid, &status, 0);

        } else {
            /* child process */
            char * command;
            for (int i = 0; i < 4; i++) {
                command = strcat(paths[i], params[0]);
                execErr = execv(command, params);
            }
        }
        if (execErr) {
            printf("%s: Command not found.\n", params[0]);
            exit(1);
        } 
    }
    return 1;
}

int run() {
    return 1;
}

/******
        SIGNAL HANDLING FUNCTIONS
******/

void handleSIGTSTP(int sig) {
    printf("Hello %d\n", sig);
    fflush(stdin);
}

/******
        BUILT-IN FUNCTIONS
******/

void addHistoryNode(char * cmd) {
    if (cmd[0] == '!') return;

    HistoryNode * newNode = malloc(sizeof(HistoryNode));
    newNode->next = NULL;
    newNode->command = strdup(cmd);
    
    HistoryNode * temp = historyHead;
    if (!temp) {
        historyHead = newNode;
        return;
    }
    
    int count = 1;
    while (temp->next && count < HISTORY_NUM) {
        temp = temp->next;
        count++;
    }

    temp->next = newNode;
    
    if (count == HISTORY_NUM) {
        temp = historyHead->next;

        free(historyHead->command);
        free(historyHead);
        
        historyHead = temp;
    }
}

void cleanHistoryList() {
    HistoryNode * temp = historyHead;

    while (temp) {
        temp = temp->next;

        free(historyHead->command);
        free(historyHead);

        historyHead = temp;
    }
}

void addPidNode(pid_t pid) {
    PidNode * newNode = malloc(sizeof(PidNode));
    newNode->pid = pid;
    newNode->next = NULL;

    PidNode * temp = pidHead;
    if (!temp) {
        pidHead = newNode;
        return;
    }

    int count = 1;
    while (temp->next && count < SHOWPIDS_NUM) {
        temp = temp->next;
        count++;
    }

    temp->next = newNode;

    if (count == SHOWPIDS_NUM) {
        temp = pidHead->next;

        free(pidHead);

        pidHead = temp;
    }
}

void cleanPidList() {
    PidNode * temp = pidHead;

    while (temp) {
        temp = temp->next;

        free(pidHead);

        pidHead = temp;
    }
}

/******
        BUILT-IN FUNCTIONS
******/

int cd(char ** params) {
    char cwd[1024];

    if (strcmp(params[1], "..") == 0) {

        /* command was "cd .." */
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            char * temp = strrchr(cwd, '/');
            *temp = '\0';
            chdir(cwd);
        }

    } else {
        
        /* command was "cd <path>" */
        if (chdir(params[1]) == -1) {
            printf("msh: cd: %s: No such file or directory\n", params[1]);
        }
    }

    return 1;
}

int history(char ** params) {
    HistoryNode * temp = historyHead;

    int i = 1;
    for ( ; temp; temp = temp->next, i++) {
        printf("%d: %s", i, temp->command);
    }
    return 1;
}

int showpids(char ** params) {
    PidNode * temp = pidHead;

    int i = 1;
    for ( ; temp; temp = temp->next, i++) {
        printf("%d: %d\n", i, temp->pid);
    }

    return 1;
}

int repeatCommand(char ** params) {
    int cmdNum = atoi(params[0]);

    HistoryNode * temp = historyHead;
    int count = 1;
    while (temp && count < cmdNum) {
        temp = temp->next;
    }

    if (!temp) {
        printf("msh: !%d: event not found", cmdNum);
    }

    addHistoryNode(temp->command);


    return 1;
}

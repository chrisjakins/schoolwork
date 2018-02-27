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

char * stringBuiltin[] = {"cd", "history", "showpids", "bg"};

#define PATH_NUM 4
char paths[PATH_NUM][MAX_COMMAND_SIZE] = {"/bin/", "/usr/bin/", "/usr/local/bin/", "./"};

pid_t currentProcess;
pid_t suspendedProcess;

/******
        DATA STRUCTURES
******/

#define HISTORY_NUM 15
#define SHOWPIDS_NUM 10

typedef struct HistoryNode {
    struct HistoryNode * next;
    char ** commandTokens;
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
void addHistoryNode(char *, char **);
void cleanHistoryList();

void addPidNode(pid_t);
void cleanPidList();

/* high-level shell operations */
int readInput(char **);
int parseInput(char *, char **);
int execute(char **);

/* signal handling functions */
void initHandlers();
void handleSignal(int sig, siginfo_t *, void * context);

/* built-in functions */
int cd(char **);
int history(char **);
int showpids(char **);
int repeatCommand(char **);
int bg(char **);

/*******
        MAIN
*******/

int main() {
    char ** token = malloc(sizeof(char *) * MAX_NUM_ARGUMENTS);
    int status, i;

    initHandlers();

    do {
        memset(token, '\0', sizeof(token) * MAX_NUM_ARGUMENTS);

        printf("msh> ");
        readInput(token);
        status = execute(token);

    } while (status);

    for (i = 0; i < MAX_NUM_ARGUMENTS && token[i]; i++) {
        free(token[i]);
    }
    free(token);
    cleanHistoryList();
    cleanPidList();
    return 0;
}

/******
        HIGH-LEVEL SHELL OPERATIONS
******/

/*
    input -> will not be modified throughout lifetime of this code

    token -> array of strings ending in (null) are stored here after function returns
    number of tokens is returned

    this code taken from Trevor Bakker :
    https://github.com/CSE3320/Shell-Assignment/blob/master/mfs.c
*/
int readInput(char ** token) {
    char * cmdStr = malloc(MAX_COMMAND_SIZE);

    while (!fgets(cmdStr, MAX_COMMAND_SIZE, stdin)) ;

    if (strcmp(cmdStr, "\n") == 0) {
        return 0;
    }

    int tokenCount = parseInput(cmdStr, token);
    addHistoryNode(cmdStr, token);

    free(cmdStr);
    return tokenCount;
}

/*
    input -> will not be modified throughout lifetime of this code

    token -> array of strings ending in (null) are stored here after function returns
    number of tokens is returned

    this code taken from Trevor Bakker :
    https://github.com/CSE3320/Shell-Assignment/blob/master/mfs.c
*/
int parseInput(char * input, char ** token) {
    int tokenCount = 0;
    char * workingStr = strdup(input);
    char * workingRoot = workingStr;
    char * argPtr;

    while ((argPtr = strsep(&workingStr, WHITESPACE)) != NULL &&
            tokenCount < MAX_NUM_ARGUMENTS) {

        if (*argPtr && strlen(argPtr)) {
            token[tokenCount] = strdup(argPtr);
            tokenCount++;
        }
    }

    free(workingRoot);
    return tokenCount;
}

/*
    params -> array of strings with each parameter taken from the command line

    this function will run the appropriate builtin, if that is what was typed
    or will spawn a child process with fork and use exec() to run the correct
    program
*/
int execute(char ** params) {
    int status, execErr = 0;

    /* if the user entered exit or quit, return 0 to end main */
    if (params[0]) {
        if (strcmp(params[0], "exit") == 0 || strcmp(params[0], "quit") == 0) {

            return 0;

        } else if (strcmp(params[0], stringBuiltin[0]) == 0) {

            execErr = cd(params);

        } else if (strcmp(params[0], stringBuiltin[1]) == 0) {

            execErr = history(params);

        } else if (strcmp(params[0], stringBuiltin[2]) == 0) {

            execErr = showpids(params);

        } else if (strcmp(params[0], stringBuiltin[3]) == 0) {

            execErr = bg(params);

        } else if (params[0][0] == '!') {

            execErr = repeatCommand(params);

        } else {

            pid_t pid = fork();

            if (pid != 0) {
                currentProcess = pid;
                addPidNode(pid);
                waitpid(pid, &status, 0);

            } else {
                /* child process */
                char * command;
                int i;
                for (i = 0; i < 4; i++) {
                    command = strcat(paths[i], params[0]);
                    execErr = execv(command, params);
                }
            }
            if (execErr) {
                printf("%s: Command not found.\n", params[0]);
                /* child exits */
                exit(1);
            } 
        }
    }
    return 1;
}

/******
        SIGNAL HANDLING FUNCTIONS
******/

/*
    this function initializes the signal handlers for the signals needed
    to be caught by this shell, uses 'void handleSignal()' as the signal
    handler

    To add more : 
    sigaction(NEWSIGNAL, &act, NULL);
*/
void initHandlers() {
    struct sigaction act;
    memset(&act, '\0', sizeof(act));
    act.sa_sigaction = &handleSignal;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGTSTP, &act, NULL);
    sigaction(SIGINT, &act, NULL);
}

/*
    sig -> integer representing the signal sent
        run kill -l from the command line to see a list of all signals available

    processInfo -> info from the process that sent the signal, might be useful
        when implementing bg

    this function catches SIGINT and SIGSTP and currently does nothing with them

    To add more :
    case SIGNALTYPE:
        process();
        break;
*/
void handleSignal(int sig, siginfo_t * processInfo, void * context) {
    switch (sig) {
        case SIGINT:
            // do nothing in parent, kills childs spawned by exec()
            kill(currentProcess, SIGINT);
            break;
        case SIGTSTP:
            //printf("Suspend process");
            suspendedProcess = currentProcess;
            kill(currentProcess, SIGTSTP);
            break;
        default:
            printf("Other signal caught...");
    }
}

/******
        DATA STRUCTURE MAINTAINENCE
******/

/*
    cmd -> a full string representing the command that was typed

    cmdArray -> a tokenized array of the strings from 'cmd'

    This function stores the above parameters into a linked list of nodes
    This linked list is used by the history command to know what commands have
    been run in the past. This function also takes care of maintaining the size
    of the linked list (only HISTORY_NUM allowable nodes at any given time)
*/
void addHistoryNode(char * cmd, char ** cmdArray) {
    if (cmd[0] == '!') return;

    HistoryNode * newNode = malloc(sizeof(HistoryNode));
    newNode->next = NULL;
    newNode->command = strdup(cmd);
    newNode->commandTokens = malloc(sizeof(char *) * MAX_NUM_ARGUMENTS);
    /* memset(newNode->commandTokens, '\0', MAX_NUM_ARGUMENTS); */

    int i;
    for (i = 0; i < MAX_NUM_ARGUMENTS && cmdArray[i]; i++) {
        newNode->commandTokens[i] = strdup(cmdArray[i]);
    }

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
        for (i = 0; i < MAX_NUM_ARGUMENTS && historyHead->commandTokens[i]; i++) {
            free(historyHead->commandTokens[i]);
        }
        free(historyHead);
        
        historyHead = temp;
    }
}

/* 
    This function frees up (very sloppily) all the memory allocated to the
    history linked list
*/
void cleanHistoryList() {
    HistoryNode * temp = historyHead;
    //int i;

    while (temp) {
        temp = temp->next;

        free(historyHead->command);
        /*
        for (i = 0; i < MAX_NUM_ARGUMENTS && historyHead->commandTokens[i] != NULL; i++) {
            free(historyHead->commandTokens[i]);
        }

        free(historyHead->commandTokens); */
        free(historyHead);

        historyHead = temp;
    }
}

/*
    pid -> a process ID to store into the linked list

    This function maintains the linked list of pids used by the showpids
    command. No more than SHOWPIDS_NUM can be present at any time.
*/
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

/*
    This function frees up all memory associated with the PID linked list 
*/
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

/*
    params -> the command run from the command line in tokenized form

    This function changes the current working directory to the specified path
    I later realized that I did not need a separate case for '..', but I was
    proud of that code, so I left it in
*/
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

/*
    params -> not used here, but kept for consistency

    this function outputs all entries in the history linked list
*/
int history(char ** params) {
    HistoryNode * temp = historyHead;

    int i = 1;
    for ( ; temp; temp = temp->next, i++) {
        printf("%d: %s", i, temp->command);
    }
    return 1;
}

/*
    params -> not used here, but kept for consistency

    this function outputs all entries in the PID linked list
*/
int showpids(char ** params) {
    PidNode * temp = pidHead;

    int i = 1;
    for ( ; temp; temp = temp->next, i++) {
        printf("%d: %d\n", i, temp->pid);
    }

    return 1;
}

/*
    params -> the tokenized list of commands/argument entered from the command line
    
    This function takes the integer from the command and reruns the corresponding
    command from the history linked list
*/
int repeatCommand(char ** params) {
    int cmdNum = atoi(params[0] + 1);

    HistoryNode * temp = historyHead;
    int count = 1;
    while (temp && count < cmdNum) {
        temp = temp->next;
        count++;
    }

    if (!temp) {
        printf("msh: !%d: event not found", cmdNum);
    }

    addHistoryNode(temp->command, temp->commandTokens);
    execute(temp->commandTokens);

    return 1;
}

/*
    params -> not used here

    This function is supposed to resume the currently suspended process
*/
int bg(char ** params) {
    // resume suspended process here
    kill(suspendedProcess, SIGCONT);
    return 1;
}

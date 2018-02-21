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

#define HISTORY_NUM 15
#define SHOWPIDS_NUM 10
char * stringBuiltin[] = {"cd", "history", "showpids"};

#define PATH_NUM 4
char paths[PATH_NUM][MAX_COMMAND_SIZE] = {"/bin/", "/usr/bin/", "/usr/local/bin/", "./"};

/* high-level shell operations */
int readInput(char **);
int execute(char **);

/* signal handling functions */
void handleSIGTSTP(int sig);

/* built-in functions */
int cd(char **);
int history();
int showpids();

/*******
        MAIN
*******/
int main() {
    char ** token = malloc( MAX_NUM_ARGUMENTS );
    int status, tokenCount;
    int execErr = 0;

    /* init handler for ctrl-z */
    struct sigaction tstop;
    memset(&tstop, '\0', sizeof(tstop));
    tstop.sa_handler = &handleSIGTSTP;
    sigaction(SIGTSTP, &tstop, NULL);

    do {
        printf("msh> ");
        memset(token, '\0', sizeof(token));
        tokenCount = readInput(token);
        status = execute(token);

    } while (status);

    printf("That was fun! Exiting...\n");
    free(token);
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

    int tokenCount = 0;
    char * argPtr;
    char * workingStr = strdup(cmdStr);
    char * workingRoot = workingStr;

    while (((argPtr = strsep(&workingStr, WHITESPACE)) != NULL) &&
              (tokenCount < MAX_NUM_ARGUMENTS)) {

        token[tokenCount] = strndup(argPtr, MAX_COMMAND_SIZE);

        if (strlen(token[tokenCount]) == 0) {
            token[tokenCount] = NULL;
        }
        tokenCount++;
    }

    free(cmdStr);
    free(workingRoot);
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

        execErr = history();

    } else if (strcmp(params[0], stringBuiltin[2]) == 0) {

        execErr = showpids();

    } else {

        pid_t pid = fork();

        if (pid != 0) {
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

}

/******
        SIGNAL HANDLING FUNCTIONS
******/

void handleSIGTSTP(int sig) {
    printf("Hello %d\n", sig);
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
    printf("in history\n");

    return 1;
}

int showpids(char ** params) {
    printf("in showpids\n");

    return 1;
}

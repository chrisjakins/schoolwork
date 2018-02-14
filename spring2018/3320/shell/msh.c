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

int promptAndReadIn(char **);
void handleSIGTSTP(int sig);

int main()
{
    char ** token = malloc( MAX_NUM_ARGUMENTS );
    int status;
    int execErr = 0;

    /* init handler for ctrl-z */
    struct sigaction tstop;
    memset(&tstop, '\0', sizeof(tstop));
    tstop.sa_handler = &handleSIGTSTP;
    sigaction(SIGTSTP, &tstop, NULL);

    while ( 1 )
    {
        int tokenCount = promptAndReadIn(token);

        if (token[0] != NULL && 
           (strcmp( token[0], "exit" ) == 0 || strcmp( token[0], "quit" ) == 0))
        {
            return 0;
        }

        pid_t pid = fork();

        if (pid != 0)
        {
            waitpid(pid, &status, 0);
        }
        else
        {
            /* store in array */
            char path1[MAX_COMMAND_SIZE] = "/bin/";
            char path2[MAX_COMMAND_SIZE] = "/usr/bin/";
            char path3[MAX_COMMAND_SIZE] = "/usr/local/bin/";
            char path4[MAX_COMMAND_SIZE] = "./";


            /* look at execv */
            char * command = strcat(path1, token[0]);
            execErr = execve(command, token, 0);

            command = strcat(path2, token[0]);
            execErr = execve(command, token, 0);

            command = strcat(path3, token[0]);
            execErr = execve(command, token, 0);

            command = strcat(path4, token[0]);
            execErr = execve(command, token, 0);

            if (execErr)
            {
                printf("%s: Command not found.\n", token[0]);
            }
            return 0;
        }



    }
    free( token );
    return 0;
}

/*
    token -> array of strings ending in (null) are stored here after function returns
    number of tokens is returned

    this code taken from Trevor Bakker :
    https://github.com/CSE3320/Shell-Assignment/blob/master/mfs.c
*/
int promptAndReadIn(char ** token)
{
    printf("msh> ");
    char * cmdStr = malloc(MAX_COMMAND_SIZE);

    while ( !fgets(cmdStr, MAX_COMMAND_SIZE, stdin) ) ;

    int tokenCount = 0;
    char * argPtr;
    char * workingStr = strdup( cmdStr );
    char * workingRoot = workingStr;

    while ( ( (argPtr = strsep(&workingStr, WHITESPACE)) != NULL ) &&
              (tokenCount < MAX_NUM_ARGUMENTS) )
    {
        token[tokenCount] = strndup( argPtr, MAX_COMMAND_SIZE );
        if ( strlen( token[tokenCount] ) == 0 )
        {
            token[tokenCount] = NULL;
        }
        tokenCount++;
    }

    free( workingRoot );
    return tokenCount;
}

void handleSIGTSTP(int sig)
{
    printf("Hello %d\n", sig);
}

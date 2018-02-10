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

#define WHITESPACE " \t\n"
#define MAX_COMMAND_SIZE 255
#define MAX_NUM_ARGUMENTS 11

int promptAndReadIn(char **);

int main()
{
    char * cmdStr = malloc( MAX_COMMAND_SIZE );

    while ( 1 )
    {
        char ** token = malloc( MAX_NUM_ARGUMENTS );
        int tokenCount = promptAndReadIn(token);
        /* printf("msh> "); */

        /* while ( !fgets(cmdStr, MAX_COMMAND_SIZE, stdin) ) ; */

        /* char * token[MAX_NUM_ARGUMENTS]; */
        /* int tokenCount = 0; */
        /* char * argPtr; */
        /* char * workingStr = strdup( cmdStr ); */
        /* char * workingRoot = workingStr; */

        /* while ( ( (argPtr = strsep(&workingStr, WHITESPACE)) != NULL ) && */
        /*           (tokenCount < MAX_NUM_ARGUMENTS) ) */
        /* { */
        /*     token[tokenCount] = strndup( argPtr, MAX_COMMAND_SIZE ); */
        /*     if ( strlen( token[tokenCount] ) == 0 ) */
        /*     { */
        /*         token[tokenCount] = NULL; */
        /*     } */
        /*     tokenCount++; */
        /* } */

        /* int tokenIndex = 0; */
        /* for (tokenIndex = 0; tokenIndex < tokenCount; tokenIndex++) */
        /* { */
        /*     printf("token[%d] = %s\n", tokenIndex, token[tokenIndex]); */
        /* } */
        /* free( workingRoot ); */
        int tokenIndex = 0;
        for (tokenIndex = 0; tokenIndex < tokenCount; tokenIndex++)
        {
            printf("token[%d] = %s\n", tokenIndex, token[tokenIndex]);
        }
    }
    free( cmdStr );
    return 0;
}

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

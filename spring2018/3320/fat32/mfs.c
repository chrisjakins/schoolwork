#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#define MAX_NUM_ARGUMENTS 2
#define MAX_COMMAND_SIZE 64
#define WHITESPACE " \n\t"

FILE * currentFP = NULL;

struct __attribute__((__packed__)) DirectoryEntry {
    char DIR_Name[11];
    uint8_t DIR_Attr;
    uint8_t Unused1[8];
    uint16_t DIR_FirstClusterHigh;
    uint8_t Unused2[4];
    uint16_t DIR_FirstClusterLow;
    uint32_t DIR_FileSize;
};

struct DirectoryEntry dir[16];

// Image Info
int16_t BytesPerSector;
int8_t SectorsPerCluster;
int16_t RsvdSectorCount;
int8_t NumFATS;
int32_t FATSz32;
char VolumeLabel[12];

// builtins
char * stringBuiltin[] = {"cd", "open", "close", "ls", "volume",
                          "info", "stat", "get", "read"};

int cd(char **);
int open(char **);
int my_close(char **);
int ls(char **);
int volume(char **);
int info(char **);
int stat(char **);
int get(char **);
int my_read(char **);

// Utility Functions
int readInput(char **);
int execute(char **);
int parseInput(char *, char **);

int main() {

    char ** token = malloc(sizeof(char *) * MAX_NUM_ARGUMENTS);
    int status, i;

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
    return 0;
}

int readInput(char ** token) {
    char * cmdStr = malloc(MAX_COMMAND_SIZE);

    while (!fgets(cmdStr, MAX_COMMAND_SIZE, stdin)) ;

    if (strcmp(cmdStr, "\n") == 0) {
        return 0;
    }

    int tokenCount = parseInput(cmdStr, token);

    free(cmdStr);
    return tokenCount;
}

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

int execute(char ** params) {
    int status, execErr = 0;

    /* if the user entered exit or quit, return 0 to end main */
    if (params[0]) {
        if (strcmp(params[0], "exit") == 0 || strcmp(params[0], "quit") == 0) {

            return 0;

        } else if (strcmp(params[0], stringBuiltin[0]) == 0) {

            execErr = cd(params);

        } else if (strcmp(params[0], stringBuiltin[1]) == 0) {

            execErr = open(params);

        } else if (strcmp(params[0], stringBuiltin[2]) == 0) {

            execErr = my_close(params);

        } else if (strcmp(params[0], stringBuiltin[3]) == 0) {

            execErr = ls(params);

        } else if (strcmp(params[0], stringBuiltin[4]) == 0) {

            execErr = volume(params);

        } else if (strcmp(params[0], stringBuiltin[5]) == 0) {

            execErr = info(params);

        } else if (strcmp(params[0], stringBuiltin[6]) == 0) {

            execErr = stat(params);

        } else if (strcmp(params[0], stringBuiltin[7]) == 0) {

            execErr = get(params);

        } else if (strcmp(params[0], stringBuiltin[8]) == 0) {

            execErr = my_read(params);

        } else {
            printf("do something\n");
        }
    }
    return 1;
}

// Builtin methods

int open(char ** params) {
    // File system image already opened
    if (currentFP) {
        printf("Error: File system image already open.\n");
        return 1;
    }

    if (!(currentFP = fopen(params[1], "r"))) {
        printf("Error: File system image not found.\n");
        return 1;
    }

    // Image successfully opened
    fseek(currentFP, 11, SEEK_SET);
    fread(&BytesPerSector, 2, 1, currentFP);

    fseek(currentFP, 13, SEEK_SET);
    fread(&SectorsPerCluster, 1, 1, currentFP);

    fseek(currentFP, 14, SEEK_SET);
    fread(&RsvdSectorCount, 2, 1, currentFP);

    fseek(currentFP, 16, SEEK_SET);
    fread(&NumFATS, 1, 1, currentFP);

    fseek(currentFP, 36, SEEK_SET);
    fread(&FATSz32, 4, 1, currentFP);

    fseek(currentFP, 71, SEEK_SET);
    fread(&VolumeLabel, 11, 1, currentFP);
    VolumeLabel[11] = 0;

    return 1;
}

int my_close(char ** params) {
    if (!currentFP) {
        printf("Error: File system not open.\n");
        return 1;
    }

    fclose(currentFP);
    currentFP = NULL;
    return 1;
}

int info(char ** params) {
    if (!currentFP) {
        printf("Error: File system image must be opened first.\n");
        return 1;
    }

    printf("Bytes per sector: 0x%x %d\n", BytesPerSector, BytesPerSector);
    printf("Secotrs Per Cluster: 0x%x %d\n", SectorsPerCluster, SectorsPerCluster);
    printf("Reserved Sector Count: 0x%x %d\n", RsvdSectorCount, RsvdSectorCount);
    printf("Number of FATs: 0x%x %d\n", NumFATS, NumFATS);
    printf("FAT Size 32: 0x%x %d\n", FATSz32, FATSz32);
    return 1;
}

int ls(char ** params) {
    if (!currentFP) {
        printf("Error: File system image must be opened first.\n");
        return 1;
    }

    int root = (NumFATS * FATSz32 * BytesPerSector) + (RsvdSectorCount * BytesPerSector);
    fseek(currentFP, root, SEEK_SET);
    fread(dir, 32, 16, currentFP);

    // debug
    printf("%s\n", dir[0].DIR_Name);

    return 1;
}

int cd(char ** params) {
    if (!currentFP) {
        printf("Error: File system image must be opened first.\n");
        return 1;
    }
    printf("%s\n", params[1]);
    return 1;
}

int volume(char ** params) {
    if (!currentFP) {
        printf("Error: File system image must be opened first.\n");
        return 1;
    }

    if (strcmp(VolumeLabel, "") == 0 || strcmp(VolumeLabel, "           ") == 0) {
        printf("Error: volume name not found.\n");
    } else {
        printf("%s\n", VolumeLabel);
    }

    return 1;
}

int get(char ** params) {
    if (!currentFP) {
        printf("Error: File system image must be opened first.\n");
        return 1;
    }
    printf("%s\n", params[1]);
    return 1;
}

int my_read(char ** params) {
    if (!currentFP) {
        printf("Error: File system image must be opened first.\n");
        return 1;
    }
    printf("%s\n", params[1]);
    return 1;
}

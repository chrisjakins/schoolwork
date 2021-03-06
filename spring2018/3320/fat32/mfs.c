/*
    Chris Jakins
    FAT32 File System Reader
    
    I apologize for the messy code...
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define MAX_NUM_ARGUMENTS 5
#define MAX_COMMAND_SIZE 64
#define WHITESPACE " \n\t"

FILE * currentFP = NULL;
char currentDirectory[24] = "";
int currentCluster;
int rootCluster;

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
int LBAToOffset(int32_t);
int16_t NextLB(uint32_t);

int main() {

    char ** token = malloc(sizeof(char *) * MAX_NUM_ARGUMENTS);
    int status, i;

    do {
        memset(token, '\0', sizeof(token) * MAX_NUM_ARGUMENTS);

        printf("msh:%s> ", currentDirectory);
        readInput(token);
        status = execute(token);

    } while (status);

    for (i = 0; i < MAX_NUM_ARGUMENTS && token[i]; i++) {
        free(token[i]);
    }
    free(token);

    if (currentFP) {
        fclose(currentFP);
    }
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
    int execErr;

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
    if (execErr) {}
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

    // populate directory info with root
    rootCluster = (NumFATS * FATSz32 * BytesPerSector) + (RsvdSectorCount * BytesPerSector);
    fseek(currentFP, rootCluster, SEEK_SET);
    fread(dir, 32, 16, currentFP);

    // keep track of where we are
    currentCluster = rootCluster;
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
    printf("Sectors Per Cluster: 0x%x %d\n", SectorsPerCluster, SectorsPerCluster);
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

    char buff[12];
    memcpy(buff, "           ", 11);
    buff[11] = 0;

    printf(".\n");
    int i;
    for (i = 0; i < 16; i++) {
        if (dir[i].DIR_Attr == 1 || dir[i].DIR_Attr == 16 || dir[i].DIR_Attr == 32) {
            memcpy(buff, dir[i].DIR_Name, 11);

            // if not deleted file
            if (buff[0] != -27) {
                printf("%s\n",  buff);
            }
        }
    }

    return 1;
}

/*
    The way strings are stored in the image file
    0   1   2   3   4   5   6   7   8   9   10  11
    (chars of filename or spaces)   (extension) \0
    all uppercase

    assumes that extensions are 3 chars

    params should (hopefully) only have one file/directory name
    will break if there is params[2], params[3], etc
*/
int stat(char ** params) {
    if (!currentFP) {
        printf("Error: File system image must be opened first.\n");
        return 1;
    }

    int i;
    char buff[12];
    memcpy(buff, "           ", 11);
    buff[11] = 0;

    // copy filename
    for (i = 0; i < 8 && params[1][i] != '.' && params[1][i] != 0; i++) {
            buff[i] = toupper(params[1][i]);
    }

    // copy extension
    if (params[1][i] == '.') {
        int length = strlen(params[1]);
        buff[8] = toupper(params[1][length - 3]);
        buff[9] = toupper(params[1][length - 2]);
        buff[10] = toupper(params[1][length - 1]);
    }

    char temp[12];
    for (i = 0; i < 16; i++) {
        if (dir[i].DIR_Attr == 1 || dir[i].DIR_Attr == 16 || dir[i].DIR_Attr == 32) {
            memcpy(temp, dir[i].DIR_Name, 11);
            temp[11] = 0;
            if (strcmp(buff, temp) == 0) {
                printf("Name: %s\nAttribute: %d\n", temp, dir[i].DIR_Attr);
                printf("First Cluster High: %d\nFirst Cluster Low: %d\n",
                        dir[i].DIR_FirstClusterHigh, dir[i].DIR_FirstClusterLow);
                printf("File Size: %d\n", dir[i].DIR_Attr == 16 ? 0 : 16);
            }
        }
    }

    return 1;
}

/*
    Assume it's stored in params[1] and ignore the rest
*/
int cd(char ** params) {
    if (!currentFP) {
        printf("Error: File system image must be opened first.\n");
        return 1;
    }

    char filenameArg[12];
    memcpy(filenameArg, "           ", 11);
    filenameArg[11] = 0;

    // copy filename
    int i;
    for (i = 0; i < 8 && params[1][i] != 0; i++) {
            filenameArg[i] = toupper(params[1][i]);
            currentDirectory[i] = params[1][i] == ' ' ? '0' : toupper(params[1][i]);
    }

    // for bonus points :D
    if (strcmp(filenameArg, "..         ") == 0) {
        currentDirectory[0] = 0;
    }

    int newCluster;

    fseek(currentFP, currentCluster, SEEK_SET);

    char temp[12];
    memcpy(temp, "           ", 11);
    temp[11] = 0;

    int found = 0;
    for (i = 0; i < 16 && !found; i++) {
        if (dir[i].DIR_Attr == 16) {
            memcpy(temp, dir[i].DIR_Name, 11);
            if (strcmp(filenameArg, temp) == 0) {
                newCluster = dir[i].DIR_FirstClusterLow;
                found = 1;
            }
        }
    }

    if (found) {
        // if user enters '..' then I just take them back to root cluster
        // will fix if have time
        int newDirectory = strcmp(filenameArg, "..         ") != 0 ? 
                            ((newCluster - 2) * BytesPerSector) + rootCluster :
                            rootCluster;

        fseek(currentFP, newDirectory, SEEK_SET);
        for (i = 0; i < 16; i++) {
            fread(&dir[i], 32, 1, currentFP);
        }
        currentCluster = newDirectory;
    } else {
        printf("cd: %s: No such file or directory\n", params[1]);
    }

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

    if (!params[1]) {
        printf("Error: get <filename>\n");
        return 1;
    }

    int dirToRead = -1, i;
    char filenameArg[12];
    memcpy(filenameArg, "           ", 11);
    filenameArg[11] = 0;
    
    // copy filename
    for (i = 0; i < 8 && params[1][i] != '.' && params[1][i] != 0; i++) {
            filenameArg[i] = toupper(params[1][i]);
    }

    // copy extension
    if (params[1][i] == '.') {
        int length = strlen(params[1]);
        filenameArg[8] = toupper(params[1][length - 3]);
        filenameArg[9] = toupper(params[1][length - 2]);
        filenameArg[10] = toupper(params[1][length - 1]);
    }

    // find file in directory
    char buff[12];
    memcpy(buff, "           ", 11);
    buff[11] = 0;
    for (i = 0; i < 16; i++) {
        memcpy(buff, "           ", 11);
        memcpy(buff, dir[i].DIR_Name, 11);
        buff[11] = 0;
        if (strcmp(buff, filenameArg) == 0) {
            dirToRead = i;
        }
    }

    char outfile[12];
    strcpy(outfile, params[1]);

    FILE * newFP = fopen(outfile, "w");

    // grab values from user input
    int readingPos = dir[dirToRead].DIR_FirstClusterLow;
    int address = LBAToOffset(readingPos);

    char byte;
    while (readingPos != -1) {
        address = LBAToOffset(readingPos);
        fseek(currentFP, address, SEEK_SET);

        for (i = 0; i < BytesPerSector; i++) {
            fread(&byte, 1, 1, currentFP);
            fwrite(&byte, 1, 1, newFP);
        }

        readingPos = NextLB(readingPos);
    }

    fclose(newFP);
    return 1;
}

/*
    Assumes all input parameters are present and valid

    read <filename> <position> <# bytes>
*/
int my_read(char ** params) {
    if (!currentFP) {
        printf("Error: File system image must be opened first.\n");
        return 1;
    }

    if (!params[1] || !params[2] || !params[3]) {
        printf("Error: read <filename> <position> <number of bytes>\n");
        return 1;
    }

    int numBytes = atoi(params[3]), dirToRead = -1, i;
    char filenameArg[12];
    memcpy(filenameArg, "           ", 11);
    filenameArg[11] = 0;
    
    // copy filename
    for (i = 0; i < 8 && params[1][i] != '.' && params[1][i] != 0; i++) {
            filenameArg[i] = toupper(params[1][i]);
    }

    // copy extension
    if (params[1][i] == '.') {
        int length = strlen(params[1]);
        filenameArg[8] = toupper(params[1][length - 3]);
        filenameArg[9] = toupper(params[1][length - 2]);
        filenameArg[10] = toupper(params[1][length - 1]);
    }

    // find file in directory
    char buff[12];
    memcpy(buff, "           ", 11);
    buff[11] = 0;
    for (i = 0; i < 16; i++) {
        memcpy(buff, "           ", 11);
        memcpy(buff, dir[i].DIR_Name, 11);
        buff[11] = 0;
        if (strcmp(buff, filenameArg) == 0) {
            dirToRead = i;
        }
    }

    // grab values from user input
    int position = atoi(params[2]);
    int readingPos = dir[dirToRead].DIR_FirstClusterLow;

    // go to user requested start value
    while (position > BytesPerSector) {
        position -= BytesPerSector;
        readingPos = NextLB(readingPos);
    }

    int address = LBAToOffset(readingPos);
    fseek(currentFP, address + position, SEEK_SET);
   
    // read out the file to stdout
    char byte;
    for (i = 0; i < numBytes; i++) {
        fread(&byte, 1, 1, currentFP);
        printf("%c", byte);
    }
    printf("\n");

    return 1;
}

/*
    This code taken from professor Trevor Bakker
*/
int16_t NextLB(uint32_t sector) {
    uint32_t FATAddress = (BytesPerSector * RsvdSectorCount) + sector * 4;
    int16_t val;
    fseek(currentFP, FATAddress, SEEK_SET);
    fread(&val, 2, 1, currentFP);
    return val;
}

int LBAToOffset(int32_t sector) {
    return ((sector - 2) * BytesPerSector) + BytesPerSector * RsvdSectorCount +
            NumFATS * FATSz32 * BytesPerSector;
}

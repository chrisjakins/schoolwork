/* Chris Jakins */
/* CSE1320 */
/* HW8 */
/* 8/09 */
#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <string.h>

int editDistance(char *, char *);
int min(int x, int y, int z);
void freeMatrix(int **, int);
void matchSearch(char **, int);

int main(int argc, char * argv[])
{
    glob_t paths;
    char * pathName = malloc(101);
    int maxEdits;

    if (argc != 3)
    {
        printf("usage:   executableName maxDistanceInteger fileNameExtension\n");
        printf("example: ./jakins-hw08 5 mp3\n");
        return EXIT_FAILURE;
    } 
  
    maxEdits = atoi(argv[1]); 
    sprintf(pathName, "*.%s", argv[2]); 
    if (glob(pathName, 0, NULL, &paths) == 0)
    {
        matchSearch(paths.gl_pathv, maxEdits);
        globfree(&paths);
    }
    free(pathName);

    return EXIT_SUCCESS;
}

/*  this function goes one by one through each string in list
    and searches the remaining portion of the list for strings that are within
    argument max edit distance of the first */
void matchSearch(char ** list, int max)
{
    char ** p, ** q;
    int distance, numMatches;
    
    for (p = list; *p != NULL; p++)
    {
        numMatches = 0;
        for (q = p + 1; *q != NULL; q++)
        {
            if ((distance = editDistance(*p, *q)) <= max)
            {   /* print the file name that is being matched */
                if (numMatches == 0) 
                    printf("%s\n", *p);
                printf("%5d, %s\n", distance, *q); /* print the matched */
                numMatches++;
            }
        }
    }
}

/*  this function follows the edit distance algorithm given by:
        www.cdn.geeksforgeeks.org/dynamic-programming-set-5-edit-distance */
int editDistance(char * str1, char * str2)
{
    int distResult, i, j;
    int row = strlen(str1) + 1, col = strlen(str2) + 1;
    int ** distMatrix = malloc(row * sizeof(int *));
    for (i = 0; i < row; i++)
        distMatrix[i] = malloc(col * sizeof(int));

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            if (i == 0)
                distMatrix[i][j] = j;
            else if (j == 0)
                distMatrix[i][j] = i;
            else if (str1[i - 1] == str2[j - 1])
                distMatrix[i][j] = distMatrix[i - 1][j - 1];
            else
                distMatrix[i][j] = 1 + min(distMatrix[i][j - 1],
                                           distMatrix[i - 1][j],
                                           distMatrix[i - 1][j - 1]);
        }
    }

    distResult = distMatrix[row - 1][col - 1];
    freeMatrix(distMatrix, row);
    return distResult;
}

/*  this function free all memory associated with dynamically-
    allocated argument matrix */
void freeMatrix(int ** matrix, int row)
{
    int i;
    for (i = 0; i < row; i++)
        free(matrix[i]);
    free(matrix);
}

/* helper function for min */
int minTwo(int x, int y)
{
    if (x <= y)
        return x;
    return y;
}

/* this function returns the min of three integers */
int min(int x, int y, int z)
{
    return minTwo(minTwo(x, y), z); 
}

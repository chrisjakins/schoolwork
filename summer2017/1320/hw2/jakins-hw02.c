/* Chris Jakins */
/* CSE1320 */
/* HW2 */
/* Due 6/21 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double calcSum(char*);
void calcMeanAndVariance(char*, double*, double*);
void digitCount(char*);
void printReport(char*, double, double, double);

int main(void)
{
    char* data[] = {"12, 34, 56, 78", "82.16, 41.296", "2, -3, 5, -7, 11, -13, 17, -19",
                    "9.00009, 90.0009, 900.009, 9000.09, 90000.9"};
    double sum, variance, mean;
    const int NUMCOLS = sizeof(data) / sizeof(data[0]);
    int index;

    for (index = 0; index < NUMCOLS; index++)
    {
        sum = calcSum(data[index]);
        calcMeanAndVariance(data[index], &mean, &variance);
        printReport(data[index], sum, mean, variance);
        digitCount(data[index]);
    }
}

double calcSum(char* numbers)
{
    char numString[100];
    double sum = 0;
    char* numTok, *delim = ",";

    strcpy(numString, numbers);
    numTok = strtok(numString, delim);
    while (numTok != NULL)
    {
        sum += atof(numTok);
        numTok = strtok(NULL, delim);
    }
    return sum;
}

/* Precondition: numbers stores at least one token */
void calcMeanAndVariance(char* numbers, double* meanPtr, double* varPtr)
{
    char numString[100];
    double nums[50]; /* max = "val,val,val,..." */
    char* numTok, *delim = ",";
    double sum = calcSum(numbers);
    int numCount = 0;
    double interVal;
    int index;
    
    /* split string and store in nums array */
    strcpy(numString, numbers);
    numTok = strtok(numString, delim);
    while (numTok != NULL)
    {
        nums[numCount] = atof(numTok);
        numTok = strtok(NULL, delim);
        numCount++;
    }
    *meanPtr = sum / numCount;
    /* variance calculations */
    sum = 0;
    for (index = 0; index < numCount; index++)
    {
        interVal = nums[index] - *meanPtr;
        sum += interVal * interVal;
    }

    if (numCount > 1)
        *varPtr = sum / (numCount - 1);
    else
        *varPtr = 0;
}

void digitCount(char* numbers)
{
    int map[10] = {0};
    int index;
    /* indices of array correspond to digits in string */
    /* value at index is incremented for each digit == index */
    while (*numbers != '\0')
    {
        if (*numbers >= '0' && *numbers <= '9')
            map[*numbers - '0']++; 
        numbers++;
    }
    /* last count is printed without the ',' */ 
    printf("  digit counts = ");
    for (index = 0; index < 9; index++)
        printf("%d, ", map[index]);
    printf("%d\n\n", map[9]);
}

void printReport(char* numbers, double sum, double mean, double var)
{
    printf("For %s\n", numbers);
    printf("  sum = %f\n", sum);
    printf("  mean = %f\n", mean);
    printf("  variance = %f\n", var);
}

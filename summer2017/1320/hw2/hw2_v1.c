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
    return EXIT_SUCCESS;
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
/* store numbers in array as you read them, use numCount to recognize end of array */
void calcMeanAndVariance(char* numbers, double* meanPtr, double* varPtr)
{
    char numString[100];
    char* numTok, *delim = ",";
    double sum = calcSum(numbers);
    int numCount = 0;
    double interVal;

    /* count the number of values and calculate mean */
    strcpy(numString, numbers);
    numTok = strtok(numString, delim);
    while (numTok != NULL)
    {
        numCount++;
        numTok = strtok(NULL, delim);
    }
    *meanPtr = sum / numCount;

    /* reset numString and calculate variance */
    sum = 0;
    strcpy(numString, numbers);
    numTok = strtok(numString, delim);
    while (numTok != NULL)
    {
        interVal = atof(numTok) - *meanPtr;
        sum += interVal * interVal; 
        numTok = strtok(NULL, delim);
    }

    if (numCount > 1)
        *varPtr = sum / (numCount - 1);
    else   /* only one element */
        *varPtr = 0;

    /*
    strcpy(numString, numbers);
    numTok = strtok(numString, delim);
    while (numTok != NULL)
    {
        val = atof(numTok);
        varSum += val * val;
        numCount++;
    }
    *meanPtr = sum / numCount;
    *varPtr = (varSum - (sum * sum) / numCount) / (numCount - 1);
    */
}

void digitCount(char* numbers)
{
    const int NUMDIGITS = 10;
    /* int map[NUMDIGITS]; */
    int map[10] = {0};
    int index;

    /* populate array with 0's */
    for (index = 0; index < NUMDIGITS; index++)
        map[index] = 0;

    /* is this really the best way to convert a char to an int? 
        atoi was not working */

    while (*numbers != '\0')
    {
        if (*numbers >= '0' && *numbers <= '9')
            map[*numbers - '0']++; 
        numbers++;
    }
    
    printf("  digit counts = ");
    for (index = 0; index < NUMDIGITS - 1; index++)
        printf("%d, ", map[index]);
    printf("%d\n\n", map[NUMDIGITS - 1]);
}

void printReport(char* numbers, double sum, double mean, double var)
{
    printf("For %s\n", numbers);
    printf("  sum = %f\n", sum);
    printf("  mean = %f\n", mean);
    printf("  variance = %f\n", var);
}

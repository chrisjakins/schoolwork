/* Chris Jakins */
/* Lab Assignment 1 9/21 */
/* CSE 2320 */
/* TO COMPILE :::::::: 'gcc -std=c89 -pedantic -Wall jakins-hw1.c' */
/* Description: */
/* This code performs merge sort on intervals. It also combines intervals */
/* that are overlapping or "swallowed." */
#include <stdio.h>
#include <stdlib.h>

#define OPEN 1
#define CLOSED 0
#define TRUE 1
#define FALSE 0

typedef struct Fraction {
    int bound;
    int top;
    int bottom;
} Fraction;

typedef struct Interval {
    Fraction left;
    Fraction right;
} Interval;

void setBound(Interval *);
void reNegate(Interval *);
int isSwallowed(Interval one, Interval two);
int isOverlapping(Interval one, Interval two);
int crossMult(Fraction, Fraction);
int mergesort(Interval[], int, int);
int merge(Interval[], int, int, int, int);

int main(void)
{
    int numIntervals, i;
    Interval * intervals;

    scanf("%d", &numIntervals);
    intervals = malloc(numIntervals * sizeof(Interval));
   
    /* input */ 
    for (i = 0; i < numIntervals; i++)
    {
        scanf("%d %d %d %d", &intervals[i].left.top, &intervals[i].left.bottom,
                             &intervals[i].right.top, &intervals[i].right.bottom);
        /* set interval bound types */ 
        setBound(&intervals[i]);
    }

    numIntervals = mergesort(intervals, 0, numIntervals - 1);

    printf("%d\n", numIntervals);
    for (i = 0; i < numIntervals; i++)
    {
        reNegate(&intervals[i]);
        printf("%d %d %d %d\n", intervals[i].left.top, intervals[i].left.bottom,
                                intervals[i].right.top, intervals[i].right.bottom);
    }

    free(intervals);
    return EXIT_SUCCESS;
}

/*  setbound()
    
    Parameters: 
        val is an interval struct that needs to have its bounds set

    if val numerators are less than 0, the respective bound is set to OPEN
        and the numerator is made positive for easier sorting
    otherwise the respective bound is set to CLOSED */
void setBound(Interval * val)
{
    if (val->left.top < 0) 
    {
        val->left.bound = OPEN;
        val->left.top *= -1;
    }
    else
        val->left.bound = CLOSED;
    if (val->right.top < 0)
    {
        val->right.bound = OPEN;
        val->right.top *= -1;
    }
    else
        val->right.bound = CLOSED; 
}

/* reNegate()

    Parameters:
        val is an interval struct that need to have its numbers reset
            to original value

    if the bound for either fraction is OPEN, then the respective
        numerator is made negative */
void reNegate(Interval * val)
{
    if (val->left.bound == OPEN) val->left.top *= -1;
    if (val->right.bound == OPEN) val->right.top *= -1;
}

/* merge()

    Return values:
        finalSize = the total number of elements stored, after all combines
        a[] from low to finalSize - 1 stores the sorted elements
    
    Parameters:
        a is the original array of interval objects.
        low is the base index for what will be the 'b' list
        mid + 1 is the base index for what will be the 'c' list
        size1 is the size of the 'b' list
        size2 is the size of the 'c' list
        
    Lists 'b' and 'c' are made with their respective elements from 'a'
    reset i and j
    loop until one of the lists has been exhausted
        determine if top elements of each list are overlapping
        if 'overlap' is less than 0, top element of 'c' list goes first
        if 'overlap' is greater than 0, top element of 'b' list goes first
        if 'overlap' is equal to 0, elements of 'b' and 'c' need to be merged
            store the lowest left fraction in 'a'
            store the greatest right fraction in 'a'
        if element just stored overlaps with previous element in list, combine them 
    end loop
    fill array with remaining elements, checking if they need to be combined */ 
int merge(Interval a[], int low, int mid, int size1, int size2)
{
    int i, j, k = low, finalSize = 0, overlap;
    Interval * b = malloc(size1 * sizeof(Interval));
    Interval * c = malloc(size2 * sizeof(Interval));

    for (i = 0; i < size1; i++)
        b[i] = a[low + i];
    for (j = 0; j < size2; j++)
        c[j] = a[mid + j + 1];

    i = 0; j = 0;
    /* until one list is exhausted */
    while (i < size1 && j < size2) 
    {   
        overlap = isOverlapping(b[i], c[j]);
        if (overlap < 0)
            a[k] = c[j++];
        else if (overlap > 0)
            a[k] = b[i++];
        else
        {
            if (crossMult(b[i].left, c[j].left) <= crossMult(c[j].left, b[i].left))
                a[k].left = b[i].left;
            else
                a[k].left = c[j].left;
            if (crossMult(b[i].right, c[j].right) <= crossMult(c[j].right, b[i].right))
                a[k].right = c[j].right;
            else
                a[k].right = b[i].right;
            i++; j++;
        }
        /* does element stored combine with previous element? */
        if (k != low && isOverlapping(a[k - 1], a[k]) == 0)
        {
            if (!isSwallowed(a[k - 1], a[k]))
                a[k - 1].right = a[k].right;
        }
        else
        {
            k++; finalSize++;
        }
    }
    /* merge rest of remaining list */
    if (i < size1)
        for ( ; i < size1; i++ )
        {
            if (isOverlapping(a[k - 1], b[i]) == 0)
            {
                if (!isSwallowed(a[k - 1], b[i]))
                    a[k - 1].right = b[i].right;
            }
            else
            {
                a[k++] = b[i];
                finalSize++;
            }
        }
    else
        for ( ; j < size2; j++ )
        {
            if (isOverlapping(a[k - 1], c[j]) == 0)
            {
                if (!isSwallowed(a[k - 1], c[j]))
                    a[k - 1].right = c[j].right;
            }
            else
            {
                a[k++] = c[j];
                finalSize++;
            }
        }

    free(b);
    free(c);
    return finalSize;
}

/*  isSwallowed()

    Return values:
        1 if interval one swallows interval two
        0 if one does not swallow interval two

    Parameters:
        two intervals, one and two */
int isSwallowed(Interval one, Interval two)
{
    if (crossMult(one.left, two.left) <= crossMult(two.left, one.left) &&
        crossMult(one.right, two.right) >= crossMult(two.right, one.right))
        return 1;
    return 0;
}

/* isOverlapping()

    Return values:
        0   -   intervals need to be merged
        1   -   interval one goes first
        -1  -   interval two goes first

    Parameters:
        two intervals, one and two

    if one.right == two.left &&
       (one.rBound !open || two.lBound !open)
            return 0
    if one.left == two.right &&
        (one.lBound !open || two.rBound !open)
            return 0
    if one.right <= two.left
            return 1 
    if two.right <= one.left
            return -1
    return 0 */
int isOverlapping(Interval one, Interval two)
{
    if (crossMult(one.right, two.left) == crossMult(two.left, one.right) &&
        !(one.right.bound == OPEN && two.left.bound == OPEN))
        return 0;
    if (crossMult(one.left, two.right) == crossMult(two.right, one.left) &&
        !(one.left.bound == OPEN && two.right.bound == OPEN))
        return 0;
    if (crossMult(one.right, two.left) <= crossMult(two.left, one.right))
        return 1;
    if (crossMult(two.right, one.left) <= crossMult(one.left, two.right))
        return -1;
    return 0;
}

/*  crossMult()

    Return values:
        the product of one.numerator * two.denominator

    Parameters:
        two Fractions, one and two */
int crossMult(Fraction one, Fraction two)
{
    return one.top * two.bottom;
}

/*  mergesort()

    Return values:
        the size of the array return from merge()
        a[] also stores the array holding the current sorted
            and unsorted values

    Parameters:
        a[] is the original array of intervals
        low is the low index of current recursive call
        high is the high index of ''        '' */
int mergesort(Interval a[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2; 
        int size1 = mergesort(a, low, mid);
        int size2 = mergesort(a, mid + 1, high);
        return merge(a, low, mid, size1, size2);
    }
    return 1;
}

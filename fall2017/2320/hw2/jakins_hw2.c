#include <stdio.h>
#include <stdlib.h>

typedef struct Bid {
    int startTime;
    int endTime;
    int weight;
} Bid;

/* i/o */
Bid * initArray(int *);
void outputArray(const Bid *, const int);
void outputDP(int **, const int);

/* DP processing */
int * findPriors(const Bid *, const int);
int schedulingDP(const Bid *, const int *, const int, int **);
void backtrace(int **, const int, const Bid *, const int *);

/* helpers */
int max(int, int);
int ** allocDP(int);
void freeDP(int **, int);

int main(void) {
    int size, i;
    Bid * bids = initArray(&size);
    int ** DP = allocDP(size);
    int * priors = findPriors(bids, size);
    int totalSum = schedulingDP(bids, priors, size, DP); 

    outputArray(bids, size);
    outputDP(DP, size);

    backtrace(DP, size, bids, priors);

    freeDP(DP, size); 
    free(priors);
    free(bids);
    return 0;
}

/*  This function finds the maximum previous interval that an interval
    does not overlap with */
int * findPriors(const Bid * bids, const int size) {
    int i, j, * final = malloc(size * sizeof(int));
    
    final[0] = 0;
    for (i = 1; i < size; i++) {
        for (j = 0; j < i; j++) {
            if (bids[i].startTime >= bids[j].endTime) {
                final[i] = j + 1;
            }
        }
    }
    return final;
}

/*  This function performs a two room weighted interval scheduling on 'input'
    the return value is the total weight achieved */
int schedulingDP(const Bid * input, const int * priors, const int numBids, int ** DP) {
    int i, j, maxSum;

    for (i = 0; i <= numBids; i++) {
        for (j = 0; j <= numBids; j++) {
            /* DP[0][0] stays as 0 */
            if (!(i == 0 && j == 0)) {
                /* upper traingle */
                if (i < j) {
                    DP[i][j] = max(DP[i][priors[j - 1]] + input[j - 1].weight, DP[i][j - 1]);
                /* lower traingle */
                } else if (i > j) {
                    DP[i][j] = max(DP[priors[i - 1]][j] + input[i - 1].weight, DP[i - 1][j]);
                /* diagonal */
                } else {
                    DP[i][j] = DP[i][j - 1];
                }
            }
        }
    }

    return DP[numBids][numBids];
}

void backtrace(int ** table, const int size, const Bid * input, const int * priors) {
    Bid * room1;
    Bid * room2;
    int i = size, j = size, interval = size;
    while (interval >= 0) {
        
    }
}

/*  This function reads in input from stdin and 
    populates the array of bids */
Bid * initArray(int * size) {
    int i;
    scanf("%d", size);
    Bid * bids = malloc(*size * sizeof(Bid));
    
    for (i = 0; i <= *size; i++) {
        scanf("%d %d %d", &bids[i].startTime,
                          &bids[i].endTime,
                          &bids[i].weight);
    }
    return bids;
}

/*  This function takes an array of bid objects and
    outputs it */
void outputArray(const Bid * bids, const int size) {
    int i;
    printf("%d\n", size);
    for (i = 0; i < size; i++) {
        printf("%d %d %d\n", bids[i].startTime,
                             bids[i].endTime,
                             bids[i].weight);
    }    
}

void outputDP(int ** table, const int size) {
    int i, j;
    for (i = 0; i <= size; i++) {
        for (j = 0; j <= size; j++) {
            printf("%2d ", table[i][j]);
        }
        printf("\n");
    }
}

int max(int one, int two) {
    return one >= two ? one : two;
}

int ** allocDP(int size) {
    int i;
    int ** DP = malloc((size + 1) * sizeof(int *));
    for (i = 0; i <= size; i++) {
        DP[i] = calloc((size + 1), sizeof(int));
    }
    return DP;
}

void freeDP(int ** DP, int size) {
    int i;
    for (i = 0; i <= size; i++) {
        free(DP[i]);
    }
    free(DP);
}

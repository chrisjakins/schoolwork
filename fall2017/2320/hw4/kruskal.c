//Kruskal's MST using union-find trees
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int numVertices, numEdges;
int *parent, *weight, numTrees;

typedef struct edge {
    char * tail, * head;
    int weight;
} edgeType;

edgeType *edgeTab;

int find(int x)
// Find root of tree containing x
{
    int i,j,root;

    // Find root
    for (i = x; parent[i] != i; i = parent[i]) ;
    root = i;
          // path compression - make all nodes on path
          // point directly at the root
    for (i = x; parent[i] != i; j = parent[i], parent[i] = root, i = j) ;

    return root;
}

void unionFunc(int i,int j)
// i and j must be roots!
{
    if (weight[i] > weight[j]) {
        parent[j] = i;
        weight[i] += weight[j];
    } else {
        parent[i] = j;
        weight[j] += weight[i];
    }
    numTrees--;
}

int weightAscending(const void* xin, const void* yin)
// Used in call to qsort()
{
    edgeType *x,*y;

    x = (edgeType*) xin;
    y = (edgeType*) yin;
    return x->weight - y->weight;
}

int isPrime(int number) {
    int i;
    for (i = 2; i < sqrt(number); i++) {
        if (number % i == 0) return 0;
    }
    return 1;
}

int getNextPrimeNumber(int number) {
    int found = 0;
    while (!found) {
        /* int i; */
        found = isPrime(number++);
    }
    return number - 1;
}

/* returns an index from 0 to m - 1 */
int hash(char * string, int m) {
    int hash = 0, i;
    for (i = 0; string[i] != 0; i++) {
        hash = (hash * 10 + string[i]) % m;
    }
    return hash % m;
}

/* returns 
        -1 if table is full
        0 if string is already stored in table
        1 if string was successfully stored in table */
int store(char * string, int num, char ** htChar, int * htIndex, int size) {
    int i;

    if (num == size) {
        return -1; // table is full, cannot be stored
    }

    for (i = 0; i < num; i++) {
        if (strcmp(string, htChar[i]) == 0) {
            return 0;
        }
    }

    int hashVal = hash(string, size);
    htChar[num] = string;

    int stored = 0, index = hashVal;
    while (!stored) {
        if (htIndex[index] == -1) {
            htIndex[index] = num;
            stored = 1;
        } else {
            if (index == size) {
                index = 0;
            } else {
                index++;
            }
        }
    }
    return 1;
}

int main()
{
    int i, MSTweight = 0;
    int root1, root2;

    scanf("%d %d", &numVertices, &numEdges);
    edgeTab = (edgeType*) malloc(numEdges * sizeof(edgeType));
    parent = (int*) malloc(numVertices * sizeof(int));
    weight = (int*) malloc(numVertices * sizeof(int));

    if (!edgeTab || !parent || !weight) {
        printf("error 2\n");
        exit(0);
    }

    /* set up hash table here */
    int tableSize = getNextPrimeNumber(numVertices * 2);
    char ** hashTableChar = malloc(tableSize * sizeof(char*));
    int * hashTableIndex = malloc(tableSize * sizeof(int));
    for (i = 0; i < tableSize; i++) {
        hashTableIndex[i] = -1;
    }
    int numElements = 0;

    for (i = 0; i < numEdges; i++) {
        edgeTab[i].tail = malloc(50);
        edgeTab[i].head = malloc(50);

        scanf("%s %s %d", edgeTab[i].tail, edgeTab[i].head, &edgeTab[i].weight);
        if (store(edgeTab[i].tail, numElements, hashTableChar, hashTableIndex, tableSize)) {
            numElements++;
        }
        if (store(edgeTab[i].head, numElements, hashTableChar, hashTableIndex, tableSize)) {
            numElements++;
        }
    }

    /* error checking here? */
    /* for (i = 0; i < tableSize; i++) { */
        /* printf("%d |||| %s\n", hashTableIndex[i], hashTableChar[i]); */
    /* } */
    /*********************************/


    numTrees = numVertices;
    qsort(edgeTab, numEdges, sizeof(edgeType), weightAscending);

    /* initialize disjoint subset representation */
    for (i = 0; i < numVertices; i++) {
        parent[i] = i;
        weight[i] = edgeTab[i].weight;
    }

    for (i = 0; i < numEdges; i++) {
        printf("%s %d\n", hashTableChar[i], i);
    }
    printf("\n");
    for (i = 0; i < numEdges; i++) {
        printf("%s %s %d\n", edgeTab[i].tail, edgeTab[i].head, i);
    }
    printf("\n");

    for (i = 0; i < numEdges; i++) {
        int j, head = 0, tail = 0;
        for (j = 0; j < numElements; j++) {
            if (strcmp(edgeTab[i].tail, hashTableChar[j]) == 0) tail = j;
            if (strcmp(edgeTab[i].head, hashTableChar[j]) == 0) head = j;
        }
        root1 = find(tail);
        root2 = find(head);
        printf("\n");
        for (j = 0; j < numVertices; j++) {
            printf("%d ", parent[j]);
        }
        printf("\n");
        for (j = 0; j < numVertices; j++) {
            printf("%d ", weight[j]);
        }
        printf("\n");
        printf("%s %s %d\n", edgeTab[i].tail, edgeTab[i].head, edgeTab[i].weight);
        printf("%d %d\n", root1, root2);

        if (root1 == root2)
            printf("%s %s %d discarded\n", edgeTab[i].tail, edgeTab[i].head, edgeTab[i].weight);
        else {
            printf("%s %s %d included\n", edgeTab[i].tail, edgeTab[i].head, edgeTab[i].weight);
            MSTweight += edgeTab[i].weight;
            unionFunc(root1, root2);
        }
    }
    
    if (numTrees != 1)
        printf("MST does not exist\n");

    printf("Sum of weights of spanning edges %d\n", MSTweight);

    /* free memory here */

    return 0;
}

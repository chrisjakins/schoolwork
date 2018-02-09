// Driver for CSE 2320 lab 3, fall 2017
// Batched retrieval operations on red-black tree
#include <stdlib.h>
#include <stdio.h>
#include "RB.h"

int main()
{
    int inserts,searchKeys,invSelectKeys,selectKeys;
    int i;
    Key insertKey;

    Key *searchKey,*invSelectKey,*selectKey;
    int *found,*rank4invSelectKey,*selectRank;

    STinit();  // Initialize red-black tree
    scanf("%d %d %d %d",&inserts,&searchKeys,&invSelectKeys,&selectKeys);
    searchKey=(Key*) malloc(searchKeys*sizeof(Key));
    found=(int*) malloc(searchKeys*sizeof(int));
    invSelectKey=(Key*) malloc(invSelectKeys*sizeof(Key));
    rank4invSelectKey=(int*) malloc(invSelectKeys*sizeof(int));
    selectRank=(int*) malloc(selectKeys*sizeof(int));
    selectKey=(Key*) malloc(selectKeys*sizeof(Key));

    if (!searchKey || !found || !invSelectKey || !rank4invSelectKey
       || !selectRank || !selectKey)
    {
        printf("malloc prob\n");
        exit(0);
    }

    for (i=0;i<inserts;i++)
    {
        scanf("%d",&insertKey);
        STinsert(insertKey);
    }
    verifyRBproperties();

    for (i=0;i<searchKeys;i++)
        scanf("%d",searchKey+i);
    STsearchBatch(searchKeys,searchKey,found);


    printf("search results\n");
    for (i=0;i<searchKeys;i++)
    {
        printf("%d ",searchKey[i]);
        if (found[i]==NULLitem)
            printf("not ");
        printf("found\n");
    }

    for (i=0;i<invSelectKeys;i++)
        scanf("%d",invSelectKey+i);

    STinvSelectBatch(invSelectKeys,invSelectKey,rank4invSelectKey);
    printf("key->rank results\n");

    for (i=0;i<invSelectKeys;i++)
        printf("%d %d\n",invSelectKey[i],rank4invSelectKey[i]);

    for (i=0;i<selectKeys;i++)
        scanf("%d",selectRank+i);

    STselectBatch(selectKeys,selectRank,selectKey);
    printf("rank->key results\n");

    for (i=0;i<selectKeys;i++)
        printf("%d %d\n",selectRank[i],selectKey[i]);

    free(searchKey);
    free(found);
    free(invSelectKey);
    free(rank4invSelectKey);
    free(selectRank);
    free(selectKey);

    return 0;
}

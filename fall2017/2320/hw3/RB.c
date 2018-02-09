// Bottom-up red-black tree implementation without deletions,
// so free() does not appear.

// July 22, 2016 - modified for CLRS, 3rd ed. insertion
/*
    CHRIS JAKINS
    TO COMPILE : gcc RB.c <main>
*/

#include <stdlib.h>
#include <stdio.h>
#include "RB.h"

link z,head;               // Pointers to sentinel and root
Item NULLitem=(-9999999);  // Data for sentinel

int trace=0;  // Controls trace output for insert

int traceBatch = 0;
int traceSeq = 0;

/*********************
    PRINTING
*********************/
void STprintBatch() {
    printf("Batched performed %d comparisons\n", traceBatch);
}

void STprintSeq() {
    printf("Unbatched performed %d comparisons\n", traceSeq);
}
/*******************
    END PRINTING
*******************/

int count1;

void STbatchR(int num, link h, Key * in, Item * out) {
    int found = 0;

    if (h->item == NULLitem) return;

    if (less(in[count1], h->item) && h->l != z) {
        STbatchR(num, h->l, in, out);
    }

    traceBatch++;

    if (less(in[count1], h->item)) {
        out[count1] = NULLitem;
        ++count1;
    }

    if (eq(in[count1], h->item)) {
        out[count1] = in[count1];
        found = 1;
        ++count1;

        if (h->r == z) return;
    }

    traceBatch++;

    if (!found && !less(h->item, in[count1])) {
        out[count1++] = NULLitem;
    }

    if (count1 == num - 1) return;
    if (less(h->item, in[count1]) && h->r != z) {
        STbatchR(num, h->r, in, out);
    }
    traceBatch++;
}

void STsearchBatch(int num, Key *in, Item *out) {
    traceBatch = 0;
    count1 = 0;

    STbatchR(num, head, in, out);
    int i;
    for (i = 0; i < num; i++) {
        out[i] = STsearch(in[i]);
    } 
    STprintBatch();
    STprintSeq();
}

int count = 0;
void STselectBatchR(int num, link h, Key * in, int * out) {
    traceBatch++;

    if (h->item == NULLitem) return;

    int r = h->l->N + 1;

    if (r > in[count])
        STselectBatchR(num, h->l, in, out);

    traceBatch++;

    if (r == in[count]) {
        out[count] = h->item;
        count++;
    } 

    traceBatch++;

    //printf("%d %d %d\n", r, h->item, count);
    
    if (r < in[count])
        STselectBatchR(num, h->r, in, out);

    if (count == num) return;
    traceBatch++;
}

void STselectBatch(int num, int *in, Item *out) {
    traceBatch = 0;

    STselectBatchR(num, head, in, out);
    STprintBatch();
    STprintSeq();
}

int count2;

void STinvBatchR(int num, int rank, link h, Key * in, int * out) {
    int found = 0;

    if (h->item == NULLitem) return;

    if (less(in[count2], h->item) && h->l != z) {
        STinvBatchR(num, rank, h->l, in, out);
    }

    traceBatch++;

    rank += h->l->N + 1;

    if (less(in[count2], h->item)) {
        out[count2] = NULLitem;
        ++count2;
    }

    traceBatch++;
    if (count2 == num) return;

    if (eq(in[count2], h->item)) {
        out[count2] = rank;
        found = 1;
        ++count2;

        if (h->r == z) return;
    }
    if (count2 == num) return;

    if (!found && !less(h->item, in[count2])) {
        out[count2++] = NULLitem;
    }

    if (count2 == num) return;
    if (less(h->item, in[count2]) && h->r != z) {
        STinvBatchR(num, rank, h->r, in, out);
    }

    traceBatch++;
}

void STinvSelectBatch(int num, Key *in, int *out) {
    traceBatch = 0;
    count2 = 0;

    STinvBatchR(num, 0, head, in, out);


    STprintBatch();
    STprintSeq();
}

link NEW(Item item, link l, link r, int N)
// Allocates and fills in a node
{
    link x = malloc(sizeof *x); 
    x->item = item;
    x->l = l;
    x->r = r;
    x->red = 1;
    x->N = N;
    return x;
}

void STinit()
{
    // Root/sentinel (head/z) is always black
    head = (z = NEW(NULLitem, 0, 0, 0));
    head->red=0;
}

Item searchR(link h, Key v)
// Recursive search for a key
{ 
    Key t = key(h->item);
    if (h == z)
        return NULLitem;

    traceSeq++;

    if (eq(v, t))
        return h->item;

    traceSeq++;

    if (less(v, t))
        return searchR(h->l, v);

    return searchR(h->r, v);
}

Item STsearch(Key v) 
{
    return searchR(head, v);
}

Item selectR(link h, int i)
// Returns the ith smallest key where i=1 returns the smallest
// key.  Thus, this is like flattening the tree inorder into an array
// and applying i as a subscript.
{ 
    int r = h->l->N+1;

    if (h == z)
    {
        printf("Impossible situation in selectR\n");
        STprintTree();
        exit(0);
    }

    traceSeq++;

    if (i==r)
        return h->item;

    traceSeq++;

    if (i<r)
        return selectR(h->l, i);

    return selectR(h->r, i-r);
}

Item STselect(int k)
{
    if (k<1 || k>head->N)
    {
        printf("Range error in STselect() k %d N %d\n",k,head->N);
        exit(0);
    }
    return selectR(head, k);
}

int invSelectR(link h, Key v)
// Inverse of selectR
{
    Key t = key(h->item);
    int work;

    if (h==z)
        return -1;  // v doesn't appear as a key

    traceSeq++;

    if (eq(v, t))
        return h->l->N+1;

    traceSeq++;

    if (less(v, t))
        return invSelectR(h->l,v);

    work=invSelectR(h->r,v);

    if (work==(-1))
        return -1;  // v doesn't appear as a key
    return 1 + h->l->N + work;
}

int STinvSelect(Key v)
{
    return invSelectR(head,v);
}

void fixN(link h)
// Fixes subtree size of h, assuming that subtrees have correct sizes
{
    h->N=h->l->N + h->r->N + 1;
}

link rotR(link h)
// Rotate right at h, i.e. flip edge between h & h->l
{
    link x = h->l;
    h->l = x->r;
    x->r = h;

    x->N = x->r->N;
    fixN(x->r);
    return x;
}

link rotL(link h)
// Rotate left at h, i.e. flip edge between h & h->r
{
    link x = h->r;
    h->r = x->l;
    x->l = h;

    x->N = x->l->N;
    fixN(x->l);
    return x;
}

void extendedTraceOn()
{
    trace=2;
}

void basicTraceOn()
{
    trace=1;
}

void traceOff()
{
    trace=0;
}

void tracePrint(char *s,link h)
{
    if (trace) {
        if (h==z)
            printf("%s at sentinel\n",s);
        else
            printf("%s at %d\n",s,key(h->item));
    }
}

link RBinsert(link h, Item item, int sw, int siblingRed, link hParent)
// CLRS, 3rd ed., RB tree insertion done recursively without parent pointers.
// Also includes tracing.  See 2320 notes.  BPW
// h is present node in search down tree.
// Returns root of modified subtree.
// item is the Item to be inserted.
// sw == 1 <=> h is to the right of its parent.
// siblingRed has color of h's sibling.
// hParent has h's parent to facilitate case 1 color flips.
{
    Key v = key(item);
    link before;  // Used to trigger printing of an intermediate tree

    tracePrint("Down",h);
    if (h == z)
        return NEW(item, z, z, 1);  // Attach red leaf

    if (eq(v, h->item))
        return h;
    else if (less(v, h->item)) {
        tracePrint("Insert left",h);
        before=h->l;
        h->l = RBinsert(h->l, item, 0, h->r->red, h); // Insert in left subtree

        if (trace==2 && before!=h->l)  // Has a rotation occurred?
            STprintTree();

        if (h->l->red) {
            if (h->red)
                if (sw)
                    if (siblingRed) {
                        tracePrint("Case ~1l",hParent);
                        hParent->red = 1;
                        hParent->l->red = 0;
                        hParent->r->red = 0;

                        if (trace==2)
                            STprintTree();
                    } else {
                        tracePrint("Case ~2",h);
                        h = rotR(h);  // Set up case ~3 after return
                    }
                else if (siblingRed) {
                    tracePrint("Case 1l",hParent);
                    hParent->red = 1;
                    hParent->l->red = 0;
                    hParent->r->red = 0;

                    if (trace==2)
                        STprintTree();
                }
                else
                    ;  // Future case 3
            else if (!h->r->red && h->l->l->red) {
                tracePrint("Case 3",h);
                h = rotR(h);
                h->red = 0;
                h->r->red = 1;
            }
        }
    } else {
        tracePrint("Insert right",h);
        before=h->r;
        h->r = RBinsert(h->r, item, 1, h->l->red, h); // Insert in right subtree
        if (trace==2 && before!=h->r)  // Has a rotation occurred?
            STprintTree();
        if (h->r->red) {
            if (h->red)
                if (!sw)
                    if (siblingRed) {
                        tracePrint("Case 1r",hParent);
                        hParent->red = 1;
                        hParent->l->red = 0;
                        hParent->r->red = 0;
                        if (trace==2)
                            STprintTree();
                    } else {
                        tracePrint("Case 2",h);
                        h = rotL(h);  // Set up case 3 after return
                    }
                else if (siblingRed) {
                    tracePrint("Case ~1r",hParent);
                    hParent->red = 1;
                    hParent->l->red = 0;
                    hParent->r->red = 0;
                    if (trace==2)
                        STprintTree();
                } else
                    ;  // Future case ~3
            else if (!h->l->red && h->r->r->red) {
                tracePrint("Case ~3",h);
                h = rotL(h);
                h->red = 0;
                h->l->red = 1;
            }
        }
    }
    fixN(h);
    tracePrint("Up",h);
    return h;
}

void STinsert(Item item)
{
    head = RBinsert(head, item, 0, 0, NULL);
    if (head->red)
        printf("red to black reset has occurred at root!!!\n");
    head->red = 0;
}

void checkRed(link h,int redParent)
// Verifies property 3 in notes
{
    if (redParent && h->red)
    {
        printf("Red property problem at %d\n",key(h->item));
        STprintTree();
        exit(0);
    }
    if (h==z)
        return;
    checkRed(h->l,h->red);
    checkRed(h->r,h->red);
}

int leftPathBlackHeight(link h)
// Counts black nodes on path to the minimum
{
    if (h==z)
        return !(h->red);
    return leftPathBlackHeight(h->l) + !(h->red);
}

void checkBlack(link h,int blackCount)
// Checks that all paths downward from a node have the same
// number of black nodes
{
    if (h==z) {
        if (blackCount==!(h->red))
            return;
        else {
            printf("Black height problem!\n");
            STprintTree();
            exit(0);
        }
    }
    if (h->red)
    {
        checkBlack(h->l,blackCount);
        checkBlack(h->r,blackCount);
    } else {
        checkBlack(h->l,blackCount-1);
        checkBlack(h->r,blackCount-1);
    }
}

Key lastInorder;    // Saves key from last node processed

void checkInorder(link h)
// Checks that inorder yields keys in ascending order
{
    if (h==z)
        return;

    checkInorder(h->l);
    if (!less(lastInorder,h->item))
    {
        printf("Inorder error\n");
        STprintTree();
        exit(0);
    }
    lastInorder=key(h->item);
    checkInorder(h->r);
}

int checkN(link h)
// Verifies that subtree sizes are correct
{
    int work;

    if (h==z)
    {
        if (h->N!=0)
        {
            printf("Count for sentinel is %d, should be 0\n",h->N);
            STprintTree();
            exit(0);
        }
    } else {
        work=checkN(h->l) + checkN(h->r) + 1;

        if (h->N!=work) {
            printf("Count for key %d is %d, should be %d\n",key(h->item),h->N,work);
            STprintTree();
            exit(0);
        }
    }
    return h->N;
}

void verifyRBproperties()
// Checks all required properties.
// If a fatal problem is found, the tree is printed before exit(0)
{
    int lpbHeight;

    if (head->red)
        printf("Root is not black!\n");
    if (z->red)
        printf("Sentinel is not black!\n");
    lastInorder=(-99999999);
    checkInorder(head);
    checkRed(head,0);
    lpbHeight=leftPathBlackHeight(head);
    checkBlack(head,lpbHeight);
    checkN(head);
}

void printTree(link h,int depth,int bhAbove)
{
    int i,bhBelow;

    if (h==z) {
        if (bhAbove!=1) {
            for (i=0;i<depth;i++)
                printf("     ");
        printf("Black-height issue detected at sentinel\n");
        }

        return;
    }

    if ((h->red))
        bhBelow=bhAbove;
    else
        bhBelow=bhAbove-1;
    printTree(h->r,depth+1,bhBelow);
    for (i=0;i<depth;i++)
        printf("     ");
    if (h->red)
        printf("[%d %d %d]\n",key(h->item),h->N,bhBelow);
    else
        printf("(%d %d %d)\n",key(h->item),h->N,bhBelow);
    printTree(h->l,depth+1,bhBelow);
}

void STprintTree()
{
    printTree(head,0,leftPathBlackHeight(head));
}

void fixAllN(link h)
// Recomputes subtree sizes for an otherwise correct tree
{
    if (h->l)
        fixAllN(h->l);
    else
        h->l=z;
    if (h->r)
        fixAllN(h->r);
    else
        h->r=z;
    fixN(h);
}

void cleanUpUnbalanced(link h)
// Checks a tree constructed elsewhere (like RB.loadAndGo.c)
{
    fixAllN(h);
    head=h;
    z->red=0;
    verifyRBproperties();
}

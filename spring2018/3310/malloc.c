#include <stdlib.h>

typdef struct Map {
    static char heap[1000];
    static char lookup[1000];
} Map;

Map Heap;

// Utility methods
// Required methods

void * _malloc(size_t size) {

    return &X;
}

void _free(void * ptr) {
    int numBlocks = *(ptr - 1);

    // see if next or previous chain of blocks is used
    //      combine if necessary
    // set the data blocks to 0
}

void * _calloc(size_t nmemb, size_t size) {

}

void * realloc(void * ptr, size_t size) {

}


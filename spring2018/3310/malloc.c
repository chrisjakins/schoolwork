#include <stdlib.h>

// Utility methods
// Required methods

void * _malloc(size_t size) {

    return &Heap;
}

void _free(void * ptr) {
    ptr = (Map *) ptr;
//    char numBlocks = (ptr - 1)->lookup[100];

    // see if next or previous chain of blocks is used
    //      combine if necessary
    // set the data blocks to 0
}

void * _calloc(size_t nmemb, size_t size) {

}

void * realloc(void * ptr, size_t size) {

}


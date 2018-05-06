#include <stdlib.h>
#include <string.h> // for memset

char heap[10000000];

typedef struct list {
    int size;
    int free;
    struct list * next;
} List;


List * freeBlocks = (void *) heap;

// Utility methods
void init() {
    freeBlocks->size = 10000000 - sizeof(List);
    freeBlocks->free = 1;
    freeBlocks->next = NULL;
}

void split(List * block, int size) {
    List * new = block + size + sizeof(List);
    new->size = block->size - size - sizeof(List);
    new->free = 1;
    new->next = block->next;

    block->size = size;
    block->free = 0;
    block->next = new;
}

void merge() {
    List * curr, * prev;
    curr = freeBlocks;
    while (curr && curr->next) {
        if (curr->free && curr->next->free) {
            curr->size += curr->next->size + sizeof(List);
            curr->next = curr->next->next;
        }
        prev = curr;
        curr = curr->next;
    }
}

// Required methods

void * _malloc(int numBytes) {
    List * curr, * prev;
    void * blockGiven;
    if (!(freeBlocks->size)) {
        init();
    }
    curr = freeBlocks;
    while ((curr->size < numBytes || curr->free == 0) && curr->next) {
        prev = curr;
        curr = curr->next;
    }

    if (curr->size == numBytes) {

        curr->free = 0;
        blockGiven = (void *) ++curr;
        return blockGiven;

    } else if (curr->size > numBytes + sizeof(List)) {

        split(curr, numBytes);
        blockGiven = (void *) ++curr;
        return blockGiven;

    } else {

        blockGiven = NULL;
        return blockGiven;

    }
}

void _free(void * ptr) {
    if ((void *) heap <= ptr && ptr <= (void * ) (heap + 10000000)) {
        List * curr = ptr;
        curr--;
        curr->free = 1;
        merge();
    }
}

// same as malloc
// but with memsets
void * _calloc(size_t nmemb, int size) {
    List * curr, * prev;
    void * result;
    if (!(freeBlocks->size)) {
        init();
    }
    curr = freeBlocks;
    while ((curr->size < size || curr->free == 0) && curr->next) {
        prev = curr;
        curr = curr->next;
    }

    if (curr->size == size) {

        result = (void *) ++curr;
        memset(result, 0, size);
        return result;

    } else if (curr->size > size + sizeof(List)) {

        split(curr, size);
        result = (void *) ++curr;
        memset(result, 0, size);
        return result;

    } else {

        result = NULL;
        return result;

    }
}

void * realloc(void * ptr, size_t size) {
    List * curr, * prev;
    void * result;
    if (!(freeBlocks->size)) {
        init();
    }
    curr = freeBlocks;
    while ((curr->size < size || curr->free == 0) && curr->next) {
        prev = curr;
        curr = curr->next;
    }

    curr->size = size;
    result = (void *) ++curr;
    return result;
}


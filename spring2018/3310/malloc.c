#include <stdlib.h>
#include <string.h>

char heap[10000000];

typedef struct list {
    int size;
    int free;
    struct list * next;
} List;


List * freeList = (void *) heap;

// Utility methods
void init() {
    freeList->size = 10000000 - sizeof(List);
    freeList->free = 1;
    freeList->next = NULL;
}

void split(List * fitting_slot, int size) {
    List * new = ((void *) fitting_slot + size + sizeof(List));
    new->size = (fitting_slot->size) - size - sizeof(List);
    new->free = 1;
    new->next = fitting_slot->next;
    fitting_slot->size = size;
    fitting_slot->free = 0;
    fitting_slot->next = new;
}

void merge() {
    List * curr, * prev;
    curr = freeList;
    while (curr->next) {
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
    void * result;
    if (!(freeList->size)) {
        init();
    }
    curr = freeList;
    while ((curr->size < numBytes || curr->free == 0) && curr->next) {
        prev = curr;
        curr = curr->next;
    }

    if (curr->size == numBytes) {

        curr->free = 0;
        result = (void *) ++curr;
        return result;

    } else if (curr->size > numBytes + sizeof(List)) {

        split(curr, numBytes);
        result = (void *) ++curr;
        return result;

    } else {

        result = NULL;
        return result;

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
    if (!(freeList->size)) {
        init();
    }
    curr = freeList;
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
    if (!(freeList->size)) {
        init();
    }
    curr = freeList;
    while ((curr->size < size || curr->free == 0) && curr->next) {
        prev = curr;
        curr = curr->next;
    }

    curr->size = size;
    result = (void *) ++curr;
    return result;
}


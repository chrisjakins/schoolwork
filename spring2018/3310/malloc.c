#include <stdlib.h>

static char X[1000];

void * _malloc(size_t size) {

    return &X;
}

void _free(void * ptr) {

}

void * _calloc(size_t nmemb, size_t size) {

}

void * realloc(void * ptr, size_t size) {

}

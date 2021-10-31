#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BinaryHeap
{
    int * tab;
    int nbElements;
    int size;
} BinaryHeap_t;

#endif
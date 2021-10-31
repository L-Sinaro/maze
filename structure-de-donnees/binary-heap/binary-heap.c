#include "binary-heap.h"




// Post-conditions : check if heap.tab has been alloc
BinaryHeap_t initBinaryHeap(int size)
{
    BinaryHeap_t heap;
    heap.tab = malloc(size * sizeof(int));
    heap.nbElements = 0;
    heap.size = size;

    return heap;
}

void freeBinaryHeap(BinaryHeap_t heap)
{
    if (heap.tab)
    {
        free(heap.tab);
    }
}


int parent(int i)
{
    return (int) (i+1)/2 - 1;
}

int left(int i)
{
    return 2*i + 1;
}
 
int right(int i)
{
    return 2*i + 2;
}

void swap(int *i, int *j)
{
    int tmp;
    tmp = *i;
    *i = *j;
    *j = tmp;
}


void percoler(BinaryHeap_t * heap)
{
    int i = heap->nbElements-1;
    while (heap->tab[i] < heap->tab[parent(i)])
    {
        swap(&heap->tab[i], &heap->tab[parent(i)]);
        i = parent(i);
    }
}

bool insert(BinaryHeap_t * heap, int x)
{
    bool success = false;
    if (heap->nbElements < heap->size)
    {
        heap->tab[heap->nbElements] = x;
        heap->nbElements++;
        percoler(heap);
        success = true;
    }

    return success;
}



void minHeapify(BinaryHeap_t * heap, int i)
{
    int l, r;
    int smallest = i;

    do
    {
        i = smallest;
        l = left(i);
        r = right(i);
        
        if (l < heap->nbElements && heap->tab[l] < heap->tab[i])
        {
            smallest = l;
        }
        else
        {
            smallest = i;
        }
        if (r < heap->nbElements && heap->tab[r] < heap->tab[smallest])
        {
            smallest = r;
        }
        if (smallest != i)
        {
            swap(&heap->tab[i], &heap->tab[smallest]);
        }
    } while (smallest != i);
}


int pop(BinaryHeap_t * heap)
{
    if (heap->nbElements > 0)
    {
        swap(&(heap->tab[0]), &(heap->tab[heap->nbElements-1]));
        heap->nbElements--;
        minHeapify(heap, 0);
    }

    return heap->tab[heap->nbElements];
}


BinaryHeap_t buildMinHeap(int * tab, int size)
{
    BinaryHeap_t heap;
    int i;
    heap = initBinaryHeap(size);
    if (heap.tab)
    {
        memcpy(heap.tab, tab, size*sizeof(tab[0]));
        heap.size = size;
        heap.nbElements = size;
        
        for (i= size/2 -1; i>=0; i--)
        {
            minHeapify(&heap, i);
        }
    }
    
    return heap;
}


void heapsort(int *tab, int size)
{
    BinaryHeap_t heap;
    int i;

    heap = buildMinHeap(tab, size);
    for (int i=0; i<size; i++)
    {
        tab[i] = pop(&heap);
    }

    memcpy(tab, heap.tab, size);
    freeBinaryHeap(heap);
}





void printTab(int * tab, int size)
{
    int i;

    for(i=0; i< size; i++)
    {
        printf("tab[%d] : %d\n", i, tab[i]);
    }
    printf("------------\n");
}


void printBinaryHeap(BinaryHeap_t heap)
{
    printTab(heap.tab, heap.nbElements);
}



int main()
{
    BinaryHeap_t heap;
    heap = initBinaryHeap(10);

    int tab[] = {4, 5, 2, 9, 3, 8};
    int size = 6;

    // If the malloc has succeed
    if (heap.tab)
    {
        // insert(&heap, 10);
        // insert(&heap, 12);
        // insert(&heap, 2);
        // insert(&heap, 7);
        // insert(&heap, 8);
        // printBinaryHeap(heap);

        printTab(tab, size);
        heap = buildMinHeap(tab, size);

        for (int i=0; i<size; i++)
        {
            tab[i] = pop(&heap);
        }
        printTab(tab, size);

    }

    freeBinaryHeap(heap);
    return 0;
}
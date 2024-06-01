#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ELEMENTS   256

typedef struct _Heap {
  int elements[MAX_ELEMENTS];
  int size;
} Heap;

Heap *createHeap() {
  Heap *heap = malloc(sizeof(Heap));
  heap->size = 0;

  return heap;
}

void swap(int *a, int *b) {
  int tmp;

  tmp = *a;
  *a = *b;
  *b = tmp;
}

int insertHeap(Heap *heap, int key) {
  int i;

  if (heap->size >= MAX_ELEMENTS) {
    fprintf(stderr, "Overflow: Could not insertKey\n");
    return -1;
  }

  heap->size++;
  i = heap->size - 1;
  
  heap->elements[i] = key;
  while (i != 0 && key > heap->elements[i/2]) {
    swap(&heap->elements[i], &heap->elements[i/2]);
    i /= 2;
  }

  return 0;

}

void heapify(Heap *heap, int idx) {
  int l_child = idx * 2;
  int r_child = idx * 2 + 1;
  int max = idx;

  if (l_child < heap->size && heap->elements[l_child] > heap->elements[max]) 
    max= l_child;

  if (r_child < heap->size && heap->elements[r_child] > heap->elements[max])
    max = r_child;

  if (idx != max) {
    swap(&heap->elements[max], &heap->elements[idx]);
    heapify(heap, max);
  }
}

int deleteHeap(Heap *heap) {
  if (heap->size <= 0) {
    fprintf(stderr, "No data in the heap\n");
    return -1;
  } 

  if (heap->size == 1) {
    heap->size--;
    return heap->elements[0];
  }

  int root = heap->elements[0];
  heap->elements[0] = heap->elements[heap->size - 1];
  heap->size--;
  heapify(heap, 0);

  return root;
}

void display_heap(Heap heap) {
  int i = 0, j = 1;
  int breakline = 0;

  for (i=0; i<heap.size; i++) {
    printf("%d ", heap.elements[i]);

    if (i == breakline) {
      printf("\n");
      breakline = breakline + pow(2, j++);
    }
   }
}

void destroyHeap(Heap *heap) {
  if (heap != NULL)
    free(heap);
}

int main(int argc, char **argv)
{
  printf("Hello World\n");

  Heap *testHeap = createHeap();

  insertHeap(testHeap, 1);
  insertHeap(testHeap, 2);
  insertHeap(testHeap, 3);
  insertHeap(testHeap, 5);
  insertHeap(testHeap, 6);
  insertHeap(testHeap, 8);
  insertHeap(testHeap, 9);

  display_heap(*testHeap);

  printf("Delete Heap: %d\n", deleteHeap(testHeap));
  printf("Delete Heap: %d\n", deleteHeap(testHeap));
  printf("Delete Heap: %d\n", deleteHeap(testHeap));

  display_heap(*testHeap);

  destroyHeap(testHeap);

  return 0;
}

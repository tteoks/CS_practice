#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ELEMENTS  256

typedef struct _Item {
  int value;
  int prirority;
} Item;

typedef struct _PriorityHeap {
  Item elements[MAX_ELEMENTS];
  int size;
} PrirorityHeap;

PrirorityHeap *createHeap() {
  PrirorityHeap *heap = malloc(sizeof(PrirorityHeap));
  heap->size = 0;

  return heap;
}

void swapItem(Item *a, Item *b) {
  Item tmp;
  
  tmp = *a;
  *a = *b;
  *b = tmp;
}


int insertHeap(PrirorityHeap *heap, int key, int prirority) {
  int i;

  if (heap->size >= MAX_ELEMENTS) {
    fprintf(stderr, "Overflow: Could not insert Key\n");
    return -1;
  }

  heap->size++;
  i = heap->size - 1;

  heap->elements[i].value  = key;
  heap->elements[i].prirority  = prirority;
  while(i != 0 && prirority > heap->elements[i/2].prirority) {
    swapItem(&heap->elements[i], &heap->elements[i/2]);
    i /= 2;
  }

  return 0;
}

void heapify(PrirorityHeap *heap, int idx) {
  int l_child = idx * 2;
  int r_child = idx * 2 + 1;
  int max = idx;

  if (l_child < heap->size && heap->elements[l_child].prirority > heap->elements[max].prirority)
    max = l_child;
  if (r_child < heap->size && heap->elements[r_child].prirority > heap->elements[max].prirority)
    max = r_child;

  if (idx != max) {
    swapItem(&heap->elements[max], &heap->elements[idx]);
    heapify(heap, max);
  }
}

Item deleteHeap(PrirorityHeap *heap) {
  Item root;

  if (heap->size <= 0)
    return root;

  if (heap->size == 1) {
    heap->size--;
    return heap->elements[0];
  }
  
  root = heap->elements[0];
  heap->elements[0] = heap->elements[heap->size - 1];
  heap->size--;

  heapify(heap, 0);

  return root;
}

void display_heap(PrirorityHeap heap) {
  int i = 0, j = 1;
  int breakline = 0;
  
  printf("ROOT NODE INFO\n");
  printf("PRIRORITY: %d\n", heap.elements[0].prirority);
  printf("VALUE: %d\n", heap.elements[0].value);


  for (i=0; i<heap.size; i++) {
    printf("%d(%d) ", heap.elements[i].prirority, heap.elements[i].value);

    if (i == breakline) {
      printf("\n");
      breakline = breakline + pow(2, j++);
    }
  }
}

void destoryHeap(PrirorityHeap *heap) {
  if (heap != NULL)
    free(heap);
}

int main(int argc, char **argv)
{
  printf("Hello world\n");

  PrirorityHeap *testHeap = createHeap();

  insertHeap(testHeap, 1, 1);
  insertHeap(testHeap, 1, 2);
  insertHeap(testHeap, 1, 3);
  insertHeap(testHeap, 9, 5);
  insertHeap(testHeap, 9, 6);
  insertHeap(testHeap, 6, 8);
  insertHeap(testHeap, 5, 9);

  display_heap(*testHeap);
  printf("\n\n");

  Item item;
  item = deleteHeap(testHeap);
  printf("Delete Heap: %d(%d)\n", item.prirority, item.value);
  item = deleteHeap(testHeap);
  printf("Delete Heap: %d(%d)\n", item.prirority, item.value);
  item = deleteHeap(testHeap);
  printf("Delete Heap: %d(%d)\n\n", item.prirority, item.value);

  display_heap(*testHeap);
  printf("\n\n");

  destoryHeap(testHeap);

  return 0;
}

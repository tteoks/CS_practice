#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _radix_queue {
  int bucket[128];
  int radix;
  int count;
} radix_queue;


void display_array(int *array, int len); 
void display_heap(int *array, int len); 
void switch_value(int *elem1, int *elem2); 
void heapify(int *array, int len); 
void radix_enqueue(radix_queue *queue, int value); 
int radix_value(int value, int radix);
int flush_radix(radix_queue *queue, int *array);

void bubble_sort(int *array, int len); 
void select_sort(int *array, int len); 
void insert_sort(int *array, int len); 
void quick_sort(int *array, int left, int right); 
void merge_sort(int *array, int left, int right); 
void heap_sort(int *array, int len);
void shell_sort(int *array, int len); 
void radix_sort(int *array, int len); 

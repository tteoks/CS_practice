#include "sort_lib.h"

void display_array(int *array, int len) {
  int i = 0;

  for (i = 0; i < len; i++) {
    printf("[%d] %d\n", i, array[i]);
  }
  printf("\n");
}

void switch_value(int *elem1, int *elem2) {
  int tmp;

  tmp = *elem1;
  *elem1 = *elem2;
  *elem2 = tmp;
}

void bubble_sort(int *array, int len) {
  int i, j, tmp;

  for (i = len; i > -1; i--) {
    for (j = 0; j < i - 1; j++) {
      if (array[j] > array[j + 1]) {
        switch_value(&array[j], &array[j + 1]);
      }
    }
  }
}

void select_sort(int *array, int len) {
  int i, j, min, min_idx;

  for (i = 0; i < len; i++) {
    min = array[i];
    min_idx = i;
    for (j = i; j < len; j++) {
      if (array[j] < min) {
        min = array[j];
        min_idx = j;
      }
    }
    switch_value(&array[min_idx], &array[i]);
  }
}


void insert_sort(int *array, int len) {
  int i, j, key;

  if (len == 2) {
    bubble_sort(array, len);
    return;
  }

  for (i = 1; i < len; i++) {
    key = array[i];
    for (j = i; j > 0; j--) {
      if (key < array[j - 1]) 
        array[j] = array[j - 1];
      else 
        break;
    }
    array[j] = key;
  }
}

void quick_sort(int *array, int left, int right) {
  int pivot = left;
  int i = left + 1, j = right;

  if (right <= left)
    return;

  while (i <= j) {
    while (array[i] < array[pivot] && i <= j)  i++;
    while (array[j] > array[pivot] && j >= i)  j--;

    if (i <= j) 
      switch_value(&array[i++], &array[j--]);
  }
  switch_value(&array[j], &array[pivot]);

  quick_sort(array, left, j - 1);
  quick_sort(array, j + 1, right);
}

void merge_for_merge_sort(int *array, int left, int mid, int right) {
  int i, j, k;
  int sorted_array[1024] = {0, };

  k = left;  i = left; j = mid + 1;

  while (i <= mid && j <= right) {
    if (array[i] <= array[j]) {
      sorted_array[k++] = array[i++];
    }
    else {
      sorted_array[k++] = array[j++];
    }
  }

  if (i <= mid) {
    for (; i <= mid; i++)  {
      sorted_array[k++] = array[i];
    }
  } else {
    for (; j <= right; j++) {
      sorted_array[k++] = array[j];
    }
  }

  for (i = left; i <= right; i++) 
    array[i] = sorted_array[i];
}

void merge_sort(int *array, int left, int right) {
  int mid;

  if (left >= right)
    return;

  mid = (left + right) / 2;

  merge_sort(array, left, mid);
  merge_sort(array, mid + 1, right); 
  merge_for_merge_sort(array, left, mid, right);
}

void display_heap(int *array, int len) {
  int i, br, column;

  br = 1;
  column = 1;
  for (i = 0; i < len; i++) {
    if (br == i) {
      printf("\n");
      br += pow(2, column);
      column++;
    }
    printf("%d ", array[i]);
  }

  printf("\n");
}

void heapify(int *array, int len) {
  int i, child, parent;

  for (i = 0; i < len ; i++) {
    child = i;
    while (child != 0) {
      parent = child / 2;
      if (array[child] < array[parent])
        switch_value(&array[child], &array[parent]);
      child = parent;
    }
  }
}

void heap_sort(int *array, int len)
{
  int heap_array[1024];
  int *heap_ptr;
  int i;

  heap_ptr = heap_array;
  for (i = 0; i < len; i++)
    heap_array[i] = array[i];

  for (i = 0; i < len; i++) {
    heapify(heap_ptr, len - i);
    array[i] = *heap_ptr++;
  }
}

void insert_sort_with_gap(int *array, int len, int gap) {
  int i, j, key;

  for (i = gap; i < len; i = i + gap) {
    key = array[i];
    for (j = i; j > 0; j = j - gap) {
      if (key < array[j - gap])
        array[j] = array[j - gap];
      else
        break;
    }
    array[j] = key;
  }
}

void shell_sort(int *array, int len) {
  int gap = len / 2;

  while (gap != 0) {
    if (gap % 2 == 0)
      gap++;

    insert_sort_with_gap(array, len, gap);

    if (gap == 1)
      return ;

    gap /= 2;
  }
}

int radix_value(int value, int radix) {
  int tmp;

  tmp = value / pow(10, radix);
  return tmp % 10;
}

void radix_enqueue(radix_queue *queue, int value) {
  int count = queue->count;
  queue->bucket[count] = value;
  queue->count++;
}

int flush_radix(radix_queue *queue, int *array) {
  int i, cnt=0, count = queue->count;

  for (i = 0; i < count; i++) {
    *array = queue->bucket[i];
    array++;
    cnt++;
  }

  queue->count = 0;

  return cnt;
}

void radix_sort(int *array, int len) {
  radix_queue queue[10];
  int i, j, rc, tmp, round = 0;
  int loop = 3;
  int *pos;

  for (i = 0; i < 10; i++) {
    queue[i].radix = i;
    queue[i].count = 0;
  }

  for (j = 0; j < loop; j++) {
    for (i = 0;i < len; i++) {
      switch (radix_value(array[i], round)) {
        case 0:
          radix_enqueue(&queue[0], array[i]);
          break;
        case 1:
          radix_enqueue(&queue[1], array[i]);
          break;
        case 2:
          radix_enqueue(&queue[2], array[i]);
          break;
        case 3:
          radix_enqueue(&queue[3], array[i]);
          break;
        case 4:
          radix_enqueue(&queue[4], array[i]);
          break;
        case 5:
          radix_enqueue(&queue[5], array[i]);
          break;
        case 6:
          radix_enqueue(&queue[6], array[i]);
          break;
        case 7:
          radix_enqueue(&queue[7], array[i]);
          break;
        case 8:
          radix_enqueue(&queue[8], array[i]);
          break;
        case 9:
          radix_enqueue(&queue[9], array[i]);
          break;
      }
    }

    pos = array;
    for (i = 0; i < 10; i++) {
      rc = flush_radix(&queue[i], pos);
      pos += rc;
    }
    round++;
  }

}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

enum RETURN_CODE{
  RET_OK = 0,
  RET_FAIL,
};

void MEM_EQUAL(void *a, void *b, size_t n);

void check_sort_perf_with_idx(void (*sort_func)(int *, int, int), \
    int *array, int first, int last, int *correct_map);

void check_sort_perf_with_len(void (*sort_func)(int *, int), \
    int *array, int len, int *correct_map);


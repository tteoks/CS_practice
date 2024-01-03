#include "sort_lib.h"
#include "utils.h"

 // #define NUM_ARRAY    5000

typedef struct _sort_func_info {
  char name[32];
  void *func;
} sort_func_info;

int compare(const void *a, const void *b) {
  if (*(int*)a > *(int*)b)
    return 1;
  else if (*(int*)a < *(int*)b)
    return -1;
  else
    return 0;
}

void all_sort_test() {
  int test_array[10] = {3, 1, 2, 5, 7, 9, 3, 4, 5, 10};
  display_array(test_array, 10);

  // printf("### Insert Sort ###\n");
  // bubble_sort(test_array, 10);

  // printf("### Insert Sort ###\n");
  // select_sort(test_array, 10);

  // printf("### Insert Sort ###\n");
  // insert_sort(test_array, 10);

  // printf("### Quick Sort ###\n");
  // quick_sort(test_array, 0, 9);

  printf("### Merge Sort ###\n");
  merge_sort(test_array, 0, 9);

  // printf("### Insert Sort ###\n");
  // heap_sort(test_array, 10);

  // printf("### Shell Sort ###\n");
  // shell_sort(test_array, 10);

  // radix_sort(test_array, 10);
  display_array(test_array, 10);
}

int *make_correct_sort_map(int *array, int len) {
  int *correct_map = NULL;

  correct_map = malloc(sizeof(int) * len);
  memset(correct_map, 0x00, sizeof(int) * len);
  memcpy(correct_map, array, sizeof(int)* len);
  qsort(correct_map, len, sizeof(int), compare); 

  return correct_map;

}

void check_perf_sort_with_len(int *array, int len) {
  int i = 0;
  int *cpy_array;
  int *correct_map;
  int sort_func_cnt = 0;

  sort_func_info sort_func[6] = {
    {"Bubble Sort", bubble_sort}, 
    {"Select Sort", select_sort},
    {"Insert Sort", insert_sort}, 
    {"Heap Sort", heap_sort},
    {"Shell Sort", shell_sort}, 
    {"Radix Sort", radix_sort}
  };

  sort_func_cnt = sizeof(sort_func) / sizeof(sort_func_info);

  correct_map = make_correct_sort_map(array, len);
  cpy_array = malloc(sizeof(int) * len);

  for (i = 0; i < sort_func_cnt; i++) {
    memset(cpy_array, 0x00, sizeof(int) * len);
    memcpy(cpy_array, array, sizeof(int)* len);

    printf("FUNC: %s\n", sort_func[i].name);
    check_sort_perf_with_len(sort_func[i].func, cpy_array, len, correct_map);
    printf("\n");
  }
  free(cpy_array);
  free(correct_map);
}

void check_perf_sort_with_idx(int *array, int first, int last) {
  int i = 0;
  int *cpy_array;
  int *correct_map;
  int sort_func_cnt = 0;
  int len = last - first + 1;

  sort_func_info sort_func[2] = {
    {"Quick Sort", quick_sort},
    {"Merge Sort", merge_sort}, 
  };
  sort_func_cnt = sizeof(sort_func) / sizeof(sort_func_info);

  correct_map = make_correct_sort_map(array, len);
  cpy_array = malloc(sizeof(int) * len);

  for (i = 0; i < sort_func_cnt; i++) {
    memset(cpy_array, 0x00, sizeof(int) * len);
    memcpy(cpy_array, array, sizeof(int)* len);

    printf("FUNC: %s\n", sort_func[i].name);
    check_sort_perf_with_idx(sort_func[i].func, cpy_array, first, last, correct_map);
    printf("\n");
  }

  free(cpy_array);
  free(correct_map);
}


void all_check_perf_sort(int *array, int first, int last) {
  int len = last - first + 1;

  check_perf_sort_with_len(array, len);
  check_perf_sort_with_idx(array, first, last);
}

void set_random_value(int *array, int array_len) {
  int i;
  
  for (i = 0; i < array_len; i++) {
    array[i] = rand() % NUM_ARRAY;
  }
}

int main(int argc, char **argv)
{
  int test_array[NUM_ARRAY] = {0, };
  int i = 0;

  // all_sort_test();

  printf("Hello World\n");
  set_random_value(test_array, NUM_ARRAY);

  all_check_perf_sort(test_array, 0, NUM_ARRAY - 1);

  return 0;
}

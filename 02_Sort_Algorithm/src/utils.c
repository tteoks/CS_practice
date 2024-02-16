#include "utils.h"
#include "sort_lib.h"

int MEM_EQAUL(void *a, void *b, size_t n) {
  int ret;

  ret = memcmp(a, b, n);

  if (ret == 0) {
    printf("[SUCCESS] Equal\n");
    return RET_OK;
  } else {
    printf("[FAIL] Not Equal\n");
    printf("%x != %x\n", (int*)(a+ret) , (int*)(b+ret));
    return RET_FAIL;
  }
}

void check_sort_perf_with_len(void (*sort_func)(int *, int), 
    int *array, int len, int *correct_map) {
  double start, end;

  if (sort_func == NULL) {
    printf("Invalid arguments in check_sort_perf function!!!\n");
    printf("\t No callback func\n");

    return ;
  }
  start = ((double) clock() / CLOCKS_PER_SEC);
  sort_func(array, len);
  end = ((double) clock() / CLOCKS_PER_SEC);
  if (MEM_EQAUL(array, correct_map, len * sizeof(int)) == RET_FAIL) {
    printf("## Correct map\n");
    display_array(correct_map, len);

    printf("## Result\n");
    display_array(array, len);
    printf("\n");
  }

  printf("End of func: %f\n", (float)(end - start));
}

void check_sort_perf_with_idx(void (*sort_func)(int *, int, int), 
    int *array, int first, int last, int *correct_map) {
  double start, end;
  int len = last - first + 1;

  if (sort_func == NULL) {
    printf("Invalid arguments in check_sort_perf function!!!\n");
    printf("\t No callback func\n");
    return ;
  }
  start = ((double) clock() / CLOCKS_PER_SEC);
  sort_func(array, first, last);
  end = ((double) clock() / CLOCKS_PER_SEC);
  if (MEM_EQAUL(array, correct_map, len * sizeof(int)) == RET_FAIL) {
    printf("## Correct map\n");
    display_array(correct_map, len);

    printf("## Result\n");
    display_array(array, len);
    printf("\n");
  }

  printf("End of func: %f\n", (float)(end - start));
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM_ELEMENTS    1000000

int comp(const void *a, const void *b) {
    if (*(int*)a > *(int*)b) {
        return 1;
    } else if (*(int*)a < *(int*)b) {
        return -1;
    } else {
        return 0;
    }
}

void copy_arr(int *src_arr, int *dst_arr, int arr_num) {
    int i;

    for (i=0; i<arr_num; i++) {
        dst_arr[i] = src_arr[i];
    }
}

void display_arr(int *arr, int arr_num) {
    int i;

    for (i=0; i<arr_num; i++) {
        if (i==0) {
            printf("%d", i);
        } else {
            printf("\t%d", i);
        }
    }

    printf("\n");
    for (i = 0; i < arr_num; i++)
    {
        if (i == 0) {
            printf("%d", arr[i]);
        }
        else {
            printf("\t%d", arr[i]);
        }
    }
    printf("\n");
}

void generate_integers(int *arr, int arr_num, int max) {
    int i;
    srand(time(NULL));
    for (i=0; i<arr_num; i++) {
        arr[i] = rand() % (max + 1);
    }
}

int sequential_search(int *arr, int arr_num, int search) {
    int i;

    for (i=0; i<arr_num; i++) {
        if (arr[i] == search) 
            return i;
    }

    return -1;
}

// 재귀 함수 활용
/*
int binary_search(int *ordered_arr, int start, int end, int search) {
    int mid = (start + end) / 2;

    printf("START: %d / MID: %d / END: %d\n", start, mid, end);

    if (start >= end) 
        return -1;

    if (ordered_arr[mid] == search)
        return mid;

    if (ordered_arr[mid] < search) {
        return binary_search(ordered_arr, mid + 1, end, search);
    } else if (ordered_arr[mid] > search) {
        return binary_search(ordered_arr, start, mid - 1, search);
    }
}
*/

// While 문을 활용
int binary_search(int *ordered_arr, int arr_num, int search) {
    int start = 0, end = arr_num - 1;
    int mid = 0;

    while (start <= end) {
        mid = (start + end) / 2;
        if (ordered_arr[mid] == search)
            return mid;
        
        if (ordered_arr[mid] < search) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    return -1;
}

void perf_search_func(int *arr, int arr_num, int search, int (*func)(int *,int,int)) {
    double start, end;
    int rc = 0;

    if (func == NULL) {
        printf("Invalid arugments..\n");
        printf("There is no callback funtion!\n");
        return;
    }

    start = ((double)clock() / CLOCKS_PER_SEC);
    rc = func(arr, arr_num, search);
    end = ((double)clock() / CLOCKS_PER_SEC);

    // display_arr(arr, arr_num);
    if (rc != -1 && arr[rc] == search) {
        printf("[SUCC] Success to find: %d\n", arr[rc]);
    } else {
        printf("[FAIL] Failed to find: %d\n", rc);
    }

    printf("End of func: %lf\n", end - start);
}

int binary_search_tree() {
    // TODO: Implement after study tree data structure
    return -1;
}

int main(int argc, char **argv)
{
    int test_data[MAX_NUM_ELEMENTS] = {0, };
    int ordered_data[MAX_NUM_ELEMENTS] = {0, };
    int search_data = rand()%MAX_NUM_ELEMENTS;

    printf("Hello World\n");
    printf("Number of elements: %d\n", MAX_NUM_ELEMENTS);
    printf("Search data: %d\n\n", search_data);

    generate_integers(test_data, MAX_NUM_ELEMENTS, MAX_NUM_ELEMENTS);
    copy_arr(test_data, ordered_data, MAX_NUM_ELEMENTS);
    qsort(ordered_data, MAX_NUM_ELEMENTS, sizeof(int), comp);

    printf("### Sequential search\n");
    perf_search_func(test_data, MAX_NUM_ELEMENTS, search_data, sequential_search);

    printf("\n");
    printf("### Binary search\n");
    perf_search_func(ordered_data, MAX_NUM_ELEMENTS, search_data, binary_search);
    // rc = binary_search(ordered_data, 0, MAX_NUM_ELEMENTS - 1, SEARCH_DATA);
    printf("\n");
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define     MAX_DATA_LEN 32

typedef struct _Node {
    char data[MAX_DATA_LEN];
    struct _Node *next;
} Node;
typedef struct _Singly_Linked_List {
    Node *head;
    Node *tail;
    Node *cur;
    int size;
} Linked_List;


void init_linked_list (Linked_List *linkedList)  {
    linkedList->head = NULL;
    linkedList->tail = NULL;
    linkedList->cur = NULL;
    linkedList->size = 0;
}

int node_size(Linked_List linkedList) {
    return linkedList.size;
}

void addNode(Linked_List *linkedList, char *data) {
    Node *tmp_data = malloc(sizeof(Node));

    snprintf(tmp_data->data, MAX_DATA_LEN, "%s", data);
    tmp_data->next = NULL;

    if (node_size(*linkedList) == 0) {
        linkedList->head = tmp_data;
    } else {
        linkedList->tail->next = tmp_data;
    }

    linkedList->tail = tmp_data;
    linkedList->cur = linkedList->head;
    linkedList->size++;
}

void deleteNode(Linked_List *linkedList) {
    int i = 0, len_node = 0;
    Node *lastNode;

    len_node = node_size(*linkedList);

    if (len_node == 0) 
        return;

    linkedList->cur = linkedList->head;
    lastNode = linkedList->tail;

    for (i=0; i<len_node-2; i++) {
        linkedList->cur = linkedList->cur->next;
    }

    linkedList->cur->next = NULL;
    linkedList->tail = linkedList->cur;

    lastNode->data[0] = '\0';
    lastNode->next = NULL;
    linkedList->size--;

    free(lastNode);
}

void insertNode(Linked_List *linkedList, char *data, int num) {
    int i = 0;

    Node *tmp_data = malloc(sizeof(Node));

    if (node_size(*linkedList) < num || node_size(*linkedList) == 0) 
        return;

    linkedList->cur = linkedList->head;

    for (i=0; i<num-1; i++) 
        linkedList->cur = linkedList->cur->next;
    
    snprintf(tmp_data->data, MAX_DATA_LEN, "%s", data);
    tmp_data->next = linkedList->cur->next;
    linkedList->cur->next = tmp_data;
    linkedList->size++;
}

void printAll(Linked_List linkedList) {
    Node *tmp = linkedList.head;

    printf("##### Print all linked list data\n");
    printf("Total Data Size: %d\n", linkedList.size);
    while (tmp->next != NULL) {
        printf("----------------------------------\n");
        printf("Node addr: %p\n", tmp);
        printf("Node data: %s\n", tmp->data);
        printf("Next node addr: %p\n", tmp->next);
        printf("----------------------------------\n");
        printf("               |  \n");
        printf("               v  \n");
        tmp = tmp->next;
    }
    printf("----------------------------------\n");
    printf("Node addr: %p\n", tmp);
    printf("Node data: %s\n", tmp->data);
    printf("Next node addr: %p\n", tmp->next);
    printf("----------------------------------\n");

    printf("Done..\n\n");
}

Node *searchNode(Linked_List linkedList, char *search) {
    int i = 0, list_len = 0;

    linkedList.cur = linkedList.head;

    list_len = node_size(linkedList);
    for (i=0; i<list_len; i++) {
        if (strcmp(search, linkedList.cur->data) == 0) 
            return linkedList.cur;
        linkedList.cur = linkedList.cur->next;
    }

    return NULL;
}

char *getData(Linked_List linkedList, int num) {
    int i = 0;
    
    if (node_size(linkedList) < num)
        return NULL;

    linkedList.cur = linkedList.head;
    for (i=0; i<num; i++) {
        linkedList.cur = linkedList.cur->next;
    }

    return linkedList.cur->data;
}

void func_test() {
    Linked_List test;
    char *str_test;
    Node *node_test;

    init_linked_list(&test);
    printf("### INSERT TEST\n");
    addNode(&test, "ADD NODE 1");
    addNode(&test, "ADD NODE 2");
    addNode(&test, "ADD NODE 3");
    addNode(&test, "ADD NODE 4");
    insertNode(&test, "INSERT NODE INTO 2", 2);
    printAll(test);
    printf("\n");
    
    printf("### SEARCH TEST\n");
    str_test = getData(test, 2);
    printf("GET DATA 2: %s\n", str_test);
    str_test = getData(test, 5);
    printf("GET DATA 5: %s\n", str_test);

    node_test = searchNode(test, "ADD NODE 4");
    printf("SEARCH DATA[ADD NODE 4]: %s\n", node_test->data);
    node_test = searchNode(test, "MINUS NODE 4");
    printf("SEARCH DATA[MINUS NODE 4]: %s\n", node_test->data);
    printf("\n");

    printf("### DELETE TEST\n");
    deleteNode(&test);
    deleteNode(&test);
    printAll(test);
    deleteNode(&test);
    deleteNode(&test);
    deleteNode(&test);
}

int main(int argc, char **argv) 
{
    func_test();

    return 0;
}
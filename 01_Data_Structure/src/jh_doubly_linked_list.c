#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define     MAX_DATA_LEN 32


/*
   void InitList();           //리스트 초기화
   bool InsertAfter(int value, Node* node);     //특정 노드 뒤 삽입
   bool InsertBefore(int value, Node* node);      //특정 노드 앞 삽입
   bool DeleteNode(Node* node);         //특정 노드 삭제
   Node* FindNodeUsingValue(int value);       //data 비교하여 노드 찾기
   Node* FindNodeUsingIndex(int num);       //index 비교하여 노드찾기
   int GetIndex(int value);         //특정 data 의 index 반환
   int GetSize() { return size; }         //리스트의 크기 반환
   void DeleteAll();            //모든 노드 제거
   void PrintList();            //모든 노드 출력
 */

typedef struct _Node {
  char data[MAX_DATA_LEN];
  struct _Node *next;
  struct _Node *prev;
} Node;

typedef struct _Doubly_Linked_List {
  Node *head;
  Node *tail;
  Node *cur;
  int size;
} DoublyLinkedList;

void init_doubly_linked_list(DoublyLinkedList *linkedList) {
  linkedList->head = NULL;
  linkedList->tail = NULL;
  linkedList->cur = NULL;
  linkedList->size = 0;
}

int linkedlist_size(DoublyLinkedList linkedList) {
  return linkedList.size;
}

void addFront(DoublyLinkedList *linkedList, char *data) {
  Node *tmp_data = malloc(sizeof(Node));

  snprintf(tmp_data->data, MAX_DATA_LEN, "%s", data);

  if (linkedlist_size(*linkedList) == 0) {
    linkedList->head = tmp_data;
    linkedList->tail = tmp_data;
  } else {
    tmp_data->prev = NULL;
    tmp_data->next = linkedList->head;
    linkedList->head->prev = tmp_data;
  }
  
  linkedList->head = tmp_data;
  linkedList->cur = linkedList->head;
  linkedList->size++;
}

void removeFront(DoublyLinkedList *linkedList) {
  Node *frontNode;

  if (linkedlist_size(*linkedList) == 0)
    return;

  frontNode = linkedList->head;

  if (linkedList->head->next == NULL) 
    linkedList->cur = linkedList->head;
  else
    linkedList->cur = linkedList->head->next;

  linkedList->cur->prev = NULL;
  linkedList->head = linkedList->cur;

  frontNode->data[0] = '\0';
  frontNode->next = NULL;
  frontNode->prev = NULL;
  
  linkedList->size--;

  free(frontNode);
}

void addBack(DoublyLinkedList *linkedList, char *data) {
  Node *tmp_data = malloc(sizeof(Node));

  snprintf(tmp_data->data, MAX_DATA_LEN, "%s", data);

  if (linkedlist_size(*linkedList) == 0) {
    linkedList->head = tmp_data;
    linkedList->tail = tmp_data;
  } else {
    tmp_data->next = NULL;
    tmp_data->prev = linkedList->tail;
    linkedList->tail->next = tmp_data;
  }
 
  linkedList->tail = tmp_data;
  linkedList->cur = linkedList->tail;
  linkedList->size++;
}

void removeBack(DoublyLinkedList *linkedList) {
  Node *tailNode;

  if (linkedlist_size(*linkedList) == 0)
    return;

  tailNode = linkedList->tail;

  if (linkedList->head->next == NULL) 
    linkedList->cur = linkedList->tail;
  else
    linkedList->cur = linkedList->tail->prev;

  linkedList->cur->next = NULL;
  linkedList->tail = linkedList->cur;

  tailNode->data[0] = '\0';
  tailNode->next = NULL;
  tailNode->prev = NULL;

  linkedList->size--;

  free(tailNode);

}

void printAll(DoublyLinkedList linkedList) {
  Node *tmp = linkedList.head;

    printf("\033[92m##### Print all linked list data\033[0m\n");
    printf("Total Data Size: %d\n", linkedList.size);
    while (tmp->next != NULL) {
        printf("----------------------------------\n");
        printf("Node addr: %p\n", tmp);
        printf("Node data: %s\n", tmp->data);
        printf("Prev node addr: %p\n", tmp->prev);
        printf("Next node addr: %p\n", tmp->next);
        printf("----------------------------------\n");
        printf("        ^       |  \n");
        printf("        |       v  \n");
        tmp = tmp->next;
    }
    printf("----------------------------------\n");
    printf("Node addr: %p\n", tmp);
    printf("Node data: %s\n", tmp->data);
    printf("Prev node addr: %p\n", tmp->prev);
    printf("Next node addr: %p\n", tmp->next);
    printf("----------------------------------\n");

    printf("Done..\n\n");

}

Node *searchNode_fromfront(DoublyLinkedList linkedList, char *search) {
  int i = 0, list_len = 0;

  linkedList.cur = linkedList.head;

  list_len = linkedlist_size(linkedList);
  for (i=0; i<list_len; i++) {
    if (strcmp(search, linkedList.cur->data) == 0) {
      // DEBUG
      printf("Move count: %d\n", i);
      return linkedList.cur;
    }
    linkedList.cur = linkedList.cur->next;
  }

  // DEBUG
  printf("Move count: %d\n", i);
  return NULL;
}

Node *searchNode_fromback(DoublyLinkedList linkedList, char *search) {
  int i = 0, list_len = 0;

  linkedList.cur = linkedList.tail;

  list_len = linkedlist_size(linkedList);
  for (i=0; i<list_len; i++) {
    if (strcmp(search, linkedList.cur->data) == 0) {
      // DEBUG
      printf("Move count: %d\n", i);
      return linkedList.cur;
    }
    linkedList.cur = linkedList.cur->prev;
  }

  // DEBUG
  printf("Move count: %d\n", i);

  return NULL;
}

char *getData(DoublyLinkedList linkedList, int num) {
  int i = 0, list_len = 0;

  list_len = linkedlist_size(linkedList);
  if (linkedlist_size(linkedList) < num)
    return NULL;

  if ((int)(list_len / 2) + 1 > num) {
    linkedList.cur = linkedList.head;
    for (i=0; i<num; i++) {
      linkedList.cur = linkedList.cur->next;
    }
  } else {
    linkedList.cur = linkedList.tail;
    for (i=0; i<list_len - num; i++) {
      linkedList.cur = linkedList.cur->prev;
    }
  }

  // FOR DEBUG
  printf("Move count: %d\n", i);

  return linkedList.cur->data;
}

void func_test() {
  DoublyLinkedList test;
  char *str_test;
  Node *node_test;

  init_doubly_linked_list(&test);

  printf("\033[92m### FRONT INSERT/REMOVE TEST\033[0m\n");
  printf("ADD FRONT DATA THIRED\n");
  addFront(&test, "ADD FRONT 1");
  addFront(&test, "ADD FRONT 2");
  addFront(&test, "ADD FRONT 3");
  printAll(test);
  printf("REMOVE FRONT DATA ONCE\n");
  removeFront(&test);
  printAll(test);

  printf("\033[92m### BACK INSERT/REMOVE TEST\033[0m\n");
  printf("ADD BACK DATA TWO\n");
  addBack(&test, "ADD BACK 1");
  addBack(&test, "ADD BACK 2");
  addBack(&test, "ADD BACK 3");
  printAll(test);
  printf("REMOVE BACK DATA ONCE\n");
  removeBack(&test);
  printAll(test);

  printf("\033[92m### SEARCH TEST\033[0m\n");
  str_test = getData(test, 1);
  printf("GET DATA 1: %s\n", str_test);
  str_test = getData(test, 3);
  printf("GET DATA 3: %s\n", str_test);
  printf("\n");

  node_test = searchNode_fromfront(test, "ADD FRONT 2");
  printf("SEARCH DATA FROM FRONT [ADD FRONT 2]: %s\n", node_test->data);
  node_test = searchNode_fromback(test, "ADD BACK 2");
  printf("SEARCH DATA FROM BACK [ADD BACK 2]: %s\n", node_test->data);

  printf("\033[92m### FINAL TEST\033[0m\n");
  printf("REMOVE FRONT/BACK DATA ONCE\n");
  removeFront(&test);
  removeBack(&test);
  printAll(test);

  // Clear all data
  removeFront(&test);
  removeFront(&test);

}


int main(int argc, char **argv) 
{
  func_test();

  return 0;
}




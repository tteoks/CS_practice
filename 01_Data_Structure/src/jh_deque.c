#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA_SIZE    32

/*
Deque function:
  pushFront
  pushRear
  getFront
  getRear
  isEmpty
  getSize;
  popFront
  popRear
 */


typedef struct _Node {
    char data[MAX_DATA_SIZE];
    struct _Node *prev;
    struct _Node *next;
} Node;

typedef struct _Deque {
    Node *front;
    Node *rear;
    int size;
} Deque;

void init_deque(Deque *deque) {
    deque->front = NULL;
    deque->rear = NULL;
    deque->size = 0;
}

int getSize(Deque deque) {
    return deque.size;
}

int isEmpty(Deque deque) {
    return (deque.size == 0);
}

void pushFront(Deque *deque, char *data) {
    Node *tmp = malloc(sizeof(Node));

    tmp->prev = NULL;
    snprintf(tmp->data, MAX_DATA_SIZE, "%s", data);

    if (isEmpty(*deque)) {
        tmp->next = NULL;
        deque->front = tmp;
        deque->rear = tmp;
    } else {
        deque->front->prev = tmp;
        tmp->next = deque->front;
        deque->front = tmp;
    }

    deque->size++;
}

void pushBack(Deque *deque, char *data) {
    Node *tmp = malloc(sizeof(Node));

    tmp->next = NULL;
    snprintf(tmp->data, MAX_DATA_SIZE, "%s", data);

    if (isEmpty(*deque)) {
        tmp->prev = NULL;
        deque->front = tmp;
        deque->rear = tmp;
    } else {
        deque->rear->next = tmp;
        tmp->prev = deque->rear;
        deque->rear = tmp;
    }

    deque->size++;
}

char *popFront(Deque *deque) {
    Node *tmp;

    if (isEmpty(*deque))
        return NULL;
    
    tmp = deque->front;
    deque->front = deque->front->next;
    if (deque->front != NULL) 
      deque->front->prev = NULL;

    tmp->next = NULL;
    tmp->prev = NULL;

    deque->size--;
    return tmp->data;
}

char *popBack(Deque *deque) {
    Node *tmp;

    if (isEmpty(*deque))
        return NULL;
    
    tmp = deque->rear;
    deque->rear = deque->rear->prev;
    if (deque->rear != NULL) 
      deque->rear->next = NULL;

    tmp->next = NULL;
    tmp->prev = NULL;

    deque->size--;
    return tmp->data;
}

char *getFront(Deque deque) {
    if (isEmpty(deque))
        return NULL;
    else
        return deque.front->data;
}

char *getBack(Deque deque) {
    if (isEmpty(deque))
        return NULL;
    else
        return deque.rear->data;
}

void printAll(Deque deque) {
  Node *tmp = deque.front;

    printf("\033[92m##### Print all linked list data\033[0m\n");
    printf("Total Data Size: %d\n", deque.size);
    printf("-------------HEAD-----------------\n");
    printf("Node addr: %p\n", tmp);
    printf("Node data: %s\n", tmp->data);
    printf("Prev node addr: %p\n", tmp->prev);
    printf("Next node addr: %p\n", tmp->next);
    printf("----------------------------------\n");

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
    printf("-------------TAIL----------------\n");
    printf("Node addr: %p\n", tmp);
    printf("Node data: %s\n", tmp->data);
    printf("Prev node addr: %p\n", tmp->prev);
    printf("Next node addr: %p\n", tmp->next);
    printf("----------------------------------\n");

    printf("Done..\n\n");

}

void func_test() {
  Deque deque;
  char *str_test;

  init_deque(&deque);

  printf("\033[92m### FRONT PUSH/POP TEST\033[0m\n");
  printf("ADD FRONT DATA TWICE\n");
  pushFront(&deque, "ADD FRONT 1");
  pushFront(&deque, "ADD FRONT 2");
  printAll(deque);
  printf("REMOVE FRONT DATA ONCE\n");
  popFront(&deque);
  printAll(deque);

  printf("\033[92m### BACK INSERT/REMOVE TEST\033[0m\n");
  printf("ADD BACK DATA TWO\n");
  pushBack(&deque, "ADD BACK 1");
  pushBack(&deque, "ADD BACK 2");
  printAll(deque);
  printf("REMOVE BACK DATA ONCE\n");
  popBack(&deque);
  printAll(deque);

  printf("\033[92m### GET DATA TEST\033[0m\n");
  printAll(deque);
  printf("GET FRONT : %s\n", getFront(deque));
  printf("GET BACK : %s\n", getBack(deque));

  printf("\033[92m### FINAL TEST\033[0m\n");
  printf("REMOVE FRONT/BACK DATA ONCE\n");
  popFront(&deque);
  popBack(&deque);
  printAll(deque);
  
}


int main(int argc, char **argv)
{
  func_test();

  return 0;
}


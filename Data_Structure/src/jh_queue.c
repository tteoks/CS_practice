#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LENGTH  128

/*
Queue function: 
   initQueue
   isEmpty
   isFull
   enQueue
   deQueue
   peek
*/

typedef struct _Node {
  int data;
  struct Node *next;
}Node;

typedef struct _Queue {
  Node *front;
  Node *rear;
  int count;
}Queue;

void initQueue(Queue *queue) {
  queue->front = NULL;
  queue->rear = NULL;
  queue->count = 0;
}

bool isEmpty(Queue *queue) {
  if (queue == NULL) {
    fprintf(stderr, "No data in queue\n");
    return false;
  }

  if (queue->count == 0)
    return true;
  else
    return false;
}

bool isFull(Queue *queue) {
  if (queue == NULL) {
    fprintf(stderr, "No data in queue\n");
    return false;
  }

  if (queue->count == MAX_LENGTH) 
    return true;
  else
    return false;
}

bool enQueue(Queue *queue, int value) {
  Node *node = malloc(sizeof(node));

  if (queue == NULL) {
    fprintf(stderr, "No data in queue\n");
    return false;
  }

  if (isFull(queue)) {
    fprintf(stderr, "No space in queue\n");
    return false;
  }
  
  node->data = value;
  node->next = NULL;

  if (isEmpty(queue)) {
    queue->rear = node;
    queue->front = node;
  } else {
    queue->rear->next = node;
    queue->rear = node;
  }

  queue->count++;
  return true;
}

int deQueue(Queue *queue) {
  int rc = 0; 

  if (queue == NULL) {
    fprintf(stderr, "No data in queue\n");
    return false;
  }

  if (isEmpty(queue)) {
    fprintf(stderr, "No data in queue\n");
    return false;
  }

  rc = queue->front->data;
  queue->front = queue->front->next;

  queue->count--;
  return rc;
}


int main(int argc, char **argv)
{
  printf("Hello World\n");
  Queue queue;
  initQueue(&queue);

  enQueue(&queue, 1);
  enQueue(&queue, 2);
  enQueue(&queue, 3);
  enQueue(&queue, 4);

  printf("Dequeue: %d\n", deQueue(&queue));
  printf("Dequeue: %d\n", deQueue(&queue));
  printf("Dequeue: %d\n", deQueue(&queue));
  printf("Dequeue: %d\n", deQueue(&queue));

  return 0;
}

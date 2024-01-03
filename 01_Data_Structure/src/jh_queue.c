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

/*
Available colors
  0: RED
  1: GREEN
  2: YELLOW
  3: BLUE
  \033[0m
 */
void color_print(int color, char *text) {
  char color_str[8];

  switch(color) {
    case 0:
      snprintf(color_str, 8, "\033[91m");
      break;
    case 1:
      snprintf(color_str, 8, "\033[92m");
      break;
    case 2:
      snprintf(color_str, 8, "\033[93m");
      break;
    case 3:
      snprintf(color_str, 8, "\033[94m");
      break;
  }

  printf("%s%s\033[0m\n", color_str, text);

}


int main(int argc, char **argv)
{
  printf("Hello World\n");
  Queue queue;
  initQueue(&queue);

  printf("\033[92m[Enqueue] %d\033[0m\n", 1);
  enQueue(&queue, 1);
  
  printf("\033[92m[Enqueue] %d\033[0m\n", 2);
  enQueue(&queue, 2);
  printf("\033[93m[Dequeue] %d\033[0m\n", deQueue(&queue));

  printf("\033[92m[Enqueue] %d\033[0m\n", 3);
  enQueue(&queue, 3);
  printf("\033[93m[Dequeue] %d\033[0m\n", deQueue(&queue));

  printf("\033[92m[Enqueue] %d\033[0m\n", 4);
  enQueue(&queue, 4);

  printf("\033[93m[Dequeue] %d\033[0m\n", deQueue(&queue));
  printf("\033[93m[Dequeue] %d\033[0m\n", deQueue(&queue));

  return 0;
}

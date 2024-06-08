#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES  50
#define MAX_QUEUE_SIZE  50

typedef struct _GraphNode {
  int vertex;
  struct _GraphNode *link;
} GraphNode;

typedef struct _GraphType {
  int n;
  GraphNode *adg_list[MAX_VERTICES];
} GraphType;

typedef struct _QueueType {
  int queue[MAX_QUEUE_SIZE];
  int front;
  int rear;
} QueueType;

int visited[MAX_VERTICES] = {0, };

void clear_visit() {
  memset(visited, 0x00, sizeof(visited));
}

// ##### QUEUE FUNCTIONS
void init_queue(QueueType *q) {
  q->front = 0;
  q->rear = 0;
}

int is_queue_empty(QueueType *q) {
  return (q->rear == q->front);
}

int is_queue_full(QueueType *q) {
  return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void enqueue(QueueType *q, int data) {
  if (is_queue_full(q)) {
    fprintf(stderr, "Queue overflow\n");
    return ;
  }

  q->queue[q->rear] = data;
  q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
}

int dequeue(QueueType *q) {
  int res;

  if (is_queue_empty(q)) {
    fprintf(stderr, "Queue underflow\n");
    return -1;
  }

  res = q->queue[q->front];
  q->front = (q->front + 1) % MAX_QUEUE_SIZE;
  
  return res;
}


// ##### GRAPH FUNCTIONS
void init_graph(GraphType *g) {
  int i;

  g->n = 0;

  for (i=0; i<MAX_VERTICES; i++) {
    g->adg_list[i] = NULL;
  }
}

void insert_vertex(GraphType *g, int v) {
  if (g->n >= MAX_VERTICES) {
    fprintf(stderr, "Overflow!!\n");
    return ;
  }
  g->n++;
}

void insert_edge(GraphType *g, int start, int end) {
  GraphNode *new_node;

  if (start >= g->n || end >= g->n) {
    fprintf(stderr, "Invalid graph key!\n");
    return;
  }

  new_node = malloc(sizeof(GraphNode));
  new_node->vertex = end;
  new_node->link = g->adg_list[start];
  g->adg_list[start] = new_node;
}

void display_adg_list(GraphType *g) {
  int i;
  for (i=0; i<g->n; i++) {
    GraphNode *p = g->adg_list[i];
    printf("정점 %d의 인접리스트\n", i);
    while (p != NULL) {
      printf(" ->%d", p->vertex);
      p = p->link;
    }
    printf("\n");
  }
}

void dfs_list(GraphType *g, int vertex) {
  GraphNode *tmp;

  visited[vertex] = 1;
  printf("VISIT: %d -> ", vertex);

  tmp = g->adg_list[vertex];
  while (tmp) {
    if (!visited[tmp->vertex]) {
      dfs_list(g, tmp->vertex);
    }
    tmp = tmp->link;
  }
}

void bfs_list(GraphType *g, int vertex) {
  int w;
  QueueType *q = malloc(sizeof(QueueType));
  GraphNode *tmp;
  
  init_queue(q);

  visited[vertex] = 1;
  printf("VISIT: %d -> ", vertex);
  enqueue(q, vertex);

  while (!is_queue_empty(q)) {
    w = dequeue(q);
    tmp = g->adg_list[w];
    while (tmp != NULL) {
      if (!visited[tmp->vertex]) {
        visited[tmp->vertex] = 1;
        printf("VISIT: %d -> ", tmp->vertex);
        enqueue(q, tmp->vertex);
      }
      tmp = tmp->link;
    }
  }
}

void destory_graph(GraphType *g) {
  free(g);
}

int main(int argc, char **argv)
{
  int  i;
  printf("Hello world\n");

  GraphType *graph = malloc(sizeof(GraphType));
  init_graph(graph);

  for (i=0; i<7; i++) {
    insert_vertex(graph, i);
  }
  insert_edge(graph,0,1);  // 그래프 간선 생성
  insert_edge(graph,0,2);
  insert_edge(graph,1,3);
  insert_edge(graph,1,4);
  insert_edge(graph,2,5);
  insert_edge(graph,2,6);

  display_adg_list(graph);
  printf("\n");

  printf("DFS\n");
  dfs_list(graph, 0);
  printf("\n");

  clear_visit();
  printf("BFS\n");
  bfs_list(graph, 0);
  printf("\n");

  destory_graph(graph);

  return 0;
}

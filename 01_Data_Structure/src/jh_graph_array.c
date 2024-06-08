#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 정점 최대 개수
#define MAX_VERTICES  50
#define MAX_QUEUE_SIZE  50

/*
 * create_greaph()
 * init(g)
 * insert_vertex(g, v)
 * insert_edge(g, u, v)
 * delete_vertex(g, v)
 * delete_edge(g, u, v)
 * is_empty(g)
 * adgacent(v)
 * destory_graph(g)
*/

typedef struct _QueueType {
  int queue[MAX_QUEUE_SIZE];
  int front;
  int rear;
} QueueType;

typedef struct _GraphType {
  // 정점 개수
  int n;
  // 인접 행렬
  int adg_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

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
  return (q->rear + 1)%MAX_QUEUE_SIZE == q->front;
}

void enqueue(QueueType *q, int data) {
  if (is_queue_full(q)) {
    fprintf(stderr, "Queue overflow\n");
    return;
  }

  q->queue[q->rear] = data;
  q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
}

int dequeue(QueueType *q) {
  int res = 0;

  if (is_queue_empty(q)) {
    fprintf(stderr, "Queue underflow\n");
    return -1;
  }

  res = q->front;
  q->front = (q->front + 1) % MAX_QUEUE_SIZE;

  return res;
}


// ##### GRAPH FUNCTIONS

void init_graph(GraphType *g){
  int i, j;
  g->n = 0;

  for (i=0; i<MAX_VERTICES * MAX_VERTICES; i++) {
    g->adg_mat[i/MAX_VERTICES][i%MAX_VERTICES] = 0;
  }
}

void insert_vertex(GraphType *g, int v) {
  if ((g->n) >= MAX_VERTICES) {
    fprintf(stderr, "Overflow!!\n");
    return ;
  }
  g->n++;
}

void insert_edge(GraphType *g, int start, int end) {
  if (start >= g->n || end >= g->n) {
    fprintf(stderr, "Invalid vertex key\n");
    return ;
  }

  g->adg_mat[start][end] = 1;
  g->adg_mat[end][start] = 1;

}

//Graph / Vertex
void dfs_mat(GraphType *g, int v) {
  int w;
  visited[v] = 1;
  printf("VISIT: %d -> ", v);

  for (w=0; w<g->n; w++) {
    if (g->adg_mat[v][w] && !visited[w])
      dfs_mat(g, w);
  }
}

void bfs_mat(GraphType *g, int v) {
  int w, tmp;
  QueueType q;

  init_queue(&q);
  visited[v] = 1;
  printf("VISIT: %d -> ", v);
  enqueue(&q, v);
  while(!is_queue_empty(&q)) {
    tmp = dequeue(&q);
    for (w=0; w<g->n; w++) {
      if (g->adg_mat[tmp][w] && !visited[w]){
        visited[w] = 1;
        printf("VISIT: %d -> ", w);
        enqueue(&q, w);
      }
    }
  }
}

void display_adg_mat(GraphType *g) {
  int i, j;

  for (i=0; i<g->n; i++) {
    for (j=0; j<g->n; j++) {
      printf("%2d", g->adg_mat[i][j]);
    }
    printf("\n");
  }
}

void destory_graph(GraphType *g) {
  free(g);
}



int main(int argc, char **argv)
{
  int i;

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

  display_adg_mat(graph);
  printf("\n");

  printf("DFS\n");
  dfs_mat(graph, 0);
  printf("\n");

  clear_visit();
  printf("BFS\n");
  bfs_mat(graph, 0);
  printf("\n");


  destory_graph(graph);

  return 0;
}

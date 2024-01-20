#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 512

// Adds a new item to a dynamic array, resizing automatically
// The dynamic array struct must have the fields data, size, and capacity
#define DYN_ADD(da, item)                                                      \
  do {                                                                         \
    if ((da)->size == (da)->capacity) {                                        \
      (da)->capacity = ((da)->capacity <= 0) ? 1 : (da)->capacity * 2;         \
      (da)->data = realloc((da)->data, (da)->capacity * sizeof(*(da)->data));  \
      assert((da)->data && "Catastrophic Failure: Allocation failed!");        \
    }                                                                          \
    (da)->data[(da)->size++] = item;                                           \
  } while (0)

// Returns true if item doesnt already exist, true otherwise
bool set_add(int *set, size_t item) {
  if (set[item] > 0) {
    return false;
  }
  set[item] += 1;
  return true;
}

// Dynamic Array consisting of vertices represented by an int id
typedef struct {
  size_t *data;
  size_t size;
  size_t capacity;
} Vertices;

typedef struct {
  Vertices v[MAX];
  size_t count;
} Graph;

Graph graph_init() { return (Graph){0}; }

void graph_add_vertex(Graph *graph, size_t vertex, size_t new_vertex) {
  assert(vertex < MAX && "Vertex too high!");
  assert(graph->count <= MAX && "Maximum vertices reached!");

  // vertex didnt previously exist
  if (graph->v[vertex].size == 0) {
    graph->count++;
  }
  DYN_ADD(&graph->v[vertex], new_vertex);
}

void graph_del(Graph *graph) {
  for (size_t i = 0; i < graph->count; i++) {
    free(graph->v[i].data);
    graph->v[i].size = 0;
    graph->v[i].capacity = 0;
  }
  graph->count = 0;
}

Vertices graph_vertices(Graph *graph, size_t vertex) {
  return graph->v[vertex];
}

typedef struct {
  size_t data[MAX];
  size_t front;
  size_t rear;
  size_t count;
} Queue;

bool que_empty(Queue *que) { return que->count == 0; }

void que_push(Queue *que, size_t item) {
  assert(que->count <= MAX && "Queue is Full!");
  que->data[que->rear++] = item;
  que->count++;
}

size_t que_pop(Queue *que) {
  assert(que->count != 0 && "Queue is Empty!");
  size_t item = que->data[que->front++];
  que->count--;
  return item;
}

// Perform Breadth First Search
void bfs(Graph *graph, size_t start) {
  int visited[MAX] = {0};
  Queue vertices = {0};

  // deal with disconnected vertices later on
  // assume all graphs start with a vertex of ID: 0 for now
  que_push(&vertices, start);

  while (!que_empty(&vertices)) {
    size_t vertex_id = que_pop(&vertices);

    // skip if vertex is already visited
    if (!set_add(visited, vertex_id)) {
      continue;
    }
    printf("%zu ", vertex_id);

    Vertices children = graph->v[vertex_id];
    for (size_t i = 0; i < children.size; i++) {
      que_push(&vertices, children.data[i]);
    }
  }
}

int main() {
  Graph g = graph_init();

  graph_add_vertex(&g, 0, 1);
  graph_add_vertex(&g, 0, 2);

  graph_add_vertex(&g, 1, 0);
  graph_add_vertex(&g, 1, 2);

  graph_add_vertex(&g, 2, 0);
  graph_add_vertex(&g, 2, 1);
  graph_add_vertex(&g, 2, 3);

  graph_add_vertex(&g, 3, 5);
  graph_add_vertex(&g, 3, 6);

  graph_add_vertex(&g, 4, 5);
  graph_add_vertex(&g, 4, 6);

  graph_add_vertex(&g, 5, 4);
  graph_add_vertex(&g, 5, 3);

  graph_add_vertex(&g, 6, 4);
  graph_add_vertex(&g, 6, 3);

  graph_add_vertex(&g, 7, 8);

  printf("%zu\n", g.count);
  bfs(&g, 2);

  return 0;
}

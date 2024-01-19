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

// Dynamic Array consisting of vertices represented by an int id
typedef struct {
  int *data;
  size_t size;
  size_t capacity;
} Vertices;

typedef struct {
  Vertices v[MAX];
  size_t count;
} Graph;

Graph graph_init() { return (Graph){0}; }

void graph_add_vertex(Graph *graph, int vertex) {
  assert(graph->count <= MAX && "Maximum vertices reached!");
  DYN_ADD(&graph->v[graph->count], vertex);
  graph->count++;
}

typedef int Set;
typedef int Queue;

bool que_empty(Queue *) { assert(0 && "TODO"); }
bool que_push(Queue *, size_t) { assert(0 && "TODO"); }
bool que_pop(Queue *) { assert(0 && "TODO"); }
bool set_get(Set *, size_t) { assert(0 && "TODO"); }

// Perform Breadth First Search
void bfs(Graph *graph) {
  Set visited = {MAX};
  Queue vertices = {MAX};

  // deal with disconnected vertices later on
  // assume all graphs start with a vertex of ID: 0 for now
  que_push(&vertices, 0);

  while (!que_empty(&vertices)) {
    size_t vertex_id = que_pop(&vertices);

    // skip if vertex is already visited
    if (set_get(&visited, vertex_id)) {
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

  printf("%zu\n", g.count);

  graph_add_vertex(&g, 23);
  printf("%d\n", g.v[0].data[0]);

  return 0;
}

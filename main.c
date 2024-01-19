#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 1024 * 128

// Adds a new item to a dynamic array, resizing automatically
// The dynamic array struct must have the fields data, size, and capacity
#define DYN_ADD(da, item)                                                      \
  do {                                                                         \
    if ((da)->size == (da)->capacity) {                                        \
      (da)->capacity = ((da)->capacity <= 0) ? 1 : (da)->capacity * 2;         \
      (da)->data = realloc((da)->data, (da)->capacity * sizeof(*(da)->data));  \
      assert((da)->data && "Error in allocating");                             \
    }                                                                          \
    (da)->data[(da)->size++] = item;                                           \
  } while (0)

// Dynamic Array consisting of vertices represented by an int id
typedef struct {
  int *data;
  size_t size;
  size_t capacity;
} Vertices;

// Adjacency list of vertices
typedef struct {
  Vertices v[MAX];
  size_t count;
} Graph;

typedef struct {
  Vertices v[MAX];
  size_t count;
} G1;

typedef struct {
  size_t count;
  Vertices v[MAX];
} G2;

Graph graph_init() { return (Graph){0}; }

void graph_add_vertex(Graph *graph, int vertex) {
  assert(graph->count <= MAX && "Maximum vertices reached!");
  DYN_ADD(&graph->v[graph->count], vertex);
  graph->count++;
}

int main() {
  Graph g = graph_init();

  printf("%zu\n", g.count);

  graph_add_vertex(&g, 23);
  printf("%d\n", g.v[0].data[0]);

  G1 a = {0};
  G2 b = {0};

  printf("G1: %zu, G2: %zu", sizeof a, sizeof b);
  return 0;
}

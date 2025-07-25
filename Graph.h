#ifndef GRAPH_H
#define GRAPH_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Maximum vertices allowed
#define GRAPH_VERTEX_MAX 512

// Dynamic Array consisting of vertices represented by
// an ID in the range: 0 <= ID < GRAPH_VERTEX_MAX
typedef struct {
  size_t *data;
  size_t size;
  size_t capacity;
} Vertices;

// count stores the no. of vertices present in the graph
typedef struct {
  Vertices v[GRAPH_VERTEX_MAX];
  bool occupied[GRAPH_VERTEX_MAX];
  size_t count;
  size_t max_id;
} Graph;

Graph graph_init(void);

// Add edge connecting `vertex_a` and `vertex_b`
void graph_add_edge(Graph *graph, size_t vertex_a, size_t vertex_b);

// Delete the graph
void graph_del(Graph *graph);

// Returns all vertices connected to `vertex`
Vertices graph_vertices(Graph *graph, size_t vertex);

// Performs Breadth First Order Traversal and stores the vertices in `vertices`
void graph_bfs(Graph *graph, size_t start, Vertices *vertices);

// Returns true if item doesnt already exist, true otherwise
bool set_add(bool *set, size_t item);

// Simple linear queue on the stack
// TODO: allocate dynamically and convert into a circular queue
typedef struct {
  size_t data[GRAPH_VERTEX_MAX];
  size_t front;
  size_t rear;
  size_t count;
} Queue;

Queue que_init(void);
bool queue_is_empty(Queue *queue);
void queue_push(Queue *queue, size_t item);
size_t queue_pop(Queue *queue);
void queue_del(Queue *queue);

#ifdef GRAPH_H_IMPLEMENTATION

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
bool set_add(bool *set, size_t item) {
  if (set[item]) {
    return false;
  }
  set[item] = true;
  return true;
}

Graph graph_init() { return (Graph){0}; }

void graph_add_edge(Graph *graph, size_t vertex_a, size_t vertex_b) {
  assert(vertex_a < GRAPH_VERTEX_MAX && vertex_b < GRAPH_VERTEX_MAX &&
         "Vertex ID too high!");
  assert(graph->count <= GRAPH_VERTEX_MAX && "Maximum vertices reached!");

  // set new maximum vertex
  size_t max = (vertex_a > vertex_b) ? vertex_a : vertex_b;
  if (graph->max_id < max) {
    graph->max_id = max;
  }

  // vertex didnt previously exist
  if (graph->v[vertex_a].size == 0) {
    graph->occupied[vertex_a] = true;
    graph->count++;
  }
  DYN_ADD(&graph->v[vertex_a], vertex_b);

  // add the opposite vertex only if they are not same
  if (vertex_a != vertex_b) {
    if (graph->v[vertex_b].size == 0) {
      graph->occupied[vertex_b] = true;
      graph->count++;
    }
    DYN_ADD(&graph->v[vertex_b], vertex_a);
  }
}

void graph_del(Graph *graph) {
  for (size_t i = 0; i <= graph->max_id; i++) {
    free(graph->v[i].data);
    graph->v[i].size = 0;
    graph->v[i].capacity = 0;
  }
  graph->count = 0;
}

Vertices graph_vertices(Graph *graph, size_t vertex) {
  return graph->v[vertex];
}

Queue que_init() { return (Queue){0}; }

bool queue_is_empty(Queue *queue) { return queue->count == 0; }

void queue_push(Queue *queue, size_t item) {
  assert(queue->count <= GRAPH_VERTEX_MAX && "Queue is Full!");
  queue->data[queue->rear++] = item;
  queue->count++;
}

size_t queue_pop(Queue *queue) {
  assert(queue->count != 0 && "Queue is Empty!");
  size_t item = queue->data[queue->front++];
  queue->count--;
  return item;
}

void queue_del(Queue *queue) {
  queue->front = 0;
  queue->rear = 0;
  queue->count = 0;
}

static inline void bfs_main(Graph *graph, Queue *vertices, bool *visited, Vertices *vertices_out) {
  while (!queue_is_empty(vertices)) {
    size_t vertex_id = queue_pop(vertices);

    // skip if vertex is already visited
    if (!set_add(visited, vertex_id)) {
      continue;
    }

    DYN_ADD(vertices_out, vertex_id);

    Vertices children = graph->v[vertex_id];
    for (size_t i = 0; i < children.size; i++) {
      queue_push(vertices, children.data[i]);
    }
  }
}

// Perform Breadth First Search
void graph_bfs(Graph *graph, size_t start, Vertices *vertices_out) {
  if (graph->v[start].size == 0) {
    return;
  }
  Queue vertices = que_init();
  queue_push(&vertices, start);

  bool visited[GRAPH_VERTEX_MAX] = {0};
  bfs_main(graph, &vertices, visited, vertices_out);
  queue_del(&vertices);

  // handle disconnected vertices
  for (size_t i = 0; i <= graph->max_id; i++) {
    if (visited[i] == true || graph->v[i].size == 0) {
      continue;
    }
    queue_push(&vertices, i);
    bfs_main(graph, &vertices, visited, vertices_out);
  }
}
#endif // !GRAPH_H
#endif // GRAPH_H_IMPLEMENTATION

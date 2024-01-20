#define GRAPH_H_IMPLEMENTATION
#include "Graph.h"

int main() {
  Graph g = graph_init();

  graph_add_vertex(&g, 0, 1);
  graph_add_vertex(&g, 0, 25);
  graph_add_vertex(&g, 0, 2);

  graph_add_vertex(&g, 1, 2);

  graph_add_vertex(&g, 2, 3);

  graph_add_vertex(&g, 3, 5);
  graph_add_vertex(&g, 3, 6);

  graph_add_vertex(&g, 4, 5);
  graph_add_vertex(&g, 4, 6);

  graph_add_vertex(&g, 7, 8);

  // BFS works with disconnected vertices as well
  graph_add_vertex(&g, 12, 12);

  printf("%zu\n", g.count);
  bfs(&g, 2);

  return 0;
}

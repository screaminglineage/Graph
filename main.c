#define GRAPH_H_IMPLEMENTATION
#include "graph.h"

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

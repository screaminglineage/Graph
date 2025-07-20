#include <stddef.h>
#include <stdio.h>
#define GRAPH_H_IMPLEMENTATION
#include "Graph.h"

void create_huge_graph(Graph *graph);

void bfs(Graph *g, size_t start) {
  Vertices vertices = {0};
  graph_bfs(g, start, &vertices);
  printf("[");
  for (size_t i = 0; i < vertices.size; i++) {
      printf(" %zu,", vertices.data[i]);
  }
  printf(" ]\n");
}

int main() {
  Graph g = graph_init();

  graph_add_edge(&g, 0, 1);

  // arbitrary vertices can be added out of order
  // as long as the vertex ID is below GRAPH_VERTEX_MAX
  graph_add_edge(&g, 0, 25);
  graph_add_edge(&g, 0, 2);

  graph_add_edge(&g, 1, 2);

  graph_add_edge(&g, 2, 3);

  graph_add_edge(&g, 3, 5);
  graph_add_edge(&g, 3, 6);

  graph_add_edge(&g, 4, 5);
  graph_add_edge(&g, 4, 6);

  graph_add_edge(&g, 7, 8);

  // BFS works with disconnected vertices as well
  graph_add_edge(&g, 12, 12);
  graph_add_edge(&g, 10, 12);

  printf("Total vertices: %zu\n", g.count);
  printf("Max ID: %zu\n", g.max_id);
  // BFS starting from vertex 2
  bfs(&g, 2);
  // Graph must be reinitialised after deleting
  graph_del(&g);
  g = graph_init();

  // generating a graph of 100 vertices
  create_huge_graph(&g);
  bfs(&g, 0);
  graph_del(&g);

  return 0;
}

void create_huge_graph(Graph *graph) {
  graph_add_edge(graph, 0, 1);
  graph_add_edge(graph, 0, 2);
  graph_add_edge(graph, 0, 4);
  graph_add_edge(graph, 0, 5);
  graph_add_edge(graph, 1, 3);
  graph_add_edge(graph, 1, 5);
  graph_add_edge(graph, 2, 3);
  graph_add_edge(graph, 2, 4);
  graph_add_edge(graph, 2, 6);
  graph_add_edge(graph, 3, 5);
  graph_add_edge(graph, 3, 7);
  graph_add_edge(graph, 4, 8);
  graph_add_edge(graph, 4, 9);
  graph_add_edge(graph, 5, 9);
  graph_add_edge(graph, 5, 11);
  graph_add_edge(graph, 6, 8);
  graph_add_edge(graph, 6, 10);
  graph_add_edge(graph, 7, 10);
  graph_add_edge(graph, 7, 12);
  graph_add_edge(graph, 8, 14);
  graph_add_edge(graph, 9, 13);
  graph_add_edge(graph, 9, 15);
  graph_add_edge(graph, 10, 11);
  graph_add_edge(graph, 10, 16);
  graph_add_edge(graph, 11, 13);
  graph_add_edge(graph, 12, 15);
  graph_add_edge(graph, 12, 17);
  graph_add_edge(graph, 13, 18);
  graph_add_edge(graph, 14, 19);
  graph_add_edge(graph, 16, 18);
  graph_add_edge(graph, 20, 21);
  graph_add_edge(graph, 20, 22);
  graph_add_edge(graph, 20, 24);
  graph_add_edge(graph, 20, 25);
  graph_add_edge(graph, 21, 23);
  graph_add_edge(graph, 21, 25);
  graph_add_edge(graph, 22, 23);
  graph_add_edge(graph, 22, 24);
  graph_add_edge(graph, 22, 26);
  graph_add_edge(graph, 23, 25);
  graph_add_edge(graph, 23, 27);
  graph_add_edge(graph, 24, 28);
  graph_add_edge(graph, 24, 29);
  graph_add_edge(graph, 25, 29);
  graph_add_edge(graph, 25, 31);
  graph_add_edge(graph, 26, 28);
  graph_add_edge(graph, 26, 30);
  graph_add_edge(graph, 27, 30);
  graph_add_edge(graph, 27, 32);
  graph_add_edge(graph, 28, 34);
  graph_add_edge(graph, 29, 33);
  graph_add_edge(graph, 29, 35);
  graph_add_edge(graph, 30, 31);
  graph_add_edge(graph, 30, 36);
  graph_add_edge(graph, 31, 33);
  graph_add_edge(graph, 32, 35);
  graph_add_edge(graph, 32, 37);
  graph_add_edge(graph, 33, 38);
  graph_add_edge(graph, 34, 39);
  graph_add_edge(graph, 36, 38);
  graph_add_edge(graph, 36, 40);
  graph_add_edge(graph, 37, 39);
  graph_add_edge(graph, 37, 41);
  graph_add_edge(graph, 38, 42);
  graph_add_edge(graph, 39, 43);
  graph_add_edge(graph, 40, 44);
  graph_add_edge(graph, 40, 45);
  graph_add_edge(graph, 41, 45);
  graph_add_edge(graph, 41, 47);
  graph_add_edge(graph, 42, 44);
  graph_add_edge(graph, 42, 46);
  graph_add_edge(graph, 43, 46);
  graph_add_edge(graph, 43, 48);
  graph_add_edge(graph, 44, 50);
  graph_add_edge(graph, 45, 49);
  graph_add_edge(graph, 45, 51);
  graph_add_edge(graph, 46, 47);
  graph_add_edge(graph, 46, 52);
  graph_add_edge(graph, 47, 49);
  graph_add_edge(graph, 48, 51);
  graph_add_edge(graph, 48, 53);
  graph_add_edge(graph, 49, 54);
  graph_add_edge(graph, 50, 55);
  graph_add_edge(graph, 52, 54);
  graph_add_edge(graph, 52, 56);
  graph_add_edge(graph, 53, 56);
  graph_add_edge(graph, 53, 57);
  graph_add_edge(graph, 54, 58);
  graph_add_edge(graph, 55, 59);
  graph_add_edge(graph, 56, 58);
  graph_add_edge(graph, 56, 60);
  graph_add_edge(graph, 57, 59);
  graph_add_edge(graph, 57, 61);
  graph_add_edge(graph, 58, 62);
  graph_add_edge(graph, 59, 63);
  graph_add_edge(graph, 60, 64);
  graph_add_edge(graph, 60, 65);
  graph_add_edge(graph, 61, 65);
  graph_add_edge(graph, 61, 67);
  graph_add_edge(graph, 62, 64);
  graph_add_edge(graph, 62, 66);
  graph_add_edge(graph, 63, 66);
  graph_add_edge(graph, 63, 68);
  graph_add_edge(graph, 64, 70);
  graph_add_edge(graph, 65, 69);
  graph_add_edge(graph, 65, 71);
  graph_add_edge(graph, 66, 67);
  graph_add_edge(graph, 66, 72);
  graph_add_edge(graph, 67, 69);
  graph_add_edge(graph, 68, 71);
  graph_add_edge(graph, 68, 73);
  graph_add_edge(graph, 69, 74);
  graph_add_edge(graph, 70, 75);
  graph_add_edge(graph, 72, 74);
  graph_add_edge(graph, 72, 76);
  graph_add_edge(graph, 73, 76);
  graph_add_edge(graph, 73, 77);
  graph_add_edge(graph, 74, 78);
  graph_add_edge(graph, 75, 79);
  graph_add_edge(graph, 76, 78);
  graph_add_edge(graph, 76, 80);
  graph_add_edge(graph, 77, 79);
  graph_add_edge(graph, 77, 81);
  graph_add_edge(graph, 78, 82);
  graph_add_edge(graph, 79, 83);
  graph_add_edge(graph, 80, 84);
  graph_add_edge(graph, 80, 85);
  graph_add_edge(graph, 81, 85);
  graph_add_edge(graph, 81, 87);
  graph_add_edge(graph, 82, 84);
  graph_add_edge(graph, 82, 86);
  graph_add_edge(graph, 83, 86);
  graph_add_edge(graph, 83, 88);
  graph_add_edge(graph, 84, 90);
  graph_add_edge(graph, 85, 89);
  graph_add_edge(graph, 85, 91);
  graph_add_edge(graph, 86, 87);
  graph_add_edge(graph, 86, 92);
  graph_add_edge(graph, 87, 89);
  graph_add_edge(graph, 88, 91);
  graph_add_edge(graph, 88, 93);
  graph_add_edge(graph, 89, 94);
  graph_add_edge(graph, 90, 95);
  graph_add_edge(graph, 92, 94);
  graph_add_edge(graph, 92, 96);
  graph_add_edge(graph, 93, 96);
  graph_add_edge(graph, 93, 97);
  graph_add_edge(graph, 94, 98);
  graph_add_edge(graph, 95, 99);
  graph_add_edge(graph, 96, 98);
  graph_add_edge(graph, 96, 100);
  graph_add_edge(graph, 97, 99);
  graph_add_edge(graph, 97, 101);
  graph_add_edge(graph, 98, 102);
  graph_add_edge(graph, 99, 103);
  graph_add_edge(graph, 100, 104);
  graph_add_edge(graph, 105, 106);
}

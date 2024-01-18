#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX 512
#define END_VAL -1

#define DYN_RESIZE(da)                                                  \
    do {                                                                \
    if ((da).capacity == 0) {                                           \
        (da).data = malloc(sizeof(*(da).data));                         \
        assert((da).data && "Error in allocating");                     \
                                                                        \
        (da).capacity += 1;                                             \
        break;                                                          \
    }                                                                   \
                                                                        \
    (da).capacity *= 2;                                                 \
    (da).data = realloc((da).data, (da).capacity * sizeof(*(da).data)); \
                                                                        \
    assert((da).data && "Error in allocating");                         \
} while (0);                                                            \


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


Graph graph_init() {
    return (Graph){0};
}

void graph_add_vertex(Graph *graph, int v) {
    DYN_ADD(&(graph->v), v);
    ++(graph->cout);
}


int main() {
    Graph g = graph_init();

    printf("%zu", g.count);
    return 0;
}

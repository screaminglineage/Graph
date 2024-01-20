# Graph

Simple Graph Implementation in C using a single header file, inspired by https://github.com/nothings/stb/.

The graph is currently uses an [Adjacency List](https://en.wikipedia.org/wiki/Adjacency_list). 
However some other required structures are currently allocated on the stack which need to be updated to use dynamic allocation instead.
Also supports performing Breadth First Search as well as automatically adding the corresponding opposite vertex when a vertex is added, 
ie. adding vertices 0 and 1, (using `graph_add_vertex`) will also add vertices 1 and 0 correspondingly to the adjacency list.


## Build Instructions

```
gcc main.c -o main
```

## Using Graph.h

To include Graph.h, do as follows

```c
#define GRAPH_H_IMPLEMENTATION
#include "Vector.h"
```

If `GRAPH_H_IMPLEMENTATION` is not defined, Vector.h acts as a header file with only the forward declarations so that the functions can be rewritten if required. Adding `GRAPH_H_IMPLEMENTATION`, makes it behave like a fully featured library.

The macro `GRAPH_VERTEX_MAX` can be defined to change the maximum no. of vertices that can be added. Note that this uses stack allocation (for now), so increasing too much may cause an overflow.

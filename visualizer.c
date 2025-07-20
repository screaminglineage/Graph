#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>
#include <time.h>

#define GRAPH_H_IMPLEMENTATION
#include "Graph.h"


int main() {
    Graph g = {0};

    Vector2 points[GRAPH_VERTEX_MAX] = {0};
    size_t points_count = 0;

    long seed = 1753009477;
    srand(seed);

    InitWindow(800, 600, "Graph");
    SetTargetFPS(60);

    int radius = 15;

    bool started = false;
    bool dragging = false;
    size_t source = 0;
    bool doing_bfs = false;
    size_t bfs_i = 0;

    Vertices bfs_vertices = {0};
    bool running = true;
    while (running && !WindowShouldClose()) {
        Vector2 mouse_pos = GetMousePosition();

        if (IsKeyPressed(KEY_Q)) {
            running = false;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            started = true;
        }

        if (started) {
            if (IsKeyPressed(KEY_ESCAPE)) {
                started = false;
            }

            if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON)) {
                points[points_count++] = mouse_pos;
            }

            if (dragging) {
                DrawLineV(points[source], mouse_pos, WHITE);
                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                    dragging = false;
                    for (size_t i = 0; i < points_count; i++) {
                        if (i != source && CheckCollisionPointCircle(mouse_pos, points[i], radius)) {
                            graph_add_edge(&g, source, i);
                            break;
                        }
                    }
                }
            } else {
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    for (size_t i = 0; i < points_count; i++) {
                        if (CheckCollisionPointCircle(mouse_pos, points[i], radius)) {
                            dragging = true;
                            source = i;
                            break;
                        }
                    }
                }
                if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                    for (size_t i = 0; i < points_count; i++) {
                        if (CheckCollisionPointCircle(mouse_pos, points[i], radius)) {
                            doing_bfs = true;
                            bfs_i = 0;
                            graph_bfs(&g, i, &bfs_vertices);
                            break;
                        }
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (!started) {
            DrawText("MMB - Add Vertex\n"
                    "LMB - Connect Vertices\n"
                    "RMB - Start BFS from target\n"
                    "Esc - Show This Screen\n"
                    "Q - Quit\n\n"
                    "Press ENTER to begin!",
            100, 100, 40, WHITE);
        }

        for (size_t i = 0; i < points_count; i++) {
            Color color = (doing_bfs && i == bfs_vertices.data[bfs_i])? RED: BLUE;
            DrawCircleLinesV(points[i], radius, color);
            Vertices neighbours = graph_vertices(&g, i);
            for (size_t j = 0; j < neighbours.size; j++) {
                size_t neighbour = neighbours.data[j];
                DrawLineV(points[i], points[neighbour], WHITE);
            }
        }
        if (doing_bfs) WaitTime(0.5);
        EndDrawing();

        if (doing_bfs) {
            if (bfs_i < bfs_vertices.size) {
                bfs_i++;
            } else {
                doing_bfs = false;
                bfs_i = 0;
                bfs_vertices.size = 0;
            }
        }
    }
    CloseWindow();
    return 0;
}

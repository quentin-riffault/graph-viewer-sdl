#ifndef GRAPH_VIEWER_APP_DRAW_H
#define GRAPH_VIEWER_APP_DRAW_H

#include "graph_viewer/graph.h"
#include "app/sdl.h"

int to_world(float x, int dimension);
void draw_node(Node* node, SDL_Renderer* renderer);
void draw_link(Link* link, SDL_Renderer* renderer);

#endif
#ifndef GRAPH_SDL_LIB
#define GRAPH_SDL_LIB

#include <SDL2/SDL_render.h>
#include <stdbool.h>

typedef float vec2[2];

typedef struct Node {
    unsigned int id;

    float value;

    vec2 pos;
    vec2 movement_vector;
} Node;

typedef struct Link {
    Node* from;
    Node* to;
    bool bidirectional;
    float weight;
} Link;

Node* create_node(float value);
Link* create_link(
    Node* from, 
    Node* to, 
    bool bidirectional, 
    float weight
);





#endif //GRAPH_SDL_LIB
#include "graph_viewer/graph.h"
#include <stdlib.h>

Node* create_node(float value){

    static unsigned int id = 0;
    Node* n = (Node*)malloc(sizeof(Node));

    if(n == NULL) return NULL;

    float x = (float)(rand())/RAND_MAX;
    float y = (float)(rand())/RAND_MAX;

    n->id = id;
    n->value = value;
    n->pos[0] = x;
    n->pos[1] = y;
    n->movement_vector[0] = 0.0f;
    n->movement_vector[1] = 0.0f;

    id++;

    return n;
}

Link* create_link(
    Node* from, 
    Node* to, 
    bool bidirectional, 
    float weight
){
    Link* l = (Link*)malloc(sizeof(Link));

    if(l == NULL || from == NULL || to == NULL) return NULL;
    
    l->from = from;
    l->to = to;
    l->bidirectional = bidirectional;
    l->weight = weight;

    return l;
}


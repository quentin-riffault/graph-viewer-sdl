#ifndef GV_PHYSICS_H
#define GV_PHYSICS_H

#include "graph_viewer/graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define POW(x) (x)*(x)

#define K 0.1f

float gv_node_distance(Node* a, Node* b);

void compute_direction_vector(const vec2 a, const vec2 b, vec2* result);

void compute_common_repulsion(Node* a, Node* b);
void compute_common_attraction(Link* l);
void compute_center_attraction(Node *a){

};
void apply_forces(Node** nodes, int num_nodes, float dt);

#endif
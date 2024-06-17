#include "graph_viewer/physics.h"

float gv_node_distance(Node* a, Node* b){
    return sqrt(
        POW(a->pos[0] - b->pos[0]) + 
        POW(a->pos[1] - b->pos[1])
    );
}

/**
 * Acts as two same-polarity magnets. The closer they are, the more they repulse. 
 */
void compute_common_repulsion(Node* a, Node* b){
    const float dist = gv_node_distance(a,b);

    if(dist > 0.7){
        return;
    }

    const float force = fminf(K, (2*K*dist));

    vec2 dir = {0.0f};
    compute_direction_vector(a->pos, b->pos, &dir);

    a->movement_vector[0] -= dir[0]*force;
    a->movement_vector[1] -= dir[1]*force;

    b->movement_vector[0] -= a->movement_vector[0];
    b->movement_vector[1] -= a->movement_vector[0];


    printf("[Repulsion %d -> %d]: (%f, %f)\n", 
        a->id, 
        b->id, 
        dir[0]*force, 
        dir[1]*force
    );

}

/**
 * Acts as a spring. When two nodes are connected but far, they attract.
 * If they are near, they attract much less.
 */
void compute_common_attraction(Link* l){
    const float dist = gv_node_distance(l->from, l->to);

    Node* a = l->to;
    Node* b = l->from;

    if(dist < K){
        return;
    }

    const float force = fminf(K, (2*K*dist));

    vec2 dir = {0.0f};
    compute_direction_vector(a->pos, b->pos, &dir);

    a->movement_vector[0] = dir[0]*force;
    a->movement_vector[1] = dir[1]*force;

    b->movement_vector[0] = - a->movement_vector[0];
    b->movement_vector[1] = - a->movement_vector[1];

    printf("[Attraction %d <-> %d]: (%f, %f)\n", 
        a->id, 
        b->id, 
        dir[0]*force, 
        dir[1]*force
    );
}

void apply_forces(Node** nodes, int num_nodes, float time){

    const float force_decay = expf(-time/100);

    for(int i = 0; i < num_nodes; i++){
        Node* current = nodes[i];
        if(current == NULL) break;

        vec2 new_pos = {
            fmaxf(0.05f, fminf(0.95f, current->pos[0] + current->movement_vector[0]*force_decay)),
            fmaxf(0.05f, fminf(0.95f, current->pos[1] + current->movement_vector[1]*force_decay)),
        };

        printf("[Node %d] position: (%f, %f), movement_vector: (%f, %f). New position: (%f, %f). Decay: %f\n", 
            current->id,
            current->pos[0], current->pos[1],
            current->movement_vector[0]*force_decay, current->movement_vector[1]*force_decay,
            new_pos[0], new_pos[1],
            force_decay
        );

        current->pos[0] = new_pos[0];
        current->pos[1] = new_pos[1];

        current->movement_vector[0] = 0.0f;
        current->movement_vector[1] = 0.0f;

    }
}

void compute_direction_vector(const vec2 a, const vec2 b, vec2* result){
    float norm = fmax(sqrt(
        POW(a[0] - b[0]) + 
        POW(a[1] - b[1])
    ), 1e-10);

    (*result)[0] = (b[0] - a[0])/norm;
    (*result)[1] = (b[1] - a[1])/norm;
}

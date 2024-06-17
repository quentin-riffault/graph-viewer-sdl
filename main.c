#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "graph_viewer/graph.h"
#include "graph_viewer/physics.h"

#include "app/draw.h"
#include "app/sdl.h"

#define MAX_NODES 300
#define MAX_LINKS 200
#define REFRESH_RATE 10.0f

void free_list(int count, void** array){
    for(int i = 0; i < count; i++){
        void* elt = array[i];
        if(elt == NULL) break;
        free(elt);
    }
}

int main(){

    SDL_Window* win = init_app();
    SDL_Renderer* mainRenderer = SDL_CreateRenderer(win, 0, 0);

    bool run = true;

    Node* node_list[MAX_NODES] = {NULL};
    Link* link_list[MAX_LINKS] = {NULL};

    node_list[0] = create_node(17.0f);
    node_list[1] = create_node(35.0f);
    node_list[2] = create_node(19.0f);
    
    link_list[0] = create_link(
        node_list[0],
        node_list[1],
        false,
        2.0f
    );

    const float dt = 1.0f/REFRESH_RATE;
    float simtime = 0.0f;

    while(run){
        SDL_Event event;
        
        while(SDL_PollEvent(&event)){
            handle_event(&event, &run);        
        }

        // All drawings        
        log_error(SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE));
        log_error(SDL_RenderClear(mainRenderer));

        // Draw nodes

        for(int i = 0; i < MAX_NODES; i++){
            Node* current = node_list[i];
            if(current == NULL){
                break;
            }
            
            draw_node(current, mainRenderer);
            for(int j = 0; j < MAX_NODES; j++){
                if(j == i){
                    continue;
                }

                Node* other = node_list[j]; 

                if( other == NULL ) break;
                compute_common_repulsion(current, other);
            }
        }
        
        // Draw links
        for(int i = 0; i < MAX_LINKS; i++){
            Link* l = link_list[i];
            if(l == NULL){
                break;
            }
            draw_link(l, mainRenderer);
            compute_common_attraction(l);
        }

        SDL_RenderPresent(mainRenderer);

        apply_forces(node_list, MAX_NODES, simtime);
        simtime += dt;
        sleep(dt);
    }

    free_list(MAX_NODES, (void**)node_list);
    free_list(MAX_LINKS, (void**)link_list);

    quit_app(mainRenderer, win);

    return 0;
}
#include "app/draw.h"

int to_world(float x, int dimension){
    return (int)(x * dimension);
}

void draw_node(Node* node, SDL_Renderer* renderer){

    // TODO: use SDL_RenderGeometry instead.
    SDL_Rect rect = {
        to_world(node->pos[0], WINDOW_WIDTH),
        to_world(node->pos[1], WINDOW_HEIGHT),
        (int)node->value,
        (int)node->value
    };
    log_error(SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE));
    log_error(SDL_RenderFillRect(renderer, &rect));

}

void draw_link(Link* link, SDL_Renderer* renderer){
    // Link representation here
    log_error(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 125));
    log_error(SDL_RenderDrawLine(
        renderer,
        to_world(link->from->pos[0], WINDOW_WIDTH) + link->from->value/2,
        to_world(link->from->pos[1], WINDOW_HEIGHT) + link->from->value/2,
        to_world(link->to->pos[0], WINDOW_WIDTH) + link->to->value/2,
        to_world(link->to->pos[1], WINDOW_HEIGHT) + link->to->value/2
    ));
}
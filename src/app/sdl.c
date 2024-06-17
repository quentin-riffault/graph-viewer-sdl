#include "app/sdl.h"

void log_error(int return_code){
    if(return_code) {
        const char* error = SDL_GetError();
        printf("An error occured: %s", error);
        SDL_ClearError();
    }
}

SDL_Window* init_app(){

    const int init_state = SDL_Init(
        SDL_INIT_VIDEO |
        SDL_INIT_EVENTS
    );

    if(init_state){
        const char* error = SDL_GetError();
        printf("An error occured while initializing SDL2 systems: %s\n", error);
        exit(1);
    }

    SDL_Window* win = SDL_CreateWindow(
        APP_TITLE, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        WINDOW_WIDTH, 
        WINDOW_HEIGHT,
        0
    );

    return win;

}

void quit_app(SDL_Renderer* renderer, SDL_Window* win){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void handle_event(const SDL_Event* event, bool* shall_continue){
    switch(event->type){
        case SDL_WINDOWEVENT:
            if(event->window.event == SDL_WINDOWEVENT_CLOSE){
                *shall_continue = false;
            }
            break;
    }
}
#include "graph_sdl.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_error.h"
#include "SDL2/SDL_video.h"
#include <stdio.h>
#include <unistd.h>

#define APP_TITLE "GraphView"
#define WINDOW_WIDTH    480
#define WINDOW_HEIGHT   480




SDL_Window* init_app();
void quit_app(SDL_Window*);
int main();


int main(){

    SDL_Window* win = init_app();

    sleep(5);

    quit_app(win);

    return 0;
}

SDL_Window* init_app(){

    const int init_state = SDL_Init(
        SDL_INIT_VIDEO |
        SDL_INIT_EVENTS
    );

    if(init_state){
        const char* error = SDL_GetError();
        printf("An error occured: %s\n", error);
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

void quit_app(SDL_Window* win){
    SDL_DestroyWindow(win);
    SDL_Quit();
}
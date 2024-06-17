#ifndef GRAPH_VIEWER_APP_SDL_H
#define GRAPH_VIEWER_APP_SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h> // For testing purpose only. TODO: remove.
#include <SDL2/SDL_render.h>

#include <stdbool.h>

#define WINDOW_WIDTH    1920
#define WINDOW_HEIGHT   1280
#define APP_TITLE "GraphView"


void log_error(int return_code);
SDL_Window* init_app();
void quit_app(SDL_Renderer*, SDL_Window*);
void handle_event(const SDL_Event*, bool*);


#endif
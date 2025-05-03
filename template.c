#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "menu.h"
#include "gamestate.c"
#include <stdlib.h>
#include <stdio.h>

static SDL_Window *window;
static SDL_Renderer *renderer;
static int w;
static int h;
int gamestate;


/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{    
 
    SDL_SetAppMetadata("SDL Menu template", "1.0", "");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Menu Sample", 640, 480, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    int num_displays;
    SDL_DisplayID *displays = SDL_GetDisplays(&num_displays);
    const SDL_DisplayMode *mode = SDL_GetDesktopDisplayMode(*displays);
    SDL_Log("Found %d display(s)", num_displays);
    SDL_Log("Display ID: %d", *displays);
    SDL_Log("Width: %d, height: %d",mode->w,mode->h);
    SDL_Log("Refresh rate: %f",mode->refresh_rate);

    w = mode->w;
    h = mode->h;
    SDL_SetWindowSize(window, mode->w, mode->h);

    SDL_free(displays);

    gamestate = INTRO_SCREEN;

    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_GetRenderOutputSize(renderer, &w, &h);
    //SDL_SetRenderScale(renderer, 2, 2);
    /* clear the window to the draw color. */
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    char *tick = malloc(sizeof(long unsigned int));
    sprintf(tick, "%ld", SDL_GetTicks());

    SDL_RenderDebugText(renderer, 0, 0, tick);

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{

}
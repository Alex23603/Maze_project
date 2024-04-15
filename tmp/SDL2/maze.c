#include <SDL.h>
#include <SDL2/SDL.h>
int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    int quit = 0;

    /*INITIALIZATION*/
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL initialization error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Window creation error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Renderer creation error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set render color and draw a rectangle
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red color
    SDL_Rect rect = {100, 100, 200, 200};
    SDL_RenderFillRect(renderer, &rect);

    // Update screen and handle events
    SDL_RenderPresent(renderer);
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    // Cleanup and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

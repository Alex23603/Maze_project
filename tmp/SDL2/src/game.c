#include "game.h"
#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TILE_SIZE 64
#define MAP_WIDTH 10
#define MAP_HEIGHT 10

/* Define the game state and variables */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *wallTexture = NULL;
static SDL_Texture *floorTexture = NULL;
static int playerX = 1;
static int playerY = 1;
static char map[MAP_HEIGHT][MAP_WIDTH] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '#', '#', '#', '#', '#', '#', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
    {'#', '.', '#', '.', '#', '#', '.', '#', '.', '#'},
    {'#', '.', '#', '.', '.', '#', '.', '#', '.', '#'},
    {'#', '.', '#', '#', '.', '#', '.', '#', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

/**
 * init_game - Initialize the game
 */
void init_game(void)
{
    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL initialization error: %s\n", SDL_GetError());
        exit(1);
    }

    /* Create window and renderer */
    window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Window creation error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Renderer creation error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    /* Load textures */
    wallTexture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("wall.bmp"));
    if (!wallTexture) {
        fprintf(stderr, "Failed to load wall texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    floorTexture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("floor.bmp"));
    if (!floorTexture) {
        fprintf(stderr, "Failed to load floor texture: %s\n", SDL_GetError());
        SDL_DestroyTexture(wallTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    printf("Initializing game...\n");
}

/**
 * render_game - Render the game world
 */
void render_game(void)
{
    int x, y;
    SDL_Rect wallRect = {0, 0, TILE_SIZE, TILE_SIZE};
    SDL_Rect floorRect = {0, 0, TILE_SIZE, TILE_SIZE};

    /* Clear the renderer */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    /* Render the map */
    for (y = 0; y < MAP_HEIGHT; y++) {
        for (x = 0; x < MAP_WIDTH; x++) {
            wallRect.x = x * TILE_SIZE;
            wallRect.y = y * TILE_SIZE;
            floorRect.x = x * TILE_SIZE;
            floorRect.y = y * TILE_SIZE;

            if (map[y][x] == '#') {
                SDL_RenderCopy(renderer, wallTexture, NULL, &wallRect);
            } else {
                SDL_RenderCopy(renderer, floorTexture, NULL, &floorRect);
            }
        }
    }

    /* Render player position */
    SDL_Rect playerRect = {playerX * TILE_SIZE, playerY * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red color
    SDL_RenderFillRect(renderer, &playerRect);

    /* Update the screen */
    SDL_RenderPresent(renderer);
}

/**
 * handle_input - Handle user input
 * @input: The input received from the user
 */
void handle_input(int input)
{
    /* Handle input to move player */
    switch (input) {
        case 'w':
            if (map[playerY - 1][playerX] != '#') {
                playerY--;
            }
            break;
        case 'a':
            if (map[playerY][playerX - 1] != '#') {
                playerX--;
            }
            break;
        case 's':
            if (map[playerY + 1][playerX] != '#') {
                playerY++;
            }
            break;
        case 'd':
            if (map[playerY][playerX + 1] != '#') {
                playerX++;
            }
            break;
        default:
            break;
    }
}
/**
 * cleanup_game - Cleanup resources used by the game
 */
void cleanup_game(void)
{
    /* Cleanup resources */
    SDL_DestroyTexture(wallTexture);
    SDL_DestroyTexture(floorTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("Cleaning up game resources...\n");
}
/**
 * cleanup_game - Cleanup resources used by the game
 */
void cleanup_game(void)
{
    /* Cleanup resources */
    SDL_DestroyTexture(wallTexture);
    SDL_DestroyTexture(floorTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("Cleaning up game resources...\n");
}

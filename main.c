#include "action.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TILE_SIZE 50  // Taille d'une case en pixels
#define WINDOW_WIDTH (WIDTH * TILE_SIZE + 200)
#define WINDOW_HEIGHT (HEIGHT * TILE_SIZE)

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    srand(time(NULL));
    terrain *t = returnMap();
    int px, py;
    char action = ' ';

    setCarac(t, 0);  // Place le personnage
    setCarac(t, 1);  // Place la sortie

    // === Initialisation SDL ===
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur d'initialisation de SDL: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL Maze Game", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    if (!window || !renderer) {
        printf("Erreur de création de la fenêtre ou du renderer: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    printMap(t);

    int quit = 0;
    while (!quit) {
        // === Gestion des événements (clavier / fermeture) ===
        action = ' ';

        px = getCaracX(t);
        py = getCaracY(t);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    printf("QUIT = %c", action);
                    quit = 1;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    printf("SDL KEY = %c", action);
                    if (event.key.scancode == SDL_SCANCODE_UP) {
                        action = 'z';
                    } else if (event.key.scancode == SDL_SCANCODE_DOWN) {
                        action = 's';
                    } else if (event.key.scancode == SDL_SCANCODE_LEFT) {
                        action = 'q';
                    } else if (event.key.scancode == SDL_SCANCODE_RIGHT) {
                        action = 'd';
                    } else if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
                        quit = 1;
                    } else {
                        break;
                    }
                    break;
            }
        }
        if (action && action != ' ') {
            action = moveCarac(t, px, py, action);
            printMap(t);
            if (action == 'l')
                quit = 1;
        }

        // === Rendu graphique ===
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Fond noir
        SDL_RenderClear(renderer);

        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                SDL_Rect rect = {x * 50, y * 50, 50, 50};

                if (t->map[y][x] == BORDER || t->map[y][x] == WALL) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Rouge
                } else if (t->map[y][x] == MAINCARACTERE) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Jaune (perso)
                } else if (t->map[y][x] == FINISH) {
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Vert (sortie)
                } else {
                    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Gris clair (sol)
                }
                SDL_RenderFillRect(renderer, &rect);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(100); // Pause pour éviter une boucle trop rapide
    }

    // === Nettoyage ===
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

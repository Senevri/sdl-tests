#include <SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window* setup() {
    SDL_Window *window = NULL;
    //SDL_Surface *surface = NULL;
    if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS )) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    };
    window = SDL_CreateWindow(
        "testkbd",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN
    );
    return window;
}

int teardown(SDL_Window *window) {
    SDL_DestroyWindow(window);
    return 0;
}

int test_keyboard() {
    SDL_Event e;
    while(true) {
        if ( SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    return 0;
                case SDL_KEYDOWN:
                    printf("scancode %d, keycode %d\n", e.key.keysym.scancode, e.key.keysym.sym);
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        return 0;
                    }
            }
        }
        SDL_Delay(1);
    }
    return 0;
}

int main (int argc, char* argv[]) {
    SDL_Window* window = setup();
    test_keyboard();
    return teardown(window);
}
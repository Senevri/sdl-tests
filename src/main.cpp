#include <SDL.h>
#include <SDL_TTF.h>
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
    TTF_Init();

    return window;
}

int teardown(SDL_Window *window) {
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit;
    return 0;
}

TTF_Font* loadfont(char* file, int ptsize) {
    auto tmpfont = TTF_OpenFont(file, ptsize);
    if (tmpfont == NULL) {
            printf("Unable to load font: %s %s \n", file, TTF_GetError());
    // Handle the error here.
    }
    return tmpfont;
}

int drawtext(SDL_Renderer *renderer, char *text) {
    SDL_RenderClear(renderer);
    SDL_Color textcolor = {0,240,0};
    auto font = loadfont("res\\CaskaydiaCoveMono.ttf", 24);
    auto rendered_text = TTF_RenderText_Solid(font, text, textcolor);
    auto texture = SDL_CreateTextureFromSurface(renderer, rendered_text);
    int w=0;
    int h=0;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);    
    SDL_Rect dstrect = {0,0,w,h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(rendered_text);
    TTF_CloseFont(font);
    return 0;
}

int test_keyboard(SDL_Window *window) {
    SDL_Event e;
    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,0);
    while(true) {
        if ( SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    return 0;
                case SDL_KEYDOWN:
                    char str[80];
                    sprintf(str, "scancode %d, keycode %d", e.key.keysym.scancode, e.key.keysym.sym);
                    printf("%s\n", str);
                    drawtext(renderer, str);
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        return 0;
                    }
            }
        }
        SDL_Delay(1);
    }
    SDL_DestroyRenderer(renderer);
    return 0;
}

int main (int argc, char* argv[]) {
    SDL_Window* window = setup();
    test_keyboard(window);
    return teardown(window);
}
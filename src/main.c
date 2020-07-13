#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(void)
{
#ifdef OS_Windows_NT
    printf("Windows dettected\n");
#elif defined OS_Linux
    printf("LINUS dettected\n");
#elif defined OS_Darwin
    printf("MacOS dettected\n");
#endif

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL)
    {
        printf("SDL_CreateWindow Error:  %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL)
    {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error:   %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;
    int i = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN)
            {
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                quit = true;
            }
        }
        //Clear screen
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(ren);
        // Render red filled quad
        SDL_Rect fillRect = {i++, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(ren, &fillRect);
        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
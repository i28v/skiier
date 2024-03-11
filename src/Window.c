#include "Window.h"

int Window_InitWindow(Window* self, const char* p_Title, unsigned int p_Width, unsigned int p_Height)
{
    int success = 1;
    self->m_Window = SDL_CreateWindow(p_Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_Width,p_Height, SDL_WINDOW_SHOWN);
    if(self->m_Window == NULL) {
        printf("ERROR: SDL Window could not be created, SDL Error: %s\n", SDL_GetError());

        success = 0;
    } else {
        self->m_Renderer = SDL_CreateRenderer(self->m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(self->m_Renderer == NULL) {
            printf("ERROR: SDL Renderer could not be created. SDL Error: %s\n", SDL_GetError());

            success = 0;
        }
    }

    return success;
}

void Window_Term(Window* self)
{
    SDL_DestroyRenderer(self->m_Renderer);

    SDL_DestroyWindow(self->m_Window);

    self->m_Window = NULL;

    self->m_Renderer = NULL;
}

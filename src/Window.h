#ifndef WINDOW_H
#define WINDOW_H

#include "Dependencies.h"

typedef struct {
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
} Window;

int Window_InitWindow(Window* self, const char* p_Title, unsigned int p_Width, unsigned int p_Height);
void Window_Term(Window* self);

#endif /* WINDOW_H */

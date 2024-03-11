#ifndef TEXTURE_H
#define TEXTURE_H

#include "Dependencies.h"

typedef struct {
    SDL_Texture* m_Texture;
} Texture;

int Texture_Init(Texture* self);
void Texture_Term(Texture* self);
int Texture_LoadTexture(Texture* self, SDL_Renderer* p_Renderer, const unsigned char* p_Texture, unsigned int p_Size);
void Texture_Render(Texture* self, SDL_Renderer* p_Renderer, SDL_Rect* p_Rect);

#endif /* TEXTURE_H */

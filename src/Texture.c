#include "Texture.h"

int Texture_Init(Texture* self)
{
    int success = 1;

    return success;
}

void Texture_Term(Texture* self)
{
    SDL_DestroyTexture(self->m_Texture);

    self->m_Texture = NULL;
}

int Texture_LoadTexture(Texture* self, SDL_Renderer* p_Renderer, const unsigned char* p_Texture, unsigned int p_Size)
{
    int success = 1;
    SDL_RWops* bmp_Array = SDL_RWFromConstMem((const unsigned char*)p_Texture, p_Size);
    SDL_Surface* t_Surface = SDL_LoadBMP_RW(bmp_Array, 1);
    if(t_Surface == NULL) {
        success = 0;
    } else {
        self->m_Texture = SDL_CreateTextureFromSurface(p_Renderer, t_Surface);
        if(self->m_Texture == NULL) {
            success = 0;
        }
    }
    SDL_FreeSurface(t_Surface);

    t_Surface = NULL;

    return success;
}

void Texture_Render(Texture* self, SDL_Renderer* p_Renderer, SDL_Rect* p_Rect)
{
    SDL_RenderCopy(p_Renderer, self->m_Texture, NULL, p_Rect);
}

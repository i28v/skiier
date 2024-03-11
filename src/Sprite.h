#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"
#include "Dependencies.h"

typedef struct {
    char* m_SpriteName;
    int m_XPos;
    int m_YPos;
    unsigned int m_Width;
    unsigned int m_Height;
    unsigned int m_Life;
    int m_HitboxOffsetX;
    int m_HitboxOffsetY;
    Texture* m_SpriteTexture;
    SDL_Rect m_Rect;
    SDL_Rect m_Hitbox;
} Sprite;

int Sprite_Init(Sprite* self, int p_XPos, int p_YPos, unsigned int p_Width, unsigned int p_Height, int p_HitboxOffsetX, int p_HitboxOffsetY, unsigned int p_HitboxWidth, unsigned int p_HitboxHeight, Texture* p_Texture, SDL_Renderer* p_Renderer, const char* p_SpriteName);
void Sprite_Term(Sprite* self);
void Sprite_Update(Sprite* self);
void Sprite_Render(Sprite* self, SDL_Renderer* p_Renderer);
void Sprite_SyncPositionToRect(Sprite* self);
void Sprite_SyncHitboxOffsetToRect(Sprite* self);

#endif /* SPRITE_H */

#include "Sprite.h"

int Sprite_Init(Sprite* self, int p_XPos, int p_YPos, unsigned int p_Width, unsigned int p_Height, int p_HitboxOffsetX, int p_HitboxOffsetY, unsigned int p_HitboxWidth, unsigned int p_HitboxHeight, Texture* p_Texture, SDL_Renderer* p_Renderer, const char* p_SpriteName)
{
    int success = 1;

    self->m_SpriteName = malloc((strlen(p_SpriteName)+1));

    strcpy(self->m_SpriteName, p_SpriteName);

/*    printf("Initializing sprite \"%s\"\n", self->m_SpriteName); */

    self->m_SpriteTexture = p_Texture;

    self->m_XPos = p_XPos;
    self->m_YPos = p_YPos;

    self->m_Width = p_Width;
    self->m_Height = p_Height;

    self->m_Hitbox.w = p_HitboxWidth;
    self->m_Hitbox.h = p_HitboxHeight;

    self->m_HitboxOffsetX = p_HitboxOffsetX;
    self->m_HitboxOffsetY = p_HitboxOffsetY;

    self->m_Rect.w = self->m_Width;
    self->m_Rect.h = self->m_Height;

    self->m_Life = 0;
    return success;
}

void Sprite_Term(Sprite* self)
{
/*    printf("Deleting sprite \"%s\"\n", self->m_SpriteName); */

    memset(self->m_SpriteName, 0, strlen(self->m_SpriteName)+1);

    free(self->m_SpriteName);

    self->m_SpriteName = NULL;
}

void Sprite_Update(Sprite* self)
{
    Sprite_SyncHitboxOffsetToRect(self);

    Sprite_SyncPositionToRect(self);

    self->m_Life++;
}

void Sprite_Render(Sprite* self, SDL_Renderer* p_Renderer)
{
    Texture_Render(self->m_SpriteTexture, p_Renderer, &self->m_Rect);
}

void Sprite_SyncPositionToRect(Sprite* self)
{
    self->m_Rect.x = self->m_XPos;

    self->m_Rect.y = self->m_YPos;
}

void Sprite_SyncHitboxOffsetToRect(Sprite* self)
{
    self->m_Hitbox.x = (self->m_XPos + self->m_HitboxOffsetX);

    self->m_Hitbox.y = (self->m_YPos + self->m_HitboxOffsetY);
}

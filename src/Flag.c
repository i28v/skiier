#include "Flag.h"

int Flag_Init(Flag* self, int p_XPos, int p_YPos, Texture* p_Texture, SDL_Renderer* p_Renderer)
{
    int success = 1;

    self->m_FlagSprite = malloc(sizeof(Sprite));

    memset(self->m_FlagSprite, 0, sizeof(Sprite));

    if(self->m_FlagSprite == NULL) {
        success = 0;
    } else {
        if(Sprite_Init(self->m_FlagSprite, p_XPos, p_YPos, FLAG_WIDTH, FLAG_HEIGHT, FLAG_HITBOX_OFFSET_X, FLAG_HITBOX_OFFSET_Y, FLAG_HITBOX_WIDTH, FLAG_HITBOX_HEIGHT, p_Texture, p_Renderer, "Flag") != 1) {
            success = 0;
        } else {
            self->m_FlagSprite->m_XPos = p_XPos;
            self->m_FlagSprite->m_YPos = p_YPos;
        }
    }
    return success;
}

void Flag_Term(Flag* self)
{
    Sprite_Term(self->m_FlagSprite);
    memset(self->m_FlagSprite, 0, sizeof(Sprite));
    free(self->m_FlagSprite);
    self->m_FlagSprite = NULL;
}

void Flag_Render(Flag* self, SDL_Renderer* p_Renderer)
{
    Sprite_Render(self->m_FlagSprite, p_Renderer);
}

void Flag_Update(Flag* self, int movespeed)
{
    Flag_Move(self, 0, -movespeed);
    Sprite_Update(self->m_FlagSprite);
}

void Flag_Move(Flag* self, int p_DirectionX, int p_DirectionY)
{
    self->m_FlagSprite->m_XPos += p_DirectionX;
    self->m_FlagSprite->m_YPos += p_DirectionY;
}

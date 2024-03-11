#ifndef FLAG_H
#define FLAG_H

#define FLAG_WIDTH 24 
#define FLAG_HEIGHT 48 

#define FLAG_HITBOX_OFFSET_X 0
#define FLAG_HITBOX_OFFSET_Y 48 

#define FLAG_HITBOX_WIDTH 8
#define FLAG_HITBOX_HEIGHT 4

#include "Sprite.h"

typedef struct {
    Sprite* m_FlagSprite;
} Flag;

int Flag_Init(Flag* self, int p_XPos, int p_YPos, Texture* p_Texture, SDL_Renderer* p_Renderer);
void Flag_Term(Flag* self);
void Flag_Render(Flag* self, SDL_Renderer* p_Renderer);
void Flag_Update(Flag* self, int movespeed);
void Flag_Move(Flag* self, int p_DirectionX, int p_DirectionY);

#endif /* FLAG_H */

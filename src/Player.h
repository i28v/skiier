#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_WIDTH 32 
#define PLAYER_HEIGHT 64 


#define PLAYER_HITBOX_OFFSET_X 0
#define PLAYER_HITBOX_OFFSET_Y 32 

#define PLAYER_HITBOX_WIDTH 32 
#define PLAYER_HITBOX_HEIGHT 32 


#include "Dependencies.h"
#include "Sprite.h"

typedef enum {
    Left=0, Down, Right
} PlayerDirection;

typedef struct {
    Sprite* m_PlayerSprite;
    PlayerDirection m_PlayerDirection;
} Player;

int Player_Init(Player* self, int p_XPos, int p_YPos, Texture* p_Texture, SDL_Renderer* p_Renderer);
void Player_Term(Player* self);
void Player_Render(Player* self, SDL_Renderer* p_Renderer);
void Player_Update(Player* self);
void Player_Move(Player* self, int p_DirectionX, int p_DirectionY);

#endif // PLAYER_H

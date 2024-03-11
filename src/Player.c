#include "Player.h"

int Player_Init(Player* self, int p_XPos, int p_YPos, Texture* p_Texture, SDL_Renderer* p_Renderer)
{
    int success = 1;

    self->m_PlayerSprite = malloc(sizeof(Sprite));

    memset(self->m_PlayerSprite, 0, sizeof(Sprite));

    if(Sprite_Init(self->m_PlayerSprite, p_XPos, p_YPos, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_HITBOX_OFFSET_X, PLAYER_HITBOX_OFFSET_Y, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, p_Texture, p_Renderer, "Player") != 1) {
        success = 0;
    } else {
        self->m_PlayerSprite->m_XPos = p_XPos;
        self->m_PlayerSprite->m_YPos = p_YPos;
        self->m_PlayerDirection = Down;
    }

    return success;
}

void Player_Term(Player* self)
{
    Sprite_Term(self->m_PlayerSprite);

    memset(self->m_PlayerSprite, 0, sizeof(Sprite));

    free(self->m_PlayerSprite);

    self->m_PlayerSprite = NULL;
}

void Player_Render(Player* self, SDL_Renderer* p_Renderer)
{
    Sprite_Render(self->m_PlayerSprite, p_Renderer);
}

void Player_Update(Player* self)
{
    Sprite_Update(self->m_PlayerSprite);
}

void Player_Move(Player* self, int p_DirectionX, int p_DirectionY)
{
    self->m_PlayerSprite->m_XPos += p_DirectionX;
    self->m_PlayerSprite->m_YPos += p_DirectionY;
}

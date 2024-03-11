#include "Tree.h"

int Tree_Init(Tree* self, int p_XPos, int p_YPos, Texture* p_Texture, SDL_Renderer* p_Renderer)
{
    int success = 1;

    self->m_TreeSprite = malloc(sizeof(Sprite));

    memset(self->m_TreeSprite, 0, sizeof(Sprite));

    if(Sprite_Init(self->m_TreeSprite, p_XPos, p_YPos, TREE_WIDTH, TREE_HEIGHT, TREE_HITBOX_OFFSET_X, TREE_HITBOX_OFFSET_Y, TREE_HITBOX_WIDTH, TREE_HITBOX_HEIGHT, p_Texture, p_Renderer, "Tree") != 1) {
        success = 0;
    } else {
        self->m_TreeSprite->m_XPos = p_XPos;
        self->m_TreeSprite->m_YPos = p_YPos;
    }

    return success;
}

void Tree_Term(Tree* self)
{
    Sprite_Term(self->m_TreeSprite);
    memset(self->m_TreeSprite, 0, sizeof(Sprite));
    free(self->m_TreeSprite);
    self->m_TreeSprite = NULL;
}

void Tree_Render(Tree* self, SDL_Renderer* p_Renderer)
{
    Sprite_Render(self->m_TreeSprite, p_Renderer);
}

void Tree_Update(Tree* self, int p_TreeMoveSpeed)
{
    Tree_Move(self, 0, -(p_TreeMoveSpeed));
    Sprite_Update(self->m_TreeSprite);
}

void Tree_Move(Tree* self, int p_DirectionX, int p_DirectionY)
{
    self->m_TreeSprite->m_XPos += p_DirectionX;
    self->m_TreeSprite->m_YPos += p_DirectionY;
}

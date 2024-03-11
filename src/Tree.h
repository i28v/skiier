#ifndef TREE_H
#define TREE_H

#define TREE_WIDTH 64 
#define TREE_HEIGHT 128 

#define TREE_HITBOX_OFFSET_X 30 
#define TREE_HITBOX_OFFSET_Y 120 

#define TREE_HITBOX_WIDTH 4
#define TREE_HITBOX_HEIGHT 8

#include "Sprite.h"

typedef struct
    t {
    Sprite* m_TreeSprite;
} Tree;

int Tree_Init(Tree* self, int p_XPos, int p_YPos, Texture* p_Texture, SDL_Renderer* p_Renderer);
void Tree_Term(Tree* self);
void Tree_Render(Tree* self, SDL_Renderer* p_Renderer);
void Tree_Update(Tree* self, int p_TreeMoveSpeed);
void Tree_Move(Tree* self, int p_DirectionX, int p_DirectionY);

#endif /* TREE_H */

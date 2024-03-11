#ifndef GAME_H
#define GAME_H

#define WINDOW_WIDTH 800 
#define WINDOW_HEIGHT 600 
#define WINDOW_NAME "Skiier"

#define TREE_ROW_SPAWN_THRESHOLD 50

#define TREE_MAX_YAW 45

#define SPAWN_MAX 16

#define TREE_ROW_SPAWN_Y 720

#define MAX_TREE_ROW_X_INCREMENT 70
#define MIN_TREE_ROW_X_INCREMENT 50

#define TREE_ROW_START_X -85

#define TREE_MOVE_SPEED 8

#define MAX_TREE_X 576
#define MIN_TREE_Y 608
#define MAX_TREE_Y -128

#define MAX_FLAG_X 576
#define MIN_FLAG_Y 608
#define MAX_FLAG_Y -128

#define PLAYER_START_X 363
#define PLAYER_START_Y 200

#define PLAYER_TURN_SPEED 3 

#define SCORE_INCREMENT 1

#define PLAYER_TEXTURE 0
#define TREE_TEXTURE 1
#define FLAG_TEXTURE 2

#include "Window.h"
#include "Sprite.h"
#include "Player.h"
#include "Tree.h"
#include "Flag.h"
#include "stack.h"
#include "CollisionDetection.h"

typedef struct {
    Window* m_GameWindow;
    SDL_Event m_EventHandler;
    Player* m_Player;
    stack m_Trees;
    stack m_Flags;
    stack m_TextureCache;
    int m_TreeMoveSpeed;
    int m_FlagStackTop;
    int m_TreeRowSpawnDelay;
    int m_TreeRowSpawnThreshold; 
    int m_Score;
    int m_IsPaused;
    int m_IsPausedKeyDown;
    int m_IsRunning;
} Game;

int Game_Init(Game* self);
void Game_Term(Game* self);
void Game_Events(Game* self);
void Game_Render(Game* self);
void Game_Update(Game* self);
/*int Game_InitSDL(Game* self);
int Game_InitWindow(Game* self);
int Game_InitIMG(Game* self);
int Game_InitTheActualGame(Game* self);
int Game_InitTextures(Game* self);
void Game_TermSprites(Game* self);
void Game_RenderTrees(Game* self);
void Game_RenderPlayer(Game* self);
void Game_UpdatePlayer(Game* self);
void Game_UpdateTrees(Game* self);
void Game_PushTree(Game* self, int p_XPos, int p_YPos);
void Game_PopTree(Game* self, unsigned int index);
void Game_PushFlag(Game* self);
void Game_PopFlag(Game* self);
*/
#endif /* GAME_H */

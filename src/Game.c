#include "Game.h"
#include "Random.h"
#include "Textures.h"
#include "Fonts.h"

static int Game_InitSDL(Game* self);
static int Game_InitWindow(Game* self);
static int Game_InitIMG(Game* self);
static int Game_InitTTF(Game* self);
static int Game_InitData(Game* self);
static int Game_InitTextures(Game* self);
static void Game_TermSprites(Game* self);
static void Game_RenderTrees(Game* self);
static void Game_RenderPlayer(Game* self);
static void Game_RenderFlags(Game* self);
static void Game_UpdatePlayer(Game* self);
static void Game_UpdateTrees(Game* self);
static void Game_UpdateFlags(Game* self);
static void Game_RenderScore(Game* self);
static void Game_PushTree(Game* self, int p_XPos, int p_YPos);
static void Game_PopTree(Game* self, int index);
static void Game_PushFlag(Game* self, int p_XPos, int p_YPos);
static void Game_PopFlag(Game* self, int index);

static TTF_Font* DejaVuSansMono = NULL;

static SDL_Color Black = {0, 0, 0};

static char ScoreText[128];

int Game_Init(Game* self)
{
    int success = 1;

    if(Game_InitSDL(self) != 1) {
        success = 0;
    } else {
        if(Game_InitWindow(self) != 1) {
            success = 0;
        } else {
            if(Game_InitIMG(self) != 1) {
                success = 0;
            } else {
                if(Game_InitTTF(self) != 1) {
                    success = 0;
                } else {
                    if(Game_InitTextures(self) != 1) {
                        success = 0;
                    } else {
                        if(Game_InitData(self) != 1) {
                            success = 0;
                        } else {
                            self->m_IsRunning = 1;
                        }
                    }
                }
            }
        }
    }
    return success;
}

static int Game_InitSDL(Game* self)
{
    int success = 1;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("ERROR: SDL could not initialize. SDL Error: %s\n", SDL_GetError());
        success = 0;
    }

    else {

    }
    return success;
}

static int Game_InitWindow(Game* self)
{
    int success = 1;

    self->m_GameWindow = malloc(sizeof(Window));

    memset(self->m_GameWindow, 0, sizeof(Window));

    if(Window_InitWindow(self->m_GameWindow, WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT) != 1) {
        success = 0;
    } else {
        SDL_SetRenderDrawColor(self->m_GameWindow->m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }

    return success;
}

static int Game_InitIMG(Game* self)
{
    int success = 1;

    int imgFlags = IMG_INIT_PNG;

    if(!(IMG_Init(imgFlags) & imgFlags)) {
        printf("ERROR: SDL_image could not initialize. SDL_image error: %s\n", IMG_GetError());

        success = 0;
    }

    return success;
}

static int Game_InitTTF(Game* self)
{
    int success = 1;
    if(TTF_Init() == -1) {
        printf("ERROR: SDL_ttf could not initialize. SDL Error: %s\n", TTF_GetError());
        success = 0;
    }
    return success;
}

static int Game_InitData(Game* self)
{
    int success = 1;
    self->m_IsPaused = 0;
    self->m_IsPausedKeyDown = 0;
    self->m_TreeRowSpawnDelay = 0;
    self->m_TreeRowSpawnThreshold = TREE_ROW_SPAWN_THRESHOLD;
    self->m_TreeMoveSpeed = TREE_MOVE_SPEED;
    self->m_Score = 0;
    self->m_Player = malloc(sizeof(Player));
    memset(self->m_Player, 0, sizeof(Player));
    stack_init(&self->m_Trees, 4);
    stack_init(&self->m_Flags, 4);
    Texture* texture = (Texture*)stack_get(&self->m_TextureCache, PLAYER_TEXTURE);
    if(Player_Init(self->m_Player, PLAYER_START_X, PLAYER_START_Y, texture, self->m_GameWindow->m_Renderer) != 1) {
        success = 0;
    }
    return success;
}

static int Game_InitTextures(Game* self)
{
    int success = 1;
    stack_init(&self->m_TextureCache, 4);
    Texture* player = malloc(sizeof(Texture));
    memset(player, 0, sizeof(Texture));
    if(Texture_LoadTexture(player, self->m_GameWindow->m_Renderer, Player_bmp, Player_bmp_len) != 1) {
        success = 0;
    } else {
        Texture* tree = malloc(sizeof(Texture));
        memset(tree, 0, sizeof(Texture));
        if(Texture_LoadTexture(tree, self->m_GameWindow->m_Renderer, Tree_bmp, Tree_bmp_len) != 1) {
            success = 0;
        } else {
            Texture* flag = malloc(sizeof(Texture));
            memset(flag, 0, sizeof(Texture));
            if(Texture_LoadTexture(flag, self->m_GameWindow->m_Renderer, Flag_bmp, Flag_bmp_len) != 1) {
                success = 0;
            } else {
                stack_push(&self->m_TextureCache, player);
                stack_push(&self->m_TextureCache, tree);
                stack_push(&self->m_TextureCache, flag);
                SDL_RWops* DejaVuSansMono_array = SDL_RWFromConstMem((const unsigned char*)DejaVuSansMono_ttf, DejaVuSansMono_ttf_len);
                DejaVuSansMono = TTF_OpenFontRW(DejaVuSansMono_array, 1, 32); 
                if(DejaVuSansMono == NULL) {
                    success = 0;
                }
            }
        }
    }
    return success;
}

void Game_Term(Game* self)
{
    Game_TermSprites(self);
    stack_delete(&self->m_Trees, 0);
    stack_delete(&self->m_Flags, 0);
    for(int i = 0; i < self->m_TextureCache.top; i++) {
        Texture* texture = (Texture*)stack_get(&self->m_TextureCache, i);
        Texture_Term(texture);
        memset(texture, 0, sizeof(Texture));
        free(texture);
    }
    stack_delete(&self->m_TextureCache, 0);
    Window_Term(self->m_GameWindow);
    memset(self->m_GameWindow, 0, sizeof(Window));
    free(self->m_GameWindow);
    self->m_GameWindow = NULL;
    TTF_Quit();
    SDL_Quit();
}

static void Game_TermSprites(Game* self)
{
    Player_Term(self->m_Player);
    memset(self->m_Player, 0, sizeof(Player));
    free(self->m_Player);
    self->m_Player = NULL;
    for(int i = 0; i < self->m_Trees.top; i++) {
        Tree* tree = (Tree*)stack_get(&self->m_Trees, i);
        Tree_Term(tree);
        memset(tree, 0, sizeof(Tree));
        free(tree);
    }
    for(int i = 0; i < self->m_Flags.top; i++) {
        Flag* flag = (Flag*)stack_get(&self->m_Flags, i);
        Flag_Term(flag);
        memset(flag, 0, sizeof(Flag));
        free(flag);
    }
}

void Game_Events(Game* self)
{
    while(SDL_PollEvent(&self->m_EventHandler) != 0) {
        switch(self->m_EventHandler.type) {
        case SDL_QUIT:
            self->m_IsRunning = 0;
        default:
            break;
        }
    }
}

void Game_Update(Game* self)
{
    const Uint8* keyPressed = SDL_GetKeyboardState(NULL);
    if(keyPressed[SDL_SCANCODE_LSHIFT] && self->m_IsPausedKeyDown == 0) {
        self->m_IsPausedKeyDown = 1;
        if(self->m_IsPaused == 0) {
            self->m_IsPaused = 1;
        } else if(self->m_IsPaused == 1) {
            self->m_IsPaused = 0;
        }
    } else if(!keyPressed[SDL_SCANCODE_LSHIFT] && self->m_IsPausedKeyDown == 1) {
        self->m_IsPausedKeyDown = 0;
    }
    if(keyPressed[SDL_SCANCODE_DOWN] && self->m_IsPaused == 0) {
        self->m_Player->m_PlayerDirection = Down;
    }
    if(keyPressed[SDL_SCANCODE_LEFT] && self->m_IsPaused == 0) {
        self->m_Player->m_PlayerDirection = Left;
    } else if(keyPressed[SDL_SCANCODE_RIGHT] && self->m_IsPaused == 0) {
        self->m_Player->m_PlayerDirection = Right;
    }
    if(self->m_IsPaused != 1) {
        if(self->m_TreeRowSpawnDelay < TREE_ROW_SPAWN_THRESHOLD) {
            switch(self->m_Player->m_PlayerDirection) {
            case Down:
                self->m_TreeRowSpawnDelay += 2;
                break;
            case Left: /* FALLTHROUGH */
            case Right:
                self->m_TreeRowSpawnDelay++;
                break;
            default:
                break;
            }
        } else {
            self->m_TreeRowSpawnDelay = 0;
            int spawn_x = TREE_ROW_START_X;
            int spawn_y = 0;
            int spawncount = 0;
            int spawnmax = SPAWN_MAX;
            int spawnflag = 0;
            int yaw = 0;
            int yawup = 0;
            do {
                yawup = rand_int(0, 1);
                yaw = rand_int(0, TREE_MAX_YAW);
                if(yawup) yaw = -yaw;
                spawn_y = TREE_ROW_SPAWN_Y + yaw;
                Game_PushTree(self, spawn_x, spawn_y);
                spawn_x += rand_int(MIN_TREE_ROW_X_INCREMENT, MAX_TREE_ROW_X_INCREMENT);
                spawnflag = rand_int(0, 10);
                spawncount++;
                if(spawnflag < 3) {
                    yawup = rand_int(0, 1);
                    yaw = rand_int(0, TREE_MAX_YAW);
                    if(yawup)yaw = -yaw;
                    spawn_y = TREE_ROW_SPAWN_Y + yaw;
                    Game_PushFlag(self, spawn_x, spawn_y);
                    spawn_x += rand_int(MIN_TREE_ROW_X_INCREMENT, MAX_TREE_ROW_X_INCREMENT);
                    spawncount++;
                }
            } while(spawncount < spawnmax);
        }
        Game_UpdatePlayer(self);
        Game_UpdateTrees(self);
        Game_UpdateFlags(self);
    }
}

void Game_Render(Game* self)
{
    SDL_RenderClear(self->m_GameWindow->m_Renderer);
    Game_RenderPlayer(self);
    Game_RenderFlags(self);
    Game_RenderTrees(self);
    Game_RenderScore(self);
    SDL_RenderPresent(self->m_GameWindow->m_Renderer);
}

static void Game_UpdatePlayer(Game* self)
{
    switch(self->m_Player->m_PlayerDirection) {
    case Left:
        Player_Move(self->m_Player, -PLAYER_TURN_SPEED, 0);
        break;
    case Right:
        Player_Move(self->m_Player, PLAYER_TURN_SPEED, 0);
        break;
    case Down:
    default:
        break;
    }

    Player_Update(self->m_Player);
}

static void Game_UpdateTrees(Game* self)
{
    for(int i = self->m_Trees.top; i --> 0; ) {
        Tree* tree = (Tree*)stack_get(&self->m_Trees, i);
        switch(self->m_Player->m_PlayerDirection) {
        case Down:
            Tree_Update(tree, self->m_TreeMoveSpeed);
            break;
        case Left: /* FALLTHROUGH */
        case Right:
            Tree_Update(tree, self->m_TreeMoveSpeed / 2);
            break;
        default:
            break;
        }
        if(tree->m_TreeSprite->m_YPos <= MAX_TREE_Y) {
            Game_PopTree(self, i);
        } else {
            if(CheckCollision(self->m_Player->m_PlayerSprite->m_Hitbox, tree->m_TreeSprite->m_Hitbox)) {
                self->m_IsRunning = 0;
            }
        }
    }
}

static void Game_UpdateFlags(Game* self)
{
    for(int i = self->m_Flags.top; i --> 0; ) {
        Flag* flag = (Flag*)stack_get(&self->m_Flags, i);
        switch(self->m_Player->m_PlayerDirection) {
        case Down:
            Flag_Update(flag, self->m_TreeMoveSpeed);
            break;
        case Left: /* FALLTHROUGH */
        case Right:
            Flag_Update(flag, self->m_TreeMoveSpeed / 2);
            break;
        default:
            break;
        }
        if(flag->m_FlagSprite->m_YPos <= MAX_TREE_Y) {
            Game_PopFlag(self, i);
        } else {
            if(CheckCollision(self->m_Player->m_PlayerSprite->m_Hitbox, flag->m_FlagSprite->m_Hitbox)) {
                Game_PopFlag(self, i);
                self->m_Score += SCORE_INCREMENT;
            }
        }
    }
}

static void Game_RenderPlayer(Game* self)
{
    Player_Render(self->m_Player, self->m_GameWindow->m_Renderer);
}

static void Game_RenderTrees(Game* self)
{
    for(int i = 0; i < self->m_Trees.top; i++) {
        Tree* tree = (Tree*)stack_get(&self->m_Trees, i);
        Tree_Render(tree, self->m_GameWindow->m_Renderer);
    }
}

static void Game_RenderFlags(Game* self)
{
    for(int i = 0; i < self->m_Flags.top; i++) {
        Flag* flag = (Flag*)stack_get(&self->m_Flags, i);
        Flag_Render(flag, self->m_GameWindow->m_Renderer);
    }
}

static void Game_RenderScore(Game* self)
{
    if(self->m_Score < 9999) {
        memset(ScoreText, 0, strlen(ScoreText));
        sprintf(ScoreText, "Score: %04d", self->m_Score);
        SDL_Surface* ScoreSurface = TTF_RenderText_Solid(DejaVuSansMono, ScoreText, Black);
        SDL_Texture* Message = SDL_CreateTextureFromSurface(self->m_GameWindow->m_Renderer, ScoreSurface);
        SDL_Rect ScoreRect;
        ScoreRect.x = 5;
        ScoreRect.y = 5;
        ScoreRect.w = 150;
        ScoreRect.h = 25;
        SDL_RenderCopy(self->m_GameWindow->m_Renderer, Message, NULL, &ScoreRect);
        SDL_FreeSurface(ScoreSurface);
        SDL_DestroyTexture(Message);
    }
}

static void Game_PushTree(Game* self, int p_XPos, int p_YPos)
{
    Tree* tree = malloc(sizeof(Tree));
    memset(tree, 0, sizeof(Tree));
    Texture* texture = (Texture*)stack_get(&self->m_TextureCache, TREE_TEXTURE);
    Tree_Init(tree, p_XPos, p_YPos, texture, self->m_GameWindow->m_Renderer);
    stack_push(&self->m_Trees, tree);
}

static void Game_PushFlag(Game* self, int p_XPos, int p_YPos)
{
    Flag* flag = malloc(sizeof(Flag));
    memset(flag, 0, sizeof(Flag));
    Texture* texture = (Texture*)stack_get(&self->m_TextureCache, FLAG_TEXTURE);
    Flag_Init(flag, p_XPos, p_YPos, texture, self->m_GameWindow->m_Renderer);
    stack_push(&self->m_Flags, flag);
}

static void Game_PopTree(Game* self, int index)
{
    Tree* tree = (Tree*)stack_get(&self->m_Trees, index);
    Tree_Term(tree);
    memset(tree, 0, sizeof(Tree));
    free(tree);
    stack_remove(&self->m_Trees, index, 0);
}

static void Game_PopFlag(Game* self, int index)
{
    Flag* flag = (Flag*)stack_get(&self->m_Flags, index);
    Flag_Term(flag);
    memset(flag, 0, sizeof(Flag));
    free(flag);
    stack_remove(&self->m_Flags, index, 0);
}

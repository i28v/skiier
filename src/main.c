#include "Game.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));
    Game* game = malloc(sizeof(Game));
    memset(game, 0, sizeof(Game));
    if(Game_Init(game) != 1) {
        printf("ERROR: Game could not initialize\n"); 
        Game_Term(game);
        memset(game, 0, sizeof(Game));
        free(game);        
        return 1;
    } else {
        while(game->m_IsRunning == 1) {
            Game_Events(game);
            Game_Update(game);
            Game_Render(game);
        }
    }
    Game_Term(game);
    memset(game, 0, sizeof(Game)); 
    free(game);
    return 0;
}

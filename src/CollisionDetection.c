#include "CollisionDetection.h"

int CheckCollision(SDL_Rect p_RectA, SDL_Rect p_RectB)
{
    int leftA, leftB;

    int rightA, rightB;

    int topA, topB;

    int bottomA, bottomB;

    leftA = p_RectA.x;

    rightA = p_RectA.x + p_RectA.w;

    topA = p_RectA.y;

    bottomA = p_RectA.y + p_RectA.h;

    leftB = p_RectB.x;

    rightB = p_RectB.x + p_RectB.w;

    topB = p_RectB.y;

    bottomB = p_RectB.y + p_RectB.h;

    if(bottomA <= topB) {
        return 0;
    }

    if(topA >= bottomB) {
        return 0;
    }

    if(rightA <= leftB) {
        return 0;
    }

    if(leftA >= rightB) {
        return 0;
    }

    return 1;
}

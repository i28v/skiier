#include "Random.h"
#include <stdlib.h>

int rand_int(int min, int max)
{
    return min + rand() % (max+1 - min);
}

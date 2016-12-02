
#include <stdlib.h>
#include <time.h>

#include "game.h"

int dice_point()
{
  srand(time(0));
  return rand() % 6 + 1;
}

char isWon()
{
  if (dice_point() > 3){
    return true;
  }
  return false;
}

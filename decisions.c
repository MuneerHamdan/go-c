#include <ncurses.h>
//#include "main.h"
#include "board.h"

int getLiberties(Board (*board)[BX], Stone* stone) {
  if (stone == NULL)
    return 0;
  stone->liberties = 4;
//  if (board[stone->bpos.y][stone->bpos.x-1].stone != NULL || (stone->bpos.x-1) < 0 || (stone->bpos.x-1) >= BX)
//    stone->liberties--;
//  if (board[stone->bpos.y][stone->bpos.x+1].stone != NULL || (stone->bpos.x+1) < 0 || (stone->bpos.x+1) >= BX)
//    stone->liberties--;
//  if (board[stone->bpos.y-1][stone->bpos.x].stone != NULL || (stone->bpos.y-1) < 0 || (stone->bpos.y-1) >= BY)
//    stone->liberties--;
//  if (board[stone->bpos.y+1][stone->bpos.x].stone != NULL || (stone->bpos.y+1) < 0 || (stone->bpos.y+1) >= BY)
//    stone->liberties--;

  return stone->liberties;
}

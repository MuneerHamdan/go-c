#include <ncurses.h>
#include "main.h"
#include "board.h"

int getLiberties(WINDOW* win, Board (*board)[BX], Stone* stone) {
  stone->liberties = 4;
  if (board[stone->bpos.y][stone->bpos.x-1].stone != NULL) stone->liberties--;
  if (board[stone->bpos.y][stone->bpos.x+1].stone != NULL) stone->liberties--;
  if (board[stone->bpos.y-1][stone->bpos.x].stone != NULL) stone->liberties--;
  if (board[stone->bpos.y+1][stone->bpos.x].stone != NULL) stone->liberties--;

  if (stone->bpos.y == 0 || stone->bpos.y == BY) stone->liberties--;
  if (stone->bpos.x == 0 || stone->bpos.x == BX) stone->liberties--;
  return stone->liberties;
}
void updateLiberties(WINDOW* win, Board (*board)[BX]) {
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      if (board[i][j].stone != NULL)
        board[i][j].stone->liberties = getLiberties(win, board, board[i][j].stone);
    }
  }
}
/*
 * ok so basically, wen you add a stone, check if its cardinal adjacent to a same colored group
 * if it is, add that stone to that group
 * else, it becomes its own group
 *
 * POSSIBLY MAKE A GROUP DYNAMIC MEMORY???????????
 */
void addtogroup(Board (*board)[BX], Stone* stone){
  // have to make only join color it belongs to
  if (board[stone->bpos.y][stone->bpos.x-1].stone != NULL && board[stone->bpos.y][stone->bpos.x-1].stone->group != NULL && board[stone->bpos.y][stone->bpos.x-1].stone->c == stone->c) stone->group = board[stone->bpos.y][stone->bpos.x-1].stone->group;
  else if (board[stone->bpos.y][stone->bpos.x+1].stone != NULL && board[stone->bpos.y][stone->bpos.x+1].stone->group != NULL && board[stone->bpos.y][stone->bpos.x+1].stone->c == stone->c) stone->group = board[stone->bpos.y][stone->bpos.x+1].stone->group;
  else if (board[stone->bpos.y-1][stone->bpos.x].stone != NULL && board[stone->bpos.y-1][stone->bpos.x].stone->group != NULL && board[stone->bpos.y-1][stone->bpos.x].stone->c == stone->c) stone->group = board[stone->bpos.y-1][stone->bpos.x].stone->group;
  else if (board[stone->bpos.y+1][stone->bpos.x].stone != NULL && board[stone->bpos.y+1][stone->bpos.x].stone->group != NULL && board[stone->bpos.y+1][stone->bpos.x].stone->c == stone->c) stone->group = board[stone->bpos.y+1][stone->bpos.x].stone->group;

  // have to make it make the liberties combined and shared among all groups members

  // what if there's two or more valid groups to join
}

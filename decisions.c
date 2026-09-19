#include <ncurses.h>
#include "main.h"
#include "board.h"

void updateGroupLiberties(Board (*board)[BX], Stone* group) {
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      if (board[i][j].stone != NULL && board[i][j].stone->group != NULL && board[i][j].stone->group == group) {
        group->liberties++;
      }
    }
  }
}
int getLiberties(Board (*board)[BX], Stone* stone) {
  stone->liberties = 4;
  if (board[stone->bpos.y][stone->bpos.x-1].stone != NULL) stone->liberties--;
  if (board[stone->bpos.y][stone->bpos.x+1].stone != NULL) stone->liberties--;
  if (board[stone->bpos.y-1][stone->bpos.x].stone != NULL) stone->liberties--;
  if (board[stone->bpos.y+1][stone->bpos.x].stone != NULL) stone->liberties--;

  if (stone->bpos.y == 0 || stone->bpos.y == BY) stone->liberties--;
  if (stone->bpos.x == 0 || stone->bpos.x == BX) stone->liberties--;
  updateGroupLiberties(board, stone);
  return stone->liberties;
}
void updateLiberties(Board (*board)[BX]) {
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      Stone* stone = board[i][j].stone;
      if (board[i][j].stone != NULL){
        (board[i-1][j].stone != NULL && board[i-1][j].stone->c == stone->c) ? stone->up = board[i-1][j].stone : NULL;
        (board[i+1][j].stone != NULL && board[i+1][j].stone->c == stone->c) ? stone->down = board[i+1][j].stone : NULL;
        (board[i][j-1].stone != NULL && board[i][j-1].stone->c == stone->c) ? stone->left = board[i][j-1].stone : NULL;
        (board[i][j+1].stone != NULL && board[i][j+1].stone->c == stone->c) ? stone->right = board[i][j+1].stone : NULL;

        board[i][j].stone->liberties += getLiberties(board, board[i][j].stone);
        /*
        if (board[i][j].stone->up != NULL) board[i][j].stone->liberties += getLiberties(board, board[i][j].stone->up);
        if (board[i][j].stone->down != NULL) board[i][j].stone->liberties += getLiberties(board, board[i][j].stone->down);
        if (board[i][j].stone->left != NULL) board[i][j].stone->liberties += getLiberties(board, board[i][j].stone->left);
        if (board[i][j].stone->right != NULL) board[i][j].stone->liberties += getLiberties(board, board[i][j].stone->right);
        */
      }
    }
  }
}
/*
 * ok so basically, when you add a stone, check if its cardinal adjacent to a same colored group
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

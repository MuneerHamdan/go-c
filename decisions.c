#include <ncurses.h>
#include "main.h"
#include "board.h"
#include "linkedlist.h"


/*
 * prob too complicated
 * 
 * can prob just calculate the linked list liberties on addtolinkedlist
void updateGroupLiberties(Board (*board)[BX], Stone* group) {
  Group* groups[10] = {0};
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      for (int k = 0; k < 10; k++) {
        if (board[i][j].group != groups[k]) {
          groups[k] = board[i][j].group;
        }
      }
    }
  }
}
 */

int getLiberties(Board (*board)[BX], Stone* stone) {
  stone->liberties = 4;
  if (board[stone->bpos.y][stone->bpos.x-1].stone != NULL) stone->liberties--;
  if (board[stone->bpos.y][stone->bpos.x+1].stone != NULL) stone->liberties--;
  if (board[stone->bpos.y-1][stone->bpos.x].stone != NULL) stone->liberties--;
  if (board[stone->bpos.y+1][stone->bpos.x].stone != NULL) stone->liberties--;

  if (stone->bpos.y == 0 || stone->bpos.y == BY) stone->liberties--;
  if (stone->bpos.x == 0 || stone->bpos.x == BX) stone->liberties--;
  //updateGroupLiberties(board, stone);
  return stone->liberties;
}
        /*
void updateLiberties(Board (*board)[BX]) {
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      Stone* stone = board[i][j].stone;
      if (board[i][j].stone != NULL){
        (board[i-1][j].stone != NULL && board[i-1][j].stone->c == stone->c) ? stone->up = board[i-1][j].stone : NULL;
        (board[i+1][j].stone != NULL && board[i+1][j].stone->c == stone->c) ? stone->down = board[i+1][j].stone : NULL;
        (board[i][j-1].stone != NULL && board[i][j-1].stone->c == stone->c) ? stone->left = board[i][j-1].stone : NULL;
        (board[i][j+1].stone != NULL && board[i][j+1].stone->c == stone->c) ? stone->right = board[i][j+1].stone : NULL;

//        board[i][j].stone->liberties += getLiberties(board, board[i][j].stone);
        if (board[i][j].stone->up != NULL) board[i][j].stone->liberties += getLiberties(board, board[i][j].stone->up);
        if (board[i][j].stone->down != NULL) board[i][j].stone->liberties += getLiberties(board, board[i][j].stone->down);
        if (board[i][j].stone->left != NULL) board[i][j].stone->liberties += getLiberties(board, board[i][j].stone->left);
        if (board[i][j].stone->right != NULL) board[i][j].stone->liberties += getLiberties(board, board[i][j].stone->right);
        if (board[i][j].stone->up != NULL) board[i][j].stone->up->group = stone->group;
        if (board[i][j].stone->down != NULL) board[i][j].stone->down->group = stone->group;
        if (board[i][j].stone->left != NULL) board[i][j].stone->left->group = stone->group;
        if (board[i][j].stone->right != NULL) board[i][j].stone->right->group = stone->group;
      }
    }
  }
}
        */
/*
 * ok so basically, when you add a stone, check if its cardinal adjacent to a same colored group
 * if it is, add that stone to that group
 * else, it becomes its own group
 *
 * POSSIBLY MAKE A GROUP DYNAMIC MEMORY???????????
 */
Group* addtogroup(Board (*board)[BX], Stone* stone, Group* groups){
  Stone* left = board[stone->bpos.y][stone->bpos.x-1].stone;
  Stone* right = board[stone->bpos.y][stone->bpos.x+1].stone;
  Stone* up = board[stone->bpos.y-1][stone->bpos.x].stone;
  Stone* down = board[stone->bpos.y+1][stone->bpos.x].stone;
  if (left != NULL && left->group != NULL && left->c == stone->c){
    board[stone->bpos.y][stone->bpos.x].group = left->group;
    stone->group = board[stone->bpos.y][stone->bpos.x].group;
    addtolinkedlist(stone, left);
  }
  else if (right != NULL && right->group != NULL && right->c == stone->c){
    board[stone->bpos.y][stone->bpos.x].group = right->group;
    stone->group = board[stone->bpos.y][stone->bpos.x].group;
    addtolinkedlist(stone, right);
  }
  else if (up != NULL && up->group != NULL && up->c == stone->c) {
    board[stone->bpos.y][stone->bpos.x].group = up->group;
    stone->group = board[stone->bpos.y][stone->bpos.x].group;
    addtolinkedlist(stone, up);
  }
  else if (down != NULL && down->group != NULL && down->c == stone->c) {
    board[stone->bpos.y][stone->bpos.x].group = down->group;
    stone->group = board[stone->bpos.y][stone->bpos.x].group;
    addtolinkedlist(stone, down);
  }
  else {
    stone->group = makeGroup(board, stone);
    if (stone->group)
      addGroup(groups, stone->group);
  }
  return stone->group;
}

#include "board.h"
#include "decisions.h"
#include "main.h"
#include <ncurses.h>
#include <stdlib.h>

Stone* makeStone(char c, Vec2i cpos, Vec2i bpos, Board (*board)[BX]) {
  Stone* stone = (Stone *)malloc(sizeof(Stone));
  stone->c = c;
  stone->cpos.y = cpos.y;
  stone->cpos.x = cpos.x;
  stone->bpos.y = bpos.y;
  stone->bpos.x = bpos.x;
  stone->liberties = getLiberties(board, stone);
  return stone;
}
void makeGroup(Board (*board)[BX], Stone* stone){
  if (board[stone->bpos.y][stone->bpos.x-1].stone != NULL && board[stone->bpos.y][stone->bpos.x-1].stone->group != NULL && board[stone->bpos.y][stone->bpos.x-1].stone->c == stone->c){
    board[stone->bpos.y][stone->bpos.x].group = board[stone->bpos.y][stone->bpos.x-1].stone->group;
    stone->group = board[stone->bpos.y][stone->bpos.x].group;
  }
  else if (board[stone->bpos.y][stone->bpos.x+1].stone != NULL && board[stone->bpos.y][stone->bpos.x+1].stone->group != NULL && board[stone->bpos.y][stone->bpos.x+1].stone->c == stone->c){
    board[stone->bpos.y][stone->bpos.x].group = board[stone->bpos.y][stone->bpos.x+1].stone->group;
    stone->group = board[stone->bpos.y][stone->bpos.x].group;
  }
  else if (board[stone->bpos.y-1][stone->bpos.x].stone != NULL && board[stone->bpos.y-1][stone->bpos.x].stone->group != NULL && board[stone->bpos.y-1][stone->bpos.x].stone->c == stone->c) {
    board[stone->bpos.y][stone->bpos.x].group = board[stone->bpos.y-1][stone->bpos.x].stone->group;
    stone->group = board[stone->bpos.y][stone->bpos.x].group;
  }
  else if (board[stone->bpos.y+1][stone->bpos.x].stone != NULL && board[stone->bpos.y+1][stone->bpos.x].stone->group != NULL && board[stone->bpos.y+1][stone->bpos.x].stone->c == stone->c) {
    board[stone->bpos.y][stone->bpos.x].group = board[stone->bpos.y+1][stone->bpos.x].stone->group;
    stone->group = board[stone->bpos.y][stone->bpos.x].group;
  }
  else{
    Group* group = (Group*)malloc(sizeof(Group));
    board[stone->bpos.y][stone->bpos.x].group = group;
    group->head = board[stone->bpos.y][stone->bpos.x].stone;
    stone->group = group;
  }
}
void placeStone(Board (*board)[BX], Stone *stone) {
  int y = stone->bpos.y, x = stone->bpos.x;
  board[y][x].stone = stone;
  board[y][x].c = stone->c;

  //  board[y][x].stone->liberties += (stone->up) ? getLiberties(board, stone->up) : 0;
  // board[y][x].stone->liberties += (stone->down) ? getLiberties(board, stone->down) : 0;
  //board[y][x].stone->liberties += (stone->left) ? getLiberties(board, stone->left) : 0;
  //board[y][x].stone->liberties += (stone->right) ? getLiberties(board, stone->right) : 0;
}
void findDead(Board (*board)[BX]) {
  // THERE'S PROBABLY AN ALGORITHM TO BE FOUND
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      if (board[i][j].stone != NULL && board[i][j].stone->liberties == 0) {
        removeStone(board, i, j);
      }
    }
  }
}
void removeStone(Board (*board)[BX], int bposy, int bposx) {
  free(board[bposy][bposx].stone);
  board[bposy][bposx].stone = NULL;
  board[bposy][bposx].c = '\0';
}
void removeStones(Board (*board)[BX]) {
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      if (board[i][j].stone != NULL) {
        free(board[i][j].stone);
        board[i][j].stone = NULL;
        board[i][j].c = '\0';
      }
    }
  }
}
void removeGroup(Board (*board)[BX], int bposy, int bposx){
  free(board[bposy][bposx].group);
  board[bposy][bposx].group = NULL;
}
void removeGroups(Board (*board)[BX]) {
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      if (board[i][j].group != NULL) {
        //        mvwprintw(win, i, j, "removing: %d %d\n", i, j);
        free(board[i][j].group);
        board[i][j].group = NULL;
      }
    }
  }
}

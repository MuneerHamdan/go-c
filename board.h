#ifndef BOARD_H
#define BOARD_H

#include <ncurses.h>
#include "main.h"

// max board size
#define BY 9
#define BX 9
/*
#define BY 13
#define BX 13
*/
/*
#define BY 19
#define BX 19
*/

typedef struct Stone {
  char c;
  Vec2i cpos;
  Vec2i bpos;
  int liberties;

  struct Stone* group;
  struct Stone* up;
  struct Stone* left;
  struct Stone* right;
  struct Stone* down;
} Stone;

typedef struct Group {
} Group;

typedef struct Board {
  char c;
  Stone* stone;
} Board;

Stone *makeStone(char c, Vec2i cpos, Vec2i bpos, Board (*board)[BX]);
Group* makeGroup();
void placeStone(Board (*board)[BX], Stone *stone);
void findDead(Board (*board)[BX]);
void removeStone(Board (*board)[BX], int bposy, int bposx);
void removeStones(Board (*board)[BX]);

#endif

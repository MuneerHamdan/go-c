#ifndef BOARD_H
#define BOARD_H

#include <ncurses.h>
#include "main.h"
#include <stdbool.h>

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

  bool checked;

  struct Group* group;
  struct Stone* prev;
  struct Stone* next;
} Stone;

typedef struct Group {
  Vec2i cpos;
  Vec2i bpos;

  Stone* stonehead;
  int liberties;
  struct Group* prev;
  struct Group* next;
  struct Group* head;
} Group;

typedef struct Board {
  char c;
  Stone* stone;
  Group* group;
} Board;

Stone* makeStone(Board (*board)[BX], char c, Vec2i cpos, Vec2i bpos);
Group* neighborGroup(Board (*board)[BX], Stone* stone, Group* groups);
Group* addStoneToGroup(Group* group, Stone* stone);

Group* getGroup(Stone* stonehead);
Group* makeGroup(Board (*board)[BX], Stone* stone, Group* groups);
Group* addGroupToGroups(Group* group, Group* groups);

Stone* removeStone(Board (*board)[BX], Group* group, Stone* stone);
Group* removeStones(Board (*board)[BX], Group* group);

Group* removeGroup(Board (*board)[BX], Group* groups, Vec2i bpos);
Group* removeGroupLL(Board (*board)[BX], Group* groups, Group* group);
Group* removeGroups(Board (*board)[BX], Group* groups);

#endif

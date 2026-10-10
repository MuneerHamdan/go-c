#include "board.h"
#include "main.h"
#include <ncurses.h>
#include <stdlib.h>

Stone* makeStone(Board (*board)[BX], char c, Vec2i cpos, Vec2i bpos) {
  Stone* stone = (Stone *)malloc(sizeof(Stone));
  stone->c = c;
  stone->checked = FALSE;
  stone->cpos.y = cpos.y;
  stone->cpos.x = cpos.x;
  stone->bpos.y = bpos.y;
  stone->bpos.x = bpos.x;
  stone->liberties = 4;
  stone->group = NULL;

  board[bpos.y][bpos.x].stone = stone;
  return stone;
}

Group* makeGroup(Board (*board)[BX], Stone* stone, Group* groups){
  Group* group = (Group*)malloc(sizeof(Group));
  group->stonehead = stone;
  stone->group = group;
  group->prev = NULL;
  group->next = NULL;
  group->head = NULL;

  board[stone->bpos.y][stone->bpos.x].group = group;

  groups = addGroupToGroups(stone->group, groups);
  return groups;
}

Group* getGroup(Stone* stonehead){
  return (stonehead && stonehead->group) ? stonehead->group : NULL;
}

Group* addGroupToGroups(Group* group, Group* groups){
  Group* prev = NULL;
  Group* ptr = groups;
  if (!groups){
    groups = group;
    groups->prev = NULL;
    groups->next = NULL;
    return groups;
  }
  if (!groups->next){
    groups->next = group;
    group->prev = groups;
    return groups;
  }
  while (ptr->next){
    prev = ptr;
    ptr = ptr->next;
  }
  ptr->prev = prev;
  ptr->next = group;
  group->prev = ptr;
  return groups;
}

Group* neighborGroup(Board (*board)[BX], Stone* stone, Group* groups){

  /*
   * is there a stone adjacent to me?
   * if yes my group becomes that stone's group
   * if no make a new group
   */
  Stone* up;
  Stone* down;
  Stone* left;
  Stone* right;
  if (stone->bpos.y-1 < 0)
    up = NULL;
  else
    up = board[stone->bpos.y-1][stone->bpos.x].stone;
  if (stone->bpos.y+1 > BY-1)
    down = NULL;
  else
    down = board[stone->bpos.y+1][stone->bpos.x].stone;
  if (stone->bpos.x-1 < 0)
    left = NULL;
  else
    left = board[stone->bpos.y][stone->bpos.x-1].stone;
  if (stone->bpos.x+1 > BX-1)
    right = NULL;
  else
    right = board[stone->bpos.y][stone->bpos.x+1].stone;

  if (up) {
    stone->liberties--;
  }
  if (down) {
    stone->liberties--;
  }
  if (left) {
    stone->liberties--;
  }
  if (right) {
    stone->liberties--;
  }

  if (up && up->c == stone->c) {
    stone->group = up->group;
  }
  else if (down && down->c == stone->c) {
    stone->group = down->group;
  }
  else if (left && left->c == stone->c){
    stone->group = left->group;
  }
  else if (right && right->c == stone->c){
    stone->group = right->group;
  }
  else{
    groups = makeGroup(board, stone, groups);
    return groups;
  }
  return stone->group;
}

Stone* removeStone(Board (*board)[BX], Group* groups, Stone* stone){
  board[stone->bpos.y][stone->bpos.x].stone = NULL;
  //groups->stone = NULL;
  free(stone);
  stone = NULL;
  return stone;
}
Group* removeStones(Group* group){
  return NULL;
}
Group* removeGroup(Board (*board)[BX], Group* groups, Vec2i bpos){
  free(board[bpos.y][bpos.x].group);
  board[bpos.y][bpos.x].group = NULL;
  //groups->group = NULL;
  return groups;
}
Group* removeGroups(Board (*board)[BX], Group* groups){
  while(groups){
    Group* ptr = groups;
    while(ptr->next->next){
      ptr = ptr->next;
    }
    removeStones(ptr->next);
    groups = removeGroup(board, groups, (Vec2i){ptr->next->stonehead->bpos.y, ptr->next->stonehead->bpos.x});
    ptr = NULL;
  }
  return NULL;
}

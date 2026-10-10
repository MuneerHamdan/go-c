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
  stone->liberties = 0;
  stone->group = NULL;

  board[bpos.y][bpos.x].stone = stone;
  return stone;
}

Group* makeGroup(Stone* stone, Group* groups){
  Group* group = (Group*)malloc(sizeof(Group));
  group->stonehead = stone;
  stone->group = group;
  group->next = NULL;
  group->head = NULL;

  addGroupToGroups(group, groups);
  return group;
}

Group* addGroupToGroups(Group* group, Group* groups){
  Group* ptr = groups;
  if (!groups){
    groups = group;
    return groups;
  }
  while (ptr->next){
    ptr = ptr->next;
  }
  if (groups != group)
    ptr->next = group;
  return groups;
}

Group* neighborGroup(Board (*board)[BX], Stone* stone, Group* groups){

  /*
   * is there a stone adjacent to me?
   * if yes my group becomes that stone's group
   * if no make a new group
   */
  Stone* up = board[stone->bpos.y-1][stone->bpos.x].stone;
  Stone* down = board[stone->bpos.y+1][stone->bpos.x].stone;
  Stone* left = board[stone->bpos.y][stone->bpos.x-1].stone;
  Stone* right = board[stone->bpos.y][stone->bpos.x+1].stone;

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
    stone->group = makeGroup(stone, groups);
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
Group* removeGroup(Group* groups, Group* group){
  return NULL;
}
Group* removeGroups(Group* groups){
  return NULL;
}

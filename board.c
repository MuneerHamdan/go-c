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
  Stone* up = NULL;
  Stone* down = NULL;
  Stone* left = NULL;
  Stone* right = NULL;
  if (!(stone->bpos.y-1 < 0))
    up = board[stone->bpos.y-1][stone->bpos.x].stone;
  if (!(stone->bpos.y+1 > BY-1))
    down = board[stone->bpos.y+1][stone->bpos.x].stone;
  if (!(stone->bpos.x-1 < 0))
    left = board[stone->bpos.y][stone->bpos.x-1].stone;
  if (!(stone->bpos.x+1 > BX-1))
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
    stone->prev = up;
  }
  else if (down && down->c == stone->c) {
    stone->group = down->group;
    stone->prev = down;
  }
  else if (left && left->c == stone->c){
    stone->group = left->group;
    stone->prev = left;
  }
  else if (right && right->c == stone->c){
    stone->group = right->group;
    stone->prev = right;
  }
  else{
    groups = makeGroup(board, stone, groups);
    return groups;
  }
  return stone->group;
}

Group* addStoneToGroup(Group* group, Stone* stone){
  Stone* ptr = group->stonehead;
  while(ptr->next){
    ptr = ptr->next;
  }
  stone->prev = ptr;
  ptr->next = stone;
  return group;
}

Stone* removeStone(Board (*board)[BX], Group* group, Stone* stone){
  board[stone->bpos.y][stone->bpos.x].stone = NULL;
  //groups->stone = NULL;
  free(stone);
  stone = NULL;
  return stone;
}
Group* removeStones(Board (*board)[BX], Group* group){
  Stone* ptr = group->stonehead;
  while (ptr){
    while (ptr->next){
      ptr = removeStone(board, group, ptr);
      ptr = ptr->next;
    }
  }
  group->stonehead = NULL;
  return group;
}
Group* removeGroup(Board (*board)[BX], Group* groups, Vec2i bpos){
  free(board[bpos.y][bpos.x].group);
  board[bpos.y][bpos.x].group = NULL;
  //groups->group = NULL;
  return groups;
}
Group* removeGroupLL(Board (*board)[BX], Group* groups, Group* group){
//  Group* ptr = groups;
  board[group->stonehead->bpos.y][group->stonehead->bpos.x].group = NULL;
  free(board[group->stonehead->bpos.y][group->stonehead->bpos.x].group);
  group = removeStones(board, group);
  Group* prev = group->prev;
  if(group->next)
    prev->next = group->next;
  else if(prev)
    prev->next = NULL;
  return groups;
}
Group* removeGroups(Board (*board)[BX], Group* groups){
  Group* prev = groups;
  Group* curr = groups;
  if (prev->next)
    curr = groups;
  while(groups){
    if (!groups->stonehead)
      return NULL;
    while(curr->next){
      curr = curr->next;
    }
    curr = removeGroupLL(board, groups, curr);
    if (curr->prev)
      curr = curr->prev;
  }
  return groups;
}

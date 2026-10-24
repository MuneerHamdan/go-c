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

Group* makeGroup(Board (*board)[BX], Stone* stone){
  Group* group = (Group*)malloc(sizeof(Group));
  group->stonehead = stone;
  stone->group = group;
  group->prev = NULL;
  group->next = NULL;
  group->head = NULL;

  board[stone->bpos.y][stone->bpos.x].group = group;

  return group;
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
    if(ptr == group)
      return groups;
    prev = ptr;
    ptr = ptr->next;
  }
  if(ptr == group)
    return groups;
  if(!(ptr->next)){
    ptr->prev = prev;
    ptr->next = group;
    group->prev = ptr;
  }
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

  /*
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
  */

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
    groups = makeGroup(board, stone);
    return groups;
  }
  return stone->group;
}
Stone* addStoneToGroup(Group* group, Stone* stone){
  Stone* ptr = group->stonehead;
  while(ptr->next){
    ptr = ptr->next;
  }
  if(stone == group->stonehead){
    stone->prev = NULL;
    stone->next = NULL;
    return stone;
  }
  stone->prev = ptr;
  ptr->next = stone;
  return stone;
}
Stone* removeStone(Board (*board)[BX], Group* group, Stone* stone){
  if (!stone)
    return NULL;
  if (stone->prev)
    stone->prev->next = stone->next;
  else if (group && group->stonehead == stone)
    group->stonehead = stone->next;
  if (stone->next)
    stone->next->prev = stone->prev;
  board[stone->bpos.y][stone->bpos.x].stone = NULL;
  board[stone->bpos.y][stone->bpos.x].group = NULL;
  //groups->stone = NULL;
  free(stone);
  return NULL;
}
Group* removeStones(Board (*board)[BX], Group* group){
  if(!group)
    return NULL;
  while (group->stonehead){
    Stone* stone = group->stonehead;
    stone = removeStone(board, group, stone);
  }

  return group;
}
Group* removeGroup(Board (*board)[BX], Group* groups, Group* group){
  if (!group)
    return groups;
  group = removeStones(board, group);

  Group* prev = group->prev;
  Group* next = group->next;

  if (prev){
    if (next){
      prev->next = next;
    }
    else{
      prev->next = NULL;
    }
    group->liberties = 0;
    group->stonehead = NULL;
    group->prev = NULL;
    group->next = NULL;
    free(group);
    return NULL;
  }
  else if(next){
    next->prev = NULL;
    groups = next;
    return groups;
  }

  return NULL;
}
Group* removeGroups(Board (*board)[BX], Group* groups){
  if (!groups)
    return NULL;
  Group* prev = groups;
  Group* curr = groups;
  if (prev->next)
    curr = groups;
  while(groups){
    if (!groups->stonehead)
      return NULL;
    if (!curr)
      return groups;
    while(curr->next){
      curr = curr->next;
    }
    curr = removeGroup(board, groups, curr);
    if (curr){
      if (curr->prev){
        curr = curr->prev;
      }
    }
  }
  return groups;
}

#include "board.h"
#include "decisions.h"
/*
 * 1. group is new
 * 2. group is not new
 *
 * if adjacent is same color -> add this new stone to the end of the linked list, and then add that liberties to the group liberties total
 */
void addtolinkedlist(Stone* stone, Stone* prev){
  Stone* ptr = prev->group->stonehead;
  while (ptr->next != NULL){
    ptr = ptr->next;
  }
  ptr->next = stone;
}

Group* addGroup(Group* groups, Group* group){
  Group* gptr = groups;
  if (!gptr)
    return gptr;
  while (gptr->next != NULL){
    gptr = gptr->next;
  }
  if (gptr != group)
    gptr->next = group;
  return gptr;
}
Group* updateGroupLiberties(Group* group, Board (*board)[BX]){
  Stone* ptr = group->stonehead;
  group->liberties = 0;
  while (ptr != NULL){
    getLiberties(board, ptr);
//    updateLiberties(board);
    group->liberties += ptr->liberties;
    /*
    if (board[ptr->bpos.y-1][ptr->bpos.x].group == ptr->group && board[ptr->bpos.y-1][ptr->bpos.x].stone->checked == FALSE)
      group->liberties--;
    else if (board[ptr->bpos.y+1][ptr->bpos.x].group == ptr->group && board[ptr->bpos.y+1][ptr->bpos.x].stone->checked == FALSE)
      group->liberties--;
    else if (board[ptr->bpos.y][ptr->bpos.x-1].group == ptr->group && board[ptr->bpos.y][ptr->bpos.x-1].stone->checked == FALSE)
      group->liberties--;
    else if (board[ptr->bpos.y][ptr->bpos.x+1].group == ptr->group && board[ptr->bpos.y][ptr->bpos.x+1].stone->checked == FALSE)
      group->liberties--;
    ptr->checked = TRUE;
    */
    ptr = ptr->next;
  }
  return group;
}
void updateGroups(Group* groups, Board (*board)[BX]){
  Group* gptr = groups;
  while (gptr != NULL){
    gptr->liberties = updateGroupLiberties(gptr, board)->liberties;
    if (!gptr->liberties){
      if (gptr->next){
        Group* tmp = gptr->next;
      }
    }
    gptr = gptr->next;
  }
}

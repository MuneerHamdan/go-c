#include "board.h"
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
  while (gptr->next != NULL){
    gptr = gptr->next;
  }
  if (gptr == groups)
    return groups;
  gptr->next = group;
  return gptr;
}
Group* updateGroupLiberties(Group* group){
  Stone* ptr = group->stonehead;
  while (ptr != NULL){
    ptr->group->liberties += ptr->liberties;
    ptr = ptr->next;
  }
  return group;
}
void updateGroups(Group* groups){
  Group* gptr = groups;
  while (gptr != NULL){
    gptr->liberties = updateGroupLiberties(gptr)->liberties;
    gptr = gptr->next;
  }
}

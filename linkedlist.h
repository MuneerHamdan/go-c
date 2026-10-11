#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "board.h"

void addtolinkedlist(Stone* stone, Stone* prev);
Group* addGroup(Group* groups, Group* group);
Group* updateGroupLiberties(Group* group, Board (*board)[BX]);
void updateGroups(Group* groups, Board (*board)[BX]);

#endif


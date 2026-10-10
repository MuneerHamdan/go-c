#ifndef DECISIONS_H
#define DECISIONS_H

#include <ncurses.h>
#include "board.h"
#include <stdbool.h>

int getStoneLiberties(Stone* stone);
Group* addToGroup(Board (*board)[BX], Stone* stone, Group* groups);

bool needGroup(Stone* stone);

#endif

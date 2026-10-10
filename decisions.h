#ifndef DECISIONS_H
#define DECISIONS_H

#include <ncurses.h>
#include "board.h"
#include <stdbool.h>

int getLiberties(Board (*board)[BX], Stone* stone);

#endif

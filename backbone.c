#include "board.h"

struct Stone{
  Stone* shead;
  Stone* prev;
  Stone* next;
};
typedef struct Stone Stone;

struct Group{
  Stone* shead;
  Group* prev;
  Group* next;
};
typedef struct Group Group;

Group* makeGroup(){
}
Group* addGroupToGroups(){
}
Stone* makeStone(){
}
Stone* addStoneToStones(){
}

removeStone(){
}
removeStones(){
}
removeGroup(){
}
removeGroups(){
}

int main(){
  char c;
  Group* groups;
  char board[BY][BX];
  while((c = getch()) != 'q'){
  }

  return 0;
}

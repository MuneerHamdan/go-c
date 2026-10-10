#include <signal.h>
#include <ncurses.h>
#include <errno.h>
#include "main.h"
#include "board.h"
//#include "decisions.h"
//#include "linkedlist.h"

// make it so that CTRL+C does not cause unfinished (no freeing of memory) end of program
void handle_sigint(int sig) {}

int main(void) {

  signal(SIGINT, handle_sigint);

  // check window
  WINDOW* win = initscr();
  errno = cbreak();
  if (errno)
    fprintf(stderr, "error cbreak%d\n", errno);
  errno = notimeout(win, FALSE);
  errno = noecho();
  if (errno)
    fprintf(stderr, "error noecho%d\n", errno);
  errno = notimeout(win, FALSE);
  if (errno)
    fprintf(stderr, "error notimeout%d\n", errno);
  errno = keypad(win, TRUE);
  if (errno)
    fprintf(stderr, "error keypad%d\n", errno);


  char turn = 0;

  /*
  // initialize board
  Board _board[BY][BX];
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      _board[i][j].c = '+';
      _board[i][j].stone = NULL;
    }
  }
  */

  Board board[BY][BX];
  for (int i = 0; i < BY; i++) {
    for (int j = 0; j < BX; j++) {
      board[i][j].c = '+';
      board[i][j].stone = NULL;
      board[i][j].group = NULL;
    }
  }

  Group* groups = NULL;

  char ch = '\0';
  int maxy, maxx = 0;
  getmaxyx(win, maxy, maxx);
  int bposy = ((BY / 2));
  int bposx = ((BX / 2));
  int cursy = maxy / 2, cursx = maxx / 2;


  //game loop
  do {
    //input
    if (errno) {
      fprintf(stderr, "error getch%d\n", errno);
      return errno;
    }
    // move cursor
    if (ch == 'h' && bposx > 0) {
      cursx--;
      bposx--;
//      wmove(win, cursy, cursx-1);
    }
    else if (ch == 'j' && bposy < 8) {
 //     wmove(win, cursy+1, cursx);
      cursy++;
      bposy++;
    }
    else if (ch == 'k' && bposy > 0) {
  //    wmove(win, cursy-1, cursx);
      cursy--;
      bposy--;
    }
    else if (ch == 'l' && bposx < 8) {
   //   wmove(win, cursy, cursx+1);
      cursx++;
      bposx++;
    }
    Stone* stone = board[bposy][bposx].stone;
    Group* group = getGroup(stone);
    // place piece
    if (ch == 'f' && board[bposy][bposx].c == '+') {
      char c = '\0';
      if (turn % 2 == 0) {
        c = 'O';
        turn++;
      }
      else {
        c = '@';
        turn--;
      }
      stone = makeStone(board, c, (Vec2i){cursy, cursx}, (Vec2i){bposy, bposx});
      group = neighborGroup(board, stone, groups);
      groups = addGroupToGroups(group, groups);
      //updateGroups(groups, board);
    }
    else if (ch == 'r' && stone) {
      stone = removeStone(board, groups, stone);
      group = removeGroup(board, groups, (Vec2i){bposy, bposx});
//      board[bposy][bposx].group = removeGroup(board, groups, board[bposy][bposx].group);
 //     board[bposy][bposx].stone = removeStone(board, bposy, bposx);
    }
    if (errno) {
      fprintf(stderr, "error move%d\n", errno);
      return errno;
    }

    //update stuff
//    updateLiberties(board);
//    updateGroups(groups, board);
//    findDead(win, board);

    //render
    clear();
    // print debug
    mvwprintw(win, 0, 0, "curs: %d, %d", cursy, cursx);
    mvwprintw(win, 1, 0, "bpos: %d, %d", bposy, bposx);
    mvwprintw(win, 2, 0, "turn: %c", turn ? '@' : 'O');
    mvwprintw(win, 3, 0, "stone?: %c", (stone) ? 'y' : 'n');
//    mvwprintw(win, 4, 0, "liberties: %d", (board[bposy][bposx].stone != NULL) ? getLiberties(board, board[bposy][bposx].stone) : 0);
    mvwprintw(win, 5, 0, "stone->cpos.y: %d, stone->cpos.x: %d", (stone) ? stone->cpos.y : -1, (stone) ? stone->cpos.x : -1);
    mvwprintw(win, 6, 0, "stone->bpos.y: %d, stone->bpos.x: %d", (stone) ? stone->bpos.y : -1, (stone) ? stone->bpos.x : -1);
    mvwprintw(win, 7, 0, "&stone: %p", (stone) ? (void *)stone : NULL);
    mvwprintw(win, 8, 0, "stone->group: %p", (stone && stone->group) ? (void *)stone->group : NULL);

//    mvwprintw(win, 9, 0, "stone->up: %p", (board[bposy][bposx].stone != NULL) ? (void *)board[bposy][bposx].stone->up : NULL);
//    mvwprintw(win, 10, 0, "stone->down: %p", (board[bposy][bposx].stone != NULL) ? (void *)board[bposy][bposx].stone->down : NULL);
//    mvwprintw(win, 11, 0, "stone->left: %p", (board[bposy][bposx].stone != NULL) ? (void *)board[bposy][bposx].stone->left : NULL);
//    mvwprintw(win, 12, 0, "stone->right: %p", (board[bposy][bposx].stone != NULL) ? (void *)board[bposy][bposx].stone->right : NULL);

//    if (board[bposy][bposx].stone) {
//      mvwprintw(win, 13, 0, "stone->up: %d", (board[bposy][bposx].stone->up != NULL) ? board[bposy][bposx].stone->up->liberties : 0);
//      mvwprintw(win, 14, 0, "stone->down: %d", (board[bposy][bposx].stone->down != NULL) ? board[bposy][bposx].stone->down->liberties : 0);
//      mvwprintw(win, 15, 0, "stone->left: %d", (board[bposy][bposx].stone->left != NULL) ? board[bposy][bposx].stone->left->liberties : 0);
//      mvwprintw(win, 16, 0, "stone->right: %d", (board[bposy][bposx].stone->right != NULL) ? board[bposy][bposx].stone->right->liberties : 0);
//    }

//    if (board[bposy][bposx].group) {
      mvwprintw(win, 18, 0, "&group: %p", (group) ? (void *)group : NULL);
    mvwprintw(win, 19, 0, "group->next: %p", (group) ? (void *)(group->next) : NULL);
      mvwprintw(win, 20, 0, "group->stonehead: %p", (group && group->stonehead) ? (void *)group->stonehead : NULL);
//      if (board[bposy][bposx].group->head) {

 //     mvwprintw(win, 20, 0, "groups: %p", (groups) ? (void *)groups : NULL);
//      mvwprintw(win, 21, 0, "groups->next: %p", (groups && groups->next) ? (void *)groups->next : NULL);
//      }
//      mvwprintw(win, 21, 0, "group->liberties: %d", board[bposy][bposx].group->liberties);
//    }
//    mvwprintw(win, 22, 0, "stone->next: %p", (board[bposy][bposx].stone && board[bposy][bposx].stone->next) ? (void *)(board[bposy][bposx].stone->next) : NULL);
//
    

    // quit info
    mvwprintw(win, maxy-1, 0, "press 'q' to quit");

    /*
    // draw _board
    for (int i = 0; i < BY; i++) {
      for (int j = 0; j < BX; j++) {
//        mvwprintw(win, ((maxy / 2) - (BY - 2) - 1 + (2 * i)), ((maxx / 2) - (BX - 2) - 1 + (2 * j)), "%c", '-');
//        mvwprintw(win, ((maxy / 2) - (BY / 2)) + i, ((maxx / 2) - (BX / 2)) + j, "%c", _board[i][j].c);
      }
    }
    */
    // draw board
    for (int i = 0; i < BY; i++) {
      for (int j = 0; j < BX; j++) {
        mvwprintw(win, ((maxy / 2) - (BY / 2)) + i, ((maxx / 2) - (BX / 2)) + j, "%c", (board[i][j].stone) ? board[i][j].stone->c : board[i][j].c);
      }
    }
    wmove(win, cursy, cursx);

    /*
    // make lip around board
    wmove(win, ((maxy / 2) - (BY / 2) - 1), ((maxx / 2) - (BX / 2) - 1));
    for (int i = 0; i < BX+2 ; i++) {
      waddch(win, '-');
      getyx(win, cursy, cursx);
    }
    for (int i = 0; i < BY+1; i++) {
      mvwaddch(win, cursy+1, cursx-1, '|');
      getyx(win, cursy, cursx);
    }
    for (int i = 0; i < BX+1; i++) {
      mvwaddch(win, cursy, cursx-2, '-');
      getyx(win, cursy, cursx);
    }
    for (int i = 0; i < BY+1; i++) {
      mvwaddch(win, cursy-1, cursx-1, '|');
      getyx(win, cursy, cursx);
    }
    */

    errno = wrefresh(win);
    if (errno) {
      fprintf(stderr, "error refreshing%d\n", errno);
    }
  } while ((ch = wgetch(win)) != 'q');

  // outside game loop

  //remove all stones
//  removeStones(board);
 // removeGroups(groups);

  endwin();
  return 0;
}

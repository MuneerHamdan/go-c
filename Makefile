all:
	gcc -g -O0 -Wall -Wextra -Wpedantic main.c board.c decisions.c linkedlist.c -lncurses
	./a.out

g:
	gcc -g -O0 -Wall -Wextra -Wpedantic main.c board.c decisions.c linkedlist.c -lncurses
	gdb -tui ./a.out

#include <queue>
#include <cstdlib>
#include <ncursesw/curses.h>
#include <ctime>
#include <fstream>
#include <iostream>

#include "snake_ncurses.hpp"
#include "snake.hpp"
#include "score.hpp"

int main(void) {
	setlocale(LC_ALL, "");
	Score S;
	S.fileread();
	int ch;
	while(1) {
		ch=show_menu();
		switch(ch) {
			case 1:
				S.addscore(classic_game());
				break;
			case 2:
				S.showscores();
				break;
			case 3:
				S.filewrite();
				endwin();
				return 0;
		}
	}
}

#include <queue>
#include <cstdlib>
#include <ncursesw/curses.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <locale.h>

#include "snake_ncurses.hpp"
#include "snake.hpp"
#include "score.hpp"
#include "wall.hpp"


void print_snake(void) {
	mvprintw(0, 14, " $$$$$$\\  $$\\   $$\\  $$$$$$\\  $$\\   $$\\ $$$$$$$$\\\n");
	mvprintw(1, 14, "$$  __$$\\ $$$\\  $$ |$$  __$$\\ $$ | $$  |$$  _____|\n");
	mvprintw(2, 14, "$$ /  \\__|$$$$\\ $$ |$$ /  $$ |$$ |$$  / $$ |\n");
	mvprintw(3, 14, "\\$$$$$$\\  $$ $$\\$$ |$$$$$$$$ |$$$$$  /  $$$$$\\\n");
	mvprintw(4, 14, " \\____$$\\ $$ \\$$$$ |$$  __$$ |$$  $$<   $$  __|\n");
	mvprintw(5, 14, "$$\\   $$ |$$ |\\$$$ |$$ |  $$ |$$ |\\$$\\  $$ |\n");
	mvprintw(6, 14, "\\$$$$$$  |$$ | \\$$ |$$ |  $$ |$$ | \\$$\\ $$$$$$$$\\\n");
	mvprintw(7, 14, " \\______/ \\__|  \\__|\\__|  \\__|\\__|  \\__|\\________|\n");
}

int show_menu(void) {
	int c=1, ch;
	initscr();
	erase();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	print_snake();
	attron(A_STANDOUT);
	mvprintw(12, 28, "Play Classic Snake Game.");
	attroff(A_STANDOUT);
	mvprintw(13, 24, "Show All Scores of Classic Mode.");
	mvprintw(14, 34, "Exit Game.");
	while(1) {
		ch=getch();
		if(ch=='\n') {
			return c;
		}
		else if(ch==KEY_UP) {
			if(c>1) {
				c--;
			}
			else {
				c=4;
			}
		}
		else if(ch==KEY_DOWN) {
			if(c<3) {
				c++;
			}
			else {
				c=1;
			}
		}
		switch(c) {
			case 1:
				erase();
				print_snake();
				attron(A_STANDOUT);
				mvprintw(12, 28, "Play Classic Snake Game.");
				attroff(A_STANDOUT);
				mvprintw(13, 24, "Show All Scores of Classic Mode.");
				mvprintw(14, 34, "Exit Game.");
				break;
			case 2:
				erase();
				print_snake();
				mvprintw(12, 28, "Play Classic Snake Game.");
				attron(A_STANDOUT);
				mvprintw(13, 24, "Show All Scores of Classic Mode.");
				attroff(A_STANDOUT);
				mvprintw(14, 34, "Exit Game.");
				break;
			case 3:
				erase();
				print_snake();
				mvprintw(12, 28, "Play Classic Snake Game.");
				mvprintw(13, 24, "Show All Scores of Classic Mode.");
				attron(A_STANDOUT);
				mvprintw(14, 34, "Exit Game.");
				attroff(A_STANDOUT);
				break;
		}
	}
}

void show_gameover(int a) {
	erase();
	timeout(TIMEOUT_GAME_OVER);
	mvprintw(3, 17, "  /$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$$\n");
    mvprintw(4, 17, " /$$__  $$ /$$__  $$| $$$    /$$$| $$_____/\n");
    mvprintw(5, 17, "| $$  \\__/| $$  \\ $$| $$$$  /$$$$| $$      \n");
    mvprintw(6, 17, "| $$ /$$$$| $$$$$$$$| $$ $$/$$ $$| $$$$$   \n");
    mvprintw(7, 17, "| $$|_  $$| $$__  $$| $$  $$$| $$| $$__/   \n");
    mvprintw(8, 17, "| $$  \\ $$| $$  | $$| $$\\  $ | $$| $$      \n");
    mvprintw(9, 17, "|  $$$$$$/| $$  | $$| $$ \\/  | $$| $$$$$$$$\n");
    mvprintw(10, 17, " \\______/ |__/  |__/|__/     |__/|________/\n");
    mvprintw(11, 17, "    /$$$$$$  /$$    /$$ /$$$$$$$$ /$$$$$$$ \n");
    mvprintw(12, 17, "   /$$__  $$| $$   | $$| $$_____/| $$__  $$\n");
    mvprintw(13, 17, "  | $$  \\ $$| $$   | $$| $$      | $$  \\ $$\n");
    mvprintw(14, 17, "  | $$  | $$|  $$ / $$/| $$$$$   | $$$$$$$/\n");
    mvprintw(15, 17, "  | $$  | $$ \\  $$ $$/ | $$__/   | $$__  $$\n");
    mvprintw(16, 17, "  | $$  | $$  \\  $$$/  | $$      | $$  \\ $$\n");
    mvprintw(17, 17, "  |  $$$$$$/   \\  $/   | $$$$$$$$| $$  | $$\n");
    mvprintw(18, 17, "   \\______/     \\_/    |________/|__/  |__/\n");
    mvprintw(20, 35, "Score:");
    attron(A_STANDOUT);
    printw("%3d", a);
    attroff(A_STANDOUT);
    getch();
}

int classic_game(void) {
	start_color();
	use_default_colors();
	init_pair(COLOR_SNAKE_HEAD, COLOR_RED, COLOR_RED);
	init_pair(COLOR_SNAKE_BODY, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(COLOR_ITEM_GROWTH, COLOR_GREEN, COLOR_GREEN);
	init_pair(COLOR_ITEM_POISON, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(COLOR_WALL, COLOR_BLUE, COLOR_BLUE);
	init_pair(COLOR_IMMUNEWALL, COLOR_BLACK, COLOR_BLACK);

	Snake S;
	int ch, d;
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	timeout(TIMEOUT);
	curs_set(0);

	
	while(1) {
		ch=getch();
		if(ch=='q') {
			return S.getscore();
		}
		else if(ch==KEY_UP || ch==KEY_DOWN || ch==KEY_RIGHT || ch==KEY_LEFT) {
			switch(ch) {
				case KEY_UP:
					d=UP;
					break;
				case KEY_DOWN:
					d=DOWN;
					break;
				case KEY_RIGHT:
					d=RIGHT;
					break;
				case KEY_LEFT:
					d=LEFT;
					break;
			}
			if(diff(S.getfdir(), d)!=2 && d!=S.getfdir()) {
				S.createNode(d);
			}
		}

		
		S.movesnake();
		S.render();
		
		// 벽에 부딪히거나 자기몸에 부딪히면 GameOver
		if(S.getcoll()) {
			timeout(TIMEOUT_LONG);
			getch();
			show_gameover(S.getscore());
			return S.getscore();
		}

		// 길이가 3미만이면 GameOver
		if(S.getscore()<DEF_LEN_CLASSIC) {
			timeout(TIMEOUT_LONG);
			getch();
			show_gameover(S.getscore());
			return S.getscore();
		}
		print_score(S.getscore());
		attron(A_STANDOUT);
		mvprintw(23, 25, "PRESS 'Q' to EXIT BACK TO MENU.");
		attroff(A_STANDOUT);
		refresh();
	}
}

Point rand_point(std::deque<Cell> cells, std::deque<Item> items, std::deque<Cell> walls){
	Point p;
	int flag;
	srand(time(NULL));
	do {
		flag=0;
		p.row=(rand()%(MAX_ROW-1))+1;
		p.col=(rand()%(MAX_COL-1))+1;
		for(std::deque<Cell>::iterator it=cells.begin(); it!=cells.end(); ++it){
			if(p.row==it->p.row && p.col==it->p.col) {
				flag=1;
				break;
			}
		}

		for(std::deque<Item>::iterator it=items.begin(); it!=items.end(); ++it){
			if(p.row==it->p.row && p.col==it->p.col) {
				flag=1;
				break;
			}
		}

		for(std::deque<Cell>::iterator it=walls.begin(); it!=walls.end(); ++it){
			if(p.row==it->p.row && p.col==it->p.col) {
				flag=1;
				break;
			}
		}

	}while(flag);
	return p;
}

int rand_score(void) {
	// millisecond 기준으로 랜덤발생
	struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);

	int rnd = rand();

	// 0 또는 1
	if(rnd%2) return 1;	
	return -1;
}


int getrow(int row) {
	if(row>=0 && row<=MAX_ROW) {
		return row;
	}
	else if(row<0) {
		return MAX_ROW+row+1;
	}
	else {
		return row-MAX_ROW-1;
	}
}

int getcol(int col) {
	if(col>=0 && col<=MAX_COL) {
		return col;
	}
	else if(col<0) {
		return MAX_COL+col+1;
	}
	else {
		return col-MAX_COL-1;
	}
}

int diff(int a, int b) {
	if((a-b)>0) {
		return a-b;
	}
	else {
		return b-a;
	}
}

void print_score(int score)
{
	mvprintw(0,MAX_COL-10, "Score : %d", score);
	refresh();
}



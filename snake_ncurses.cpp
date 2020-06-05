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

void print_snake(void) 
{
	mvprintw(0, 7, " $$$$$$\\  $$\\   $$\\  $$$$$$\\  $$\\   $$\\ $$$$$$$$\\\n");
	mvprintw(1, 7, "$$  __$$\\ $$$\\  $$ |$$  __$$\\ $$ | $$  |$$  _____|\n");
	mvprintw(2, 7, "$$ /  \\__|$$$$\\ $$ |$$ /  $$ |$$ |$$  / $$ |\n");
	mvprintw(3, 7, "\\$$$$$$\\  $$ $$\\$$ |$$$$$$$$ |$$$$$  /  $$$$$\\\n");
	mvprintw(4, 7, " \\____$$\\ $$ \\$$$$ |$$  __$$ |$$  $$<   $$  __|\n");
	mvprintw(5, 7, "$$\\   $$ |$$ |\\$$$ |$$ |  $$ |$$ |\\$$\\  $$ |\n");
	mvprintw(6, 7, "\\$$$$$$  |$$ | \\$$ |$$ |  $$ |$$ | \\$$\\ $$$$$$$$\\\n");
	mvprintw(7, 7, " \\______/ \\__|  \\__|\\__|  \\__|\\__|  \\__|\\________|\n");
}

int show_menu(void) 
{
	int c=1, ch;
	initscr();
	
	erase();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	print_snake();
	attron(A_STANDOUT);
	mvprintw(12, 22, "Play Snake Game.");
	attroff(A_STANDOUT);
	mvprintw(13, 22, "Show All Scores");
	mvprintw(14, 24, "Exit Game.");
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
				mvprintw(12, 22, "Play Snake Game.");
				attroff(A_STANDOUT);
				mvprintw(13, 22, "Show All Scores");
				mvprintw(14, 24, "Exit Game.");
				break;
			case 2:
				erase();
				print_snake();
				mvprintw(12, 22, "Play Snake Game.");
				attron(A_STANDOUT);
				mvprintw(13, 22, "Show All Scores");
				attroff(A_STANDOUT);
				mvprintw(14, 24, "Exit Game.");
				break;
			case 3:
				erase();
				print_snake();
				mvprintw(12, 22, "Play Snake Game.");
				mvprintw(13, 22, "Show All Scores");
				attron(A_STANDOUT);
				mvprintw(14, 24, "Exit Game.");
				attroff(A_STANDOUT);
				break;
		}
	}
}

void show_gameover(int a) 
{
	erase();
	timeout(TIMEOUT_GAME_OVER);
	mvprintw(3, 10, "  /$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$$\n");
    mvprintw(4, 10, " /$$__  $$ /$$__  $$| $$$    /$$$| $$_____/\n");
    mvprintw(5, 10, "| $$  \\__/| $$  \\ $$| $$$$  /$$$$| $$      \n");
    mvprintw(6, 10, "| $$ /$$$$| $$$$$$$$| $$ $$/$$ $$| $$$$$   \n");
    mvprintw(7, 10, "| $$|_  $$| $$__  $$| $$  $$$| $$| $$__/   \n");
    mvprintw(8, 10, "| $$  \\ $$| $$  | $$| $$\\  $ | $$| $$      \n");
    mvprintw(9, 10, "|  $$$$$$/| $$  | $$| $$ \\/  | $$| $$$$$$$$\n");
    mvprintw(10, 10, " \\______/ |__/  |__/|__/     |__/|________/\n");
    mvprintw(11, 10, "    /$$$$$$  /$$    /$$ /$$$$$$$$ /$$$$$$$ \n");
    mvprintw(12, 10, "   /$$__  $$| $$   | $$| $$_____/| $$__  $$\n");
    mvprintw(13, 10, "  | $$  \\ $$| $$   | $$| $$      | $$  \\ $$\n");
    mvprintw(14, 10, "  | $$  | $$|  $$ / $$/| $$$$$   | $$$$$$$/\n");
    mvprintw(15, 10, "  | $$  | $$ \\  $$ $$/ | $$__/   | $$__  $$\n");
    mvprintw(16, 10, "  | $$  | $$  \\  $$$/  | $$      | $$  \\ $$\n");
    mvprintw(17, 10, "  |  $$$$$$/   \\  $/   | $$$$$$$$| $$  | $$\n");
    mvprintw(18, 10, "   \\______/     \\_/    |________/|__/  |__/\n");
    mvprintw(20, 25, "Score:");
    attron(A_STANDOUT);
    printw("%3d", a);
    attroff(A_STANDOUT);
    getch();
}

void print_score(Snake& s)
{
	for(int r=1; r<=7; r++) mvprintw(r,25, "|");
	for(int r=1; r<=7; r++) mvprintw(r,50, "|");
	for(int c=25; c<=50; c++) mvprintw(1,c, "-");
	for(int c=25; c<=50; c++) mvprintw(7,c, "-");

	mvprintw(2, 26, "*******SCORE BOARD******");

	mvprintw(3, 27, "B: %d", s.getscore());
	mvprintw(4, 27, "+: %d", s.getCntGrowth());
	mvprintw(5, 27, "-: %d", s.getCntPoison());
	mvprintw(6, 27, "G: %d", s.getCntGate());
	

	refresh();
}

void print_mission(const Snake& s)
{
	for(int r=10; r<=17; r++) mvprintw(r,25, "|");
	for(int r=10; r<=17; r++) mvprintw(r,50, "|");
	for(int c=25; c<=50; c++) mvprintw(10,c, "-");
	for(int c=25; c<=50; c++) mvprintw(17,c, "-");
	
	mvprintw(11, 26, "******MISSION BOARD*****");

	refresh();
}


int classic_game(void) 
{
	start_color();
	use_default_colors();
	init_pair(COLOR_SNAKE_HEAD, COLOR_RED, COLOR_RED);
	init_pair(COLOR_SNAKE_BODY, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(COLOR_ITEM_GROWTH, COLOR_GREEN, COLOR_GREEN);
	init_pair(COLOR_ITEM_POISON, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(COLOR_IMMUNEWALL, COLOR_BLACK, COLOR_BLACK);
	init_pair(COLOR_WALL, COLOR_BLACK, COLOR_BLACK);
	init_pair(COLOR_GATE, COLOR_BLUE, COLOR_BLUE);

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
		print_score(S);
		print_mission(S);
		
		attron(A_STANDOUT);
		mvprintw(23, 15, "PRESS 'Q' to EXIT BACK TO MENU.");
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

Point rand_point(std::deque<Cell> cells, std::deque<Item> items, std::deque<Cell> walls, std::deque<Cell> gates)
{
	Point p;
	int flag;
	srand(time(NULL));
	do {
		flag=0;

		// index = rand() % walls.size();
		// p = walls[index].p;
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

		// gate가 겹치면 안됨
		for(std::deque<Cell>::iterator it=gates.begin(); it!=gates.end(); ++it){
			if(p.row==it->p.row && p.col==it->p.col) {
				flag=1;
				break;
			}
		}

		for(std::deque<Cell>::iterator it=walls.begin(); it!=walls.end(); ++it){
			if(p.row==it->p.row && p.col==it->p.col && it->type==IMMUNEWALL) {
				flag=1;
				break;
			}
		}

	}while(flag);
	return p;
}


int rand_score(void) {
	// 초단위로하면, 동시출현 아이템들의 생성시간이 거의 같아서 종류가 같아지는 버그가 발생.
	// 따라서 millisecond 기준으로 랜덤처리.
	struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);

	int rnd = rand();

	// 1은 Growth
	// -1은 Poison
	if(rnd%2) return 1;	
	return -1;
}

int diff(int a, int b) {
	if((a-b)>0) {
		return a-b;
	}
	else {
		return b-a;
	}
}


void settingMap(std::deque<Cell>& walls, int stage)
{
	Cell temp1, temp2;

	for(int i=0; i<MAX_ROW; i++){
        temp1.p.col = 0;
        temp2.p.col = MAX_COL-1;
        temp1.p.row = i;
        temp2.p.row = i;

        // 가장자리는 Gate로 변할 수 없음(=IMMUNEWALL)
        if(i==0 || i==MAX_ROW-1){
            temp1.type = IMMUNEWALL;
            temp2.type = IMMUNEWALL;
        }else{
            temp1.type = WALL;
            temp2.type = WALL;
        }
        walls.push_back(temp1);
        walls.push_back(temp2);
    }

    for(int i=0; i<MAX_COL-1; i++){
        temp1.p.col = i;
        temp2.p.col = i;
        temp1.p.row = 0;
        temp2.p.row = MAX_ROW-1;

        // 가장자리는 Gate로 변할 수 없음(=IMMUNEWALL)
        if(i==0 || i==MAX_COL-1){
            temp1.type = IMMUNEWALL;
            temp2.type = IMMUNEWALL;
        }else{
            temp1.type = WALL;
            temp2.type = WALL;
        }
        
        walls.push_back(temp1);
        walls.push_back(temp2);
    }

}
#ifndef SNAKE_NCURSES_HPP
#define SNAKE_NCURSES_HPP

#define MAX_ROW 18
#define MAX_COL 79
#define DEF_LEN_FUN 25
#define DEF_LEN_CLASSIC 3

#define FILE_NAME "snake.db"

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define TIMEOUT 100
#define TIMEOUT_GAME_OVER 100000
#define TIMEOUT_LONG 10000

// COLOR 팔레트
#define SNAKE_HEAD 1
#define SNAKE_BODY 2
#define ITEM_GROWTH 3
#define ITEM_POISON 4

#define MAX_ITEM 3
#define ITEM_TIME 5

struct Point{
	int row, col;
};

struct Node {
	Point p;
	int dir;
};

struct Cell {
	Point p;
	char c;
};

struct Item {
	Point p;
	int points;
	char c;
};

// 먹은 아이템에 정보를 저장
struct CurrentItem {
	std::deque<Item>::iterator t;
	Point p;
	int itemFlag;
};

void print_snake(void);
int show_menu(void);
void show_gameover(int);
Point rand_point(std::deque<Cell>, std::deque<Item>);
int rand_score(void);
int getrow(int);
int getcol(int);
int diff(int, int);
int classic_game(void);
void print_score(int);

#endif

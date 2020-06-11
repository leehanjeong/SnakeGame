#ifndef SNAKE_NCURSES_HPP
#define SNAKE_NCURSES_HPP

#define MAX_ROW 21
#define MAX_COL 31
#define DEF_LEN_FUN 25
#define DEF_LEN_CLASSIC 3

#define FILE_NAME "snake.db"

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define TIMEOUT 100
#define TIMEOUT_GAME_OVER 100000
#define TIMEOUT_LONG 3000

#define GAMEOVER_DELAY 3

// COLOR 팔레트
#define COLOR_SNAKE_HEAD 1
#define COLOR_SNAKE_BODY 2
#define COLOR_ITEM_GROWTH 3
#define COLOR_ITEM_POISON 4
#define COLOR_WALL 5
#define COLOR_IMMUNEWALL 6
#define COLOR_GATE 7

#define MAX_ITEM 3
#define ITEM_TIME 5

// Wall의 종류
#define WALL 1
#define IMMUNEWALL 2
#define GATEWALL 3

// Snake길이가 10이상일때 Gate가 출현한다.
#define APPEAR_GATE_LEN 6
#define GATE_TIME 10

#define GAME_STAGE 4

struct Point{
	int row, col;
};


struct Cell {
	Point p;
	int type;
};

struct Item {
	Point p;
	int points;
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
void print_mission();
void print_nextStage(int);
void show_gameClear();
void classic_game(void);

Point rand_point(std::deque<Cell>, std::deque<Item>, std::deque<Cell>);
Point rand_point(std::deque<Cell>, std::deque<Item>, std::deque<Cell>, std::deque<Cell>);
int rand_score(void);
int diff(int, int);
int missionClear(int, int, int, int, int);


#endif

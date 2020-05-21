#include <queue>
#include <cstdlib>
#include <ncursesw/curses.h>
#include <locale.h>
#include <ctime>
#include <fstream>
#include <iostream>

#include "snake_ncurses.hpp"
#include "snake.hpp"
#include "score.hpp"


Snake::Snake(int len) {
	int i;
	Cell temp;
	fdir=RIGHT;
	temp.p.row=0;

	for(i=0; i<len-1; i++) {
		temp.p.col=i;
		cells.push_front(temp);
	}

	temp.p.col=i;
	cells.push_front(temp);
}

void Snake::createNode(int d) 
{
	fdir=d;
}

void Snake::render(void) {
	erase();
	for(std::deque<Cell>::iterator it=cells.begin(); it!=cells.end(); ++it){
		mvaddch(it->p.row, it->p.col, it->c);	// r,c로 움직이고 c를 출력하는함수(ncurses)
	}
	refresh();
}

void Snake::movesnake(void) {
	Point f, b;
	Cell temp;

	f=cells.front().p;
	b=cells.back().p;
	cells.front().c='@';

	switch(fdir) {
		case UP:
			f.row=getrow(f.row-1);
			break;
		case DOWN:
			f.row=getrow(f.row+1);
			break;
		case RIGHT:
			f.col=getcol(f.col+1);
			break;
		case LEFT:
			f.col=getcol(f.col-1);
			break;
	}
	temp.p=f;
	temp.c='O';
	
	// 맨뒤 아이템을 삭제하고 앞에 갱신하는 형태
	cells.push_front(temp);
	// if(!nodes.empty()) {
	// 	if(b.row==nodes.front().p.row && b.col==nodes.front().p.col) {
	// 		nodes.pop_front();
	// 	}
	// }
	cells.pop_back();
}

int Snake::getfdir(void) 
{
	return fdir;
}

void Snake::setfdir(int dir) 
{
	fdir=dir;
}

Classic_Snake::Classic_Snake():Snake(3) 
{
	
	makeItem();
	score=cells.size();
	coll=0;  
}

void Classic_Snake::makeItem(void) 
{
	erase();
	item_starttime = time(NULL);
	srand(time(NULL));
	int cnt = (rand()%MAX_ITEM)+1;
	//bool flag = false;

	for(int i=0; i<cnt; i++){
		T[i].p=rand_point(cells, T, itemCnt);
		T[i].points=rand_score();		
	}
	itemCnt = cnt;
	itemStatus.itemFlag = 0;
	itemStatus.idx = -1;
	refresh();
}

void Classic_Snake::eatItem(void)
{
	int index = itemStatus.idx;

	T[index].points = 0;
	for(int i=index+1; i<itemCnt; i++)
		T[i-1] = T[i];
	// T[itemCnt-1].p.row = -1;
	// T[itemCnt-1].p.col = -1;

	itemCnt--;
	//erase();
}

void Classic_Snake::movesnake(void) 
{
	Point f, b;
	Cell temp;
	f=cells.front().p;
	b=cells.back().p;
	cells.front().c='@';
	switch(fdir) {
		case UP:
			f.row=getrow(f.row-1);
			break;
		case DOWN:
			f.row=getrow(f.row+1);
			break;
		case RIGHT:
			f.col=getcol(f.col+1);
			break;
		case LEFT:
			f.col=getcol(f.col-1);
			break;
	}
	temp.p=f;
	cells.push_front(temp);
	
	// 충돌하면 게임 종료
	if(collide()) {
		coll=1;
		return;
	}

	bool itemFlag = false;
	for(int i=0; i<itemCnt; i++){
		if(cells.front().p.row!=T[i].p.row || cells.front().p.col!=T[i].p.col) {
			
		}else{
			itemFlag = true;

			itemStatus.idx = i;
			itemStatus.p.row = T[i].p.row;
			itemStatus.p.col = T[i].p.col;
			itemStatus.itemFlag = T[i].points;
			break;
		}
	}

	// 1) Growth 아이템을 먹었을 경우 : 그대로 몸 증가(액션X)
	// 2) Poision 아템을 먹었을 경우 : 몸의 길이가 2개 감소
	// 3) 아무일도 일어나지 않았을 경우 : 몸의 길이가 1개 감소.
	// Snake가 움직일 때마다, Node를 하나씩 추가하므로.
	if(itemFlag){
		if(itemStatus.itemFlag == -1){	//Poison Item
			cells.pop_back();
			cells.pop_back();
		}else if(itemStatus.itemFlag == 1){	
			//cells.push_back(temp2);
		}
		score = cells.size();
		eatItem();
	}else{	
		cells.pop_back();
	}

	// 아이템은 5초가 지나면 자동으로 나타난다.
	time_t cur_time;
	cur_time = time(NULL);

	if(cur_time-item_starttime >= ITEM_TIME){
		makeItem();
	}
}

void Classic_Snake::render(void) 
{
	erase();
	
	for(std::deque<Cell>::iterator it=cells.begin(); it!=cells.end(); ++it){
		if(it==cells.begin()){
			attron(COLOR_PAIR(SNAKE_HEAD));
			mvprintw(it->p.row, it->p.col, "\u2B1B");  //\u2B1C
			attroff(COLOR_PAIR(SNAKE_HEAD));
		}else{
			attron(COLOR_PAIR(SNAKE_BODY));
			mvprintw(it->p.row, it->p.col, "\u2B1B");
			attroff(COLOR_PAIR(SNAKE_BODY));
		}
		//mvaddch(it->p.row, it->p.col, it->c);
	}

	// time_t cur_time;
	// cur_time = time(NULL);
	// mvprintw(2, MAX_COL-5, "%d", cur_time-item_starttime);
	for(int i=0; i<itemCnt; i++){
		if(T[i].points == 1){
			attron(COLOR_PAIR(ITEM_GROWTH));
			mvprintw(T[i].p.row, T[i].p.col, "\u2B1B");
			attroff(COLOR_PAIR(ITEM_GROWTH));
		}else if(T[i].points == -1){
			attron(COLOR_PAIR(ITEM_POISON));
			mvprintw(T[i].p.row, T[i].p.col, "\u2B1B");
			attroff(COLOR_PAIR(ITEM_POISON));
		}
	}	
	refresh();
}

// 충돌
int Classic_Snake::collide(void) {
	for(std::deque<Cell>::iterator it=cells.begin(); it!=cells.end(); ++it){
		if(cells.front().p.row==it->p.row && cells.front().p.col==it->p.col && it!=cells.begin()) {
			return 1;
		}
	}
	return 0;
}

int Classic_Snake::getcoll(void) {
	return coll;
}

int Classic_Snake::getscore(void) {
	return score;
}

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


Snake::Snake(int len)
{
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

	makeItem();
	coll=0;  
}


int Snake::getfdir(void) 
{
	return fdir;
}

void Snake::setfdir(int dir) 
{
	fdir=dir;
}

void Snake::createNode(int d) 
{
	fdir=d;
}

void Snake::makeItem(void) 
{
	erase();
	
	item_starttime = time(NULL);
	srand(time(NULL));

	items.clear();
	Item tempItem;
	int cnt = (rand()%MAX_ITEM)+1;

	for(int i=0; i<cnt; i++){
		tempItem.p = rand_point(cells, items);
		tempItem.points = rand_score();	
		items.push_back(tempItem);		
	}
	curitem.itemFlag = 0;
	refresh();
}

void Snake::eatItem(void)
{
	items.erase(curitem.t);
}

void Snake::movesnake(void) 
{
	Point f, b;
	Cell temp;
	f=cells.front().p;
	b=cells.back().p;

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

	for(std::deque<Item>::iterator it=items.begin(); it!=items.end(); ++it){
		if(cells.front().p.row==it->p.row && cells.front().p.col==it->p.col) { //snake머리랑 아이템이랑 위치 같으면
			itemFlag = true;

			curitem.t = it;
			curitem.p.row = it->p.row;
			curitem.p.col = it->p.col;
			curitem.itemFlag = it->points;
			break;
		}
	}

	// 1) Growth 아이템을 먹었을 경우 : 그대로 몸 증가(액션X)
	// 2) Poision 아템을 먹었을 경우 : 몸의 길이가 2개 감소
	// 3) 아무일도 일어나지 않았을 경우 : 몸의 길이가 1개 감소.
	// Snake가 움직일 때마다, Node를 하나씩 추가하므로.
	if(itemFlag){
		if(curitem.itemFlag == -1){	//Poison Item
			cells.pop_back();
			cells.pop_back();
		}else if(curitem.itemFlag == 1){	//Growth Item
			//cells.push_back(temp2);
		}
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

void Snake::render(void)   //ncurses 화면 구현?
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
	}

	for(std::deque<Item>::iterator it=items.begin(); it!=items.end(); ++it){
		if(it->points == 1){
			attron(COLOR_PAIR(ITEM_GROWTH));
			mvprintw(it->p.row, it->p.col, "\u2B1B");
			attroff(COLOR_PAIR(ITEM_GROWTH));
		}else if(it->points == -1){
			attron(COLOR_PAIR(ITEM_POISON));
			mvprintw(it->p.row, it->p.col, "\u2B1B");
			attroff(COLOR_PAIR(ITEM_POISON));
		}
	}
	refresh();
}

// 충돌판단
int Snake::collide(void) {
	for(std::deque<Cell>::iterator it=cells.begin(); it!=cells.end(); ++it){
		if(cells.front().p.row==it->p.row && cells.front().p.col==it->p.col && it!=cells.begin()) {
			return 1;
		}
	}
	return 0;
}

int Snake::getcoll(void) 
{
	return coll;
}

int Snake::getscore(void) 
{
	return cells.size();
}


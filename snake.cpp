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

	// Wall 설정
	setWall();
	
	fdir=RIGHT;
	temp.p=rand_point(cells, items, walls);

	// Snake길이때문에 가끔 화면을 넘어가는 경우가 발생해서 예외조건설정.
	if(temp.p.row+DEF_LEN_CLASSIC >= MAX_ROW-1){
		temp.p.row=MAX_ROW-DEF_LEN_CLASSIC-1;
	}

	for(i=0; i<len-1; i++) {
		temp.p.col+=i;
		if(temp.p.col+i >= MAX_COL-1){
			temp.p.col=MAX_COL-i-1;
		}
		cells.push_front(temp);
	}

	temp.p.col+=i;
	cells.push_front(temp);

	// 아이템생성(랜덤)
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
		tempItem.p = rand_point(cells, items, walls);
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
			f.row-=1;
			break;
		case DOWN:
			f.row+=1;
			break;
		case RIGHT:
			f.col+=1;
			break;
		case LEFT:
			f.col-=1;
			break;
	}
	temp.p=f;
	
	// 벽에 부딪히면 게임 종료
	if(wallcollid()){
		coll=1;
		return;
	}
	
	// 충돌하면 게임 종료
	if(collide()) {
		coll=1;
		return;
	}

	cells.push_front(temp);

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
			attron(COLOR_PAIR(COLOR_SNAKE_HEAD));
			mvprintw(it->p.row, it->p.col, "\u2B1B");  //\u2B1C
			attroff(COLOR_PAIR(COLOR_SNAKE_HEAD));
		}else{
			attron(COLOR_PAIR(COLOR_SNAKE_BODY));
			mvprintw(it->p.row, it->p.col, "\u2B1B");
			attroff(COLOR_PAIR(COLOR_SNAKE_BODY));
		}
	}
	
	// item
	for(std::deque<Item>::iterator it=items.begin(); it!=items.end(); ++it){
		if(it->points == 1){
			attron(COLOR_PAIR(COLOR_ITEM_GROWTH));
			mvprintw(it->p.row, it->p.col, "\u2B1B");
			attroff(COLOR_PAIR(COLOR_ITEM_GROWTH));
		}else if(it->points == -1){
			attron(COLOR_PAIR(COLOR_ITEM_POISON));
			mvprintw(it->p.row, it->p.col, "\u2B1B");
			attroff(COLOR_PAIR(COLOR_ITEM_POISON));
		}
	}

	// wall
	for(std::deque<Cell>::iterator it=walls.begin(); it!=walls.end(); ++it){
		if(it->type == IMMUNEWALL){
			attron(COLOR_PAIR(COLOR_IMMUNEWALL));
			mvprintw(it->p.row, it->p.col, "\u2B1B");
			attroff(COLOR_PAIR(COLOR_IMMUNEWALL));
		}else if(it->type == WALL){
			attron(COLOR_PAIR(COLOR_IMMUNEWALL));
			mvprintw(it->p.row, it->p.col, "\u2B1B");
			attroff(COLOR_PAIR(COLOR_IMMUNEWALL));
		}
	}
	refresh();
}

// Snake Head가 자신의 Body에 부딪혔을 경우를 찾음
int Snake::collide(void) {
	for(std::deque<Cell>::iterator it=cells.begin(); it!=cells.end(); ++it){
		if(cells.front().p.row==it->p.row && cells.front().p.col==it->p.col && it!=cells.begin()) {
			return 1;
		}
	}
	return 0;
}

// Snake Head가 Wall에 부딪혔을 경우를 찾음
int Snake::wallcollid()
{
	for(std::deque<Cell>::iterator it=walls.begin(); it!=walls.end(); ++it){
		if(cells.front().p.row==it->p.row && cells.front().p.col==it->p.col){
			if(it->type != GATEWALL)
				return 1;
		}
	}
	return 0;
}

// 기본 Wall Setting
// 1) 모서리는 Gate로 변할 수 없어서 IMMUNEWALL로 고정
// 2) WALL은 Gate로 변할 수 있음.
void Snake::setWall()
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


int Snake::getcoll(void) 
{
	return coll;
}

int Snake::getscore(void) 
{
	return cells.size();
}

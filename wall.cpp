#include <queue>
#include <cstdlib>
#include <ncursesw/curses.h>
#include <locale.h>
#include <ctime>
#include <iostream>

#include "snake_ncurses.hpp"
#include "wall.hpp"

Wall::Wall(int row, int col)
{
    setWall(row, col);
}


// 가장자리는 일단 먼저 IMMUNEWALL 로 설정한다.
void Wall::setWall(int r, int c)
{
    Cell temp1, temp2;

    for(int i=0; i<r; i++){
        temp1.p.col = 0;
        temp2.p.col = c-1;
        temp1.p.row = i;
        temp2.p.row = i;

        // 가장자리는 Gate로 변할 수 없음(=IMMUNEWALL)
        if(i==0 || i==r-1){
            temp1.type = IMMUNEWALL;
            temp2.type = IMMUNEWALL;
        }else{
            temp1.type = WALL;
            temp2.type = WALL;
        }
        cells.push_back(temp1);
        cells.push_back(temp2);
    }

    for(int i=0; i<c; i++){
        temp1.p.col = i;
        temp2.p.col = i;
        temp1.p.row = 0;
        temp2.p.row = r-1;

        // 가장자리는 Gate로 변할 수 없음(=IMMUNEWALL)
        if(i==0 || i==r-1){
            temp1.type = IMMUNEWALL;
            temp2.type = IMMUNEWALL;
        }else{
            temp1.type = WALL;
            temp2.type = WALL;
        }
        
        cells.push_back(temp1);
        cells.push_back(temp2);
    }
}


std::deque<Cell> Wall::getcells()
{
    return cells;
}

 void Wall::setcells(std::deque<Cell> cells)
{
    this->cells = cells;
}
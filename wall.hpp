
#ifndef WALL_HPP
#define WALL_HPP

#define WALL 1
#define IMMUNEWALL 2
#define GATEWALL 3

class Wall {
private:
    std::deque<Cell> cells;

public:
    Wall(int row=MAX_ROW, int col=MAX_COL);

    void setWall(int, int);     
    void setcells(std::deque<Cell>);
    std::deque<Cell> getcells();
};

#endif
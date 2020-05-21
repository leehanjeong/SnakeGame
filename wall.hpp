
#ifndef WALL_HPP
#define WALL_HPP

#define WALL 1
#define IMMUNEWALL 2

class Wall {
private:
    std::deque<Cell> cells;

public:
    Wall(int row=MAX_ROW, int col=MAX_COL);
    void setWall(int, int);     
};

#endif
#ifndef SNAKE_HPP
#define SNAKE_HPP


class Snake{
protected:
	time_t item_starttime;

	std::deque<Cell> cells;
	std::deque<Item> items;
	
	CurrentItem curitem;	// 아이템을 먹었을 경우, 어떤 아이템을 먹었는 지에 대한 정보(좌표, 종류) 저장.
	
	int fdir;
	int score, coll;	

public:
	Snake(int len=DEF_LEN_CLASSIC);
	void createNode(int d);
	
	void makeItem(void);
	void eatItem(void);
	void movesnake(void);	// snake가 움직였을때 row,col를 변화시키는 함수. 
	void render(void);	// 변화된 rol,col를 화면에서 변화시킴.
	int collide(void);

	int getscore(void);
	int getcoll(void);
	int getfdir(void);
	void setfdir(int);
};

#endif

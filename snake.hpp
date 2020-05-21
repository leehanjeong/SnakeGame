#ifndef SNAKE_HPP
#define SNAKE_HPP

class Snake {
protected:
	std::deque<Cell> cells;
	std::deque<Node> nodes;
	int fdir;
public:
	Snake(int len=DEF_LEN_FUN);
	void createNode(int d);
	virtual void render(void);
	virtual void movesnake(void);
	int getfdir(void);
	void setfdir(int);
};

class Classic_Snake:public Snake {
protected:
	int score, coll, itemCnt;
	time_t item_starttime;
	Treat T[3];
	Status itemStatus;	// 아이템을 먹었을 경우, 어떤 아이템을 먹었는 지에 대한 정보(좌표, 종류) 저장.
	

public:
	Classic_Snake();
	void makeItem(void);
	void eatItem(void);
	virtual void movesnake(void);	// snake가 움직였을때 row,col를 변화시키는 함수. 
	virtual void render(void);	// 변화된 rol,col를 화면에서 변화시킴.
	int collide(void);
	int getscore(void);
	int getcoll(void);
};

#endif

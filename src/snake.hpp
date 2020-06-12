#ifndef SNAKE_HPP
#define SNAKE_HPP


class Snake{
protected:
	int len;
	int stage;

	time_t item_starttime;	// Item은 5초마다 새로 생성해야하므로, 아이템의 생성시간을 담는 변수
	time_t gate_starttime;

	std::deque<Cell> cells;	// Snake head,body 좌표를 저장하는 queue
	std::deque<Item> items;	// Item의 좌표를 저장하는 queue
	std::deque<Cell> walls; // WALL,IMMUNEWALL,GATE 정보들
	std::deque<Cell> gates;
	
	CurrentItem curitem;	// 아이템을 먹었을 경우, 어떤 아이템을 먹었는 지에 대한 정보(좌표, 종류) 저장.
	
	int fdir;				// Snake의 현재진행방향
	int score, coll;		// score=Snake의 길이, coll=충돌했는지에 대한 flag

	int poison;
	int growth;
	int gate;

public:
	Snake(int s=1);	
	void createNode(int d);	// Snake가 움직일때, 새로운 Node를 추가하게됨. -> Item이벤트 발생하지않으면 다시 queue에서 삭제됨. 
	
	void makeItem();	// 아이템 생성(랜덤, 최대3개)
	void eatItem();		// 아이템을 먹었을 때의 변화	
	void movesnake();	// snake가 움직였을때 row,col를 변화시키는 함수. 
	void render();		// 변화된 rol,col를 화면에 출력
	int collide();		// Snake의 머리가 몸통에 부딪히면 충돌판단 -> GameOver

	void setWall(int stage);    	// 초기 벽 설정(WALL,IMMUNEWALL)
	int wallcollid();	// 벽 충돌여부 확인 함수
	void makeGate();	// Snake길이가 APPEAR_GATE_LEN(=10) 이상일때 Gate 출현

	int getscore();		// Score는 Snake의 길이
	int getcoll();		// collide()함수 호출시, 변화되는 변수coll Get Function
	int getfdir();		// Snake의 진행방향 Get Function
	void setfdir(int);		// Snake의 진행방향 Set Function

	int getCntGrowth();
	int getCntPoison();
	int getCntGate();
	int getStage();

	int isWall(Point p);
	
};

#endif

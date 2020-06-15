C++ 언어를 사용하고 ncurses 라이브러리를 활용하여 제작한 Snake Game Project 입니다.  <br>

## 프로젝트 설명

### 목차

- [1. Team](#1-team)
- [2. Compile](#2-compile)
- [3. Excute](#3-excute)
- [4. Game Rule](#4-game-rule)
  - [4.1 Snake](#41-snake)
  - [4.2 Item](#42-item)
  - [4.3 Wall](#43-wall)
    - [4.3.1 Wall](#431-wall)
    - [4.3.2 Immune Wall](#432-immune-wall)
    - [4.3.3 Gate](#433-gate)
  - [4.4 Score Board](#44-score-board)
  - [4.5 Stage](#45-stage)
- [5. About Code](#5-about-code)
  - [5.1 Map 구성](#51-map-구성)
  - [5.2 Snake Movement](#52-snake-movement)
  - [5.3 Item](#53-item)
  - [5.4 Gate](#54-gate)
  - [5.5 Score Board 및 Misson](#55-score-board-및-mission)


## 1. Team

### 5조 

| Name   | Student ID | 역할             |
| ------ | ---------- | ---------------- |
| 윤서영 | 20191633   | 프로젝트 리더    |
| 이한정 | 20191650   | Stage 구성 및 QA |
| 조규현 | 20191669   | UI 구성          |
| 황영서 | 20191691   | 게임 로직 구현   |

<br>

## 2. Compile

- 개발OS: Linux Ubuntu 16.04 LTS
- Version: C++ 14
- Compile Command: ``` make ```

<br>

## 3. Excute

- Command: ``` ./snake_ncurses ```

<br>

## 4. Game Rule

### 4.1 Snake

- 처음 시작 방향은 오른쪽(RIGHT) 이다.
- 방향키(←↑→↓) 로 이동방향을 조정할 수 있다.
- 일정시간마다 사용자가 입력한 방향으로 나아간다.
- 현재 진행방향과 반대로 이동 시, Skip 된다.
- 머리와 몸통이 부딪히면 게임 종료
- Wall, Immune Wall과 부딪히면 게임 종료

### 4.2 Item

- Growth Item은 <b>초록색 네모</b> / Poison Item은 <b>보라색 네모</b> 로 출현
- Growth Item
  - 획득 시, 몸의 길이가 1만큼 증가한다.
  - 몸의 길이는 현재 진행방향으로 증가한다.
- Poison Item
  - 획득 시, 몸의 길이가 1만큼 감소한다.
  - 길이가 3미만이 됐을 경우 게임 종료
- Item 출현
  - Snake, Wall이 있지 않은 임의의 위치에서 출현한다.
  - 출현 후, 5초가 지나면 사라지고, 다른 위치에 출현한다.
  - Item은 1~3개까지 종류별로 랜덤하게 출현한다.

### 4.3 Wall

#### 4.3.1 Wall

- Snake가 통과할 수 없다. (게임 종료)
- Gate가 생성될 수 있다.

#### 4.3.2 Immune Wall

- Snake가 통과할 수 없다. (게임 종료)
- Gate가 생성될 수 있다.

#### 4.3.3 Gate

- 두 개가 한 쌍이며, 한 번에 한 쌍만 나타난다.
- Gate는 서로 겹치지 않는다.
- 임의의 Wall에서 나타난다.
- Snake길이가 7 이상일 때 나타난다.
- 진입 중인 경우, Gate는 사라지거나 다른 위치에 나타나지 않는다.
- Gate 진입 시, 이동방향
  - Gate가 나타나는 벽이 가장자리에 있을 경우
    | 벽의 위치 | 진행 방향   |
    | --------- | ----------- |
    | 상단      | 아래 방향   |
    | 하단      | 위 방향     |
    | 좌측      | 오른쪽 방향 |
    | 우측      | 왼쪽 방향   |
    
  - Gate가 나타나는 벽이 Map의 안쪽에 위치할 경우
    - 진입 방향과 일치하는 방향이 우선
    - 진입 방향과 반대 방향
    - 진입 방향의 시계방향

### 4.4 Score Board

- 프로그램 우측에는 게임 점수와 미션을 표시함
- Mission을 달성하면 다음 Stage로 진행된다.
- Score Board
  - B: 현재 길이
  - +: 획득한 Growth Item 수
  - -: 획득한 Poison Item 수
  - g: Gate 사용 횟수
- Mission Board
  - B: 10 (목표 달성 여부)
  - +: 7 (V)
  - -: 3 ()
  - g: 1 ()

### 4.5 Stage

- Stage는 총 4단계로 구성되어있다. 
- 각 단계별 Mission을 Clear하게되면, 다음 단계로 넘어가게 된다.
  | 단계  | Misson내용                             |
  | ----- | -------------------------------------- |
  | 1단계 | 길이=7 / Growth=3 / Poison=1 / Gate=1  |
  | 2단계 | 길이=10 / Growth=4 / Poison=2 / Gate=1 |
  | 3단계 | 길이=12 / Growth=5 / Poison=3 / Gate=2 |
  | 4단계 | 길이=14 / Growth=6 / Poison=4 / Gate=3 |

<br>

## 5. About Code

### 5.1 Map 구성

- Map 크기 : 21 X 31 (ROW, COL)
- Map은 Stage마다 다르게 구성되어있다. 

#### 5.1.1 setStageWall() 

초기 Map을 구성하는 함수

```C++
// stage.cpp
std::deque<Cell> setStageWall(int stage)
{
    std::deque<Cell> tmpWall;

    for(int i=0; i<MAX_ROW; i++){
        Cell temp;
        temp.p.row = i;
        for(int j=0; j<MAX_COL; j++){
            temp.p.col = j;

            if(MAP[stage-1][i][j] == 2){
                temp.type = IMMUNEWALL;
                tmpWall.push_back(temp);
            }else if(MAP[stage-1][i][j] == 0){
                temp.type = WALL;
                tmpWall.push_back(temp);
            }
        }
    }

    return tmpWall;
}
```

- 임시변수 tmpWall을 deque 자료형으로 선언함.
- 미리 저장되어있는 MAP 배열의 값을 확인하여 ImmuneWall/Wall인지를 판단한다.
  - MAP\[STAGE\]\[ROW\]\[COL\]==0 : WALL
  - MAP\[STAGE\]\[ROW\]\[COL\]==2 : IMMUNEWALL

#### 5.1.2 void Snake::setWall(int stage)

Snake 클래스의 메소드이며, Snake가 생성됨과 동시에 Map을 생성해도록 해준다.
setStageWall 메소드를 호출할 때, stage 인자값을 넘겨준다.

```C++
// snake.cpp
void Snake::setWall(int stage)
{
	walls = setStageWall(stage);
}
```

### 5.2 Snake Movement

#### 5.2.1 Snake Class

Snake 클래스에서는 Snake생성, 아이템 생성, 초기 Map구성, Gate출현의 기능을 수행하는 메소드가 존재한다.

```c++
// snake.hpp
class Snake{
protected:
	int len;
	int stage;

	time_t item_starttime;			// Item은 5초마다 새로 생성해야하므로, 아이템의 생성시간을 담는 변수
	time_t gate_starttime;

	std::deque<Cell> cells;			// Snake head,body 좌표를 저장하는 queue
	std::deque<Item> items;			// Item의 좌표를 저장하는 queue
	std::deque<Cell> walls; 		// WALL,IMMUNEWALL,GATE 정보들
	std::deque<Cell> gates;
	
	CurrentItem curitem;			// 아이템을 먹었을 경우, 어떤 아이템을 먹었는 지에 대한 정보(좌표, 종류) 저장.
	
	int fdir;						// Snake의 현재진행방향
	int score, coll;				// score=Snake의 길이, coll=충돌했는지에 대한 flag

	int poison;						// 현재까지 획득한 Poison아이템수
	int growth;						// 현재까지 획득한 Growth아이템수
	int gate;						// 현재까지 통과한 Gate의 수

public:
	Snake(int s=1);	
	void createNode(int d);	
	
	void makeItem();				// 아아템 생성(랜덤, 최대3개)
	void eatItem();					// 아이템을 먹었을 때의 변화	
	void movesnake();				// snake가 움직였을때 row,col를 변화시키는 함수. 
	void render();					// 변화된 rol,col를 화면에 출력
	int collide();					// Snake의 머리가 몸통에 부딪히면 충돌판단 -> GameOver

	void setWall(int stage);    	// 초기 벽 설정(WALL,IMMUNEWALL)
	int wallcollid();				// 벽 충돌여부 확인 함수
	void makeGate();				// Snake길이가 APPEAR_GATE_LEN 이상일때 Gate 출현
	int isWall(Point p);			// 해당 좌표가 Wall인지 Check하는 함수

	int getscore();					// Score는 Snake의 길이
	int getcoll();					// collide()함수 호출시, 변화되는 변수coll Get Function
	int getfdir();					// Snake의 진행방향 Get Function
	void setfdir(int);				// Snake의 진행방향 Set Function

	int getCntGrowth();				// return growth
	int getCntPoison();				// return poison
	int getCntGate();				// return gate
	int getStage();					// return stage
};
```

#### 5.2.2 Snake 생성

Snake클래스의 생성자를 통해 Snake를 생성한다. 인자값으로는 stage의 값을 넘겨받게 된다. 

- 길이가 3인 Snake를 생성
- Score Board에 표시할 점수 변수들을 초기화(growth/poison/gate)
- item을 획득한 시간을 초기화
- 기본 이동방향을 오른쪽(RIGHT)으로 설정
- 초기 Map설정
- 초기 Item설정

```c++
// snake.cpp
Snake::Snake(int s) : len(DEF_LEN_CLASSIC), stage(s)
{
	int i;
	Cell temp;

	// Score Board를 위한 초기화
	growth = 0;
	poison = 0;
	gate = 0;

	// Wall 설정
	setWall(stage);

	// time초기화
	item_starttime = 0;
	gate_starttime = 0;
	
	fdir=RIGHT;
	temp.p=rand_point(cells, items, walls);

	// Snake길이때문에 가끔 화면을 넘어가는 경우가 발생해서 예외조건설정.
	Point tmpP = temp.p;
	tmpP.col += DEF_LEN_CLASSIC;

	if((temp.p.col+DEF_LEN_CLASSIC) >= MAX_ROW-1){
		temp.p.col -= (MAX_ROW-DEF_LEN_CLASSIC);
	}else if(isWall(tmpP)){
		temp.p.col -= MAX_ROW-DEF_LEN_CLASSIC;
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
```

#### 5.2.3 방향키 입력

사용자가 방향키를 입력하게 되면, Snake가 움직이게 된다. 
![Snake움직임](https://raw.githubusercontent.com/young43/SnakeGame/master/img/2%EB%8B%A8%EA%B3%841.png?token=ANEQJDDKMMGS7W5LV4WFM6S64JNE6)
![Snake움직임2](https://raw.githubusercontent.com/young43/SnakeGame/master/img/2%EB%8B%A8%EA%B3%842.png?token=ANEQJDCS5K64VJZAVBMYVMS64JNGY)

- 다음과 같은 상황에는 방향키 입력이 무시된다.
  - 현재 진행방향과 같은 방향
  - 현재 진행방향과 반대 방향
- 게임 진행 중, 'q' 입력 시, 메인 화면으로 돌아간다.
- 벽에 부딪히거나 자기몸에 부딪히면 게임 종료
- Snake의 몸의 길이가 3미만이면 게임 종료
- 해당 Stage에 대한 Mission을 Clear하면, 다음 Stage로 넘어가게 된다.

```c++
// snake_ncurses.cpp
while(1) {
		ch=getch();
		if(ch=='q') {
			return S.getscore();
		}
		else if(ch==KEY_UP || ch==KEY_DOWN || ch==KEY_RIGHT || ch==KEY_LEFT) {
			switch(ch) {
				case KEY_UP:
					d=UP;
					break;
				case KEY_DOWN:
					d=DOWN;
					break;
				case KEY_RIGHT:
					d=RIGHT;
					break;
				case KEY_LEFT:
					d=LEFT;
					break;
			}
			if(diff(S.getfdir(), d)!=2 && d!=S.getfdir()) {
				S.createNode(d);	// 진행방향 설정
			}
		}
		S.movesnake();
		S.render();

		print_score(S);
		print_mission(S);

		// 벽에 부딪히거나 자기몸에 부딪히면 GameOver
		if(S.getcoll()) {
			timeout(TIMEOUT_LONG);
			getch();
			show_gameover(S.getscore());
			return S.getscore();
		}

		// 길이가 3미만이면 GameOver
		if(S.getscore()<DEF_LEN_CLASSIC) {
			timeout(TIMEOUT_LONG);
			getch();
			show_gameover(S.getscore());
			return S.getscore();
		}

		if(missionClear(stage, S.getscore(), S.getCntGrowth(), S.getCntPoison(), S.getCntGate())){
			if(stage==4) break;
			print_nextStage(stage);
			stage++;
			S = Snake(stage);
			continue;
		}

	}
```

#### 5.2.4 Snake 움직임 표현

사용자가 방향키를 입력하게 되면, Snake의 좌표는 1초마다 진행방향쪽으로 변하게 된다.
- 방향키 입력에 따른 좌표 변화
  | 방향키 | 좌표변화        |
  | ------ | --------------- |
  | 상     | 행이 1만큼 감소 |
  | 하     | 행이 1만큼 증가 |
  | 좌     | 열이 1만큼 감소 |
  | 우     | 열이 1만큼 증가 |
- 구현방법
  - 변화된 좌표를 front에 push한다.
  - 아이템을 먹지 않았을 경우, pop을 하여 맨 뒤 원소를 삭제한다.

```C++
// snake.cpp
// Snake::movesnake()
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

// 충돌하면 게임 종료
if(wallcollid() || collide()){
	coll=1;
	return;
}

cells.push_front(temp);
cells.pop_back();   
```

#### 5.2.5 화면 출력

Snake가 움직임을 표현하기위해 매번 refresh하여 출력해준다.
- cells : Snake의 좌표정보 deque
- items : Item들의 좌표정보 deque 
- walls : Immunewall과 wall의 정보 및 좌표 deque
- gates : Gate의 좌표정보(한쌍) deque

```C++
// snake.cpp
void Snake::render()   
{
	erase();
	
	for(std::deque<Cell>::iterator it=cells.begin(); it!=cells.end(); ++it){
		if(it==cells.begin()){
			attron(COLOR_PAIR(COLOR_SNAKE_HEAD));
			mvprintw(it->p.row, it->p.col, "\u2B1B");  
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

	// Wall
	for(std::deque<Cell>::iterator it=walls.begin(); it!=walls.end(); ++it){
		if(it->type == IMMUNEWALL){
			attron(COLOR_PAIR(COLOR_IMMUNEWALL));
			mvprintw(it->p.row, it->p.col, "\u2B1B");
			attroff(COLOR_PAIR(COLOR_IMMUNEWALL));
		}else if(it->type == WALL){
			attron(COLOR_PAIR(COLOR_WALL));
			mvprintw(it->p.row, it->p.col, "\u2B1B");
			attroff(COLOR_PAIR(COLOR_WALL));
		}
	}

	// Gate
	for(std::deque<Cell>::iterator it=gates.begin(); it!=gates.end(); ++it){
		attron(COLOR_PAIR(COLOR_GATE));
		mvprintw(it->p.row, it->p.col, "\u2B1B");
		attroff(COLOR_PAIR(COLOR_GATE));
	}
	refresh();
}
```


### 5.3 Item

#### 5.3.1 Item 출현

아이템은 5초가 지나면 랜덤하게 나타나게 된다. 
- 아이템의 좌표는 Snake와 Wall과 겹치지 않도록 생성한다.
- 최소 1개부터 최대 3개까지의 아이템이 랜덤하게 생성된다.
- 아이템의 종류 또한 랜덤하게 출현한다. 
  - rand_score()함수 : 1 또는 -1을 리턴한다.
    - 1  : Growth아이템
    - -1 : Poison아이템 

```c++
// snake.cpp 
void Snake::makeItem() 
{
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
}
```

#### 5.3.2 Item 획득

Snake Head 부분이 Item과 부딪히게 됐을 경우를 획득했다라고 판단하며, 획득 시 몸의 길이가 증가하거나 감소한다.
- Growth 아이템 획득
  ![아이템출현](https://raw.githubusercontent.com/young43/SnakeGame/master/img/3%EB%8B%A8%EA%B3%84_growth1.png?token=ANEQJDDO72BV7FNPN7I2XKS64JNIC)
  ![아이템출현](https://raw.githubusercontent.com/young43/SnakeGame/master/img/3%EB%8B%A8%EA%B3%84_growth2.png?token=ANEQJDFPGEVZT36PO7M64DS64JNIU)
- Poison 아이템 획득
  ![아이템출현](https://raw.githubusercontent.com/young43/SnakeGame/master/img/3%EB%8B%A8%EA%B3%84_poison1.png?token=ANEQJDEX4DHM2XDNTIUKTU264JNKI)
  ![아이템출현](https://raw.githubusercontent.com/young43/SnakeGame/master/img/3%EB%8B%A8%EA%B3%84_poison2.png?token=ANEQJDG7BSSANH6UVQQJEOC64JNLA)
- Snake Head 부분 = cells.front() 
- Head와 아이템 좌표가 같아질 경우, 획득한 아이템에 대한 정보들을 저장한다.
  - 현재 아이템의 iterator(삭제를 위함)
  - 현재 아이템의 좌표
  - 아이템 flag (Poison인지/Growth인지 구별하기 위함)
- 아이템을 획득하면, 해당 아이템은 화면에서 사라진다. 
  - eatItem()
- 아이템 획득 시, 현재까지 획득한 아이템 갯수를 저장하는 변수를 1 증가시킨다.

```c++
// snake.cpp
// Snake::movesnake()
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

// 1) Growth 아이템을 먹었을 경우 : 그대로 몸 증가
// 2) Poision 아템을 먹었을 경우 : 몸의 길이가 감소
if(itemFlag){
	if(curitem.itemFlag == -1){			//Poison Item
		cells.pop_back();
		cells.pop_back();
		poison++;
	}else if(curitem.itemFlag == 1){	//Growth Item
		growth++;
	}
	eatItem();
}

// 아이템은 5초가 지나면 자동으로 나타난다.
time_t cur_time;
cur_time = time(NULL);

if(cur_time-item_starttime >= ITEM_TIME){
	makeItem();
}
```

```c++
// snake.cpp
void Snake::eatItem()
{
	items.erase(curitem.t);
}
```


### 5.4 Gate

#### 5.4.1 Gate출현

Gate는 기본적으로 Snake 길이가 6이상일 때, 출현하게 된다. 10초마다 Gate를 새로 출현하게 되는데, Snake가 통과 중일 때는 생성하지 않는다.
![게이트출현](https://raw.githubusercontent.com/young43/SnakeGame/master/img/4%EB%8B%A8%EA%B3%841.png?token=ANEQJDFQKF3S2RHTSUJHONK64JNMC)

- Snake(cells) 길이가 6 이상이고, gate가 출현한지 10초이상이면 새로운 Gate를 출현시킨다.
- Snake가 gate를 통과 중인지 Check하고, 통과 중이면 생성하지 않는다.
- Wall 중에 Gate 한 쌍을 랜덤하게 출현 시킨다. 
  - Snake/Item과 좌표가 겹치지 않게 좌표를 가져온다.
  - Gate는 한 쌍이므로, 총 두개의 Gate를 생성하여 gates deque에 저장한다.

```c++
// snake.cpp
// Snake::movesnake()
if(cells.size() >= APPEAR_GATE_LEN && (cur_time-gate_starttime >= GATE_TIME || gate_starttime==0)){
	makeGate();
}
```

  ```c++
// snake.cpp
void Snake::makeGate()
{
	//snake가 gate 통과중인지 check;
	for(std::deque<Cell>::iterator snake=cells.begin(); snake!=cells.end(); ++snake){
		for(std::deque<Cell>::iterator gate=gates.begin(); gate!=gates.end(); ++gate){
			if(snake->p.row==gate->p.row && snake->p.col==gate->p.col) { 
				return;
			}
		}
	}

	gates.clear();
	gate_starttime = time(NULL);

	// WALL 중에 GATE를 두개 뽑아낸다.
	for(int i=0; i<2; i++){
		Cell temp;
		temp.p = rand_point(cells, items, walls, gates);
		gates.push_back(temp);		
	}

}
  ```

#### 5.4.2 Gate 통과

Snake가 하나의 Gate에 통과 중일 경우, 다른 Gate로 나와야한다.
![게이트통과](https://raw.githubusercontent.com/young43/SnakeGame/master/img/4%EB%8B%A8%EA%B3%842.png?token=ANEQJDGOI23PTUNH3GDDQLS64JNM4)
![게이트통과](https://raw.githubusercontent.com/young43/SnakeGame/master/img/4%EB%8B%A8%EA%B3%843.png?token=ANEQJDDDGRBIS33JUSQW2QC64JNNO)

- 우선 Gate가 통과 중인 지 Check하고, gateFlag 값을 true로 설정한다.
- 그렇지 않은경우, 반대편 Gate의 좌표를 저장한다.
- gateFlag==true일 경우
  - 앞에서 설정한 기준값에 따라 Gate의 이동방향을 설정해준다.
  - gate통과 횟수를 저장하는 변수를 1 증가시킨다.

```c++
// snake.cpp
// Snake::movesnake() 
// Gate통과중인지 Check
bool gateFlag = false;
Point gateP;	// 통과중인 Gate말고 반대 Gate

for(std::deque<Cell>::iterator gate=gates.begin(); gate!=gates.end(); ++gate){
	if(cells.front().p.row==gate->p.row && cells.front().p.col==gate->p.col) { 
		gateFlag = true;	
	}else{
		gateP = gate->p;
	}
}

if(gateFlag){
	Cell temp;
	temp.p = gateP;

	// 진입 gate가 가장자리면
	if(gateP.row == 0){
		fdir = DOWN;
	}else if(gateP.row == MAX_ROW-1){
		fdir = UP;
	}else if(gateP.col == 0){
		fdir = RIGHT;
	}else if(gateP.col == MAX_COL-1){
		fdir = LEFT;
	}else{

		// 진입할 방향이 Wall 인지 확인
		for(int i=0; i<4; i++){
			Point tmp = gateP;
			switch(fdir) {
				case UP:
					tmp.row-=1;
					break;
				case DOWN:
					tmp.row+=1;
					break;
				case RIGHT:
					tmp.col+=1;
					break;
				case LEFT:
					tmp.col-=1;
					break;
			}

			// 벽이 아니면 진행방향으로.
			if(!isWall(tmp)) break;

			// 1) 진행방향과 반대
			// 2) 그다음부턴 시계방향
			if(i==0) fdir = (fdir+2)%4;
			else fdir = (fdir+1)%4;
		}
	}

	cells.push_front(temp);
	cells.pop_back();
	gate++;

}
```



### 5.5 Score Board 및 Mission

### 5.5.1 Score Board

Score Board에서는 현재까지 Snake가 획득한 점수들을 출력한다. 

![스코어보드](https://raw.githubusercontent.com/young43/SnakeGame/master/img/5%EB%8B%A8%EA%B3%84_%EC%8A%A4%EC%BD%94%EC%96%B4%EB%B3%B4%EB%93%9C.png?token=ANEQJDAIQTXPK3KBSMCLPKC64JNPU)
- Snake.getscore() : Snake의 현재 길이
- Snake.getCntGrowth() : 현재까지 획득한 Growth 아이템 수
- Snake.getCntPoison(): 현재까지 획득한 Poison 아이템 수
- Snake.getCntGate() : 현재까지 통과한 Gate 수

```c++
// snake_ncurses.cpp
void print_score(Snake& s)
{
	for(int r=1; r<=7; r++) mvprintw(r,35, "|");
	for(int r=1; r<=7; r++) mvprintw(r,60, "|");
	for(int c=35; c<=60; c++) mvprintw(1,c, "-");
	for(int c=35; c<=60; c++) mvprintw(7,c, "-");
	mvprintw(2, 36, "*******SCORE BOARD******");

	mvprintw(3, 37, "B: %d", s.getscore());
	mvprintw(4, 37, "+: %d", s.getCntGrowth());
	mvprintw(5, 37, "-: %d", s.getCntPoison());
	mvprintw(6, 37, "G: %d", s.getCntGate());
	refresh();
}
```

```c++
// snake.cpp
int Snake::getscore() 
{
	return cells.size();
}

int Snake::getCntGrowth()
{
	return growth;
}

int Snake::getCntPoison()
{
	return poison;
}

int Snake::getCntGate()
{
	return gate;
}
```

### 5.5.2 Mission Board & Stage

Mission Board에서는 각 Stage마다 수행해야할 Mission들이 출력된다.
- 1단계
  ![스테이지1](https://raw.githubusercontent.com/young43/SnakeGame/master/img/5%EB%8B%A8%EA%B3%84_%EC%8A%A4%ED%85%8C%EC%9D%B4%EC%A7%801.png?token=ANEQJDCRYLL7FZWMUNL4PRC64JNQS)
- 2단계
  ![스테이지2](https://raw.githubusercontent.com/young43/SnakeGame/master/img/5%EB%8B%A8%EA%B3%84_%EC%8A%A4%ED%85%8C%EC%9D%B4%EC%A7%802.png?token=ANEQJDH3IWVYMCFOEIRY6QS64JNRE)
- 3단계
  ![스테이지3](https://raw.githubusercontent.com/young43/SnakeGame/master/img/5%EB%8B%A8%EA%B3%84_%EC%8A%A4%ED%85%8C%EC%9D%B4%EC%A7%803.png?token=ANEQJDH7AGW3KL67MNJCXBC64JNR2)
- 4단계
  ![스테이지4](https://raw.githubusercontent.com/young43/SnakeGame/master/img/5%EB%8B%A8%EA%B3%84_%EC%8A%A4%ED%85%8C%EC%9D%B4%EC%A7%804.png?token=ANEQJDCZR4G6AD4HF244BN264JNSM)
- 각 Mission을 완수할 경우, 'V' 자를 표시한다.

```c++
// snake_ncurses.cpp
void print_mission(Snake& s)
{
	for(int r=10; r<=16; r++) mvprintw(r,35, "|");
	for(int r=10; r<=16; r++) mvprintw(r,60, "|");
	for(int c=35; c<=60; c++) mvprintw(10,c, "-");
	for(int c=35; c<=60; c++) mvprintw(16,c, "-");

	mvprintw(11, 36, "******MISSION BOARD*****");

	int stg = s.getStage();
	if(MISSION[stg-1][0] <= s.getscore())
		mvprintw(12, 37, "B: %d (V)", MISSION[stg-1][0]);
	else
		mvprintw(12, 37, "B: %d (%d)", MISSION[stg-1][0], s.getscore());

	if(MISSION[stg-1][1] <= s.getCntGrowth())
		mvprintw(13, 37, "+: %d (V)", MISSION[stg-1][1]);
	else
		mvprintw(13, 37, "+: %d (%d)", MISSION[stg-1][1], s.getCntGrowth());

	if(MISSION[stg-1][2] <= s.getCntPoison())
		mvprintw(14, 37, "-: %d (V)", MISSION[stg-1][2]);
	else
		mvprintw(14, 37, "-: %d (%d)", MISSION[stg-1][2], s.getCntPoison());

	if(MISSION[stg-1][3] <= s.getCntGate())
		mvprintw(15, 37, "G: %d (V)", MISSION[stg-1][3]);
	else
		mvprintw(15, 37, "G: %d (%d)", MISSION[stg-1][3], s.getCntGate());

	refresh();
}
```




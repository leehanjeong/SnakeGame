## Snake Game Project

C++ 언어를 사용하고 ncurses 라이브러리를 활용하여 제작한 Snake Game Project 입니다.  <br>

## 프로젝트 설명

### 목차

- [1. Team](#1-team)

- [2. Compile](#2-compile)

- [3. Excute](#3-excute)

- [4. Game Rule](#4-game-rule)

  - [4.1 Snake](#4-1-snake)
  - [4.2 Item](#4-2-item)
  - [4.3 Wall](#4-3-wall)
    - [4.3.1 Wall](#4-3-1-wall)
    - [4.3.2 Immune Wall](#4-3-2-immune-wall)
    - [4.3.3 Gate](#4-3-3-gate)
  - [4.4 Score Board](#4-4-score-board)
  - [4.5 Stage](#4-5-stage)

- [5. About Code](#5-about-code)

  - [5.1 Map 구성](#5-1-map-구성)

  - [5.2 Snake Movement](#5-2-snake-movement)

  - [5.3 Item(Growth/Poison)](#5-3-item-growth-poison)

  - [5.4 Gate](#5-4-gate)

  - [5.5 Score Board 및 Misson](#5-5-score-board-및-mission)

    

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














#pragma once
#include "gameNode.h"

class block;
class burger;

enum CATSTATE
{
	IDLE,
	RUN,
	UP,
	AIR,
	EAT,
	END
};

struct stCAT
{
	image* img;
	RECT rc;
	RECT observer;
	RECT upObserv;
	RECT downObserv;
	CATSTATE state;
	int radius;
	int startX, startY;
	int x, y;
	int spd;
	int fCount;
	int countDivide;
	bool isRight;
};

class cat : public gameNode
{
private:
	stCAT _cat;
	burger* _burger;
	block* _block;

	image* _blockImg;

	int _moveVector;
	int _gravity;
	int _eatCount;
	bool _catStart;
public:
	cat();
	~cat();

	HRESULT init(int x, int y);
	void release();
	void update();
	void render();

	void move();
	void frame();
	void ai();
	void observerFunction();

	void setCatStart() { _catStart = true; }
	void setCatPause() { _catStart = false; }
	void setCatMove() { _cat.state = RUN; }
	void setCatStop() { _cat.state = IDLE; }

	int getStartX() { return _cat.startX; }
	int getStartY() { return _cat.startY; }
	CATSTATE getState() { return _cat.state; }

	void setBlockMemoryLink(block* blockMemory) { _block = blockMemory; }
	void setBurgerMemoryLink(burger* burgerMemory) { _burger = burgerMemory; }

};


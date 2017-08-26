#pragma once
#include "gameNode.h"

struct stBURGER
{
	image* img;
	RECT rc;
	int x, y;
	bool isEat;
};

class burger : public gameNode
{
private:
	stBURGER _burger;

public:
	burger();
	~burger();

	HRESULT init(int x, int y);
	void release();
	void update();
	void render();

	RECT getRc() { return _burger.rc; }
	
	void setEat() { _burger.isEat = true; }
};


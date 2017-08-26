#pragma once
#include "gameNode.h"
#include "button.h"

class cat;
class block;

struct stICON
{
	button* button;
	image* img;
	RECT rc;
	int x, y;
};

class icon : public gameNode
{
private:
	image* _board;
	stICON _stick;
	stICON _pick;
	stICON _start;
	stICON _pause;
	stICON _return;

	cat* _cat;
	block* _block;

	char* _colorBgName;

public:
	icon();
	~icon();

	HRESULT init();
	void release();
	void update();
	void render();

	void start();
	void stop();
	void catReturn();
	void userUpdate();

	void setBgName(char* bgName) { _colorBgName = bgName; }

	void setCatMemoryLink(cat* catLink) { _cat = catLink; }
	void setCBlockMemoryLink(block* blockLink) { _block = blockLink; }

};


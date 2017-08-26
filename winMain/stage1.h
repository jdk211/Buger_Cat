#pragma once
#include "gameNode.h"
#include "cat.h"
#include "icon.h"
#include "block.h"
#include "burger.h"

class stage1 : public gameNode
{
protected:
	//캣
	cat* _burgerCat;
	
	//버거
	burger* _burger;

	//아이콘
	icon* _icon;

	//배경
	image* _img;

	//블럭
	block* _block;
	bool _blockRender;

	char* _colorBgName;
	char* _nextStage;

public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();

	void nextStage();

	char* getBgName() { return _colorBgName; }
};


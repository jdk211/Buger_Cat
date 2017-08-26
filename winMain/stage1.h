#pragma once
#include "gameNode.h"
#include "cat.h"
#include "icon.h"
#include "block.h"
#include "burger.h"

class stage1 : public gameNode
{
protected:
	//Ĺ
	cat* _burgerCat;
	
	//����
	burger* _burger;

	//������
	icon* _icon;

	//���
	image* _img;

	//��
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


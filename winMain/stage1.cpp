#include "stdafx.h"
#include "stage1.h"


stage1::stage1()
{
}


stage1::~stage1()
{
}

HRESULT stage1::init()
{
	_colorBgName = "map1BgColor";
	//배경
	IMAGEMANAGER->addImage(_colorBgName, "image/map_color.bmp", 640, 479, false, false);
	//_img = IMAGEMANAGER->addImage("bg", "image/map1.bmp", 640, 479, false, false);
	
	//고양이
	_burgerCat = new cat;
	_burgerCat->init(50, 334);
	
	//버거
	_burger = new burger;
	_burger->init(560, 342);

	//아이콘
	_icon = new icon;
	_icon->init();
	_icon->setBgName(_colorBgName);

	//블럭	
	_block = new block;
	_block->init(_colorBgName);

	//메모리 링크
	_burgerCat->setBlockMemoryLink(_block);
	_burgerCat->setBurgerMemoryLink(_burger);
	_icon->setCatMemoryLink(_burgerCat);
	_icon->setCBlockMemoryLink(_block);

	_nextStage = "stage2";

	return S_OK;
}

void stage1::release()
{
	_burgerCat->release();
	SAFE_DELETE(_burgerCat);
	_burger->release();
	SAFE_DELETE(_burger);
	_icon->release();
	SAFE_DELETE(_icon);
	_block->release();
	SAFE_DELETE(_block);
}

void stage1::update()
{
	_burgerCat->update();
	_burger->update();
	_icon->update();
	_block->update();
	if(_burgerCat->getState() == END) nextStage();
}

void stage1::render()
{
	//_img->render(getMemDC(), 0, 63);
	_icon->render();
	_block->render();
	_burger->render();
	_burgerCat->render();
}

void stage1::nextStage()
{
	SCENEMANAGER->changeScene(_nextStage);
}


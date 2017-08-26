#include "stdafx.h"
#include "stage3.h"


stage3::stage3()
{
}


stage3::~stage3()
{
}

HRESULT stage3::init()
{
	_colorBgName = "map3BgColor";
	//배경
	IMAGEMANAGER->addImage(_colorBgName, "image/map3_color.bmp", 640, 479, false, false);
	//_img = IMAGEMANAGER->addImage("bg", "image/map1.bmp", 640, 479, false, false);

	//고양이
	_burgerCat = new cat;
	_burgerCat->init(300, 110);

	//버거
	_burger = new burger;
	_burger->init(210, 374);

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

	_nextStage = "stage1";

	return S_OK;
}

void stage3::release()
{
	stage1::release();
}

void stage3::update()
{
	stage1::update();
}

void stage3::render()
{
	stage1::render();
}

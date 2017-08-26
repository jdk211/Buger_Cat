#include "stdafx.h"
#include "stage2.h"


stage2::stage2()
{
}


stage2::~stage2()
{
}

HRESULT stage2::init()
{
	_colorBgName = "map2BgColor";
	//배경
	IMAGEMANAGER->addImage(_colorBgName, "image/map2_color.bmp", 640, 479, false, false);
	//_img = IMAGEMANAGER->addImage("bg", "image/map1.bmp", 640, 479, false, false);
	
	//고양이
	_burgerCat = new cat;
	_burgerCat->init(50, 270);

	//버거
	_burger = new burger;
	_burger->init(560, 278);

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

	_nextStage = "stage3";

	return S_OK;
}

void stage2::release()
{
	stage1::release();
}

void stage2::update()
{
	stage1::update();
}

void stage2::render()
{
	stage1::render();
}

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
	//���
	IMAGEMANAGER->addImage(_colorBgName, "image/map2_color.bmp", 640, 479, false, false);
	//_img = IMAGEMANAGER->addImage("bg", "image/map1.bmp", 640, 479, false, false);
	
	//�����
	_burgerCat = new cat;
	_burgerCat->init(50, 270);

	//����
	_burger = new burger;
	_burger->init(560, 278);

	//������
	_icon = new icon;
	_icon->init();
	_icon->setBgName(_colorBgName);

	//��	
	_block = new block;
	_block->init(_colorBgName);

	//�޸� ��ũ
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

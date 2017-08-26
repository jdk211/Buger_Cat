#include "stdafx.h"
#include "burger.h"

burger::burger()
{
}


burger::~burger()
{
}

HRESULT burger::init(int x, int y)
{
	_burger.img = IMAGEMANAGER->addImage("burger", "image/burger.bmp", 24, 20, true, RGB(255, 0, 255));
	_burger.x = x;
	_burger.y = y;
	_burger.rc = RectMakeCenter(_burger.x, _burger.y, _burger.img->getWidth(), _burger.img->getHeight());
	_burger.isEat = false;

	return S_OK;
}

void burger::release()
{	
}

void burger::update()
{
}

void burger::render()
{
	if (!_burger.isEat)
	{
		_burger.img->render(getMemDC(), _burger.rc.left, _burger.rc.top);
	}
}

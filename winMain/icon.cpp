#include "stdafx.h"
#include "icon.h"
#include "cat.h"
#include "block.h"

icon::icon()
{
}

icon::~icon()
{
}

HRESULT icon::init()
{
	_board = IMAGEMANAGER->addImage("board", "image/board.bmp", 640, 63, false, false);

	_stick.img = IMAGEMANAGER->addFrameImage("stick", "image/stick2.bmp", 48, 96, 1, 2, false, false);
	_stick.button = new button;
	_stick.x = 32;
	_stick.y = 32;
	_stick.rc = RectMakeCenter(_stick.x , _stick.y, _stick.img->getFrameWidth(), _stick.img->getFrameHeight());
	_stick.button->init("stick", _stick.x, _stick.y, pointMake(0, 1), pointMake(0, 0));

	_pick.img = IMAGEMANAGER->addFrameImage("pick", "image/pickax.bmp", 48, 96, 1, 2, false, false);
	_pick.button = new button;
	_pick.x = 90;
	_pick.y = 32;
	_pick.rc = RectMakeCenter(_pick.x, _pick.y, _pick.img->getFrameWidth(), _pick.img->getFrameHeight());
	_pick.button->init("pick", _pick.x, _pick.y, pointMake(0, 1), pointMake(0, 0));
	
	_start.img = IMAGEMANAGER->addFrameImage("start", "image/start2.bmp", 33, 66, 1, 2, false, false);
	_start.button = new button;
	_start.x = 510;
	_start.y = 30;
	_start.rc = RectMakeCenter(_start.x, _start.y, _start.img->getFrameWidth(), _start.img->getFrameHeight());
	_start.button->init("start", _start.x, _start.y, pointMake(0, 1), pointMake(0, 0));

	_pause.img = IMAGEMANAGER->addFrameImage("pause", "image/pause2.bmp", 33, 66, 1, 2, false, false);
	_pause.button = new button;
	_pause.x = 554;
	_pause.y = 30;
	_pause.rc = RectMakeCenter(_pause.x, _pause.y, _pause.img->getFrameWidth(), _pause.img->getFrameHeight());
	_pause.button->init("pause", _pause.x, _pause.y, pointMake(0, 1), pointMake(0, 0));

	_return.img = IMAGEMANAGER->addFrameImage("return", "image/return.bmp", 33, 66, 1, 2, false, false);
	_return.button = new button;
	_return.x = 598;
	_return.y = 30;
	_return.rc = RectMakeCenter(_return.x, _return.y, _return.img->getFrameWidth(), _return.img->getFrameHeight());
	_return.button->init("return", _return.x, _return.y, pointMake(0, 1), pointMake(0, 0));

	return S_OK;
}

void icon::release()
{
	_stick.button->release();
	SAFE_DELETE(_stick.button);
	_pick.button->release();
	SAFE_DELETE(_pick.button);
	_start.button->release();
	SAFE_DELETE(_start.button);
	_pause.button->release();
	SAFE_DELETE(_pause.button);
	_return.button->release();
	SAFE_DELETE(_return.button);
}

void icon::update()
{
	_stick.button->update();
	_pick.button->update();
	_start.button->update();
	_pause.button->update();
	_return.button->update();

	start();
	stop();
	catReturn();
	userUpdate();
}

void icon::render()
{
	_board->render(getMemDC(), 0, 0);
	_stick.button->render();
	_pick.button->render();
	_start.button->render();
	_pause.button->render();
	_return.button->render();
}

void icon::start()
{
	if (PtInRect(&_start.rc, pointMake(_ptMouse.x, _ptMouse.y)))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_cat->setCatStart();
			_cat->setCatMove();
		}
	}
}

void icon::stop()
{
	if (PtInRect(&_pause.rc, pointMake(_ptMouse.x, _ptMouse.y)))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_cat->setCatPause();
			_cat->setCatStop();
		}
	}
}

void icon::catReturn()
{
	if (PtInRect(&_return.rc, pointMake(_ptMouse.x, _ptMouse.y)))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_cat->init(_cat->getStartX(), _cat->getStartY());
			_block->init(_colorBgName);
		}
	}
}

void icon::userUpdate()
{
	if (PtInRect(&_stick.rc, pointMake(_ptMouse.x, _ptMouse.y)))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_block->setUpBlockUser();
		}
	}

	if (PtInRect(&_pick.rc, pointMake(_ptMouse.x, _ptMouse.y)))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_block->setPickaxUser();
		}
	}
}

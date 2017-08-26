#include "stdafx.h"
#include "block.h"

block::block()
{
}

block::~block()
{
}

HRESULT block::init(const char * imageName)
{
	IMAGEMANAGER->addImage("block_collision", "image/block_collision.bmp", 32, 32, false, false);
	IMAGEMANAGER->addImage("block_up", "image/block_up.bmp", 32, 32, false, false);
	IMAGEMANAGER->addImage("block_iron", "image/block_iron.bmp", 32, 32, false, false);

	_bgImg = IMAGEMANAGER->findImage(imageName);

	_size = 32;

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			_block[i * 20 + j].rc = RectMake(j * _size, (i * _size), _size, _size);

			COLORREF color = GetPixel(_bgImg->getMemDC(), (j * _size), (i * _size));

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 255)
			{
				_block[i * 20 + j].blockImg = IMAGEMANAGER->findImage("block_collision");
				_block[i * 20 + j].state = COLLISION_BLOCK;
			}
			else if (r == 0 && g == 255 && b == 0)
			{
				_block[i * 20 + j].blockImg = IMAGEMANAGER->findImage("block_up");
				_block[i * 20 + j].state = UP_BLOCK;
			}
			else if (r == 100 && g == 100 && b == 100)
			{
				_block[i * 20 + j].blockImg = IMAGEMANAGER->findImage("block_iron");
				_block[i * 20 + j].state = IRON_BLOCK;
			}
			else
			{
				_block[i * 20 + j].state = IDLE_BLOCK;
			}
		}
	}

	_viewBlock = true;

	return S_OK;
}

void block::release()
{
}

void block::update()
{
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_viewBlock = !_viewBlock;
	}

	blockUpdate();
}

void block::render()
{
	for (int i = STARTBLOCK; i < BLOCKMAX; i++)
	{
		if (_block[i].state == COLLISION_BLOCK)
		{
			HBRUSH myBrush, oldBrush;
			myBrush = CreateSolidBrush(RGB(255, 0, 255));
			oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
			Rectangle(getMemDC(), _block[i].rc.left, _block[i].rc.top, _block[i].rc.right, _block[i].rc.bottom);
			DeleteObject(oldBrush);

			if (_viewBlock)
			{
				_block[i].blockImg->render(getMemDC(), _block[i].rc.left, _block[i].rc.top);
			}
		}
		else if (_block[i].state == UP_BLOCK)
		{
			HBRUSH myBrush, oldBrush;
			myBrush = CreateSolidBrush(RGB(0, 255, 0));
			oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
			Rectangle(getMemDC(), _block[i].rc.left, _block[i].rc.top, _block[i].rc.right, _block[i].rc.bottom);
			DeleteObject(oldBrush);

			if (_viewBlock)
			{
				_block[i].blockImg->render(getMemDC(), _block[i].rc.left, _block[i].rc.top);
			}
		}
		else if (_block[i].state == IRON_BLOCK)
		{
			HBRUSH myBrush, oldBrush;
			myBrush = CreateSolidBrush(RGB(100, 100, 100));
			oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
			Rectangle(getMemDC(), _block[i].rc.left, _block[i].rc.top, _block[i].rc.right, _block[i].rc.bottom);
			DeleteObject(oldBrush);

			if (_viewBlock)
			{
				_block[i].blockImg->render(getMemDC(), _block[i].rc.left, _block[i].rc.top);
			}
		}
		else
		{
			if (!_viewBlock)
			{
				HBRUSH myBrush, oldBrush;
				myBrush = CreateSolidBrush(RGB(255, 255, 255));
				oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
				Rectangle(getMemDC(), _block[i].rc.left, _block[i].rc.top, _block[i].rc.right, _block[i].rc.bottom);
				DeleteObject(oldBrush);
			}
		}
	}
}

void block::blockUpdate()
{
	for (int i = STARTBLOCK; i < BLOCKMAX; i++)
	{
		if (PtInRect(&_block[i].rc, pointMake(_ptMouse.x, _ptMouse.y)) && _block[i].state == IDLE_BLOCK)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _user == UPBLOCK_USER)
			{
				_block[i].state = UP_BLOCK;
				_block[i].blockImg = IMAGEMANAGER->findImage("block_up");
			}
			else if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				_block[i].state = COLLISION_BLOCK;
				_block[i].blockImg = IMAGEMANAGER->findImage("block_collision");
			}
		}
		else if (PtInRect(&_block[i].rc, pointMake(_ptMouse.x, _ptMouse.y)) && _user == PICKAX_USER && _block[i].state != IRON_BLOCK)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_block[i].state = IDLE_BLOCK;
			}
		}
	}
}

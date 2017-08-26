#include "stdafx.h"
#include "cat.h"
#include "block.h"
#include "burger.h"

cat::cat()
{
}


cat::~cat()
{
}

HRESULT cat::init(int x, int y)
{
	IMAGEMANAGER->addImage("cat_idle", "image/cat_idle.bmp", 32, 36, true, RGB(255, 0, 255));			//캣_대기상태
	IMAGEMANAGER->addFrameImage("cat_run", "image/cat_run.bmp", 216, 72, 6, 2, true, RGB(255, 0, 255)); //캣_움직일떄
	IMAGEMANAGER->addFrameImage("cat_air", "image/cat_air.bmp", 72, 72, 2, 2, true, RGB(255, 0, 255));	//캣_떨어질떄
	IMAGEMANAGER->addFrameImage("cat_up", "image/cat_up2.bmp", 600, 100, 9, 2, true, RGB(255, 0, 255));	//캣_올라갈떄
	IMAGEMANAGER->addFrameImage("cat_eat", "image/cat_eat.bmp", 108, 38, 3, 1, true, RGB(255, 0, 255));	//캣_먹을떄

	_moveVector = -1;
	_gravity = 1;
	
	_cat.img = IMAGEMANAGER->findImage("cat_idle");
	_cat.radius = 16;
	_cat.x = _cat.startX = x;
	_cat.y = _cat.startY = y;
	_cat.fCount = 0;
	_cat.countDivide = 7;
	_cat.isRight = true;
	_cat.spd = 1 * _moveVector;
	_cat.state = IDLE;

	_cat.rc = RectMakeCenter(_cat.x, _cat.y, _cat.img->getWidth(), _cat.img->getHeight());
	_cat.observer = RectMakeCenter(_cat.x + (_cat.img->getFrameWidth() / 2) - 10, _cat.y, 5, 5);
	_cat.upObserv = RectMakeCenter(_cat.x + (_cat.img->getFrameWidth() / 2) - 10, _cat.y - (_cat.img->getFrameHeight() / 2), 5, 5);
	_cat.downObserv = RectMakeCenter(_cat.x + (_cat.img->getFrameWidth() / 2), _cat.y + (_cat.img->getFrameHeight()), 5, 5);

	_catStart = false;
	_eatCount = 0;

	return S_OK;
}

void cat::release()
{
}

void cat::update()
{
	if (_catStart)
	{
		ai();
		frame();
		observerFunction();
	}
}

void cat::render()
{
	//Rectangle(getMemDC(), _cat.rc.left, _cat.rc.top, _cat.rc.right, _cat.rc.bottom);
	_cat.img->frameRender(getMemDC(), _cat.rc.left, _cat.rc.top, _cat.img->getFrameX(), _cat.img->getFrameY());
	//Rectangle(getMemDC(), _cat.observer.left, _cat.observer.top, _cat.observer.right, _cat.observer.bottom);
	//Rectangle(getMemDC(), _cat.downObserv.left, _cat.downObserv.top, _cat.downObserv.right, _cat.downObserv.bottom);
	//Rectangle(getMemDC(), _cat.upObserv.left, _cat.upObserv.top, _cat.upObserv.right, _cat.upObserv.bottom);
}

//==========================================================================================================================//

void cat::move()
{
	if (_cat.state == RUN)
	{
		_cat.x += _cat.spd * _moveVector;
	}
	else if (_cat.state == AIR)
	{
		_cat.y += _gravity;
	}
}

void cat::frame()
{
	//행동별 이미지
	if (_cat.state == IDLE)
	{
		_cat.img = IMAGEMANAGER->findImage("cat_idle");
	}
	else if (_cat.state == RUN)
	{
		_cat.img = IMAGEMANAGER->findImage("cat_run");
	}
	else if (_cat.state == UP)
	{
		_cat.img = IMAGEMANAGER->findImage("cat_up");
	}
	else if (_cat.state == AIR)
	{
		_cat.img = IMAGEMANAGER->findImage("cat_air");
	}
	else if (_cat.state == EAT)
	{
		_cat.img = IMAGEMANAGER->findImage("cat_eat");
	}

	if (_cat.isRight)
	{
		_cat.img->setFrameY(0);
	}
	else
	{
		_cat.img->setFrameY(1);
	}

	//렉트생성
	if (_cat.state == RUN)
	{
		_cat.rc = RectMakeCenter(_cat.x, _cat.y, _cat.img->getFrameWidth(), _cat.img->getFrameHeight());
	}
	else if (_cat.state == UP)
	{
		if (_cat.isRight)
		{
			_cat.rc = RectMakeCenter(_cat.x, _cat.y - 15, _cat.img->getFrameWidth(), _cat.img->getFrameHeight());
		}
		else
		{
			_cat.rc = RectMakeCenter(_cat.x, _cat.y - 15, _cat.img->getFrameWidth(), _cat.img->getFrameHeight());
		}
	}
	else
	{
		_cat.rc = RectMakeCenter(_cat.x, _cat.y, _cat.img->getFrameWidth(), _cat.img->getFrameHeight());
	}

	//프레임 카운터
	if (_cat.state != IDLE)
	{
		_cat.fCount++;

		if (_cat.fCount % _cat.countDivide == 0)
		{
			if(_cat.img->getFrameX() >= _cat.img->getMaxFrameX())
			{
				_cat.img->setFrameX(0);
				_cat.fCount = 0;
				
				if (_cat.state == UP)
				{
					if (_cat.isRight)
					{
						_cat.x += _cat.radius * 2;
					}
					else
					{
						_cat.x -= _cat.radius * 2;
					}
					_cat.y -= 22;
					_cat.state = RUN;
				}
				else if (_cat.state == EAT)
				{
					_eatCount++;
					if (_eatCount > 3)
					{
						_cat.state = END;
					}
				}
			}
			else
			{
				_cat.img->setFrameX(_cat.img->getFrameX() + 1);
				if (_cat.img->getFrameX() < 6)
				{
					if (_cat.state == UP)
					{
						_cat.y -= 2;
					}
				}
			}
		}
	}

	move();
}

void cat::ai()
{
	for (int i = 0; i < BLOCKMAX; i++)
	{
		//한칸 올라갈 수 있는 블럭
		if (PtInRect(&_block->getBlockRc(i), pointMake(_cat.upObserv.right, _cat.upObserv.top)) && _block->getBlockStat(i) != IDLE_BLOCK)
		{
			_cat.isRight = !_cat.isRight;
			_moveVector = _moveVector * -1;
			break;
		}
		else if (PtInRect(&_block->getBlockRc(i), pointMake(_cat.observer.right, _cat.observer.top)) && _block->getBlockStat(i) == UP_BLOCK)
		{
			_cat.state = UP;
		}
		//부딪히면 반대로 움직이는 블럭
		else if (PtInRect(&_block->getBlockRc(i), pointMake(_cat.observer.right, _cat.observer.top)) && _block->getBlockStat(i) == COLLISION_BLOCK)
		{
			_cat.state = RUN;
			_cat.isRight = !_cat.isRight;
			_moveVector = _moveVector * -1;
		}

		if (PtInRect(&_block->getBlockRc(i), pointMake(_cat.downObserv.right, _cat.observer.bottom)) && _block->getBlockStat(i) != IDLE_BLOCK)
		{
			_cat.y -= _cat.radius;
			_cat.state = RUN;
		}
		else if (_cat.state == RUN)
		{
			if (PtInRect(&_block->getBlockRc(i), 
				pointMake((_cat.downObserv.right + _cat.downObserv.left) / 2, (_cat.downObserv.bottom + _cat.downObserv.top) / 2))
				&& _block->getBlockStat(i) == IDLE_BLOCK)
			{
				_cat.state = AIR;
				_cat.x = (_block->getBlockRc(i).left + _block->getBlockRc(i).right) / 2;
			}
		}
	}
	
	if (PtInRect(&_burger->getRc(), pointMake(((_cat.rc.right + _cat.rc.left) / 2), ((_cat.rc.bottom + _cat.rc.top) / 2))))
	{
		_cat.state = EAT;
		_burger->setEat();
	}
}

void cat::observerFunction()
{
	if (_moveVector == -1)
	{
		_cat.observer = RectMakeCenter(_cat.x + (_cat.img->getFrameWidth() / 2) - 10, _cat.y, 5, 5);
		_cat.upObserv = RectMakeCenter(_cat.x + (_cat.img->getFrameWidth() / 2) - 10, _cat.y - (_cat.img->getFrameHeight() / 2), 5, 5);
		_cat.downObserv = RectMakeCenter(_cat.x, _cat.y + (_cat.img->getFrameHeight() / 2), 5, 5);
	}
	else
	{
		_cat.observer = RectMakeCenter(_cat.x - (_cat.img->getFrameWidth() / 2) + 10, _cat.y, 5, 5);
		_cat.upObserv = RectMakeCenter(_cat.x - (_cat.img->getFrameWidth() / 2) + 10, _cat.y - (_cat.img->getFrameHeight() / 2), 5, 5);
		_cat.downObserv = RectMakeCenter(_cat.x, _cat.y + (_cat.img->getFrameHeight() / 2), 5, 5);
	}
}


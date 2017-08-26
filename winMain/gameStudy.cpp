#include "stdafx.h"
#include "gameStudy.h"


gameStudy::gameStudy()
{
}


gameStudy::~gameStudy()
{
}

HRESULT gameStudy::init()
{
	gameNode::init(true);
	
	IMAGEMANAGER->addImage("background","image/background.bmp", 640, 479, false, false);

	SCENEMANAGER->addScene("stage1", new stage1);
	SCENEMANAGER->addScene("stage2", new stage2);
	SCENEMANAGER->addScene("stage3", new stage3);

	SCENEMANAGER->changeScene("stage1");

	return S_OK;
}

void gameStudy::release()
{
	
	gameNode::release();
}

void gameStudy::update()
{
	SCENEMANAGER->update();

	gameNode::update();
}

void gameStudy::render( )
{
	//백버퍼에서 뿌려줌
	/*HDC backDC = this->getBackBuffer()->getMemDC();*/
	PatBlt( getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS );
	//============================================================
	
	IMAGEMANAGER->findImage("background")->render(getMemDC());

	SCENEMANAGER->render();

	//============================================================
	//백버퍼에 있는 그림을 HDC에 그리자
	this->getBackBuffer()->render( getHDC(), 0, 0 );
}


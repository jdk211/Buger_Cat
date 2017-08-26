#pragma once

#include "gameNode.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"

class gameStudy : public gameNode
{
private:

public:
	gameStudy();
	virtual ~gameStudy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};


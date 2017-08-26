#pragma once

#include "gameNode.h"

class pixelCollisionTest : public gameNode
{
	image* _mountain;
	image* _ball;

	RECT _rc;

	float _x, _y;

	int _probeY;

	bool _collision;

public:
	pixelCollisionTest();
	~pixelCollisionTest();

	HRESULT init();
	void release();
	void update();
	void render();
};


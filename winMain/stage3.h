#pragma once
#include "stage1.h"

class stage3 : public stage1
{
public:
	stage3();
	~stage3();

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	virtual char* getBgName() { return _colorBgName; }
};


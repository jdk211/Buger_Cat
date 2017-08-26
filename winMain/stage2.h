#pragma once
#include "stage1.h"

class stage2 : public stage1
{
public:
	stage2();
	~stage2();

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	virtual char* getBgName() { return _colorBgName; }
};


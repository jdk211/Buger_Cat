#pragma once
#include "gameNode.h"

#define BLOCKMAX 300
#define STARTBLOCK 40

enum eUSERSTATE
{
	IDLE_USER,
	UPBLOCK_USER,
	PICKAX_USER
};

enum eRCSTATE
{
	IDLE_BLOCK,
	COLLISION_BLOCK,
	UP_BLOCK,
	IRON_BLOCK
};

struct stRECT
{
	image* blockImg;
	RECT rc;
	eRCSTATE state;
};

class block : public gameNode
{
private:
	image* _bgImg;

	stRECT _block[BLOCKMAX];
	eUSERSTATE _user;

	int _size;

	bool _viewBlock;

	char* _colorBgName;

public:
	block();
	~block();

	HRESULT init(const char* imageName);
	void release();
	void update();
	void render();
	
	void blockUpdate();
	void setUpBlockUser() { _user = UPBLOCK_USER; }
	void setPickaxUser() { _user = PICKAX_USER; }

	stRECT getBlock(int arrNum) { return _block[arrNum]; }
	RECT getBlockRc(int arrNum) { return _block[arrNum].rc; }
	eRCSTATE getBlockStat(int arrNum) { return _block[arrNum].state; }
	int getBlockSize() { return 300; }

};

#pragma once

#include "singletonBase.h"

#include <vector>
#include <map>

//struct elements //아래와 같다
//{
//	const char* name;
//	float increaseSpeed;
//	float maxSpeed;
//	float angle;
//	int currentHP;
//	int maxHP;
//};

class elements
{
public:
	const char* name;
	float increaseSpeed;
	float maxSpeed;
	float angle;
	int currentHP;
	int maxHP;

	elements() {}
	~elements() {}
};

class database : public singletonBase<database>
{
private:
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;
	typedef map<string, elements*> arrElement;
	typedef map<string, elements*>::iterator iterElement;

private:
	arrElement _mTotalElement;

public:
	database();
	~database();

	HRESULT init();
	void release();

	void loadDatabase( string name );

	elements* getElementData( string str ) { return _mTotalElement.find( str )->second; } 

	void setElementDataIncreaseSpeed( string str, float is );
	void setElementDataMaxSpeed( string str, float ms );
	void setElementDataAngle( string str, float a );
	void setElementDataCurrentHP( string str, int ch );
	void setElementDataMaxHP( string str, int mh );
};


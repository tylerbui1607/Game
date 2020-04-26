#pragma once
#include "GameObject.h"
class Torch :
	public CGameObject
{
	//int Health;

	//virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();


public:
	Torch();
	~Torch() {};
	
	virtual void SetState(int state);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom)
	{
		DebugOut(L"GetBbox torch\n");
		left = x;
		right = 32 + x;
		top = y;
		bottom = y + 64;
	};
};


#pragma once
#include "GameObject.h"
#include"Textures.h"
#include"Sprites.h"
#define ID_TEX_WEAPON 50
#define ID_TEX_WEAPONii 60
class Weapon :
	public CGameObject
{
public:
	bool EndAni;
	int level;
	int ani;
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animation = CAnimations::GetInstance();
	DWORD startATK;
	DWORD ATKTime = 300;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		
		if (nx == -1)
		{
			left = x+50;
			top = y+15;
			right = left + 100;
			bottom = top + 20;
			DebugOut(L"Get BBox weapon right\n");
		}
		else
		{
			left = x + 30;
			top = y + 15;
			right = left + 50;
			bottom = top + 20;
			DebugOut(L"Get BBox weapon left\n");
		}
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void UpdateAnimation();
	void Attack();
public:
	Weapon();
	void SetPosition(int a, int b, int c);
	void AdaptPosition();
	virtual void SetState(int state);
	~Weapon();
};


#pragma once
#include "GameObject.h"
#include"Textures.h"
#include"Sprites.h"
#define ID_TEX_WEAPON 50
#define ID_TEX_WEAPONii 60
class Weapon :
	public CGameObject
{
	bool EndAni;
	int level;
	int ani;
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animation = CAnimations::GetInstance();
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		DebugOut(L"Get BBox weapon\n");
		if (nx == -1)
		{
			left = x+50;
			top = y+15;
			right = left + 100;
			bottom = top + 20;
		}
		else
		{
			left = x + 30;
			top = y + 15;
			right = left + 50;
			bottom = top + 20;
		}
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void UpdateAnimation();

public:
	Weapon();
	void SetPosition(int a, int b, int c);
	void AdaptPosition();
	virtual void SetState(int state);
	~Weapon();
};


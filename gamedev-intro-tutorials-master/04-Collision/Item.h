#pragma once
#include "GameObject.h"
#define ItemGravity  0.001f
class Item :
	public CGameObject
{
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animation = CAnimations::GetInstance();
	int ani = 0;

public:
	Item(int ObjX, int ObjY,int Type);
	//map<int, vector<int>>animation;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
	void Render();
	void UpdateAni();
	~Item();
};


#pragma once
#include "Weapon.h"
#include"GameObject.h"
#define Knife_Speed  0.2f
class Knife  :
	public CGameObject
{

	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animation = CAnimations::GetInstance();
public:
	int ani;
	bool IsActivated, IsAttacking;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void UpdateAni();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	Knife(int SimonX,int SimonY);
	void SetPosition(int a, int b, int c);
	void AdaptPosition();
	void ACTIVATE(int weapontype, bool Atk);
	virtual void SetState(int state);
	~Knife();
};



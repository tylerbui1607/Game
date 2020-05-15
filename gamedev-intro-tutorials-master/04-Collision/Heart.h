#pragma once
#include"Game.h"
#include"Sprites.h"
#include"GameObject.h"
class Heart:
	public CGameObject
{
	
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animation = CAnimations::GetInstance();
public:
	Heart(int a, int b);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
	void Render();
	void UpdateAni();
};


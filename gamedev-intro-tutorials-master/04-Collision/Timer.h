#pragma once
#include "GameObject.h"
#include"Sprites.h"
#include"Textures.h"
class Timer 
{
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprite = CSprites::GetInstance();
	CAnimations* animation = CAnimations::GetInstance();
	vector<LPSPRITE>sprites;
	int TimeLimit =300;
	DWORD Count = 0;
	//map<int, vector<int>>animation;tual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void LoadSprites();
	void SetState(int state);
	void SimonAttack();
	void Render();
	void UpdateAni();
	
};


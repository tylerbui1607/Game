#pragma once
#include "Textures.h"
#include "GameObject.h"
#include"Weapon.h"
#include<unordered_map>
#include<map>
#define Simon_Speed  0.2f
#define Simon_Gravity  0.005f
#define Simon_Jump_Speed  0.32f
//State
#define Simon_Turn_Left 1
#define Simon_Stand   0
#define Simon_Turn_right -1
#define Simon_Dead 4
#define Simon_ATK 2
#define Simon_Jump 3
//Animation
#define Simon_Stand_Right 0
#define Simon_Stand_Left 2
#define Simon_STATE_WALKING_RIGHT	1
#define Simon_STATE_WALKING_LEFT	3
#define Simon_Attack_Right	4
#define Simon_Attack_Left	5
#define Simon_Jumping_Right 6
#define Simon_Jumping_Left 7

#define ID_TEX_SIMON 30
#define ID_TEX_SIMONii 40
class Simon :
	public CGameObject
{
public:
	Weapon *weapon = new Weapon() ;
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animation = CAnimations::GetInstance();
	bool IsAttacking, IsWalking,IsJumping;
	int ani = 0;
	int atk;
	DWORD totaltime;
	DWORD startATK;
	DWORD ATKTime = 330 ;
	//map<int, vector<int>>animation;
	Simon() 
	{
		nx = -1;
		UpdateAni();
		IsAttacking = false;
		IsWalking = false;
		 y = 255;
		 x = 0;
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
	void SimonAttack();
	void Render();
	void UpdateAni();
	~Simon();
};


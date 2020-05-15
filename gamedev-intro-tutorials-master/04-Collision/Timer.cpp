#include "Timer.h"

Timer::Timer()
{
	x = 335;
	y = 30;
	UpdateAni();
}

void Timer::LoadSprites()
{


}

void Timer::SetState(int state)
{
}

void Timer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (Count >= 1000)
	{
		TimeLimit--;
		Count = 0;
	}
	else
	{
		Count += dt;
	}
}

void Timer::Render(int ID, float X , float Y)
{
	animations[ID]->RenderEX(X, Y);
	
}

void Timer::Render()
{
}

void Timer::UpdateAni()
{
	textures->Add(10, L"textures\\font.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 textfont = textures->Get(10);
	sprite->Add(0, 0, 28, 15, 42, textfont);
	sprite->Add(1, 15, 28, 30, 42, textfont);
	sprite->Add(2, 30, 28, 45, 42, textfont);
	sprite->Add(3, 45, 28, 60, 42, textfont);
	sprite->Add(4, 60, 28, 75, 42, textfont);
	sprite->Add(5, 75, 28, 90, 42, textfont);
	sprite->Add(6, 90, 28, 105, 42, textfont);
	sprite->Add(7, 105, 28, 120, 42, textfont);
	sprite->Add(8, 120, 28, 135, 42, textfont);
	sprite->Add(9, 135, 28, 150, 42, textfont);
	LPANIMATION ani;
	ani = new CAnimation(100);
	ani->Add(0);
	animation->Add(0, ani);

	ani = new CAnimation(100);
	ani->Add(1);
	animation->Add(1, ani);

	ani = new CAnimation(100);
	ani->Add(2);
	animation->Add(2, ani);
	ani = new CAnimation(100);
	ani->Add(3);
	animation->Add(3, ani);
	ani = new CAnimation(100);
	ani->Add(4);
	animation->Add(4, ani);
	ani = new CAnimation(100);
	ani->Add(5);
	animation->Add(5, ani);
	ani = new CAnimation(100);
	ani->Add(6);
	animation->Add(6, ani);
	ani = new CAnimation(100);
	ani->Add(7);
	animation->Add(7, ani);
	ani = new CAnimation(100);
	ani->Add(8);
	animation->Add(8, ani);
	ani = new CAnimation(100);
	ani->Add(9);
	animation->Add(9, ani);
	
	AddAnimation(0);
	AddAnimation(1);
	AddAnimation(2);
	AddAnimation(3);
	AddAnimation(4);
	AddAnimation(5);
	AddAnimation(6); 
	AddAnimation(7);
	AddAnimation(8);
	AddAnimation(9);
}

void Timer::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

Timer::~Timer()
{
}

#include "Timer.h"

Timer::Timer()
{
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

void Timer::Render()
{
	DebugOut(L"x%f,y%f\n", x, y);
	/*int temp = TimeLimit;
	for (int i = 0; i < 3; i++)
	{
		
		temp = temp / 10;
	}*/
	/*animations[2]->Render(x, y);*/
}

void Timer::UpdateAni()
{
	textures->Add(10, L"textures\\font.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 textfont = textures->Get(10);
	sprite->Add(0, 0, 28, 42, 15, textfont);
	sprite->Add(1, 15, 28, 42, 30, textfont);
	sprite->Add(2, 30, 28, 42, 45, textfont);
	sprite->Add(3, 45, 28, 42, 60, textfont);
	sprite->Add(4, 60, 28, 42, 75, textfont);
	sprite->Add(5, 75, 28, 42, 90, textfont);
	sprite->Add(6, 90, 28, 42, 105, textfont);
	sprite->Add(7, 105, 28, 42, 120, textfont);
	sprite->Add(8, 120, 28, 42, 135, textfont);
	sprite->Add(9, 135, 28, 42, 150, textfont);
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

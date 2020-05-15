#include "Knife.h"

void Knife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (IsActivated)
	{
		if (nx == -1)
			vx = Knife_Speed;
		else
			vx = -Knife_Speed;
		x += dx;

		for (int i = 0; i < coObjects->size(); i++)
		{
			if (IsCollision(coObjects->at(i)))
			{
				coObjects->at(i)->SubHealth();
				this->SubHealth();
				IsActivated = false;
				IsAttacking == false;
			}

		}
		/*DebugOut(L"UpdateWeapon2\n");*/
	}
}

void Knife::Render()
{
	
}

void Knife::UpdateAni()
{
	textures->Add(10, L"textures\\Item.png", D3DCOLOR_XRGB(116, 116, 116));
	textures->Add(20, L"textures\\Item2.png", D3DCOLOR_XRGB(116, 116, 116));
	LPDIRECT3DTEXTURE9 textitem = textures->Get(10);
	LPDIRECT3DTEXTURE9 textitem2 = textures->Get(20);
	sprites->Add(0, 0, 34, 32, 66, textitem);
	sprites->Add(1, 468, 34, 499, 66, textitem2);
	LPANIMATION ani;
	ani = new CAnimation(100);
	ani->Add(0);
	animation->Add(0, ani);
	ani = new CAnimation(100);
	ani->Add(1);
	animation->Add(1, ani);
	AddAnimation(0);
	AddAnimation(1);
}

void Knife::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y ;
	right = left + 33;
	bottom = top + 34;
}

Knife::Knife(int SimonX, int SimonY)
{
	UpdateAni();
	IsActivated = false;
	x = SimonX;
	y = SimonY;
}

void Knife::SetPosition(int a, int b, int c)
{
	if (c == -1)
		ani = 1;
	else
		ani = 0;
	x = a;
	y = b;
	nx = c;
}

void Knife::AdaptPosition()
{
	if (nx == -1)
	{
		this->x = x + 55;
		this->y += 3;
	}
	else
	{
		this->x = x ;
		this->y += 2;
	}
}

void Knife::ACTIVATE(int weapontype,bool Atk)
{
	if (weapontype == 1 && Atk == true && !IsAttacking)
	{
		IsActivated = true;
		IsAttacking = true;
	}
	
}



void Knife::SetState(int state)
{


}

Knife::~Knife()
{
}

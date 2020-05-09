#include "Weapon.h"

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"toa do:%d/n", coObjects->size());
	DebugOut(L"UpdateWeapon\n");
	DebugOut(L"Ani Frame %d%d\n", ani, animations[ani]->currentFrame);
	if (this->animations[ani]->currentFrame == 2)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (IsCollision(coObjects->at(i)))
				coObjects->at(i)->SubHealth();
		}
		DebugOut(L"UpdateWeapon2\n");
	}
}



void Weapon::Render()
{
	
}

void Weapon::UpdateAnimation()
{
	textures->Add(ID_TEX_WEAPON, L"textures\\weapon.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_WEAPONii, L"textures\\weapon2.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 textweapon = textures->Get(ID_TEX_WEAPON);
	LPDIRECT3DTEXTURE9 textweapon2 = textures->Get(ID_TEX_WEAPONii);
	sprites->Add(203, 0, 0, 160, 68, textweapon);
	sprites->Add(202, 161, 0, 321, 68, textweapon);
	sprites->Add(201, 322, 0, 482, 68, textweapon);
	sprites->Add(200, 483, 0, 640, 68, textweapon);

	sprites->Add(204, 0, 0, 160, 68, textweapon2);
	sprites->Add(205, 161, 0, 321, 68, textweapon2);
	sprites->Add(206, 322, 0, 482, 68, textweapon2);
	sprites->Add(207, 483, 0, 640, 68, textweapon2);

	LPANIMATION ani;
	ani = new CAnimation(100);
	ani->Add(200);
	ani->Add(201);
	ani->Add(202);
	ani->Add(203);
	animation->Add(699, ani);
	AddAnimation(699);

	ani = new CAnimation(100);
	ani->Add(204);
	ani->Add(205);
	ani->Add(206);
	ani->Add(207);
	animation->Add(700, ani);
	AddAnimation(700);
}

void Weapon::Attack()
{
	EndAni = false;
	startATK = GetTickCount64();
}

Weapon::Weapon()
{
	UpdateAnimation();
}

void Weapon::SetPosition(int a, int b, int c)
{
	if (c == -1)
		ani = 1;
	else
		ani = 0;
	x = a;
	y = b;
	nx = c;

}

void Weapon::AdaptPosition()
{
	
		if (nx == 1)
		{
			this->x = x - 78;
			this->y -= 1;
		}
		else
		{
			this->x = x - 25;
			this->y -= 2;
		}
	
	
}

void Weapon::SetState(int state)
{

}

Weapon::~Weapon()
{
}

#include "Weapon.h"

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"toa do:%d/n", coObjects->size());
	/*DebugOut(L"UpdateWeapon\n");
	DebugOut(L"Ani Frame %d%d\n", ani, animations[ani]->currentFrame);*/
	if (this->animations[ani]->currentFrame == 2)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (IsCollision(coObjects->at(i)))
				coObjects->at(i)->SubHealth();
		}
		/*DebugOut(L"UpdateWeapon2\n");*/
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

	sprites->Add(211, 0, 67, 160, 134, textweapon);
	sprites->Add(210, 161, 67, 321, 134, textweapon);
	sprites->Add(209, 322, 67, 482, 134, textweapon);
	sprites->Add(208, 483, 67, 640, 134, textweapon);

	sprites->Add(212, 0, 67, 160, 134, textweapon2);
	sprites->Add(213, 161, 67, 321, 134, textweapon2);
	sprites->Add(214, 322, 67, 482, 134, textweapon2);
	sprites->Add(215, 483, 67, 640, 134, textweapon2);

	sprites->Add(219, 0, 134, 160, 203, textweapon);
	sprites->Add(218, 161, 134, 321, 203, textweapon);
	sprites->Add(217, 322, 134, 482, 203, textweapon);
	sprites->Add(216, 483, 134, 640, 203, textweapon);

	sprites->Add(220, 0, 134, 160, 203, textweapon2);
	sprites->Add(221, 161, 134, 321, 203, textweapon2);
	sprites->Add(222, 322, 134, 482, 203, textweapon2);
	sprites->Add(223, 483, 134, 640, 203, textweapon2);
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

	ani = new CAnimation(100);
	ani->Add(208);
	ani->Add(209);
	ani->Add(210);
	ani->Add(211);
	animation->Add(701, ani);
	AddAnimation(701);

	ani = new CAnimation(100);
	ani->Add(212);
	ani->Add(213);
	ani->Add(214);
	ani->Add(215);
	animation->Add(702, ani);
	AddAnimation(702);

	ani = new CAnimation(100);
	ani->Add(216);
	ani->Add(217);
	ani->Add(218);
	ani->Add(219);
	animation->Add(703, ani);
	AddAnimation(703);

	ani = new CAnimation(100);
	ani->Add(220);
	ani->Add(221);
	ani->Add(222);
	ani->Add(223);
	animation->Add(704, ani);
	AddAnimation(704);
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

//void Weapon::ACTIVATE(int weapontype, int Atk)
//{
//}

void Weapon::SetState(int state)
{

}

Weapon::~Weapon()
{
}

#include "Effect.h"

void Effect::IsDeadObj(int Health)
{
	
}

void Effect::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void Effect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (animations[0]->currentFrame == 3)
	{
		Health = 0;
	}
	
}

void Effect::Render()
{
	DebugOut(L"Hi\n");
	/*if (animations[0]->EndAni == false)
	{
		DebugOut(L"Hello\n");
		animations[0]->RenderEX(x, y);
	}*/
	animations[0]->Render(x, y);
}

void Effect::SetState(int state)
{
	
}

void Effect::UpdateAnimation()
{
	textures->Add(ID_TEX_EFFECT, L"textures\\effect.png", D3DCOLOR_XRGB(255, 0, 255));
	
	LPDIRECT3DTEXTURE9 texteffect = textures->Get(ID_TEX_EFFECT);
	sprites->Add(100,0, 0, 40, 44, texteffect);
	sprites->Add(101, 40, 0, 80, 44, texteffect);
	sprites->Add(102, 80, 0, 120, 44, texteffect);
	LPANIMATION ani;
	ani = new CAnimation(100);
	ani->Add(100);
	ani->Add(101);
	ani->Add(102);
	ani->Add(100);
	animation->Add(1, ani);

	AddAnimation(1);
	

}

Effect::Effect(int objx, int objy,int type)
{
	UpdateAnimation();
	animations[0]->EndAni = false;
	this->x = objx;
	this->y = objy;
	ItemType = type;
}

Effect::~Effect()
{
}

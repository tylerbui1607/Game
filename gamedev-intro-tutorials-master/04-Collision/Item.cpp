#include "Item.h"
#include "Ground.h"

Item::Item(int ObjX, int ObjY,int Type)
{
	UpdateAni();
	x = ObjX;
	y = ObjY;
	ItemType = Type;
}

void Item::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	
		left = x;
		right = 20 + x;
		top = y;
		bottom = y + 17;
	
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt);
	

	vy += ItemGravity * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Ground*>(e->obj)) // if e->obj is Ground
			{
				// block 
				// nx*0.4f : need to push out a bit to avoid overlapping next frame
				y += min_ty * dy + ny * 0.4f;
				if (ny != 0) vy = 0;
			}
			
			
		}
	}
}

void Item::SetState(int state)
{
}

void Item::Render()
{
		animations[ItemType]->Render(x, y);	
}

void Item::UpdateAni()
{
	textures->Add(10, L"textures\\Item.png", D3DCOLOR_XRGB(116, 116, 116));
	LPDIRECT3DTEXTURE9 textitem= textures->Get(10);
	sprites->Add(0, 56, 9, 80, 28, textitem);
	sprites->Add(1, 0, 34, 32, 66, textitem);
	sprites->Add(2, 0, 0, 32, 32, textitem);
	LPANIMATION ani;
	ani = new CAnimation(100);
	ani->Add(0);
	animation->Add(0, ani);

	ani = new CAnimation(100);
	ani->Add(1);
	animation->Add(1,ani);

	ani = new CAnimation(100);
	ani->Add(2);
	animation->Add(2, ani);

	AddAnimation(0);
	AddAnimation(1);
	AddAnimation(2);
}

Item::~Item()
{
}

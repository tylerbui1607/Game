#include "Simon.h"

void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	weapon->nx = nx;
	
	// Calculate dx, dy 
	if (vx > 0 && x >1476) x = 1476;
	if (vx < 0 && x < 0) x = 0;
	if (IsWalking == false && IsAttacking == false)
	{
		//DebugOut(L"Stand\n");
		if (nx == Simon_Turn_right)
			ani = 0;
		else
			ani = 2;
	}
	if (IsWalking == true )
	{	
		x += dx;
		y += dy;		
		if (nx == Simon_Turn_right)
			ani = 1;
		else
			ani = 3;
	}
	 if(IsAttacking==true)
	{	 
		 weapon->Update(dt, coObjects);
		
		if (nx == Simon_Turn_Left)
		{
			if (ani != Simon_Attack_Left)
			{
				ani = Simon_Attack_Left;
				animations[ani]->currentFrame = 0;
				animations[ani]->SetState(1);
			}
			this->SimonAttack();
			weapon->animations[1]->SetCurrentFrame(animations[ani]->currentFrame);
			
			
		}
		else if(nx==Simon_Turn_right)
		{
			if (ani != Simon_Attack_Right)
			{
				ani = Simon_Attack_Right;
				animations[ani]->currentFrame = 0;
				animations[ani]->SetState(1);
			}
			this->SimonAttack();
			weapon->animations[0]->SetCurrentFrame(animations[ani]->currentFrame);
			
		}
		if (GetTickCount64()-startATK>=ATKTime)
		{
			
			IsAttacking = false;	
			weapon->EndAni = true;
			ani = 0;
			//animations[ani]->currentFrame = 0;
		}
	}
}

void Simon::SetState(int state)
{
	switch (state)
	{
	case Simon_Stand:
			vx = 0;
			IsWalking = false;
			break;
	case Simon_Turn_right:
		    IsWalking = true;
			vx = Simon_Speed;
			nx = -1;
			break;
	case Simon_Turn_Left:
		    IsWalking = true;
			vx = -Simon_Speed;	
			nx = 1;
			break;
	case Simon_ATK:
		    vx = 0;
			IsWalking = false;
			IsAttacking = true;
			startATK = GetTickCount64();
			weapon->Attack();
			break;
	}

}

void Simon::SimonAttack()
{
	weapon->SetPosition(this->x, this->y,this->nx);
	weapon->AdaptPosition();
	
}

void Simon::Render()
{
	
	if (IsAttacking == false && IsWalking == false)
	{
		animations[ani]->Render(x, y);
	}
	if (IsAttacking == true)
	{
		
		if (nx == Simon_Turn_Left)
		{
			
			weapon->animations[1]->Render(weapon->x, weapon->y);
		}
		else
		{
			DebugOut(L"Weapon%d\n",weapon->animations[0]->currentFrame);
			weapon->animations[0]->Render(weapon->x, weapon->y);

		}
		animations[ani]->Render(x, y);
	}

	else
		animations[ani]->Render(x, y);
	
	}
	


void Simon::UpdateAni()
{

	textures->Add(ID_TEX_SIMON, L"textures\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_SIMONii, L"textures\\simon2.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 textsimon = textures->Get(ID_TEX_SIMON);
	LPDIRECT3DTEXTURE9 textsimon2 = textures->Get(ID_TEX_SIMONii);
	sprites->Add(4001, 0, 0, 60, 65, textsimon);
	sprites->Add(4002, 61, 0, 121, 65, textsimon);
	sprites->Add(4003, 182, 0, 242, 65, textsimon);

	sprites->Add(4004, 420, 0, 480, 65, textsimon2);
	sprites->Add(4005, 359, 0, 419, 65, textsimon2);
	sprites->Add(4006, 298, 0, 359, 65, textsimon2);

	sprites->Add(4007, 108, 0, 162, 65, textsimon2);
	sprites->Add(4008, 62, 0, 106, 65, textsimon2);
	sprites->Add(4009, 0, 0, 61, 65, textsimon2);

	sprites->Add(40012, 418, 0, 480, 65, textsimon);
	sprites->Add(40011, 363, 0, 417, 65, textsimon);
	sprites->Add(40010, 303, 0, 363, 65, textsimon);

	LPANIMATION ani;
	ani = new CAnimation(100);
	ani->Add(4004);
	animation->Add(100, ani);

	ani = new CAnimation(100);	// walk right
	ani->Add(4004);
	ani->Add(4005);
	ani->Add(4006);
	animation->Add(101, ani);

	ani = new CAnimation(100);
	ani->Add(4001);
	animation->Add(102, ani);

	ani = new CAnimation(100);	// walk left
	ani->Add(4001);
	ani->Add(4002);
	ani->Add(4003);
	animation->Add(103, ani);

	ani = new CAnimation(100);
	ani->Add(4007);
	ani->Add(4008);
	ani->Add(4009);
	animation->Add(104, ani);

	ani = new CAnimation(100);
	ani->Add(40010);
	ani->Add(40011);
	ani->Add(40012);
	animation->Add(105, ani);

	AddAnimation(100);
	AddAnimation(101);
	AddAnimation(102);
	AddAnimation(103);
	AddAnimation(104);
	AddAnimation(105);
	SetPosition(0, 150);

}

Simon::~Simon()
{
}

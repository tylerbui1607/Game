#include "Simon.h"
#include"Ground.h"
#include "Item.h"
void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!IsSitting)
	{
		left = x;
		top = y;
		right = left + 60;
		bottom = top + 65;
	}
	else
	{
		left = x;
		top = y+20;
		right = left + 60;
		bottom = y+65;
	}
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!IsLevelUp)
	{
		CGameObject::Update(dt);
		weapons[0]->nx = nx;

		vy += Simon_Gravity * dt;
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		CalcPotentialCollisions(coObjects, coEvents);
		if (coEvents.size() == 0)
		{
			x += dx;
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
					IsJumping = false;
					// block 
					x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
					y += min_ty * dy + ny * 0.4f;
					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;
				}
				else
				{
					x += dx;
				}
				if (dynamic_cast<Item*>(e->obj))
				{

					if (e->obj->getHealth() != 0)
					{
						switch (e->obj->ItemType)
						{
						case 0:
							this->Health++;
							break;
						case 1:
							this->WeaponType = 1;
							break;
						case 2:
							IsLevelUp = true;
							LevelUptime = GetTickCount64();
							WPT++;
							break;
						}
						e->obj->SubHealth();
					}
				}
			}
		}
		// Calculate dx, dy 
		if (vx > 0 && x > 1476) x = 1476;
		if (vx < 0 && x < 0) x = 0;
		if (IsAttacking == true)
		{
			if (IsWaiting)
			{
				if (!knife->IsActivated)
				{
					knife->SetPosition(x, y, nx);
					knife->Health++;
				}
			}
			if (!knife->IsActivated)
				knife->ACTIVATE(WeaponType, IsWaiting);
			weapons[0]->animations[weapons[0]->ani]->SetCurrentFrame(animations[ani]->currentFrame);
			weapons[0]->Update(dt, coObjects);
		}
		knife->Update(dt, coObjects);
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void Simon::SetState(int state)
{
	switch (state)
	{
	case Simon_Stand:
		if (IsSitting)
		{
			
			IsSitting = false;
		}
			vx = 0;
			
			IsWalking = false; 	
			break;
	case Simon_ATK:
			vx = 0;
			IsWalking = false;
			IsAttacking = true;
			startATK = GetTickCount64();
			weapons[0]->Attack();
			break;
	case Simon_Turn_right:
		if(!IsAttacking&&!IsAttacking&&!IsSitting)
		{
			IsWalking = true;
			vx = Simon_Speed;
			nx = -1;
		}
			break;
	case Simon_Turn_Left:
		if (!IsAttacking && !IsAttacking && !IsSitting)
		{
			IsWalking = true;
			vx = -Simon_Speed;	
			nx = 1;
		}
			break;

	case Simon_Jump:
		if(!IsJumping)
		{
			vy = -Simon_Jump_Speed;
			IsJumping = true;
		}
			break;
	case Simon_Sit:
		if (IsSitting)
			return;
		
		vx = 0;
		IsWalking = false;
		IsSitting = true;					
		break;
	}

}

void Simon::SimonAttack()
{
	if (IsSitting)
	{
		weapons[0]->SetPosition(this->x, this->y+20, this->nx);
	}
	else
	{
		weapons[0]->SetPosition(this->x, this->y, this->nx);
	}
	weapons[0]->AdaptPosition();	
}

void Simon::Render()
{

	if (IsWalking == false && IsAttacking == false)
	{
		if (nx == Simon_Turn_right)
			ani = 0;
		else
			ani = 2;
	}
	if (IsWalking == true)
	{
		//x += dx;
		//y += dy;
		if (IsJumping == true)
		{
			ani = 6;
		}
		else
		{
			if (nx == Simon_Turn_right)
				ani = 1;
			else
				ani = 3;
		}
	}
	if (IsJumping == true)
	{
		if (nx == -1)
			ani = 6;
		else
		{
			ani = 7;
		}
	}
	if (IsSitting&&!IsAttacking)
	{
		if (nx == -1)
			ani = 6;
		else
		{
			ani = 7;
		}
	}
	if (IsAttacking == true)
	{
		
			if (nx == Simon_Turn_Left)
			{
				if (IsSitting)
				{
					if (ani != Simon_Sitting_Attack_Left)
					{
						ani = Simon_Sitting_Attack_Left;
						animations[ani]->currentFrame = 0;
						animations[ani]->lastFrameTime = GetTickCount64();
						this->SimonAttack();
						if (WPT == 1)
							weapons[0]->ani = 3;
						else if (WPT == 2)
						{
							weapons[0]->ani = 5;
						}
						else
							weapons[0]->ani = 1;
					}
				}
				else
				{
					if (ani != Simon_Attack_Left)
					{
						ani = Simon_Attack_Left;
						animations[ani]->currentFrame = 0;
						animations[ani]->lastFrameTime = GetTickCount64();
						this->SimonAttack();
						if (WPT == 1)
							weapons[0]->ani = 3;
						else if (WPT == 2)
						{
							weapons[0]->ani = 5;
						}
						else
							weapons[0]->ani = 1;
					}
				}
				

			}
			else if (nx == Simon_Turn_right)
			{
				
				if (IsSitting)
				{
					if (ani != Simon_Sitting_Attack_Right)
					{
						ani = Simon_Sitting_Attack_Right;
						animations[ani]->currentFrame = 0;
						animations[ani]->lastFrameTime = GetTickCount64();
						this->SimonAttack();
						if (WPT == 1)
							weapons[0]->ani = 2;
						else if (WPT == 2)
						{
							weapons[0]->ani = 4;
						}
						else
							weapons[0]->ani = 0;
					}
				}
			
				else
				{
					if (ani != Simon_Attack_Right)
					{
						ani = Simon_Attack_Right;
						animations[ani]->currentFrame = 0;
						animations[ani]->lastFrameTime = GetTickCount64();
						this->SimonAttack();
						if (WPT == 1)
							weapons[0]->ani = 2;
						else if (WPT == 2)
						{
							weapons[0]->ani = 4;
						}
						else
							weapons[0]->ani = 0;
						
					}
				}
			}
			//DebugOut(L"FrameATK%d\n", animations[ani]->currentFrame);
		if (GetTickCount64() - startATK >= ATKTime)
		{

			IsAttacking = false;
			weapons[0]->EndAni = true;
			if (nx == Simon_Turn_Left)
				ani = 0;
			else
				ani = 1;
			//animations[ani]->currentFrame = 0;
		}
	}
	

	if (IsAttacking == true && IsWaiting == false)
	{
		
		/*if (nx == Simon_Turn_Left)
		{
		*/	
			weapons[0]->animations[weapons[0]->ani]->Render(weapons[0]->x, weapons[0]->y);
		//}
		//else
		//{
		//	//DebugOut(L"%d %d\n",animations[ani]->currentFrame,weapons[0]->animations[0]->currentFrame);
		//	weapons[0]->animations[0]->Render(weapons[0]->x, weapons[0]->y);

		//}
		animations[ani]->Render(x, y);
	}
	if (IsLevelUp)
	{
		if (nx == Simon_Turn_Left)
			ani = 11;
		else
			ani = 10;
		animations[ani]->Render(x, y);
		if (GetTickCount64() - LevelUptime >= 300)
		{
			IsLevelUp = false;
			if (nx == Simon_Turn_Left)
				ani = 0;
			else
				ani = 1;
		}
	}
	if (knife->IsActivated==true)
	{
		knife->animations[knife->ani]->Render(knife->x, knife->y);
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
	sprites->Add(4002, 61, 0, 121, 65, textsimon);//Simon WalkLeft
	sprites->Add(4003, 182, 0, 242, 65, textsimon);

	sprites->Add(4004, 420, 0, 480, 65, textsimon2);
	sprites->Add(4005, 359, 0, 419, 65, textsimon2);//Simon WalkRight
	sprites->Add(4006, 298, 0, 359, 65, textsimon2);

	sprites->Add(4007, 108, 0, 162, 65, textsimon2);
	sprites->Add(4008, 62, 0, 106, 65, textsimon2); //Simon ATK Right
	sprites->Add(4009, 0, 0, 61, 65, textsimon2);

	sprites->Add(4012, 418, 0, 480, 65, textsimon);
	sprites->Add(4011, 363, 0, 417, 65, textsimon);//Simon Atk Left
	sprites->Add(4010, 303, 0, 363, 65, textsimon);

	sprites->Add(4013, 190, 0, 233, 65, textsimon2);  //Simon Jump
	sprites->Add(4014, 250, 0, 288, 65, textsimon);

	sprites->Add(4015, 0, 65, 60, 130, textsimon2);
	sprites->Add(4017, 374, 130, 426, 195, textsimon2);
	sprites->Add(4016, 426, 130, 480, 195, textsimon2);

	sprites->Add(4020, 420, 65, 480, 130, textsimon);
	sprites->Add(4019, 0, 130, 60, 195, textsimon);
	sprites->Add(4018, 60, 130, 120, 195, textsimon );

	sprites->Add(4021, 300, 196, 360, 260, textsimon2);
	sprites->Add(4022, 360, 196, 420, 260, textsimon2);
	sprites->Add(4023, 420, 196, 480, 260, textsimon2);

	sprites->Add(4024, 120, 196, 180, 260, textsimon);
	sprites->Add(4025, 60, 196, 120, 260, textsimon);
	sprites->Add(4026, 0, 196, 60, 260, textsimon);

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
	ani->Add(4010);
	ani->Add(4011);
	ani->Add(4012);
	animation->Add(105, ani);

	ani = new CAnimation(100);
	ani->Add(4013);
	animation->Add(106,ani);

	ani = new CAnimation(100);
	ani->Add(4014);
	animation->Add(107, ani);

	ani = new CAnimation(100);
	ani->Add(4015);
	ani->Add(4016);
	ani->Add(4017);
	animation->Add(108, ani);

	ani = new CAnimation(100);
	ani->Add(4018);
	ani->Add(4019);
	ani->Add(4020);
	animation->Add(109, ani);

	ani = new CAnimation(100);
	ani->Add(4021);
	ani->Add(4022);
	ani->Add(4023);
	animation->Add(110, ani);

	ani = new CAnimation(100);
	ani->Add(4024);
	ani->Add(4025);
	ani->Add(4026);
	animation->Add(111, ani);

	AddAnimation(100);
	AddAnimation(101);
	AddAnimation(102);
	AddAnimation(103);
	AddAnimation(104);
	AddAnimation(105);
	AddAnimation(106);
	AddAnimation(107);
	AddAnimation(108);
	AddAnimation(109);
	AddAnimation(110);
	AddAnimation(111);
	SetPosition(0, 150);
	IsSitting = false;
}

Simon::~Simon()
{
}

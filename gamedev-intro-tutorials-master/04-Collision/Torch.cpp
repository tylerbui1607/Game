#include "Torch.h"



void Torch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void Torch::Render()
{
	int ani = 0;
	animations[ani]->Render(x, y, 255);
}

Torch::Torch(int type)
{
	ItemType = type;
	Health = 1;
}

void Torch::SetState(int state)
{
}

#include "Score.h"

Score::Score()
{
}

void Score::GetTime()
{
	timer = new Timer();
	int temp = TimeLimit;
	for (int i = 0; i < 3; i++)
	{		
		timer->Render(temp % 10, 339 - i * 15, -68);
		temp = temp / 10;
	}
}

void Score::Update(DWORD dt)
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

Score::~Score()
{
}

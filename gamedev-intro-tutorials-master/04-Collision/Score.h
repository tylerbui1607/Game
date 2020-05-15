#pragma once
#include"Timer.h"
class Score
{
	int TimeLimit = 300;
	DWORD Count = 0;
	Timer* timer ;
public:
	Score();
	void GetTime();
	void Update(DWORD dt);
	~Score();

};


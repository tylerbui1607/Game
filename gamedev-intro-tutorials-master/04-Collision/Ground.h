#pragma once
#include "GameObject.h"

class Ground :
	public CGameObject
{
	int Width, Height;
	
public:
	Ground(int W,int H);
	void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};


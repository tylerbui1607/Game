#include "Ground.h"

Ground::Ground(int W, int H)
{
	this->Width = W;
	this->Height = H;
}

void Ground::Render()
{
}

void Ground::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + Width;
	bottom = y + Height;
}

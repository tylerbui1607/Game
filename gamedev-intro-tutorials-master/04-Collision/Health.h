#pragma once
#include"Sprites.h"
#include"Textures.h"
#include <iostream>
#include"Game.h"
class Health
{
	int Width;
	int Height;
	CTextures* textures = new CTextures();
	CSprites* sprites = new CSprites();
public:

	void DrawHeart(int x, int y, int Health);
	void DrawHeartLost(int x, int y);
};


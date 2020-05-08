#pragma once
#include"Sprites.h"
#include"Textures.h"
#include <iostream>
#include "Game.h"
class Board
{
	int Width;
	int Height;
	int x, y;
	CTextures* textures = new CTextures();
	CSprites* sprites = new CSprites();
public:
	void DrawBoard();
};


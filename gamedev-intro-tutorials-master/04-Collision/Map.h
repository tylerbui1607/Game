#pragma once
#include"Sprites.h"
#include"Textures.h"
#include <iostream>
#include <fstream>
#include "Game.h"
class Map
{
	int collum;
	int row;
	int TiledWidth;
	int TiledID[100][100];
	CTextures* textures = new CTextures();
	CSprites* sprites = new CSprites();
public:
	Map();
	void ReadMap();
	void DrawMap();
	void AddIDMap();
	~Map();
};


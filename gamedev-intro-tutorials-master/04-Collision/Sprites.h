 #pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include"Textures.h"
#define ID_TEX_SIMON 30
#define ID_TEX_SIMONii 40
using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left; 
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public: 
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);

	void DrawFlip(float x, float y, int alpha = 255);
	void Draw(float x, float y, int alpha = 255);
	void DrawBoard(float x, float y, int alpha=255);
};

typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);
	LPSPRITE &operator[](int id) {return sprites[id];}

	static CSprites * GetInstance();
};

/*
	Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
public:
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	bool EndAni ;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, int alpha=255);
	void RenderEX(float x, float y, int alpha = 255);
	int GetCurentFrame()
	{
		return currentFrame;
	};
	void SetCurrentFrame(int SimonFrame);
	void SetState(int state);
};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;
	

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
	void LoadResource();
	static CAnimations * GetInstance();
};




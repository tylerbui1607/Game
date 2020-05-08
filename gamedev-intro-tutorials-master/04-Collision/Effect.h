
#include"Textures.h"
#include "GameObject.h"

#define IsDead 1
#define ID_TEX_EFFECT 70
class Effect :
public CGameObject
{
	int ani;
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animation = CAnimations::GetInstance();
	void IsDeadObj(int Health);
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void SetState(int state);
	void UpdateAnimation();
	Effect(int objx, int objy);
	~Effect();
};

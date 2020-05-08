#include "Timer.h"

void Timer::LoadSprites()
{
	textures->Add(10, L"textures\\font.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 textfont = textures->Get(10);
	//sprite->Add(100, , , , , textfont);
}

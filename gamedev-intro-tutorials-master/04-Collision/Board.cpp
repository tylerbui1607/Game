#include "Board.h"

void Board::DrawBoard()
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(L"textures\\mapx.png", &info);
	if (result != D3D_OK)
	{
		/*DebugOut(L"[ERROR] GetImageInfoFromFile failed ne: \n");*/
		return;
	}
	/*DebugOut(L"[ERROR] GetImageInfoFromFile \n");*/
	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DTEXTURE9 texture;

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		L"textures\\board.png",							// Path to the image to load
		info.Width = 520,							// Texture width
		info.Height = 80,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}
	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = 520;
	r.bottom = 80;
	CGame::GetInstance()->DrawBoard(0, -80 , texture, r.left, r.top, r.right, r.bottom);
	
		
}

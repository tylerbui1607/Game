#include "Map.h"
#include"GameObject.h"
Map::Map()
{
	sprites = new CSprites();
	ReadMap();
	AddIDMap();
	
}

void Map::ReadMap()
{
	ifstream ifs("textures\\map.txt", ios::in);
	ifs >> row >>collum;
	for(int i=0;i<row;i++)
	{
		for (int j = 0; j < collum; j++)
		{
			ifs >> TiledID[i][j];
			/*DebugOut(L"%d", TiledID[i][j]);*/
		}
		/*DebugOut(L"\n");*/
	}
	ifs.close();
}

void Map::DrawMap()
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
		L"textures\\mapx.png",							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255,0,255),
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}
	for(int i=0 ; i<row ;i++)
		for (int j = 0; j < collum; j++)
		{
			int Id = TiledID[i][j];
			RECT r;
			r.left = (Id - 1) % 7 * 64;
			r.top = (Id - 1) / 7 * 64;
			r.right = r.left + 64;
			r.bottom = r.top + 64;
			//DebugOut(L"%d\n",Id);
			CGame::GetInstance()->Draw(j * 64, i*64, texture, r.left, r.top, r.right, r.bottom);
		}
}

void Map::AddIDMap()
{
	textures->Add(100, L"textures\\mapx.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 textmap = textures->Get(100);
	int IDFrame=1;
	for (int i = 0; i <6  ; i++)
	{
		for(int j=0;j<7;j++)
		{
			/*DebugOut(L"%d", textmap);*/
			sprites->Add(IDFrame, j* 64,i*64,64+j*64,64+i*64,textmap);
			IDFrame++;		
		}
					
	}
}

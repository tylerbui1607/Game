/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions: 
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox
		
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include"Ground.h"
#include "Mario.h"
#include "Brick.h"
#include "Goomba.h"
#include"Simon.h"
#include"Torch.h"
#include"Map.h"
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 450
#define SCREEN_HEIGHT 380

#define MAX_FRAME_RATE 120

#define ID_TEX_SIMON 30
#define ID_TEX_SIMONii 40
#define ID_TEX_TORCH 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_WEAPON 50

CGame *game;
Simon* simon;
//CMario *mario;
CGoomba *goomba;
Torch* torch;
Weapon* weapon;
Map* Mapx;
vector<LPGAMEOBJECT> objects;

class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	/*if (simon->state == Simon_ATK)
		return;*/
	switch (KeyCode)
	{
	case DIK_SPACE:
		simon->SetState(Simon_Jump);
		break;
	case DIK_A: // reset
		simon->SetState( Simon_ATK);
		//simon->SetPosition(50.0f,0.0f);
		break;
	
	}
}
void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	// disable control key when Mario die 
	if (simon->GetState() == Simon_Dead) return;
	if (simon->IsAttacking)
		return;
	if (game->IsKeyDown(DIK_RIGHT))
		simon->SetState(Simon_Turn_right);
	else if (game->IsKeyDown(DIK_LEFT))
		simon->SetState(Simon_Turn_Left);
	/*else if (game->IsKeyDown(DIK_A))
		simon->SetState(Simon_ATK);*/
	else
		simon->SetState(Simon_Stand);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	
	CTextures * textures = CTextures::GetInstance();
	 Mapx = new Map();

	textures->Add(ID_TEX_MISC, L"textures\\misc.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
	
	textures->Add(ID_TEX_SIMON, L"textures\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_SIMONii, L"textures\\simon2.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_TORCH, L"textures\\torch.png", D3DCOLOR_XRGB(255, 0, 255));
	
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	

	LPDIRECT3DTEXTURE9 textsimon = textures->Get(ID_TEX_SIMON);
	LPDIRECT3DTEXTURE9 textsimon2 = textures->Get(ID_TEX_SIMONii);
	LPDIRECT3DTEXTURE9 texttorch = textures->Get(ID_TEX_TORCH);
	LPDIRECT3DTEXTURE9 textweapon = textures->Get(ID_TEX_WEAPON);
	LPANIMATION ani;
	//animations->Add(503, ani);
	sprites->Add(101, 0, 0, 32, 64, texttorch);
	sprites->Add(102, 32, 0, 64, 64, texttorch);
	Ground* ground = new Ground(1556, 64);
	ground->SetPosition(0, 320);
	ani = new CAnimation(100);		// torch animation
	ani->Add(101);
	ani->Add(102);
	animations->Add(599, ani);

	weapon = new Weapon();
	

	
		Torch* torch = new Torch();
		torch->AddAnimation(599);
		torch->SetPosition(192  , 256);
		objects.push_back(torch);
		
		Torch* torch1 = new Torch();
		torch1->AddAnimation(599);
		torch1->SetPosition(448, 256);
		objects.push_back(torch1);
		
		Torch* torch2 = new Torch();
		torch2->AddAnimation(599);
		torch2->SetPosition(704, 256);
		objects.push_back(torch2);
		
		Torch* torch3 = new Torch();
		torch3->AddAnimation(599);
		torch3->SetPosition(960, 256);
		objects.push_back(torch3);
		
		Torch* torch4 = new Torch();
		torch4->AddAnimation(599);
		torch4->SetPosition(1216, 256);
		objects.push_back(torch4);
	
		objects.push_back(ground);
	Mapx = new Map();
	simon = new Simon();
	simon->SetPosition(0, 200);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	//DebugOut(L"size:%d /n", coObjects.size());
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,&coObjects);
	}
	simon->Update(dt,&objects);

	// Update camera to follow mario
	float cx, cy;
	//mario->GetPosition(cx, cy);
	simon->GetPosition(cx, cy);
	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;
	if (cx < 0)
		cx = 0;
	if (cx + SCREEN_WIDTH >= 1536)
		cx = 1536 - SCREEN_WIDTH;
	CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
}

/*
	Render a frame 
*/
void Render()
{

	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);
		//Mapx->DrawMap();
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		Mapx->DrawMap();
		for (int i = 0; i < objects.size(); i++)
			if(objects[i]->getHealth()>0)
				objects[i]->Render();
		
		simon->Render();
		spriteHandler->End();
		d3ddv->EndScene();
	}
	
	
	d3ddv->Present(NULL, NULL, NULL, NULL);
	

}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}
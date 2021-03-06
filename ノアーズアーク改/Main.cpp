#include "GameScene.h"
#include "Mouse.h"
#include "Control.h"
#include "char.h"
#include "finish.h"
#include"Sound.h"
#include "GameSceneScroll.h"
#include "gameSceneControl.h"
#include "title.h"
#include "sceneSelect.h"
#include "gameSceneControl.h"
#include "systemCount.h"
#include <tchar.h>

#define WINDOW_W 1440				// ウィンドウ幅
#define WINDOW_H 650					// ウィンドウ高さ

LPDIRECT3D9			g_pDirect3D = NULL;		// DirectXオブジェクトのポインタ
LPDIRECT3DDEVICE9	g_pDirect3DDevice = NULL;	// DirectXデバイスのポインタ
D3DDISPLAYMODE		g_D3DdisplayMode;
extern LPDIRECTSOUND8      g_lpDS;
extern LPDIRECTSOUNDBUFFER g_lpSecondary;
extern LPDIRECTSOUNDBUFFER g_lpSecondary2;
extern LPDIRECTSOUNDBUFFER g_lpSecondary3;
extern LPDIRECTSOUNDBUFFER g_lpSecondary4;
extern LPDIRECTSOUNDBUFFER g_lpSecondary5;



// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam)
{
	if (mes == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, mes, wParam, lParam);
}

// エントリポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//---------------------------------------------------------------------
	//							ウィンドウ生成処理
	//---------------------------------------------------------------------

	MSG msg;			// メッセージを格納する構造体
	HWND hWnd;			// ウィンドウハンドル
	WNDCLASS winc;
	//HDC hDC;            // このウィンドウ(hWnd)のデバイスコンテキストハンドルhDC.
	POINT pt;           // マウス位置座標を表すPOINT構造体変数pt.
	//Windows情報の設定
	winc.style = CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc = WndProc;
	winc.cbClsExtra = winc.cbWndExtra = 0;
	winc.hInstance = hInstance;
	winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = WINDOW_TITLE;	//クラス名

										//Windowの登録
	if (!RegisterClass(&winc)) return 0;
	//Windowの生成
	hWnd = CreateWindow(
		WINDOW_TITLE,						//ウィンドウのクラス名
		WINDOW_TITLE, 						//ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//ウィンドウスタイル
		CW_USEDEFAULT,						// ウィンドウの横方向の位置x
		CW_USEDEFAULT,						// ウィンドウの縦方向の位置y
		WINDOW_W,							// Width（幅）
		WINDOW_H,							// Height（高さ）
		NULL,
		NULL,
		hInstance,							// アプリケーションインスタンスのハンドル
		NULL
	);
	if (!hWnd) return 0;


	ShowWindow(hWnd, SW_SHOW);
	// InitDInputMouse(hWnd);


	//---------------------------------------------------------------------
	//							DirectX初期化処理
	//---------------------------------------------------------------------

	// DirectXオブジェクト生成
	g_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	// オブジェクトの生成に成功したかチェック
	if (g_pDirect3D == NULL)
	{
		// 生成に失敗したら終了する
		return 0;
	}

	// DisplayModeの取得
	g_pDirect3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,
		&g_D3DdisplayMode);

	// DirectXのデバイスを生成する際に必要な情報を用意
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferFormat = g_D3DdisplayMode.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;

	// DirectXのデバイス生成
	g_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pDirect3DDevice);

	// DirectXのデバイスを生成できたかチェック
	if (g_pDirect3DDevice == NULL)
	{
		// 生成に失敗したらDirectXオブジェクトを解放して終了する
		g_pDirect3D->Release();
		return 0;
	}

	SoundInit(hWnd);
	

	if (!CreateSoundBuffer(&g_lpSecondary, "village10.wav")) {
		SoundRelease();
		return -1;
	}

	if (!CreateSoundBuffer(&g_lpSecondary2, "n37.wav")) {
		SoundRelease();
		return -1;
	}

	if (!CreateSoundBuffer(&g_lpSecondary3, "town25b.wav")) {
		SoundRelease();
		return -1;
	}

	if (!CreateSoundBuffer(&g_lpSecondary4, "j_25.wav")) {
		SoundRelease();
		return -1;
	}

	if (!CreateSoundBuffer(&g_lpSecondary5, "piano37.wav")) {
		SoundRelease();
		return -1;
	}


	//---------------------------------------------------------------------
	//							ゲームループ
	//---------------------------------------------------------------------

	GameSceneInit();	// ゲームシーンの初期化関数
	DWORD SyncOld = timeGetTime();	//	システム時間を取得
	DWORD SyncNow;
	DWORD CountStart = timeGetTime();  //開始三秒間の計測用
	DWORD CountEnd;

	timeBeginPeriod(1);
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SyncNow = timeGetTime();
			CountEnd = timeGetTime();
			if (SyncNow - SyncOld >= 1000 / 60) //	1秒間に60回この中に入る
			{
				//フレームカウント
				///////////////////////////////////////
			/*	static  int fcount;
				fcount++;
				TCHAR buff[255];
				_stprintf_s(buff, _T("%d\n"), fcount);//文字列をセット
				OutputDebugString(buff);   //ここで出力デバックに表示*/
				/////////////////////////////////////
					MouseCursor(hWnd);
					pictureDraw();
					sceneControl();
			}
			
		}
		//CircleCllide();

		//SyncOld = SyncNow;
	}


	timeEndPeriod(1);

	SoundRelease();

	GameSceneFree();				// ゲームシーンの解放関数

	g_pDirect3DDevice->Release();	// DirectXのデバイスの解放
	g_pDirect3D->Release();			// DirectXオブジェクトの解放
	return 0;
}

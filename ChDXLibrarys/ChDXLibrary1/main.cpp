
#include"Include/ChDXFrameWork/CGameIncludeFile.h"

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height

LPDIRECT3D9				lpD3D;		// Direct3Dインターフェイス

LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス

D3DPRESENT_PARAMETERS d3dpp;

///////////////////////////////////////////////////////////////////////////////////////
//Texture,XFireなどのデータ用定数
//※ここに登録してある文字を利用してしたりデータの検索をかける描画する
///////////////////////////////////////////////////////////////////////////////////////

//Texture
const enum { Sq, Ground };

//XFile
const enum { Sura };

////  グローバル変数宣言

LPD3DXFONT lpFont;		// フォント

bool gameFullScreen;	// フルスクリーン（true,false)

D3DXMATRIX Mat, CamMat;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

D3DXMATRIX TestMat;
ChCamera *Camera;
ChSmpXlist *Xlist;
ChSp *Sprite;
ChTexlist *Texlist;
ChPoBo *PoBo;
ChLight *Light;
ChShader *Effect;
ChObjCon *ObjCon;
LpChFileCon FileCon;

D3DXMATRIX SuraAS, SuraAE1, SuraAE2, SuraAN;
D3DXMATRIX Sura2Mat,Sura2OffsetMat;
bool HitFlg;
float HitLen;
float End = 1.0f, AniCnt = 0.0f;
unsigned char AniCheck = 0;
bool AniChengeFlg;

// 更新処理
void Update(void)
{
	D3DXVECTOR3 TmpVec;
	float TmpF1, TmpF2;

	GetKey(VK_RIGHT) {
		D3DXMATRIX TmpMat;
		D3DXMatrixRotationY(&TmpMat, D3DXToRadian(5));
		CamMat = TmpMat * CamMat;
	}
	GetKey(VK_LEFT) {
		D3DXMATRIX TmpMat;
		D3DXMatrixRotationY(&TmpMat, D3DXToRadian(-5));
		CamMat = TmpMat * CamMat;
	}

	if (AniCheck == 0)AniChengeFlg = ObjCon->SimpleAnimetion(&SuraAS, &SuraAE1, (End / 2.0f), &AniCnt, &SuraAN, 60.0f);
	else AniChengeFlg = ObjCon->SimpleAnimetion(&SuraAE1, &SuraAE2, End, &AniCnt, &SuraAN, 60.0f);
	if (AniChengeFlg)(AniCheck += 1) %= 2;
	TmpVec = *Camera->GetCamLook() - *Camera->GetCamPos();
	D3DXVec3Normalize(&TmpVec, &TmpVec);
	Camera->SetCamLook(&D3DXVECTOR3(SuraAN._41, SuraAN._42, SuraAN._43));
	HitFlg = ObjCon->SmpXFileHitRay(Xlist->GetSmpXFile(Sura), &SuraAN, Camera->GetCamPos(), &TmpVec,&HitLen);
	
	D3DXVec3TransformCoord(&TmpVec, &D3DXVECTOR3(SuraAN._41, SuraAN._42, SuraAN._43), &Sura2OffsetMat);

	TmpF1 = D3DXVec3Length(&TmpVec);

	D3DXVec3TransformCoord(&TmpVec, &D3DXVECTOR3(SuraAN._41, 0.0f, SuraAN._43), &Sura2OffsetMat);

	TmpF2 = D3DXVec3Length(&TmpVec);

	TmpF1 = acosf((TmpF2 / TmpF1));

	TmpF1 = D3DXToDegree(TmpF1);

	D3DXMatrixRotationX(&Sura2Mat,D3DXToRadian( -TmpF1));
}

// 3D描画
void Render3D(void)
{
	Light->SetLight(FALSE);
	D3DXMATRIX TmpMat;

	Effect->LightCheck(TRUE);
	Effect->SetCam(Camera);
	Effect->SetLight(Light);
	Effect->SmpXfileDraw(Xlist->GetSmpXFile(Sura), &SuraAN,ChToonEffect);
	//Xlist->DrawSmpXFile(&SuraAN, Sura);

	TmpMat = Sura2Mat * Sura2OffsetMat;
	Effect->SmpXfileDraw(Xlist->GetSmpXFile(Sura), &TmpMat, ChNoEffect);
	//Xlist->DrawSmpXFile(&TmpMat, Sura);


	D3DXMatrixTranslation(&TmpMat, 0.0f, 1.0f, 0.0f);
	PoBo->SetXYPosition(&D3DXVECTOR3(1.0f, 1.0f, 0.0f), 2.0f, 2.0f);
	if(HitFlg)PoBo->Draw(Texlist->GetTex(Sq),&TmpMat);

	D3DXMatrixTranslation(&TmpMat, 0.0f, 0.0f, 0.0f);
	PoBo->SetZXPosition(&D3DXVECTOR3(-5.0f, 0.0f, 5.0f), 10.0f, 10.0f);
	PoBo->Draw(Texlist->GetTex(Ground), &TmpMat);
}

// 2D描画
void Render2D(void)
{


	//////////////////////////////////////////////////
	///	スプライトの描画処理
	//////////////////////////////////////////////////
	D3DXMATRIX TmpMat;
	D3DXMatrixRotationY(&TmpMat, D3DXToRadian(80));
	//Sprite->DrawSprite(Texlist->GetTex(Sq), &TmpMat);

	RECT rc = { 0,0,8,16 };
	for (char i = 0; i < 0; i++) {
		//lpFont->DrawText(NULL, *(buf + 1), -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void GameFrame(void)
{
	// バックバッファと Z バッファをクリア
	lpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);


	// 更新処理
	Update();


	// 描画開始
	lpD3DDevice->BeginScene();

	Camera->SetCamPos(&D3DXVECTOR3(0.0f, 2.0f, -5.0f));
	Camera->SetView();



	// 3D描画
	Render3D();

	// 2D描画
	Render2D();



	// 描画終了
	lpD3DDevice->EndScene();

	// バックバッファをプライマリバッファにコピー
	lpD3DDevice->Present(NULL, NULL, NULL, NULL);
}

LRESULT APIENTRY WndFunc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		return 0;

	}
	return DefWindowProc(hwnd, msg, wParam, lParam);

}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,
	LPSTR lpszCmdParam, int nCmdshow)
{
	MSG msg;

	HWND hwnd;
	WNDCLASS wc;
	char szAppName[] = "Generic Game SDK Window";

	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = WndFunc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;

	RegisterClass(&wc);

	hwnd = CreateWindowEx(
		0,
		szAppName,
		"Direct X",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCRW, SCRH,
		NULL, NULL, hInst,
		NULL);

	if (!hwnd)return FALSE;

	ShowWindow(hwnd, nCmdshow);
	UpdateWindow(hwnd);
	SetFocus(hwnd);

	gameFullScreen = false;	// ウィンドウモード

	if (gameFullScreen) {
		ShowCursor(FALSE);
	}
	else {
		RECT rc = { 0,0,SCRW,SCRH };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(hwnd, NULL, 50, 50, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW | SWP_NOZORDER);
	}

	//---------------------DirectX Graphics関連-----------------------

	// Direct3D オブジェクトを作成
	lpD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!lpD3D)
	{
		// オブジェクト作成失敗
		MessageBox(NULL, "Direct3D の作成に失敗しました。", "ERROR", MB_OK | MB_ICONSTOP);
		// 終了する
		return 0;
	}
	int adapter;

	// 使用するアダプタ番号
	adapter = D3DADAPTER_DEFAULT;

	// ウインドウの作成が完了したので、Direct3D を初期化する
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	// Direct3D 初期化パラメータの設定
	if (gameFullScreen)
	{
		// フルスクリーン : ほとんどのアダプタでサポートされているフォーマットを使用
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// ウインドウ : 現在の画面モードを使用
		D3DDISPLAYMODE disp;
		// 現在の画面モードを取得
		lpD3D->GetAdapterDisplayMode(adapter, &disp);
		d3dpp.BackBufferFormat = disp.Format;
	}
	// 表示領域サイズの設定
	d3dpp.BackBufferWidth = SCRW;
	d3dpp.BackBufferHeight = SCRH;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;

	if (!gameFullScreen)
	{
		// ウインドウモード
		d3dpp.Windowed = 1;
	}

	// Z バッファの自動作成
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//ﾊﾞｯｸﾊﾞｯﾌｧをﾛｯｸ可能にする(GetDCも可能になる)
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	// デバイスの作成 - T&L HAL
	if (FAILED(lpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &lpD3DDevice)))
	{
		// 失敗したので HAL で試行
		if (FAILED(lpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &lpD3DDevice)))
		{
			// 失敗したので REF で試行
			if (FAILED(lpD3D->CreateDevice(adapter, D3DDEVTYPE_REF, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &lpD3DDevice)))
			{
				// 結局失敗した
				MessageBox(NULL, "DirectX9が初期化できません。\n未対応のパソコンと思われます。", "ERROR", MB_OK | MB_ICONSTOP);
				lpD3D->Release();
				// 終了する
				return 0;
			}
		}
	}

	// レンダリング・ステートを設定
	// Z バッファ有効化->前後関係の計算を正確にしてくれる
	lpD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// アルファブレンディング有効化
	lpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// アルファブレンディング方法を設定
	lpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// レンダリング時のアルファ値の計算方法の設定
	lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	// テクスチャの色を使用
	lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	// 頂点の色を使用
	lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	// レンダリング時の色の計算方法の設定
	lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	//裏面カリング
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// フィルタ設定
	lpD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	lpD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	lpD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);


	lpD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	// 頂点フォーマットの設定
	lpD3DDevice->SetFVF(FVF_VERTEX);

	timeBeginPeriod(1);

	// ゲームに関する初期化処理 ---------------------------

	FileCon = new ChFileCon();

	Camera = new ChCamera(lpD3DDevice,&CamMat);

	Xlist = new ChSmpXlist(lpD3DDevice);

	Texlist = new ChTexlist(lpD3DDevice);

	Sprite = new ChSprite(lpD3DDevice);

	PoBo = new ChPoBo(lpD3DDevice);

	Light = new ChLight(lpD3DDevice);

	Effect = new ChShader("Include/ChDXFrameWork/EffectDate/Model.cso", lpD3DDevice
		,"Include/ChDXFrameWork/EffectDate/NoToon.png"
		,"Include/ChDXFrameWork/EffectDate/Toon.png"
		,"Include/ChDXFrameWork/EffectDate/White.bmp");

	ObjCon = new ChObjCon();


	system("cd \Date && dir *.txt /b > TmpDate.ChD");

	Xlist->SetSmpXFile("XFile/sura.x", Sura);

	D3DXMatrixTranslation(&Mat, 0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&SuraAN, 0.0f, 0.0f, 0.0f);
	D3DXMatrixRotationY(&SuraAS, D3DXToRadian(0));
	D3DXMatrixRotationY(&SuraAE1, D3DXToRadian(180));
	SuraAE1._42 = 1.0f;
	D3DXMatrixRotationY(&SuraAE2, D3DXToRadian(360));
	SuraAE2._42 = 2.0f;

	CamMat = Mat;

	Texlist->SetTexture("Texture/sq.png", Sq, 999, 545, WW, WH, NULL);
	Texlist->SetTexture("Texture/36.jpg", Ground, 512, 512, 512, 512, NULL);

	D3DXMatrixRotationY(&Sura2OffsetMat, D3DXToRadian(90));
	Sura2OffsetMat._41 = -2.0f;
	// フォント作成
	D3DXCreateFont(lpD3DDevice, 16, 16, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "ＭＳ ゴシック", &lpFont);

	lpFont->OnResetDevice();

	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, NULL, 0, 0))break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			GameFrame();
		}
	}

	// ゲームに関する終了処理 ---------------------------
	system("cd \Date && del /q TmpDate.ChD");
	delete FileCon;
	delete ObjCon;
	delete Effect;
	delete Xlist;
	delete Texlist;
	delete PoBo;
	delete Light;
	delete Sprite;
	delete Camera;


	lpFont->Release();		// フォント


	timeEndPeriod(1);

	// Direct3D オブジェクトを解放
	lpD3DDevice->Release();
	lpD3D->Release();

	return (int)msg.wParam;
}

#include"Include/ChDXFrameWork/CGameIncludeFile.h"

#define	SCRW		1280	// �E�B���h�E���iWidth
#define	SCRH		720		// �E�B���h�E�����iHeight

LPDIRECT3D9				lpD3D;		// Direct3D�C���^�[�t�F�C�X

LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDevice�C���^�[�t�F�C�X

D3DPRESENT_PARAMETERS d3dpp;

///////////////////////////////////////////////////////////////////////////////////////
//Texture,XFire�Ȃǂ̃f�[�^�p�萔
//�������ɓo�^���Ă��镶���𗘗p���Ă�����f�[�^�̌�����������`�悷��
///////////////////////////////////////////////////////////////////////////////////////

//Texture
const enum { Sq, Ground };

//XFile
const enum { Sura };

////  �O���[�o���ϐ��錾

LPD3DXFONT lpFont;		// �t�H���g

bool gameFullScreen;	// �t���X�N���[���itrue,false)

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

// �X�V����
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

// 3D�`��
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

// 2D�`��
void Render2D(void)
{


	//////////////////////////////////////////////////
	///	�X�v���C�g�̕`�揈��
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
	// �o�b�N�o�b�t�@�� Z �o�b�t�@���N���A
	lpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);


	// �X�V����
	Update();


	// �`��J�n
	lpD3DDevice->BeginScene();

	Camera->SetCamPos(&D3DXVECTOR3(0.0f, 2.0f, -5.0f));
	Camera->SetView();



	// 3D�`��
	Render3D();

	// 2D�`��
	Render2D();



	// �`��I��
	lpD3DDevice->EndScene();

	// �o�b�N�o�b�t�@���v���C�}���o�b�t�@�ɃR�s�[
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

	gameFullScreen = false;	// �E�B���h�E���[�h

	if (gameFullScreen) {
		ShowCursor(FALSE);
	}
	else {
		RECT rc = { 0,0,SCRW,SCRH };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(hwnd, NULL, 50, 50, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW | SWP_NOZORDER);
	}

	//---------------------DirectX Graphics�֘A-----------------------

	// Direct3D �I�u�W�F�N�g���쐬
	lpD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!lpD3D)
	{
		// �I�u�W�F�N�g�쐬���s
		MessageBox(NULL, "Direct3D �̍쐬�Ɏ��s���܂����B", "ERROR", MB_OK | MB_ICONSTOP);
		// �I������
		return 0;
	}
	int adapter;

	// �g�p����A�_�v�^�ԍ�
	adapter = D3DADAPTER_DEFAULT;

	// �E�C���h�E�̍쐬�����������̂ŁADirect3D ������������
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	// Direct3D �������p�����[�^�̐ݒ�
	if (gameFullScreen)
	{
		// �t���X�N���[�� : �قƂ�ǂ̃A�_�v�^�ŃT�|�[�g����Ă���t�H�[�}�b�g���g�p
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// �E�C���h�E : ���݂̉�ʃ��[�h���g�p
		D3DDISPLAYMODE disp;
		// ���݂̉�ʃ��[�h���擾
		lpD3D->GetAdapterDisplayMode(adapter, &disp);
		d3dpp.BackBufferFormat = disp.Format;
	}
	// �\���̈�T�C�Y�̐ݒ�
	d3dpp.BackBufferWidth = SCRW;
	d3dpp.BackBufferHeight = SCRH;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;

	if (!gameFullScreen)
	{
		// �E�C���h�E���[�h
		d3dpp.Windowed = 1;
	}

	// Z �o�b�t�@�̎����쐬
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//�ޯ��ޯ̧��ۯ��\�ɂ���(GetDC���\�ɂȂ�)
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	// �f�o�C�X�̍쐬 - T&L HAL
	if (FAILED(lpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &lpD3DDevice)))
	{
		// ���s�����̂� HAL �Ŏ��s
		if (FAILED(lpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &lpD3DDevice)))
		{
			// ���s�����̂� REF �Ŏ��s
			if (FAILED(lpD3D->CreateDevice(adapter, D3DDEVTYPE_REF, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &lpD3DDevice)))
			{
				// ���ǎ��s����
				MessageBox(NULL, "DirectX9���������ł��܂���B\n���Ή��̃p�\�R���Ǝv���܂��B", "ERROR", MB_OK | MB_ICONSTOP);
				lpD3D->Release();
				// �I������
				return 0;
			}
		}
	}

	// �����_�����O�E�X�e�[�g��ݒ�
	// Z �o�b�t�@�L����->�O��֌W�̌v�Z�𐳊m�ɂ��Ă����
	lpD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�u�����f�B���O�L����
	lpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// �A���t�@�u�����f�B���O���@��ݒ�
	lpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �����_�����O���̃A���t�@�l�̌v�Z���@�̐ݒ�
	lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	// �e�N�X�`���̐F���g�p
	lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	// ���_�̐F���g�p
	lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	// �����_�����O���̐F�̌v�Z���@�̐ݒ�
	lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	//���ʃJ�����O
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �t�B���^�ݒ�
	lpD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	lpD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	lpD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);


	lpD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	// ���_�t�H�[�}�b�g�̐ݒ�
	lpD3DDevice->SetFVF(FVF_VERTEX);

	timeBeginPeriod(1);

	// �Q�[���Ɋւ��鏉�������� ---------------------------

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
	// �t�H���g�쐬
	D3DXCreateFont(lpD3DDevice, 16, 16, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "�l�r �S�V�b�N", &lpFont);

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

	// �Q�[���Ɋւ���I������ ---------------------------
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


	lpFont->Release();		// �t�H���g


	timeEndPeriod(1);

	// Direct3D �I�u�W�F�N�g�����
	lpD3DDevice->Release();
	lpD3D->Release();

	return (int)msg.wParam;
}
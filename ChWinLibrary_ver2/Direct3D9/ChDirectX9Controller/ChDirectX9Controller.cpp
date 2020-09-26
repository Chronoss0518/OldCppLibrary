
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

using namespace ChD3D9;

void DirectX3D9::Init(
	const HWND _hWnd
	, const bool _FullScreenFlg
	, const unsigned short _ScrW
	, const unsigned short _ScrH)
{



	if (_FullScreenFlg) {

	}
	else {
		RECT rc = { 0,0,_ScrW,_ScrH };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(_hWnd, NULL, 10, 10, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW | SWP_NOZORDER);
	}

	D3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!D3D9)
	{
		// �I�u�W�F�N�g�쐬���s
		MessageBox(NULL, "Direct3D �̍쐬�Ɏ��s���܂����B", "ERROR", MB_OK | MB_ICONSTOP);
		// �I������
		PostQuitMessage(0);
		return;
	}
	// �g�p����A�_�v�^�ԍ�
	adapter = 0;

	// �E�C���h�E�̍쐬�����������̂ŁADirect3D ������������
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	// Direct3D �������p�����[�^�̐ݒ�
	if (_FullScreenFlg)
	{
		// �t���X�N���[�� : �قƂ�ǂ̃A�_�v�^�ŃT�|�[�g����Ă���t�H�[�}�b�g���g�p
		//		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// �E�C���h�E : ���݂̉�ʃ��[�h���g�p
		D3DDISPLAYMODE disp;
		// ���݂̉�ʃ��[�h���擾
		D3D9->GetAdapterDisplayMode(adapter, &disp);
		d3dpp.BackBufferFormat = disp.Format;
	}
	// �\���̈�T�C�Y�̐ݒ�
	d3dpp.BackBufferWidth = _ScrW;
	d3dpp.BackBufferHeight = _ScrH;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;

	if (!_FullScreenFlg)
	{
		// �E�C���h�E���[�h
		d3dpp.Windowed = 1;
	}

	// Z �o�b�t�@�̎����쐬
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//�ޯ��ޯ̧��ۯ��\�ɂ���(GetDC���\�ɂȂ�)
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	//�t���[�����̐�������.
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//ؾ�ėp�ɏ�ԏ���ۑ�
	Param = d3dpp;

	if (!CreateD3DXDevice(_hWnd, &d3dpp))
	{
		D3D9->Release();
		PostQuitMessage(0);
		return;
	}

	// �����_�����O�E�X�e�[�g��ݒ�//
	// Z �o�b�t�@�L����->�O��֌W�̌v�Z�𐳊m�ɂ��Ă����//
	ZBufferUseFlg(ChStd::True);

	// �A���t�@�u�����f�B���O�L����//
	AlphaBlendUseFlg(ChStd::True);

	// �A���t�@�u�����f�B���O���@��ݒ�//
	AlphaBlendSetting();

	// �����_�����O���̃A���t�@�l�̌v�Z���@�̐ݒ�//
	RenderSetting();

	//���ʃJ�����O
	SetCullMode(CULL::CCW);

	// �t�B���^�ݒ�
	SetFilter(D3DTEXF_LINEAR, D3DTEXF_LINEAR, D3DTEXF_LINEAR);

	// ���C�g
	LightSetting(ChStd::True);

	SetBackBuffer();

	SetFVF((FVF::XYZ | FVF::DIFFUSE | FVF::TEX));

	SetInitFlg(true);

}

///////////////////////////////////////////////////////////////////////////////////

void DirectX3D9::Release()
{

	if (ChPtr::NotNullCheck(D3D9))D3D9->Release(); D3D9 = nullptr;
	if (ChPtr::NotNullCheck(BackBuffer))BackBuffer->Release(); BackBuffer = nullptr;
	if (ChPtr::NotNullCheck(Device))Device->Release(); Device = nullptr;

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool DirectX3D9::CreateD3DXDevice(const HWND _hWnd
	, D3DPRESENT_PARAMETERS *_d3dpp)
{
	// �f�o�C�X�̍쐬 - T&L HAL
	if (FAILED(D3D9->CreateDevice(adapter, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, _d3dpp, &Device)))
	{
		// ���s�����̂� HAL �Ŏ��s
		if (FAILED(D3D9->CreateDevice(adapter, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, _d3dpp, &Device)))
		{
			// ���s�����̂� REF �Ŏ��s
			if (FAILED(D3D9->CreateDevice(adapter, D3DDEVTYPE_REF, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, _d3dpp, &Device)))
			{
				// ���ǎ��s����
				MessageBox(NULL, "DirectX9���������ł��܂���B\n���Ή��̃p�\�R���Ǝv���܂��B", "ERROR", MB_OK | MB_ICONSTOP);

				return ChStd::False;
			}
		}
	}

	return ChStd::True;
}

///////////////////////////////////////////////////////////////////////////////////

void DirectX3D9::DrawStart(const D3DCOLOR&
	_BackColor)
{
	// �`�揀��
	Device->BeginScene();
	// �o�b�N�o�b�t�@�� Z �o�b�t�@���N���A
	Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, _BackColor, 1.0f, 0);
	
	DFlg = true;

}

///////////////////////////////////////////////////////////////////////////////////

void DirectX3D9::DrawEnd(const ChStd::Bool& _RTFlg)
{

	// �`��I��
	Device->EndScene();

	DFlg = false;

	if (_RTFlg)return;

	// �o�b�N�o�b�t�@���v���C�}���o�b�t�@�ɃR�s�[
	if (FAILED(Device->Present(NULL, NULL, NULL, NULL)))
	{
		Device->Reset(&Param);
	}

}

///////////////////////////////////////////////////////////////////////////////////

ChVec3_9 DirectX3D9::GetOnViewPos(const ChMat_9& _Mat)
{
	Device->BeginScene();

	D3DVIEWPORT9 ViewPort;
	ChMat_9 TmpMat, TmpVMat, TmpPMat;
	ChVec3_9 TmpVec;
	TmpVec = _Mat;

	TmpMat.Identity();

	Device->GetViewport(&ViewPort);

	Device->GetTransform(D3DTS_VIEW, &TmpVMat);
	Device->GetTransform(D3DTS_PROJECTION, &TmpPMat);

	D3DXVec3Project(&TmpVec, &TmpVec, &ViewPort, &TmpPMat, &TmpVMat, &TmpMat);

	Device->EndScene();

	return TmpVec;
}

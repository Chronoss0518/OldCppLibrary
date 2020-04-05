#ifndef ChShader_h
#define ChShader_h

#include"../../CGameIncludeFile.h"

typedef const enum{ChNoEffect,ChToonEffect}ChEffectType;

typedef class ChShader {
private:

	LPD3DXEFFECT Effect = nullptr;
	LPDIRECT3DDEVICE9 Device;
	LPDIRECT3DTEXTURE9 LightEffectTex[2];
	LPDIRECT3DTEXTURE9 WhiteTexture;

	///////////////////////////////////////////////////////////////////////////////////

	void SetTexture(
		const char *TexFName
		, unsigned int _W
		, unsigned int _H
		, LPDIRECT3DTEXTURE9 *lpTex) {
		D3DXCreateTextureFromFileEx(Device, TexFName, _W, _H, 1, 0, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT
			, D3DCOLOR_ARGB(255, 255, 255, 255), NULL, NULL, lpTex);
	}

	///////////////////////////////////////////////////////////////////////////////////

	void SetVPMatrix(void)
	{
		D3DXMATRIX vMat, pMat;
		Device->GetTransform(D3DTS_VIEW, &vMat);
		Device->GetTransform(D3DTS_PROJECTION, &pMat);

		Effect->SetMatrix("g_mV", &vMat);
		Effect->SetMatrix("g_mP", &pMat);
	}

	///////////////////////////////////////////////////////////////////////////////////

	void LoadTex(
		LPDIRECT3DTEXTURE9 *lpTex
		, const char *_TextureName
		, unsigned int W
		, unsigned int H
		, const D3DCOLOR Color)
	{
		if (W == 0)W = D3DX_DEFAULT;
		if (H == 0)H = D3DX_DEFAULT;
		D3DXCreateTextureFromFileEx(Device, _TextureName, W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, lpTex);
	}

public:

	///////////////////////////////////////////////////////////////////////////////////

	void LightCheck(bool Flg) { Effect->SetInt("g_LightEnable", Flg ? 1 : 0); }

	///////////////////////////////////////////////////////////////////////////////////

	void SetLight(const ChLight *_Light)
	{
		Effect->SetValue("g_LightDir", &_Light->Light.Direction, sizeof(D3DXVECTOR3));
		Effect->SetValue("g_LightColor", &_Light->Light.Diffuse, sizeof(D3DXCOLOR));
		Effect->SetValue("g_LightAmbient", &_Light->Light.Ambient, sizeof(D3DXCOLOR));
	}

	///////////////////////////////////////////////////////////////////////////////////

	void SetCam(const ChCamera *Cam){Effect->SetValue("g_CamPos", Cam->CamP, sizeof(D3DXVECTOR3));}

	///////////////////////////////////////////////////////////////////////////////////

	ChShader(
		const char *EffectName
		, LPDIRECT3DDEVICE9 _d
		,const char *_UseNoToonTexPath
		, const char *_UseToonTexPath
		,const char *_UseWhiteTexPath) {
		Device = _d;
		LPD3DXBUFFER pBff;

		if (D3DXCreateEffectFromFile(Device, EffectName, nullptr, nullptr
			, 0, nullptr, &Effect, &pBff) != D3D_OK) {
			PostQuitMessage(0);
			return;
		}
		delete[] pBff;
		SetTexture(_UseNoToonTexPath, 256, 256, &LightEffectTex[0]);
		SetTexture(_UseNoToonTexPath, 256, 256, &LightEffectTex[1]);
		SetTexture(_UseWhiteTexPath, 256, 256, &WhiteTexture);

	}

	///////////////////////////////////////////////////////////////////////////////////

	void SmpXfileDraw(const LpChSmpX _x,const D3DXMATRIX *_Mat, ChEffectType _Type);

	///////////////////////////////////////////////////////////////////////////////////

	~ChShader() { Effect->Release(); }

}ChEffect, *LpChEffect;




#endif
//CopyRight Chronoss0518 2018/08
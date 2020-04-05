#ifndef Ch_D3D9_Li_h
#define Ch_D3D9_Li_h

#include"../../CGameIncludeFile.h"

//Light用定数
const enum{ L_POINT = 1,L_SPOT,L_DIRECTIONAL};

class ChLight 
{
private:
	LPDIRECT3DDEVICE9 Device;
	bool PointFlg;
	bool LightFlg;
	void RegisterLight()
	{
		Device->SetLight(0, &Light);
		Device->LightEnable(0, TRUE);
	}

public:
	D3DLIGHT9 Light;

	ChLight(LPDIRECT3DDEVICE9 _Dv);

	D3DLIGHT9 GetLight(void) { return Light; }


	//Light用定数を用いてセットする
	void SetType(unsigned char _LightTypeNum);

	//Lightを使用するかしないかの設定
	void SetLight(bool Flg) 
	{
		Device->SetRenderState(D3DRS_LIGHTING, Flg); 
		LightFlg = Flg;
	}

	//Lightの位置の設定
	void SetPos(const D3DXVECTOR3 *_Pos)
	{
		Light.Position = *_Pos;
		RegisterLight();
	}

	//Lightの角度の設定
	void SetDir(const D3DXVECTOR3 *_Dir)
	{
		Light.Direction = *_Dir;
		RegisterLight();
	}

	//ライトの効果距離を設定する
	void SetRange(const float _Range)
	{
		Light.Range = _Range;
		RegisterLight();
	}


	//Lightの光源色のセット
	void SetLightDif(const float _a, const float _r, const float _g, const float _b)
	{
		Light.Diffuse.a = _a;
		Light.Diffuse.r = _r;
		Light.Diffuse.g = _g;
		Light.Diffuse.b = _b;
		RegisterLight();
	}

	//Lightの光沢効果のセット
	void SetLightSpe(bool _SpeFlg, const float _r, const float _g, const float _b)
	{
		Device->SetRenderState(D3DRS_SPECULARENABLE, _SpeFlg);
		Light.Specular.r = _r;
		Light.Specular.g = _g;
		Light.Specular.b = _b;
		RegisterLight();
	}

	//Lightの光沢効果のセット
	void SetLightAmb(bool _AmbFlg, const float _r, const float _g, const float _b)
	{
		Device->SetRenderState(D3DRS_AMBIENT, _AmbFlg);
		Light.Ambient.r = _r;
		Light.Ambient.g = _g;
		Light.Ambient.b = _b;
		RegisterLight();
	}

	//変数名最後尾の数字の値が増えれば増えるほど、遠くを映すライトが強くなる
	void SetAtt(const float _Attenuation0, const float _Attenuation1, const float _Attenuation2)
	{
		Light.Attenuation0 = _Attenuation0;
		Light.Attenuation1 = _Attenuation1;
		Light.Attenuation2 = _Attenuation2;
		RegisterLight();
	}

};

#endif
//CopyRight Chronoss0518 2018/08
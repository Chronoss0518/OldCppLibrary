#ifndef Ch_D3D9_DiLi_h
#define Ch_D3D9_DiLi_h

//Light用定数//
const enum{ L_POINT = 1,L_SPOT,L_DIRECTIONAL};

//拡張中//
//標準機能で利用するLightの設定(今後利用する可能性低)//
class ChLight9
{
public:

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestRucter//

	ChLight9(LPDIRECT3DDEVICE9 _Dv);

	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	//Lightを使用するかしないかの設定//
	void SetLight(bool Flg);

	//Lightの角度の設定//
	void SetDir(const ChVec3_9& _Dir);

	//Lightの角度の設定//
	void SetPos(const D3DXVECTOR3 *_Pos);

	//Lightの光源色のセット//
	void SetLightDif(const float _a, const float _r, const float _g, const float _b);

	//Lightの光沢効果のセット//
	void SetLightSpe(bool _SpeFlg, const float _r, const float _g, const float _b);

	//Lightの光沢効果のセット//
	void SetLightAmb(bool _AmbFlg, const float _r, const float _g, const float _b);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	const inline D3DLIGHT9* GetLight(void) { return &Light; }

	///////////////////////////////////////////////////////////////////////////////////

private:

	LPDIRECT3DDEVICE9 Device;

	void RegisterLight();

	D3DLIGHT9 Light;

};

#endif
//CopyRight Chronoss0518 2018/08


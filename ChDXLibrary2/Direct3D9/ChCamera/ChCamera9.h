#ifndef Ch_D3D9_Cam_h
#define Ch_D3D9_Cam_h

namespace ChSystem
{
	class BaseSystem;
}

//(改良中)//
//基本的にView.Projection行列を設定するためのクラス//
class ChCamera9:public ChCpp::ChCp::InitPack
{
public:

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	ChCamera9(const LPDIRECT3DDEVICE9 _Dv,const ChSystem::BaseSystem* _Sys);

	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	//カメラの位置設定//
	void SetCamPos(const D3DXVECTOR3& _CamPos) { CamP = _CamPos; }

	//カメラの見る位置の設定//
	void SetCamLook(const D3DXVECTOR3& _CamLook) { CamL = _CamLook; }

	//データをビュー行列に設定//
	void SetView();

	//描画する最大距離設定//
	void SetLookMaxLen(const float _Len) { LookMaxLen = _Len; }

	//カメラの上方向の向きを出すためのマトリックスの設定//
	void SetCamMat(const ChMatrix_9 *_Mat) { CamHMat = *_Mat; }

	//固定機能描画を行う際の霧効果設定//
	void SetFog(const bool _Flg
		, const float _LookMin
		, const float _LookMax
		, const D3DCOLOR _color);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	//カメラの現在位置取得//
	inline D3DXVECTOR3 GetCamPos() { return CamP; }

	//カメラの見ている位置取得//
	inline D3DXVECTOR3 GetCamLook() { return CamL; }

	///////////////////////////////////////////////////////////////////////////////////

	//カメラの描画するための翡翠台の角度//
	void ZoomUpRadian(const float _UpRad);

	///////////////////////////////////////////////////////////////////////////////////

	//カメラのベースとなる翡翠台の角度に戻す//
	void  ReSetForFalcomDeg() { ForFalcomDeg = StartForFalcomDeg; }


private:

	LPDIRECT3DDEVICE9 Device = nullptr;
	ChSystem::BaseSystem* System = nullptr;
	float LookMaxLen;
	float FogMin, FogMax;
	float ForFalcomDeg = 60;
	float StartForFalcomDeg = 60;
	ChVec3_9 CamH;
	ChVec3_9 CamP, CamL;
	ChMat_9 CamHMat;

};

#endif
//CopyRight Chronoss0518 2018/08
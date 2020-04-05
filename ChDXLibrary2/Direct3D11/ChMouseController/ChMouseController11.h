#ifndef Ch_D3D9_Mou_h
#define Ch_D3D9_Mou_h

namespace ChSystem
{
	class Windows;
}

//マウスを管理するクラス//
//Windowsでのみ機能する//
typedef class ChMouseController9 {
public:

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	ChMouseController9(
		const ChStd::Bool _MouseCamSetFlg
		, const ChSystem::Windows* _Win);

	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	//カーソル画像をセットする関数//
	inline void SetCursorTex(const std::string _TexName) { CursorTexName = _TexName; }

	//カーソルの位置をセットする関数//
	void SetCursolOffsetPos(void);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	//カーソルの動いた量を返す関数//
	void GetMovePos(ChStd::FPOINT *_OutMoveVec);

	//カーソルが3D空間上でどの位置に存在するかをチェックする関数//
	//(未テスト)//
	void GetCamCursorPos(
		const D3DXVECTOR3 *_CamPos
		,const D3DXVECTOR3 *_CamLook
		, D3DXVECTOR3 *_OutVec);

	//カーソル画像を利用する際の値を返す関数//
	inline std::string GetCursorTexNo(){ return CursorTexName; }

	///////////////////////////////////////////////////////////////////////////////////

	//標準のカーソルを見えるようにするかのフラグ//
	inline void ShouFlg(const ChStd::Bool _f) { ShowCursor(_f); }

	///////////////////////////////////////////////////////////////////////////////////

private:
	HWND hWind;
	POINT MouSPos;
	POINT MouNPos;
	ChStd::Bool MouseCamLFlg;
	std::string CursorTexName;

}ChMouCon,*LpMouCon;

#endif
//CopyRight Chronoss0518 2018/08
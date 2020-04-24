#ifndef Ch_D3D9_PB_h
#define Ch_D3D9_PB_h

#include"../../CGameIncludeFile.h"



typedef struct ChVERTEXpctsn{
	D3DXVECTOR3 pos;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
	//D3DCOLOR specular;
	//D3DXVECTOR3 normal;
}ChVertex,*LpChVertex;


typedef class ChPolygonBoard {
private:
	bool AlphaFlg;
	//bool UpDateFlg = NULL;
	static const unsigned char VertexMaxCnt = 4;
	LPDIRECT3DDEVICE9 Device;
public:

	///////////////////////////////////////////////////////////////////////////////////

	ChVertex Ver[VertexMaxCnt];

	///////////////////////////////////////////////////////////////////////////////////

	void SetAlphaFlg(bool _Flg) { AlphaFlg = _Flg; }

	///////////////////////////////////////////////////////////////////////////////////

	//※設定を行わない場合、Defolt値の左上を(1.0f,1.0f,0.0f)を初期値とした2づつずれた向きがXY壁をセットする。
	ChPolygonBoard(LPDIRECT3DDEVICE9 _Dv);

	///////////////////////////////////////////////////////////////////////////////////

	//スペキュラ情報などを含むか含まないか
	//void SetUpDateFlg(const bool _Flg) { UpDateFlg = _Flg; }

	///////////////////////////////////////////////////////////////////////////////////

	//左上のD3DXVECTOR3を取得し、そこからの幅高さを計算し出力してくれる。
	//XY方向の板ポリゴンのポジション指定
	void SetXYPosition(const D3DXVECTOR3 *_LeftTopPos,const float _W,const float _H);

	///////////////////////////////////////////////////////////////////////////////////

	//YZ方向の板ポリゴンのポジション指定
	void SetYZPosition(const D3DXVECTOR3 *_LeftTopPos, const float _W, const float _H);

	///////////////////////////////////////////////////////////////////////////////////

	//ZX方向の板ポリゴンのポジション指定
	void SetZXPosition(const D3DXVECTOR3 *_LeftTopPos, const float _W, const float _H);

	///////////////////////////////////////////////////////////////////////////////////

	//対象のVertexをオリジナルの位置へ持っていくことができる。
	void SetPositionVector(const D3DXVECTOR3 _Pos, const char _PosNo)
	{
		if (_PosNo > VertexMaxCnt)return;
		Ver[_PosNo].pos = _Pos;
	}

	///////////////////////////////////////////////////////////////////////////////////

	//対象のVertexの色情報をセットできる
	void SetColor(const D3DCOLOR _Col, const unsigned char _PosNo) 
	{ 
		if (_PosNo > VertexMaxCnt)return;
		Ver[_PosNo].col = _Col;
	}

	///////////////////////////////////////////////////////////////////////////////////

	//対象のVertexのTexture描画地点(スクリーン座標系)の設定を行うことができる。
	void SetTex(const D3DXVECTOR2 _Tex, const unsigned char _PosNo)
	{
		if (_PosNo > VertexMaxCnt)return;
		Ver[_PosNo].tex = _Tex;
	}

	///////////////////////////////////////////////////////////////////////////////////

	//対象のVerTexの法線をセットできる。
	void SetNormal(const D3DXVECTOR3 _Normal, const char _PosNo)
	{
		if (_PosNo > VertexMaxCnt)return;
		//Ver[_PosNo].normal = _Normal;
	}

	///////////////////////////////////////////////////////////////////////////////////

	void Draw(const LpChTex _Tex, const LPD3DXMATRIX _Mat);

}ChPoBo;




#endif
//CopyRight Chronoss0518 2018/08
#ifndef Ch_D3D9_PB_h
#define Ch_D3D9_PB_h

namespace ChTex
{
	typedef class BaseTexture9 Texture9;

	//板ポリゴン管理用クラス//
	class PolygonBoard9:public ChCp::Initializer
	{
	public:

		//板ポリゴンで利用する頂点情報//
		struct ChVertex9
		{
			ChVec3_9 pos;
			D3DCOLOR col;
			D3DXVECTOR2 tex;
		};

		ChVertex9& operator[](int _size)
		{
			return this->ver[_size];
		}

		ChVertex9 operator[](const int _size)const
		{
			return this->ver[_size];
		}

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(const LPDIRECT3DDEVICE9& _dv);

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//透過させるかさせないかのフラグ//
		void SetAlphaFlg(bool _flg) { alphaFlg = _flg; }

		//スペキュラ情報などを含むか含まないか//
		//void SetUpDateFlg(const bool _Flg) { UpDateFlg = _Flg; }

		//左上のD3DXVECTOR3を取得し、そこからの幅高さを計算し出力してくれる。//
		//XY方向の板ポリゴンのポジション指定//
		void SetXYPosition(const ChVec3_9& _leftTopPos, const float _w, const float _h);

		//YZ方向の板ポリゴンのポジション指定//
		void SetYZPosition(const ChVec3_9& _leftTopPos, const float _w, const float _h);

		//ZX方向の板ポリゴンのポジション指定//
		void SetZXPosition(const ChVec3_9& _leftTopPos, const float _w, const float _h);

		//対象のVertexをオリジナルの位置へ持っていくことができる。//
		void SetPositionVector(const D3DXVECTOR3* _pos, const char _posNo);

		//対象のVertexの色情報をセットできる//
		void SetColor(const D3DCOLOR _col, const unsigned char _posNo);

		//対象のVertexのTexture描画地点(スクリーン座標系)の設定を行うことができる。//
		void SetTex(const D3DXVECTOR2 _tex, const unsigned char _posNo);

		//第二引数には、オリジナルサイズから見たピクセルサイズ。//
		//第三引数には、画像の左上画像位置。//
		void SetRectTex(
			const ChPtr::Shared<BaseTexture9> _tex
			, const RECT& _rect
			, const unsigned char _sPosNo);

		//対象のVerTexの法線をセットできる。//
		//void SetNormal(const D3DXVECTOR3 _Normal, const char _PosNo);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		const inline ChVertex9* GetPosVertex(unsigned char _vertexCnt)
		{
			if (vertexMaxCnt < _vertexCnt)return nullptr;
			return &ver[_vertexCnt];
		}

		///////////////////////////////////////////////////////////////////////////////////

		void Draw(
			const ChPtr::Shared<BaseTexture9>& _Tex
			, const LPD3DXMATRIX& _Mat);

	protected:



		ChStd::Bool alphaFlg;

		static const unsigned char vertexMaxCnt = 4;

		LPDIRECT3DDEVICE9 device;

		union
		{
			struct
			{
				ChVertex9 _1,_2,_3,_4;
			};

			ChVertex9 ver[vertexMaxCnt];

		};

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		//※設定を行わない場合、Defolt値の左上を(1.0f,1.0f,0.0f)//
		//を初期値とした2づつずれた向きがXY壁をセットする。//
		PolygonBoard9() {};


	public:

		inline static PolygonBoard9& GetIns()
		{
			static PolygonBoard9 ins;
			return ins;
		}

	};

	static const std::function<PolygonBoard9&()> PoBo9 = PolygonBoard9::GetIns;

}

#endif
//CopyRight Chronoss0518 2018/08
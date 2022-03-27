#ifndef Ch_D3D9_PB_h
#define Ch_D3D9_PB_h

namespace ChTex
{
	typedef class BaseTexture9 Texture9;

	//板ポリゴン管理用クラス//
	class PolygonBoard9 {
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
			return this->Ver[_size];
		}

		ChVertex9 operator[](const int _size)const
		{
			return this->Ver[_size];
		}

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(const LPDIRECT3DDEVICE9& _Dv);

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//透過させるかさせないかのフラグ//
		void SetAlphaFlg(bool _Flg) { AlphaFlg = _Flg; }

		//スペキュラ情報などを含むか含まないか//
		//void SetUpDateFlg(const bool _Flg) { UpDateFlg = _Flg; }

		//左上のD3DXVECTOR3を取得し、そこからの幅高さを計算し出力してくれる。//
		//XY方向の板ポリゴンのポジション指定//
		void SetXYPosition(const ChVec3_9& _LeftTopPos, const float _W, const float _H);

		//YZ方向の板ポリゴンのポジション指定//
		void SetYZPosition(const ChVec3_9& _LeftTopPos, const float _W, const float _H);

		//ZX方向の板ポリゴンのポジション指定//
		void SetZXPosition(const ChVec3_9& _LeftTopPos, const float _W, const float _H);

		//対象のVertexをオリジナルの位置へ持っていくことができる。//
		void SetPositionVector(const D3DXVECTOR3* _Pos, const char _PosNo);

		//対象のVertexの色情報をセットできる//
		void SetColor(const D3DCOLOR _Col, const unsigned char _PosNo);

		//対象のVertexのTexture描画地点(スクリーン座標系)の設定を行うことができる。//
		void SetTex(const D3DXVECTOR2 _Tex, const unsigned char _PosNo);

		//第二引数には、オリジナルサイズから見たピクセルサイズ。//
		//第三引数には、画像の左上画像位置。//
		void SetRectTex(
			const ChPtr::Shared<BaseTexture9> _Tex
			, const RECT& _rect
			, const unsigned char _SPosNo);

		//対象のVerTexの法線をセットできる。//
		//void SetNormal(const D3DXVECTOR3 _Normal, const char _PosNo);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		const inline ChVertex9* GetPosVertex(unsigned char _VertexCnt)
		{
			if (VertexMaxCnt < _VertexCnt)return nullptr;
			return &Ver[_VertexCnt];
		}

		///////////////////////////////////////////////////////////////////////////////////

		void Draw(
			const ChPtr::Shared<BaseTexture9>& _Tex
			, const LPD3DXMATRIX& _Mat);

	protected:



		ChStd::Bool AlphaFlg;

		static const unsigned char VertexMaxCnt = 4;

		LPDIRECT3DDEVICE9 Device;

		union
		{
			struct
			{
				ChVertex9 _1,_2,_3,_4;
			};

			ChVertex9 Ver[VertexMaxCnt];

		};

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		//※設定を行わない場合、Defolt値の左上を(1.0f,1.0f,0.0f)//
		//を初期値とした2づつずれた向きがXY壁をセットする。//
		PolygonBoard9() {};

		virtual ~PolygonBoard9() { InitFlg = false; }

	private:

		ChStd::Bool InitFlg = false;

	public:

		inline ChStd::Bool IsInit() { return InitFlg; }

		inline static PolygonBoard9& GetIns()
		{
			static PolygonBoard9 Ins;
			return Ins;
		}

	};

	static const std::function<PolygonBoard9&()> PoBo9 = PolygonBoard9::GetIns;

}

#endif
//CopyRight Chronoss0518 2018/08
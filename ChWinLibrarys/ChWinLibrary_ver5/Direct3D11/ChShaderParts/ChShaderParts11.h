#ifndef Ch_D3D11_SParts_h
#define Ch_D3D11_SParts_h

namespace ChD3D11
{
	namespace ShaderParts
	{
		class ViewPort final
		{

		public:

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			inline void SetWindPos(const ChVec2& _Pos) { View.TopLeftX = _Pos.x; View.TopLeftY = _Pos.y; }

			inline void SetWindSize(const ChVec2& _Size) { View.Width = _Size.x; View.Height = _Size.y; }

			inline void SetDrawDepth(const float _Min,const float _Max) { View.MinDepth = _Min; View.MaxDepth = _Max; }

			void SetDrawData(ID3D11DeviceContext* _DC);

			///////////////////////////////////////////////////////////////////////////////////

		private:

			D3D11_VIEWPORT View;

		};

		class DrawWindow final:public ChCp::Initializer
		{

		public:

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			void Init(
				ID3D11Device* _device
				,IDXGISwapChain* _sc);

			void Release();

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetSwapEffect(const DXGI_SWAP_EFFECT& _effect) { sEffect = _effect; }

			void SetDrawData(ID3D11DeviceContext* _dc, ID3D11DepthStencilView* _dsView = nullptr);

			///////////////////////////////////////////////////////////////////////////////////

			void ClearView(ID3D11DeviceContext* _dc,const ChVec4& _color);

			///////////////////////////////////////////////////////////////////////////////////

			void Draw();

			///////////////////////////////////////////////////////////////////////////////////


		private:

			IDXGISwapChain* window = nullptr;

			//描画後にバックバッファを消去する等のフラグメント//
			DXGI_SWAP_EFFECT sEffect = DXGI_SWAP_EFFECT_DISCARD;

			//描画用//
			ID3D11RenderTargetView* bbTargetView = nullptr;
		};

		class ChLightHeader final :public ChCp::Initializer,public ChCp::Releaser
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			//Structures//
			struct DirectionalLight
			{
				ChVec3 dif;
				bool useLightFlg = false;
				ChVec3 dir;
				float ambPow = 0.0f;
			};

			struct PointLight
			{
				ChVec3 pos;
				float len = 10.0f;
				ChVec3 dif;
				bool useFlg = false;
			};

			struct LightData
			{
				ChVec3 camPos;
				DirectionalLight light;
				PointLight pLight[10];
			};

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			void Init(ID3D11Device* _device);

			void Release()override;

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetLightDiffuse(const ChVec3& _dif);

			void SetUseLightFlg(const ChStd::Bool& _flg);

			void SetLightDir(const ChVec3& _dir);

			void SetLightAmbientPow(const float _amb);

			void SetPLightPos(const ChVec3& _pos,const unsigned long _no = 0);

			void SetPLightLen(const float _len, const unsigned long _no = 0);

			void SetPLightDiffuse(const ChVec3& _dif, const unsigned long _no = 0);

			void SetPLightUseFlg(const ChStd::Bool& _flg, const unsigned long _no = 0);

			void SetCamPos(const ChVec3& _camPos);

			void SetLightData(const LightData& _ld);

			void SetPSDrawData(ID3D11DeviceContext* _dc);

			void SetVSDrawData(ID3D11DeviceContext* _dc);

			void SetDrawData(ID3D11DeviceContext* _dc);

			void SetImportLightPowMap(ChPtr::Shared<Texture11>& _lightPowMap);

			///////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			LightData GetLightData();

			///////////////////////////////////////////////////////////////////////////////////

			void ClearImportLightPowMap();

		private:

			void SetTexture(ID3D11DeviceContext* _dc);

			void Update(ID3D11DeviceContext* _dc);

			struct UseLightData
			{
				ChVec3 camPos;
				int pLightCount = 10;
				DirectionalLight light;
				PointLight pLight[10];
			};

			UseLightData lightDatas;
			ID3D11Device* device = nullptr;
			ConstantBuffer buf = nullptr;
			ChStd::Bool updateFlg = true;

			Texture11 lightPow;
			ChPtr::Shared<Texture11>importLightPowMap;
		};

	}

}


#endif

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

		class DrawWindow final:public ChCpp::ChCp::Initializer
		{

		public:

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			void Init(
				ID3D11Device* _Device
				,IDXGISwapChain* _SC);

			void Release();

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetSwapEffect(const DXGI_SWAP_EFFECT& _Effect) { SEffect = _Effect; }

			void SetDrawData(ID3D11DeviceContext* _DC, ID3D11DepthStencilView* _DSView = nullptr);

			///////////////////////////////////////////////////////////////////////////////////

			void ClearView(ID3D11DeviceContext* _DC,const ChVec4& _Color);

			///////////////////////////////////////////////////////////////////////////////////

			void Draw();

			///////////////////////////////////////////////////////////////////////////////////


		private:

			IDXGISwapChain* Window = nullptr;

			//描画後にバックバッファを消去する等のフラグメント//
			DXGI_SWAP_EFFECT SEffect = DXGI_SWAP_EFFECT_DISCARD;

			//描画用//
			ID3D11RenderTargetView* BBTargetView = nullptr;
		};

	}

}


#endif

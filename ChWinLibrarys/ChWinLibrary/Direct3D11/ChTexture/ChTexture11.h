#ifndef Ch_D3D11_Tex_h
#define Ch_D3D11_Tex_h

namespace ChD3D11
{

	class Texture11:public ChCpp::ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		Texture11(){}

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////////
		//CreateFunction//

		void CreateTexture(
			const std::string& _TexPath
			, ID3D11Device* _Device);

		void CreateTexture(const std::string& _TexPath);

		void CreateTexture(
			const std::wstring& _TexPath
			, ID3D11Device* _Device);

		void CreateTexture(const std::wstring& _TexPath);

		void CreateColorTexture(
			ID3D11Device* _Device
			, const ChVec4& _Color
			, const unsigned long _Width
			, const unsigned long _Height
			, const unsigned int _CPUFlg = 0);

		void CreateColorTexture(
			const ChVec4& _Color
			, const unsigned long _Width
			, const unsigned long _Height
			, const unsigned int _CPUFlg = 0);

		void CreateColorTexture(
			ID3D11Device* _Device
			, const ChVec4* _ColorArray
			, const unsigned long _Width
			, const unsigned long _Height
			, const unsigned int _CPUFlg = 0);

		void CreateColorTexture(
			const ChVec4* _ColorArray
			, const unsigned long _Width
			, const unsigned long _Height
			, const unsigned int _CPUFlg = 0);

		void CreateRenderTarget(
			ID3D11Device* _Device
			, IDXGISwapChain* _SC
			, const unsigned long _Width
			, const unsigned long _Height
			, const unsigned int _CPUFlg = 0);

		void CreateRenderTarget(
			const unsigned long _Width
			, const unsigned long _Height
			, const unsigned int _CPUFlg = 0);

		void CreateDepthBuffer(
			ID3D11Device* _Device
			, const float& _Width
			, const float& _Height
			, const unsigned int _CPUFlg = 0);

		void CreateDepthBuffer(
			const float& _Width
			, const float& _Height
			, const unsigned int _CPUFlg = 0);

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetSampler(D3D11_SAMPLER_DESC& _SDesc)
		{
			SDesc = _SDesc;
			SDUpdateFlg = true;
		}

		void SetDrawData(ID3D11DeviceContext* _DC, unsigned int _TextureNo);

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		ID3D11ShaderResourceView*  GetSRView()
		{
			return TexView;
		}

		ID3D11RenderTargetView* GetRTView()
		{
			return RTView;
		}

		ID3D11DepthStencilView* GetDSView()
		{
			return DSView;
		}

		ID3D11Resource* GetTex()
		{
			return BaseTex;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		ChStd::Bool IsTex() { return ChPtr::NotNullCheck(BaseTex); }

		///////////////////////////////////////////////////////////////////////////////////////

		void ClearBackBuffer(ID3D11DeviceContext* _DC, const ChVec4& _BuckColor);

		void ClearDepthBuffer(
			ID3D11DeviceContext* _DC
			, const UINT _Flgment = D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL);

		///////////////////////////////////////////////////////////////////////////////////////

	protected:

		void Init(ID3D11Device* _Device);

		void CreateSRV();

		void InitSampler();

		void UpdateSampler();

		ChVec4 GetBitColor(
			const unsigned int _Width
			, const unsigned int _Height);

		D3D11_SAMPLER_DESC SDesc;
		ChStd::Bool SDUpdateFlg = true;
		ID3D11SamplerState* Sampler = nullptr;

		ID3D11ShaderResourceView* TexView = nullptr;
		ID3D11RenderTargetView* RTView = nullptr;
		ID3D11DepthStencilView* DSView = nullptr;

		ID3D11Texture2D* BaseTex = nullptr;
		ChVec4* PixellData = nullptr;
		unsigned long TextureSize = 0;

		ID3D11Device* Device = nullptr;

		private:

	};

}
#endif

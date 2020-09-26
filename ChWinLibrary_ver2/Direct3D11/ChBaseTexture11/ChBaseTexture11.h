#ifndef Ch_D3D11_Tex_h
#define Ch_D3D11_Tex_h

namespace ChTex
{

	class ChBaseTexture11
	{
	public:
		
		void Init(const std::string& _TexPath, ID3D11Device* _Device);

	protected:

		ChStd::COLOR1f GetBitColor(
			const unsigned int _Width
			, const unsigned int _Height);


		ID3D11ShaderResourceView* BaseTex = nullptr;

		//“o˜^—pD3D11Device//
		ID3D11Device* Device = nullptr;

	};

}
#endif

#ifndef Ch_D3D11_Tex_h
#define Ch_D3D11_Tex_h

namespace ChD3D11
{

	class Texture11
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void CreateTexture(const std::string& _TexPath, ID3D11Device* _Device);

		void CreateTexture(const std::string& _TexPath);

		void CreateTexture(const std::wstring& _TexPath, ID3D11Device* _Device);

		void CreateTexture(const std::wstring& _TexPath);

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		ChStd::Bool IsTex() { return ChPtr::NotNullCheck(BaseTex); }

	protected:

		ChStd::COLOR1f GetBitColor(
			const unsigned int _Width
			, const unsigned int _Height);


		ID3D11ShaderResourceView* TexView = nullptr;

		ID3D11Resource* BaseTex = nullptr;

	};

}
#endif

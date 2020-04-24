#ifndef Ch_D3D9_StCo_h
#define Ch_D3D9_StCo_h

//(改良中)(使用不可)//
//その場で文字列用テクスチャを生成、ベースとなるテクスチャを用意する必要がある//
//あるフォルダに置かれた一文字づつの画像を操作するコントローラー。//
//始めにその画像群の置かれたディレクトリパスを入力する。//
//画像サイズは統一する。//

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	typedef class StringController9
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDextructer//

		StringController9(
			const LPDIRECT3DDEVICE9 _Dv
			, const std::string& _Path
			, const std::string& _Type
			, const unsigned short _OriginalWedth
			, const unsigned short _OriginalHeight);

		~StringController9() {};

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetStringColor(const ChStd::COLOR255& _Color);

		void SetStringAlpha(const unsigned char _a);

		///////////////////////////////////////////////////////////////////////////////////

		void DrawSprightString(
			const std::string& _Str
			, const ChMat_9& _Mat
			, Sprite9 &_Sp);

		///////////////////////////////////////////////////////////////////////////////////

	private:
		std::string StrPath;
		std::string TypeName;
		unsigned short W;
		unsigned short H;
		ChPtr::Shared<Texture9> StrTex;
		LPDIRECT3DDEVICE9 Device = nullptr;

		///////////////////////////////////////////////////////////////////////////////////

		void SetStrTexture(const std::string& _Str);
		
		///////////////////////////////////////////////////////////////////////////////////


	}StrCon;
}


#endif
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

	typedef class StringController9:public ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDextructer//

		StringController9(
			const LPDIRECT3DDEVICE9 _dv
			, const std::string& _path
			, const std::string& _type
			, const unsigned short _originalWedth
			, const unsigned short _originalHeight);

		~StringController9() { SetInitFlg(false); };

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetStringColor(const ChVec4& _color);

		void SetStringAlpha(const unsigned char _a);

		///////////////////////////////////////////////////////////////////////////////////

		void DrawSprightString(
			const std::string& _str
			, const ChMat_9& _mat
			, Sprite9 &_sp);

		///////////////////////////////////////////////////////////////////////////////////

	private:
		std::string strPath;
		std::string typeName;
		
		ChMath::Vector2Base<unsigned short>size;

		ChPtr::Shared<Texture9> strTex;
		LPDIRECT3DDEVICE9 device = nullptr;

		///////////////////////////////////////////////////////////////////////////////////

		void SetStrTexture(const std::string& _Str);
		
		///////////////////////////////////////////////////////////////////////////////////


	}StrCon;
}


#endif
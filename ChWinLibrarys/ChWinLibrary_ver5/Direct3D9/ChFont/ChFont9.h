#ifndef Ch_D3D9_Fo_h
#define Ch_D3D9_Fo_h

namespace ChD3D9
{

	//�W���@�\�ŕ`�悳���t�H���g�N���X//
	class DrawFont:public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(const LPDIRECT3DDEVICE9 _dv);

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�`�悷��ۂ̃t�H���g�T�C�Y//
		inline void SetFontSize(const unsigned long _W, const unsigned long _H) {
			
			fontSize.w = _W;
			fontSize.h = _H;
			Release();
			Init(device);
		}

		///////////////////////////////////////////////////////////////////////////////////

		//�t�H���g�̕`��//
		void Draw(
			std::string _drawStr
			, const long _x
			, const long y
			, ChVec4 _col = ChVec4(1.0f,1.0f,1.0f,1.0f));

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		DrawFont() {}


		LPD3DXFONT lpFont;
		LPDIRECT3DDEVICE9 device;
		const long startSize = 90;

		ChMath::Vector2Base<long>fontSize;

		ChVec4 fontColor = { 1.0f,1.0f,1.0f,1.0f };
		std::string fontType;

	public:

		static DrawFont& GetIns()
		{
			static DrawFont ins;
			return ins;
		}
	};

	static const std::function<DrawFont&()>Font = DrawFont::GetIns;

}

#endif
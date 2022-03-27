#ifdef _WINDOWS_

#ifndef Ch_Win_DTexter_h
#define Ch_Win_DTexter_h

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{
	class DrawTexter:public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(const HWND& _baseWindHandl);

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//
		
		inline void SetWind(const HWND& _wind)
		{
			if (ChPtr::NullCheck(_wind))return;
			hOwn = _wind;

			InvalidateRect(hOwn, nullptr, true);
			UpdateWindow(hOwn);

		}

		void SetFontData(
			const long& _FWidth
			, const long& _FHeight
			, const long& _FSize
			, const ChStd::Bool& _ULFlg);

		//ï`âÊÇ∑ÇÈï∂éöóÒÇÃêFê›íË//
		inline void SetTexColor(const ChMath::Vector4Base<unsigned char>& _color)
		{
			fontColor.a = _color.a * 255;
			fontColor.r = _color.r * 255;
			fontColor.g = _color.g * 255;
			fontColor.b = _color.b * 255;
		}

		//ï`âÊÇ∑ÇÈï∂éöóÒÇÃîwåiêFê›íË//
		inline void SetTexBackColor(const ChMath::Vector4Base<unsigned char>& _color)
		{
			backColor.a = _color.a * 255;
			backColor.r = _color.r * 255;
			backColor.g = _color.g * 255;
			backColor.b = _color.b * 255;
		}

		///////////////////////////////////////////////////////////////////////////////////////

		void Draw(
			const std::string&_drawText
			, const long& _x
			, const long& _y);

	private:


		///////////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		inline DrawTexter(){}


		HWND hOwn = nullptr;

		HFONT fontData = nullptr;

		ChMath::Vector4Base<unsigned char> fontColor;
		ChMath::Vector4Base<unsigned char> backColor;

	public:

		static inline DrawTexter& GetIns()
		{
			static DrawTexter ins;
			return ins;
		}

	};

	static const std::function<DrawTexter&()>TextDraw = DrawTexter::GetIns;
}

#endif

#endif
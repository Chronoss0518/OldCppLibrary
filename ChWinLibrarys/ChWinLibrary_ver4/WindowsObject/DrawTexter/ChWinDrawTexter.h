#ifdef _WINDOWS_

#ifndef Ch_Win_DTexter_h
#define Ch_Win_DTexter_h

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{
	class DrawTexter:public ChCpp::ChCp::Initializer,public ChCpp::ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(const HWND& _BaseWindHandl);

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//
		
		inline void SetWind(const HWND& _Wind)
		{
			if (ChPtr::NullCheck(_Wind))return;
			HOwn = _Wind;

			InvalidateRect(HOwn, nullptr, true);
			UpdateWindow(HOwn);

		}

		void SetFontData(
			const long& _FWidth
			, const long& _FHeight
			, const long& _FSize
			, const ChStd::Bool& _ULFlg);

		//ï`âÊÇ∑ÇÈï∂éöóÒÇÃêFê›íË//
		inline void SetTexColor(const ChVec4& _Color)
		{
			FontColor = _Color * 256;
		}

		//ï`âÊÇ∑ÇÈï∂éöóÒÇÃîwåiêFê›íË//
		inline void SetTexBackColor(const ChVec4& _Color)
		{
			BackColor = _Color * 256;
		}

		///////////////////////////////////////////////////////////////////////////////////////

		void Draw(
			const std::string&_DrawText
			, const long& _x
			, const long& _y);

	private:


		///////////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		inline DrawTexter(){}


		HWND HOwn = nullptr;

		HFONT FontData = nullptr;

		ChVec4 FontColor;
		ChVec4 BackColor;

	public:

		static inline DrawTexter& GetIns()
		{
			static DrawTexter Ins;
			return Ins;
		}

	};

	static const std::function<DrawTexter&()>TextDraw = DrawTexter::GetIns;
}

#endif

#endif
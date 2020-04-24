#ifdef _WINDOWS_

#ifndef Ch_Win_DTexter_h
#define Ch_Win_DTexter_h

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{
	class DrawTexter:public ChCpp::ChCp::InitPack
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(const HWND& _BaseWindHandl);

		void Release();

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
		inline void SetTexColor(const ChStd::COLOR255& _Color)
		{
			FontColor = _Color;
		}

		//ï`âÊÇ∑ÇÈï∂éöóÒÇÃîwåiêFê›íË//
		inline void SetTexBackColor(const ChStd::COLOR255& _Color)
		{
			BackColor = _Color;
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

		inline ~DrawTexter()
		{
			Release();
		}

		HWND HOwn = nullptr;

		HFONT FontData;

		ChStd::COLOR255 FontColor;
		ChStd::COLOR255 BackColor;

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
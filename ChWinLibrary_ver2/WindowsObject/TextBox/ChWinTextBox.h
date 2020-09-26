#ifdef _WINDOWS_

#ifndef Ch_Win_TextBox_h
#define Ch_Win_TextBox_h

#include"../BaseWind/ChWinBaseWind.h"

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{

	class TextBox :public WindObject
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//TextBox‚©‚çText‚Ìo—Í//
		std::string GetText();

		//TextBox‚Ö“ü—Í‚Å‚«‚é•¶š”‚Ì§ŒÀ//
		inline unsigned long GetCharLimit()
		{
			return CharLimit;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//TextBox‚ÖText‚Ì“ü—Í//
		void SetText(const std::string& _Text);

		//TextBox‚Ö“ü—Í‚Å‚«‚é•¶š”‚Ì§ŒÀ//
		void SetCharLimit(const unsigned long _Size);

		void Update(const WPARAM& _wParam)override;

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		inline ChStd::Bool IsSelect() { return SelectFlg; }

		///////////////////////////////////////////////////////////////////////////////////////

		//TextBox‚Ìì¬//
		void Create(
			const std::string& _StartText
			, const int _x
			, const int _y
			, const int _w
			, const int _h
			, const HWND _ParentHandl = nullptr);

	private:

		unsigned long CharLimit = 50;

		ChStd::Bool SelectFlg = false;



	};

}


#endif

#endif

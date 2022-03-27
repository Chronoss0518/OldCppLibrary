#ifdef _WINDOWS_

#ifndef Ch_Win_TextBox_h
#define Ch_Win_TextBox_h

#ifndef Ch_Win_BObj_h
#include"../BaseWind/ChWinBaseWind.h"
#endif

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

		//TextBox����Text�̏o��//
		std::string GetText();

		//TextBox�֓��͂ł��镶�����̐���//
		inline unsigned long GetCharLimit()
		{
			return charLimit;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//TextBox��Text�̓���//
		void SetText(const std::string& _text);

		//TextBox�֓��͂ł��镶�����̐���//
		void SetCharLimit(const unsigned long _size);

		void Update(const WPARAM& _wParam)override;

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		inline ChStd::Bool IsSelect() { return selectFlg; }

		///////////////////////////////////////////////////////////////////////////////////////

		//TextBox�̍쐬//
		void Create(
			const std::string& _startText
			, const int _x
			, const int _y
			, const int _w
			, const int _h
			, const HWND _parentHandl = nullptr);

	private:

		unsigned long charLimit = 50;

		ChStd::Bool selectFlg = false;



	};

}


#endif

#endif

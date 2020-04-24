#ifdef _WINDOWS_

#ifndef Ch_Win_TextBox_h
#define Ch_Win_TextBox_h

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
			return CharLimit;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//TextBox��Text�̓���//
		void SetText(const std::string& _Text);

		//TextBox�֓��͂ł��镶�����̐���//
		void SetCharLimit(const unsigned long _Size);

		///////////////////////////////////////////////////////////////////////////////////////

		//TextBox�̍쐬//
		void Create(
			const std::string& _StartText
			, const int _x
			, const int _y
			, const int _w
			, const int _h
			, const HWND _ParentHandl = nullptr);

	private:

		unsigned long CharLimit = 50;

	};

}


#endif

#endif

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

		//TextBoxからTextの出力//
		std::string GetText();

		//TextBoxへ入力できる文字数の制限//
		inline unsigned long GetCharLimit()
		{
			return CharLimit;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//TextBoxへTextの入力//
		void SetText(const std::string& _Text);

		//TextBoxへ入力できる文字数の制限//
		void SetCharLimit(const unsigned long _Size);

		///////////////////////////////////////////////////////////////////////////////////////

		//TextBoxの作成//
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

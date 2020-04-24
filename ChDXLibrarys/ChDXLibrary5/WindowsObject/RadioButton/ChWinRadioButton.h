#ifdef _WINDOWS_

#ifndef Ch_Win_RdBu_h
#define Ch_Win_RdBu_h

#include"../BaseWind/ChWinBaseWind.h"

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{

	class RadioButton :public WindObject
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////

		void Create(
			const std::string& _ButtonText
			, const int _x
			, const int _y
			, const int _w
			, const int _h
			, const HWND _ParentHandl = nullptr
			, const ChStd::Bool _GlpFlg = false);

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		ChStd::Bool IsSelection()
		{
			return (SendMessage(HIns, BM_GETCHECK, 0, 0) == BST_CHECKED);
		}

		///////////////////////////////////////////////////////////////////////////////////////

	protected:




	};

}

#endif

#endif
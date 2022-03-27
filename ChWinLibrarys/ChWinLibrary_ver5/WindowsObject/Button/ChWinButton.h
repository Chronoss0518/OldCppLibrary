#ifdef _WINDOWS_

#ifndef Ch_Win_BuOb_h
#define Ch_Win_BuOb_h

#include"../BaseWind/ChWinBaseWind.h"

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{

	class BaseButton :public WindObject
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////

		void Create(
			const std::string& _ButtonText
			, const int _x
			, const int _y
			, const int _w
			, const int _h
			, const HWND _parentHandl = nullptr
			, const std::function<void()> _callBack = nullptr);

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetFunction(const std::function<void()> _callBack);

		///////////////////////////////////////////////////////////////////////////////////////

		void Update(const WPARAM& _wParam)override;

	protected:

		std::function<void()>Function;


	};

}

#endif

#endif
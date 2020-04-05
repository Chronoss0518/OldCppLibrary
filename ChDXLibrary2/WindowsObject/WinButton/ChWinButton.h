#ifdef _WINDOWS_

#ifndef Ch_Win_BuOb_h
#define Ch_Win_BuOb_h

#include"../WinBaseWind/ChWinBaseWind.h"

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
		//ConstructerDestructer//

		BaseButton(const HWND& _WindHndl) { Init(_WindHndl); };

		///////////////////////////////////////////////////////////////////////////////////////

		void Create(
			const std::string& _ButtonText
			, const int _x
			, const int _y
			, const int _w
			, const int _h
			, const std::function<void()> _CallBack = nullptr);

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetFunction(const std::function<void()> _CallBack);

		///////////////////////////////////////////////////////////////////////////////////////

		void Update()override;

	protected:

		std::function<void()>Function;


	};

}

#endif

#endif
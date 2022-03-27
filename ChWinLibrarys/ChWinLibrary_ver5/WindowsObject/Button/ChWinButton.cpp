#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"ChWinButton.h"

///////////////////////////////////////////////////////////////////////////////////////
//BaseButtonÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::BaseButton::Create(const std::string& _buttonText
	, const int _x
	, const int _y
	, const int _w
	, const int _h
	, const HWND _parentHandl
	, const std::function<void()> _callBack)
{
	if (!IsInit())return;

	Release();

	x = _x;
	y = _y;
	w = _w;
	h = _h;

	RegisterObj();

	hIns = CreateWindow(
		"BUTTON",  // Predefined class; Unicode assumed 
		_buttonText.c_str(),      // Button text 
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_CLIPCHILDREN,  // Styles 
		_x,         // x position 
		_y,         // y position 
		_w,        // Button width
		_h,        // Button height
		_parentHandl,     // Parent window
		(HMENU)myID,       // No menu.
		(HINSTANCE)GetWindowLong(hOwn, GWL_HINSTANCE),
		NULL);      // Pointer not needed.


	Function = _callBack;
	RedrawWindow(hOwn, nullptr, nullptr, true);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::BaseButton::SetFunction(const std::function<void()> _callBack)
{
	Function = _callBack;
}

void ChWin::BaseButton::Update(const WPARAM& _wParam)
{
	if (Function == nullptr)return;
	Function();
}


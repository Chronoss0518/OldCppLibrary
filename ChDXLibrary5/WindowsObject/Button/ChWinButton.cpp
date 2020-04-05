#include<Windows.h>
#include"../../ChInclude/ChGameBI.h"
#include"ChWinButton.h"

///////////////////////////////////////////////////////////////////////////////////////
//BaseButtonÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::BaseButton::Create(const std::string& _ButtonText
	, const int _x
	, const int _y
	, const int _w
	, const int _h
	, const HWND _ParentHandl
	, const std::function<void()> _CallBack)
{
	if (!IsInit())return;

	Release();

	x = _x;
	y = _y;
	w = _w;
	h = _h;

	RegisterObj();

	HIns = CreateWindow(
		"BUTTON",  // Predefined class; Unicode assumed 
		_ButtonText.c_str(),      // Button text 
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_CLIPCHILDREN,  // Styles 
		_x,         // x position 
		_y,         // y position 
		_w,        // Button width
		_h,        // Button height
		_ParentHandl,     // Parent window
		(HMENU)MyID,       // No menu.
		(HINSTANCE)GetWindowLong(HOwn, GWL_HINSTANCE),
		NULL);      // Pointer not needed.


	Function = _CallBack;
	RedrawWindow(HOwn, nullptr, nullptr, true);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::BaseButton::SetFunction(const std::function<void()> _CallBack)
{
	Function = _CallBack;
}

void ChWin::BaseButton::Update(const WPARAM& _wParam)
{

	if (Function == nullptr)return;
	Function();
}


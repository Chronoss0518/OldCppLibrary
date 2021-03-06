#include<Windows.h>
#include"../../ChGameIncludeFile.h"
#include"ChWinButton.h"

///////////////////////////////////////////////////////////////////////////////////////
//BaseButton???\?b?h//
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::BaseButton::Create(const std::string& _ButtonText
	, const int _x
	, const int _y
	, const int _w
	, const int _h
	, const std::function<void()> _CallBack)
{
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
		HOwn,     // Parent window
		(HMENU)MyID,       // No menu.
		(HINSTANCE)GetWindowLong(HOwn, GWL_HINSTANCE),
		NULL);      // Pointer not needed.


	Function = _CallBack;


}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::BaseButton::SetFunction(const std::function<void()> _CallBack)
{
	Function = _CallBack;
}

void ChWin::BaseButton::Update()
{

	if (Function == nullptr)return;
	Function();
}


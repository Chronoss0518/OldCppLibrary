
#include<Windows.h>
#include"../../ChInclude/ChGameBI.h"
#include"ChWinRadioButton.h"


///////////////////////////////////////////////////////////////////////////////////////
//RadioButtonÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::RadioButton::Create(const std::string& _ButtonText
	, const int _x
	, const int _y
	, const int _w
	, const int _h
	, const HWND _ParentHandl
	, const ChStd::Bool _GlpFlg)
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
		WS_VISIBLE
		| WS_CHILD
		| (_GlpFlg ? 0 : WS_GROUP)
		| BS_AUTORADIOBUTTON
		| WS_CLIPCHILDREN,  // Styles 
		_x,         // x position 
		_y,         // y position 
		_w,        // Button width
		_h,        // Button height
		_ParentHandl,     // Parent window
		(HMENU)MyID,       // No menu.
		(HINSTANCE)GetWindowLong(HOwn, GWL_HINSTANCE),
		NULL);      // Pointer not needed.


	RedrawWindow(HOwn, nullptr, nullptr, NULL);

}

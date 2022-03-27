#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"ChWinTextBox.h"


///////////////////////////////////////////////////////////////////////////////////////
//TextBoxÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::TextBox::Create(
	const std::string&  _startText
	, const int _x
	, const int _y
	, const int _w
	, const int _h
	, const HWND _parentHandl)
{

	if (!IsInit())return;
	RegisterObj();
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	
	hIns = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"EDIT",
		_startText.c_str(),
		WS_VISIBLE
		| WS_CHILD
		| WS_BORDER
		| ES_LEFT
		| WS_GROUP,
		_x,
		_y,
		_w,
		_h,
		_parentHandl,
		(HMENU)myID,
		(HINSTANCE)GetWindowLong(hOwn, GWL_HINSTANCE),
		NULL);

	
	//RegisterObj();
	SetWindowLong(hIns, GWLP_USERDATA, (long)this);

}

///////////////////////////////////////////////////////////////////////////////////////

std::string ChWin::TextBox::GetText()
{
	std::string Text = "";

	if (selectFlg)return Text;
	char tmp[1500] = "\0";

	SendMessage(hIns, WM_GETTEXT, (WPARAM)1500, (LPARAM)tmp);

	Text = tmp;

	return Text;

}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::TextBox::SetText(const std::string& _text)
{

	if (selectFlg)return;
	SendMessage(hIns, WM_SETTEXT, (WPARAM)_text.size(), (LPARAM)_text.c_str());

}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::TextBox::SetCharLimit(const unsigned long _size)
{
	if (selectFlg)return;
	SendMessage(hIns, EM_SETLIMITTEXT, (WPARAM)_size, NULL);
	charLimit = _size;

}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::TextBox::Update(const WPARAM& _wParam)
{
	switch (HIWORD(_wParam))
	{
	case EN_KILLFOCUS:
		selectFlg = false;
		break;
	case EN_SETFOCUS:
		selectFlg = true;
		break;
	default:
		//SendMessage(HIns, WM_PAINT, NULL, NULL);

		break;
	}
}

#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"ChWinTextBox.h"


///////////////////////////////////////////////////////////////////////////////////////
//TextBoxÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::TextBox::Create(
	const std::string&  _StartText
	, const int _x
	, const int _y
	, const int _w
	, const int _h
	, const HWND _ParentHandl)
{

	if (!IsInit())return;
	RegisterObj();
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	
	HIns = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"EDIT",
		_StartText.c_str(),
		WS_VISIBLE
		| WS_CHILD
		| WS_BORDER
		| ES_LEFT
		| WS_GROUP,
		_x,
		_y,
		_w,
		_h,
		_ParentHandl,
		(HMENU)MyID,       
		(HINSTANCE)GetWindowLong(HOwn, GWL_HINSTANCE),
		NULL);

	
	//RegisterObj();
	SetWindowLong(HIns, GWLP_USERDATA, (long)this);

}

///////////////////////////////////////////////////////////////////////////////////////

std::string ChWin::TextBox::GetText()
{
	std::string Text = "";

	if (SelectFlg)return Text;
	char Tmp[1500];

	SendMessage(HIns, WM_GETTEXT, (WPARAM)1500, (LPARAM)Tmp);

	Text = Tmp;

	return Text;

}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::TextBox::SetText(const std::string& _Text)
{

	if (SelectFlg)return;
	SendMessage(HIns, WM_SETTEXT, (WPARAM)_Text.size(), (LPARAM)_Text.c_str());

}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::TextBox::SetCharLimit(const unsigned long _Size)
{
	if (SelectFlg)return;
	SendMessage(HIns, EM_SETLIMITTEXT, (WPARAM)_Size, NULL);
	CharLimit = _Size;

}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::TextBox::Update(const WPARAM& _wParam)
{
	switch (HIWORD(_wParam))
	{
	case EN_KILLFOCUS:
		SelectFlg = false;
		break;
	case EN_SETFOCUS:
		SelectFlg = true;
		break;
	default:
		//SendMessage(HIns, WM_PAINT, NULL, NULL);

		break;
	}
}

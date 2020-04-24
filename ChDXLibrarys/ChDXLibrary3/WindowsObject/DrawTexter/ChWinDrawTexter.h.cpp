#include<Windows.h>
#include"../../ChGameIncludeFile.h"
#include"ChWinDrawTexter.h"


///////////////////////////////////////////////////////////////////////////////////////
//DrawTexterÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::DrawTexter::Init(const HWND& _BaseWindHandl)
{
	if (*this)return;
	if (ChPtr::NullCheck(_BaseWindHandl))return;

	SetWind(_BaseWindHandl);

	FontData = CreateFont(
		16
		, 8
		, 0
		, 0
		, 2
		, false
		, false
		, false
		, SHIFTJIS_CHARSET
		, OUT_DEFAULT_PRECIS
		, CLIP_DEFAULT_PRECIS
		, DEFAULT_PITCH
		, FF_DONTCARE
		, NULL);

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::DrawTexter::Release()
{
	if (!*this)return;

	DeleteObject(FontData);

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::DrawTexter::SetFontData(
	const long& _FWidth
	, const long& _FHeight
	, const long& _FSize
	, const ChStd::Bool& _ULFlg)
{

	DeleteObject(FontData);

	FontData = CreateFont(
		_FWidth
		, _FHeight
		, 0
		, 0
		, _FSize
		, false
		, _ULFlg
		, false
		, SHIFTJIS_CHARSET
		, OUT_DEFAULT_PRECIS
		, CLIP_DEFAULT_PRECIS
		, DEFAULT_PITCH
		, FF_DONTCARE
		, NULL);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::DrawTexter::Draw(
	const std::string&_DrawText
	, const long& _x
	, const long& _y)
{

	HDC TmpDC;
	TmpDC = GetDC(HOwn);

	SelectObject(TmpDC, FontData);
	SetTextColor(TmpDC, RGB(FontColor.r, FontColor.g, FontColor.b));

	if (BackColor.a <= 0)
	{
		SetBkMode(TmpDC, TRANSPARENT);
	}
	else
	{
		SetBkColor(TmpDC, RGB(BackColor.r, BackColor.g, BackColor.b));
	}

	TextOut(TmpDC, _x, _y, _DrawText.c_str(),_DrawText.size() + 1);

	DeleteDC(TmpDC);

}

///////////////////////////////////////////////////////////////////////////////////////

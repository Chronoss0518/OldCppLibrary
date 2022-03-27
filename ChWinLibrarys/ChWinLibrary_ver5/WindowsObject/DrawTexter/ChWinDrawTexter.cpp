#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"ChWinDrawTexter.h"


///////////////////////////////////////////////////////////////////////////////////////
//DrawTexterÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::DrawTexter::Init(const HWND& _baseWindHandl)
{
	if (*this)return;
	if (ChPtr::NullCheck(_baseWindHandl))return;

	SetWind(_baseWindHandl);

	fontData = CreateFont(
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

	DeleteObject(fontData);

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::DrawTexter::SetFontData(
	const long& _fWidth
	, const long& _fHeight
	, const long& _fSize
	, const ChStd::Bool& _ulFlg)
{

	DeleteObject(fontData);

	fontData = CreateFont(
		_fWidth
		, _fHeight
		, 0
		, 0
		, _fSize
		, false
		, _ulFlg
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
	const std::string&_drawText
	, const long& _x
	, const long& _y)
{
	return;
	HDC tmpDC;
	tmpDC = GetDC(hOwn);

	SelectObject(tmpDC, fontData);
	SetTextColor(tmpDC, RGB(fontColor.r, fontColor.g, fontColor.b));

	if (backColor.a <= 0)
	{
		SetBkMode(tmpDC, TRANSPARENT);
	}
	else
	{
		SetBkColor(tmpDC, RGB(backColor.r, backColor.g, backColor.b));
	}

	TextOut(tmpDC, _x, _y, _drawText.c_str(), _drawText.size() + 1);

	DeleteDC(tmpDC);

}

///////////////////////////////////////////////////////////////////////////////////////

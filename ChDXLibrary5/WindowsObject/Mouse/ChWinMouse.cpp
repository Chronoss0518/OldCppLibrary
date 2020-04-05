
#include<Windows.h>
#include"../../ChInclude/ChGameBI.h"
#include"../../CPP/ChBitBool/ChBitBool.h"
#include"../../ChBaseSystem/ChWindows/ChWindows.h"
#include"ChWinMouse.h"

///////////////////////////////////////////////////////////////////////////////////
//MouseControllerÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////

void ChWin::MouseController::Init(
	const HWND& _hWnd
	, const unsigned long _WindWidth
	, const unsigned long _WindHeight)
{
	if (ChPtr::NullCheck(_hWnd))return;

	hWnd = _hWnd;

	WindWidth = _WindWidth;
	WindHeight = _WindHeight;

	CenterPos.x = _WindWidth / 2;
	CenterPos.y = _WindHeight / 2;

	ClientToScreen(_hWnd, &CenterPos);

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ChWin::MouseController::Init(const ChSystem::Windows& _Win)
{
	Init(_Win.GethWnd(), _Win.GetWindWidth(), _Win.GetWindHeight());
}

///////////////////////////////////////////////////////////////////////////////////

void ChWin::MouseController::Release()
{
	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

ChVec2 ChWin::MouseController::GetNowPosToChVec2()
{
	if (!*this)return { 0.0f,0.0f };

	ChVec2 TmpVec;
	TmpVec.x = static_cast<float>(NowPos.x);
	TmpVec.y = static_cast<float>(NowPos.y);
	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec2 ChWin::MouseController::GetNowProPosToChVec2()
{
	if (!*this)return { 0.0f,0.0f };

	float TmpX, TmpY;
	TmpX = static_cast<float>(WindWidth);
	TmpY = static_cast<float>(WindHeight);

	ChVec2 TmpVec;
	TmpVec.x = static_cast<float>(NowPos.x);
	TmpVec.y = static_cast<float>(NowPos.y);


	TmpVec.x /= (TmpX);
	TmpVec.y /= (TmpY);

	TmpVec *= 2.0f;

	TmpVec -= 1.0f;

	TmpVec.y *= -1.0f;



	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

POINT ChWin::MouseController::GetMoveValue()
{
	if (!*this)return { 0,0 };

	POINT Tmp;
	Tmp.x = (NowPos.x - BeforPos.x);
	Tmp.y = (NowPos.y - BeforPos.y);

	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec2 ChWin::MouseController::GetMoveValueToChVec2()
{

	if (!*this)return { 0.0f,0.0f };

	ChVec2 TmpVec;
	TmpVec.x = static_cast<float>(NowPos.x - BeforPos.x);
	TmpVec.y = static_cast<float>(NowPos.y - BeforPos.y);

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

void ChWin::MouseController::Update()
{
	if (!*this)return;

	BeforPos = NowPos;

	if (SetCenterPosFlg)
	{
		BeforPos = CenterPos;
	}

	GetCursorPos(&NowPos);

	ScreenToClient(hWnd, &NowPos);

	if (SetCenterPosFlg)
	{
		SetCursorPos(CenterPos.x, CenterPos.y);
	}


	RECT Rec;

	GetClientRect(hWnd, &Rec);

	WindWidth = Rec.right - Rec.left;
	WindHeight = Rec.bottom - Rec.top;

}
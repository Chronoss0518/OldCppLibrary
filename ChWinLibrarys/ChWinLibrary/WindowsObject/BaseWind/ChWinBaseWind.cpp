
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../SubWind/ChWinSubWind.h"
#include"ChWinBaseWind.h"
#include"../../BaseSystem/ChWindows/ChWindows.h"

std::map<unsigned long, ChWin::WindObject*>ChWin::WindObject::ObjList;

std::string ChWin::WindObject::ClassName = "";

//WindProcedureは登録する際に静的な関数でなければならない//
LRESULT CALLBACK SubWndProc(
	HWND _hWnd
	, UINT _uMsg
	, WPARAM _wParam
	, LPARAM _lParam)
{
	if(ChSystem::Windows::ImGuiProc)if (ChSystem::Windows::ImGuiProc(_hWnd, _uMsg, _wParam, _lParam))return true;

	switch (_uMsg)
	{	
	case WM_MOVE:
		ChWin::WindMoveUpdate(_hWnd,_lParam);
		break;
	case WM_SIZE:
		ChWin::WindSizeUpdate(_hWnd, _lParam);
		break;

	case WM_COMMAND:
		ChWin::ObjUpdate(_wParam);

		DefWindowProc((HWND)_lParam, _uMsg, _wParam, _lParam);
		break;
	}

	return DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::ObjUpdate(const WPARAM& _wParam)
{
	if (ChWin::WindObject::ObjList.empty())return;
	ChWin::WindObject::ObjList[LOWORD(_wParam)]->Update(_wParam);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::WindMoveUpdate(const HWND _hWnd, LPARAM _lParam)
{


	if (ChWin::WindObject::ObjList.empty())return;

	auto Wind = ((ChWin::SubWind*)GetWindowLongPtr(_hWnd, GWLP_USERDATA));
	if (ChPtr::NullCheck(Wind))return;

	if(!Wind->StartMoveFlg)return;

	{

		RECT TmpRec;

		GetClientRect(_hWnd, &TmpRec);

		if (TmpRec.bottom != Wind->h
			|| TmpRec.right != Wind->w) {

			return;
		}
	}

	if (Wind->NotCMoveFlg)
	{
		MoveWindow(_hWnd, Wind->x, Wind->y, Wind->w, Wind->h, true);

		return;
	}

	Wind->x = LOWORD(_lParam);
	Wind->y = HIWORD(_lParam);



}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::WindSizeUpdate(const HWND _hWnd, LPARAM _lParam)
{
	if (ChWin::WindObject::ObjList.empty())return;

	auto Wind = ((ChWin::SubWind*)GetWindowLongPtr(_hWnd, GWLP_USERDATA));
	if (ChPtr::NullCheck(Wind))return;

	if (!Wind->StartMoveFlg)
	{

		RECT TmpRec;
		GetClientRect(_hWnd, &TmpRec);

		if (TmpRec.right >= Wind->w
			&& TmpRec.bottom >= Wind->y
			)
		{
			Wind->StartMoveFlg = true;
			return;
		}

	}

	if (!Wind->NotCMoveFlg)
	{

		RECT TmpRec;

		GetWindowRect(_hWnd, &TmpRec);
		Wind->x = TmpRec.top;
		Wind->y = TmpRec.left;
	}

	if (Wind->NotCSizeFlg)
	{

		MoveWindow(_hWnd, Wind->x, Wind->y, Wind->w, Wind->h, true);

		return;
	}

	Wind->w = LOWORD(_lParam);
	Wind->h = HIWORD(_lParam);





}

///////////////////////////////////////////////////////////////////////////////////////
//WindObjectメソッド//
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::WindObject::Init(const HWND& _hWnd)
{
	if (ChPtr::NullCheck(_hWnd))return;
	HOwn = _hWnd;
	SetInitFlg(true);


	if (!(ClassName.length() <= 0))return;

	ClassName = "ChSubClass";
	{

		WNDCLASS wc;

		wc.style = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;
		wc.lpfnWndProc = SubWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = (HINSTANCE)GetWindowLong(HOwn, GWL_HINSTANCE);
		wc.hIcon = NULL;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.lpszMenuName = (LPSTR)NULL;
		wc.lpszClassName = ClassName.c_str();

		RegisterClass(&wc);

	}

}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::WindObject::Release()
{
	if (ChPtr::NullCheck(HIns))return;
	DestroyWindow(HIns);
	HIns = nullptr;

	StartMoveFlg = false;

	SetInitFlg(false);

	ObjList.erase(MyID);

	if (!ObjList.empty()) return;

	UnregisterClass(
		ClassName.c_str()
		, (HINSTANCE)GetWindowLong(HOwn, GWL_HINSTANCE));

}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::WindObject::Move(const int _x
	, const int _y
	, const int _w
	, const int _h)
{
	if (ChPtr::NullCheck(HIns))return;
	MoveWindow(HIns, _x, _y, _w, _h, true);
}

void ChWin::WindObject::Move(const int _x
	, const int _y)
{

	if (ChPtr::NullCheck(HIns))return;
	MoveWindow(HIns, _x, _y, w, h, true);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::WindObject::ReSize(
	const int _w
	, const int _h)
{
	if (ChPtr::NullCheck(HIns))return;
	MoveWindow(HIns, x, y, _w, _h, true);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::WindObject::RegisterObj()
{
	MyID = ObjList.size();
	ObjList[MyID] = (this);
}

///////////////////////////////////////////////////////////////////////////////////////

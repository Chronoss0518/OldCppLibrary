
#include<Windows.h>
#include"../../ChGameIncludeFile.h"
#include"ChWinBaseWind.h"

std::vector<ChWin::WindObject*>ChWin::WindObject::ObjList;

std::string ChWin::WindObject::ClassName = "";

//WindProcedureは登録する際に静的な関数でなければならない//
LRESULT CALLBACK SubWndProc(
	HWND _hWnd
	, UINT _uMsg
	, WPARAM _wParam
	, LPARAM _lParam)
{

	switch (_uMsg)
	{	
	case WM_COMMAND:
		ChWin::ObjUpdate(_wParam);
		break;
	}

	return DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
}


///////////////////////////////////////////////////////////////////////////////////////
//WindObjectメソッド//
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::WindObject::Init(const HWND& _ParentHndl)
{
	HOwn = _ParentHndl;
	SetInitFlg(true);
	if (!(ClassName.length() <= 0))return;

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

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::WindObject::Release()
{
	if (ChPtr::NullCheck(HIns))return;
	DestroyWindow(HIns);
	HIns = nullptr;

	SetInitFlg(false);

	if (MyID <= 0)return;

	auto It = ObjList.begin();
	It += MyID;
	ObjList.erase(It);

	if (!ObjList.empty())return;


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
	ObjList.push_back(this);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::ObjUpdate(const WPARAM _wParam)
{
	if (WindObject::ObjList.empty())return;
	WindObject::ObjList[LOWORD(_wParam)]->Update();
}

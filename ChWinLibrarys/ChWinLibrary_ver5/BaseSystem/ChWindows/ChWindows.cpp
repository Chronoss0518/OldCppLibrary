
#include<windows.h>

#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"

#include"../../CPP/ChBitBool/ChBitBool.h"
#include"../ChBaseSystem/ChBaseSystem.h"
#include"ChWindows.h"
#include"../../WindowsObject/BaseWind/ChWinBaseWind.h"
#include"../../WindowsObject/Mouse/ChWinMouse.h"

using namespace ChSystem;

ChStd::Bool BaseWndProcs(
	const HWND _hWnd
	, const UINT _uMsg
	, const WPARAM _wParam
	, const LPARAM _lParam);

std::function<ChStd::Bool(
	HWND _hWnd
	, UINT _uMsg
	, WPARAM _wParam
	, LPARAM _lParam)>Windows::ImGuiProc;

///////////////////////////////////////////////////////////////////////////////////////
//ChWindowsƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void Windows::Init(
	const std::string& _appName
	, const std::string& _windClassName
	, const unsigned int _windWidth
	, const unsigned int _windHeight
	, const HINSTANCE _hInst
	, const int _nCmdShow)
{

	windSize.w = _windWidth;
	windSize.h = _windHeight;

	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _hInst;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = (LPSTR)NULL;
	wc.lpszClassName = _windClassName.c_str();
	RegisterClass(&wc);

	WinProcs = BaseWndProcs;

	className = wc.lpszClassName;

	hWnd = CreateWindow(
		wc.lpszClassName
		, _appName.c_str()
		, WS_OVERLAPPEDWINDOW
		| WS_CLIPCHILDREN 
		| WS_GROUP
		, 10
		, 10
		, _windWidth
		, _windHeight
		, NULL
		, NULL
		, _hInst
		, nullptr);


	ShowWindow(hWnd, _nCmdShow);
	UpdateWindow(hWnd);

	buttonList.SetSize((256 / 8) + 1);
	isNowPush.SetSize((256 / 8) + 1);

	SetInitFlg(true);

	SetWindowLongPtr(hWnd, GWLP_USERDATA, (long)this);
}

///////////////////////////////////////////////////////////////////////////////////

void Windows::Release()
{
	SetInitFlg(false);
	UnregisterClass(
		className.c_str()
		, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE));
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool Windows::IsPushKey(const int _Key)
{
	SetKeyCode();

	if (buttonList.GetBitFlg(_Key))
	{
		isNowPush.SetBitTrue(_Key);
		return true;
	}
	isNowPush.SetBitFalse(_Key);
	return false;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool Windows::IsPushKeyNoHold(const int _Key)
{
	SetKeyCode();

	if (buttonList.GetBitFlg(_Key))
	{
		if (!isNowPush.GetBitFlg(_Key))
		{
			isNowPush.SetBitTrue(_Key);
			return true;
		}
		return false;
	}
	isNowPush.SetBitFalse(_Key);
	return false;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool Windows::IsPause(const int _Key)
{
	SetKeyCode();

	ChStd::Bool tmpFlg;
	tmpFlg = IsPushKey(_Key);

	if (tmpFlg && nowKey)return pauseFlg;
	nowKey = false;

	if (!tmpFlg)return pauseFlg;

	pauseFlg = !pauseFlg;
	nowKey = true;

	return pauseFlg;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool Windows::IsMessage(
	const std::string& _mainStr
	, const std::string& _subStr)
{

 	if (ChPtr::NullCheck(hWnd))return true;

	if (MessageBox(
		hWnd
		, &_mainStr[0]
		, &_subStr[0]
		, MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)
		== IDYES)return true;

	return false;

}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool Windows::IsUpdate()
{
	if (ChPtr::NullCheck(hWnd))return false;

	isKeyUpdate = false;
	if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))return true;

	if (!(GetMessage(&msg, NULL, 0, 0)))return false;
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	
	{

		RECT tmp;
		GetClientRect(hWnd, &tmp);

		windSize.w = tmp.right - tmp.left;
		windSize.h = tmp.bottom - tmp.top;

	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////

void Windows::SetKeyCode()
{
	if (!system->IsUseSystemButtons())return;
	if (isKeyUpdate)return;
	unsigned char keyCode[256];
	int tmp = GetKeyboardState(keyCode);
	buttonList.SetAllDownFlg();

	for (unsigned short i = 0; i < 256; i++)
	{
		if (!(keyCode[i] & ChStd::MAX_CHAR_BIT))continue;

		buttonList.SetBitTrue((unsigned char)i);
	}

	isKeyUpdate = true;
}

///////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK ChSystem::WndProc(
	HWND _hWnd
	, UINT _uMsg
	, WPARAM _wParam
	, LPARAM _lParam)
{

	if (Windows::ImGuiProc)if (Windows::ImGuiProc(_hWnd, _uMsg, _wParam, _lParam))return true;

	auto base = SysManager().GetSystem<Windows>();

	if (base)
	{
		base->WinProcs(_hWnd, _uMsg, _wParam, _lParam);
	}
	else
	{
		switch (_uMsg)
		{
		case WM_COMMAND:

			ChWin::ObjUpdate(_wParam);
			break;

		case WM_DESTROY:

			PostQuitMessage(0);
			return 0;

		default:
			break;
		}
	}
	return DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
}

///////////////////////////////////////////////////////////////////////////////////
//GlobalFunction//
///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool BaseWndProcs(
	const HWND _hWnd
	, const UINT _uMsg
	, const WPARAM _wParam
	, const LPARAM _lParam)
{

	switch (_uMsg)
	{
	case WM_MOUSEWHEEL:

	{

		POINTS tmp;
		tmp.y = 0;
		tmp.x = GET_WHEEL_DELTA_WPARAM(_wParam);
		ChWin::Mouse().WheelUpdate(tmp);

	}
	break;

	case WM_MOUSEHWHEEL:
	{
		POINTS tmp;
		tmp.x = 0;
		tmp.y = GET_WHEEL_DELTA_WPARAM(_wParam);
		ChWin::Mouse().WheelUpdate(tmp);

	}
	break;

	case WM_COMMAND:

		ChWin::ObjUpdate(_wParam);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}



	return true;

}

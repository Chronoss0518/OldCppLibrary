
#include<windows.h>

#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"

#include"../../CPP/ChBitBool/ChBitBool.h"
#include"../ChBaseSystem/ChBaseSystem.h"
#include"ChWindows.h"
#include"../../WindowsObject/BaseWind/ChWinBaseWind.h"
#include"../../WindowsObject/Mouse/ChWinMouse.h"

using namespace ChSystem;

namespace ChWin
{

	static const std::map<int, std::string>WindowsKeyName
	{
		{(int)'\0',"None" },{(int)'A',"A Key"},{(int)'B',"B Key"}
		,{(int)'C',"C Key"},{(int)'D',"D Key"},{(int)'E',"E Key"}
		,{(int)'F',"F Key"},{(int)'G',"G Key"},{(int)'H',"H Key"}
		,{(int)'I',"I Key"},{(int)'J',"J Key"},{(int)'K',"K Key"}
		,{(int)'L',"L Key"},{(int)'M',"M Key"},{(int)'N',"N Key"}
		,{(int)'O',"O Key"},{(int)'P',"P Key"},{(int)'Q',"Q Key"}
		,{(int)'R',"R Key"},{(int)'S',"S Key"},{(int)'T',"T Key"}
		,{(int)'U',"U Key"},{(int)'V',"V Key"},{(int)'W',"W Key"}
		,{(int)'X',"X Key"},{(int)'Y',"Y Key"},{(int)'Z',"Z Key"}
		,{(int)'1',"1 Key"},{(int)'2',"2 Key"},{(int)'3',"3 Key"}
		,{(int)'4',"4 Key"},{(int)'5',"5 Key"},{(int)'6',"6 Key"}
		,{(int)'7',"7 Key"},{(int)'8',"8 Key"},{(int)'9',"9 Key"}
		,{(int)'0',"0 Key"},{VK_SHIFT,"Shift Key"},{VK_SPACE,"Space Key"}
		,{VK_ESCAPE,"Escape Key"},{VK_RETURN,"Enter Key"}
		,{VK_UP,"Up Key"},{VK_DOWN,"Down Key"}
		,{VK_LEFT,"Left Key"},{VK_RIGHT,"Right Key"}
		,{VK_RBUTTON,"Mouse_R Button"}
		,{VK_LBUTTON,"Mouse_L Button"}
		,{VK_MBUTTON,"Mouse_Center Button"}
	};

	std::map<int, std::string> GetWindowsKeyName()
	{
		return WindowsKeyName;
	}
}

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
	const std::string& _APPName
	, const std::string& _WindClassName
	, const unsigned int _WindWidth
	, const unsigned int _WindHeight
	, const HINSTANCE _hInst
	, const int _nCmdShow)
{

	WindSize[0] = _WindWidth;
	WindSize[1] = _WindHeight;

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
	wc.lpszClassName = _WindClassName.c_str();
	RegisterClass(&wc);

	WinProcs = BaseWndProcs;

	ClassName = wc.lpszClassName;

	hWnd = CreateWindow(
		wc.lpszClassName
		, _APPName.c_str()
		, WS_OVERLAPPEDWINDOW
		| WS_CLIPCHILDREN 
		| WS_GROUP
		, 10
		, 10
		, _WindWidth
		, _WindHeight
		, NULL
		, NULL
		, _hInst
		, nullptr);


	ShowWindow(hWnd, _nCmdShow);
	UpdateWindow(hWnd);

	ButtonList.SetSize((256 / 8) + 1);
	IsNowPush.SetSize((256 / 8) + 1);

	SetInitFlg(true);

	SetWindowLongPtr(hWnd, GWLP_USERDATA, (long)this);
}

///////////////////////////////////////////////////////////////////////////////////

void Windows::Release()
{
	SetInitFlg(false);
	UnregisterClass(
		ClassName.c_str()
		, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE));
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool Windows::IsPushKey(const int _Key)
{
	SetKeyCode();

	if (ButtonList.GetBitFlg(_Key))
	{
		IsNowPush.SetBitTrue(_Key);
		return true;
	}
	IsNowPush.SetBitFalse(_Key);
	return false;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool Windows::IsPushKeyNoHold(const int _Key)
{
	SetKeyCode();

	if (ButtonList.GetBitFlg(_Key))
	{
		if (!IsNowPush.GetBitFlg(_Key))
		{
			IsNowPush.SetBitTrue(_Key);
			return true;
		}
		return false;
	}
	IsNowPush.SetBitFalse(_Key);
	return false;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool Windows::IsPause(const int _Key)
{
	SetKeyCode();

	ChStd::Bool TmpFlg;
	TmpFlg = IsPushKey(_Key);

	if (TmpFlg && NowKey)return PauseFlg;
	NowKey = false;

	if (!TmpFlg)return PauseFlg;

	PauseFlg = !PauseFlg;
	NowKey = true;

	return PauseFlg;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool Windows::IsMessage(
	const std::string& _MainStr
	, const std::string& _SubStr)
{

 	if (ChPtr::NullCheck(hWnd))return true;

	if (MessageBox(
		hWnd
		, &_MainStr[0]
		, &_SubStr[0]
		, MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)
		== IDYES)return true;

	return false;

}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool Windows::IsUpdate()
{
	if (ChPtr::NullCheck(hWnd))return false;

	IsKeyUpdate = false;
	if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))return true;

	if (!(GetMessage(&msg, NULL, 0, 0)))return false;
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	
	{

		RECT Tmp;
		GetClientRect(hWnd, &Tmp);

		WindSize[0] = Tmp.right - Tmp.left;
		WindSize[1] = Tmp.bottom - Tmp.top;

	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////

void Windows::SetKeyCode()
{
	if (!System->IsUseSystemButtons())return;
	if (IsKeyUpdate)return;
	unsigned char KeyCode[256];
	int Tmp = GetKeyboardState(KeyCode);
	ButtonList.SetAllDownFlg();

	for (unsigned short i = 0; i < 256; i++)
	{
		if (!(KeyCode[i] & ChStd::MAX_CHAR_BIT))continue;

		ButtonList.SetBitTrue((unsigned char)i);
	}

	IsKeyUpdate = true;
}

///////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK ChSystem::WndProc(
	HWND _hWnd
	, UINT _uMsg
	, WPARAM _wParam
	, LPARAM _lParam)
{

	if (Windows::ImGuiProc)if (Windows::ImGuiProc(_hWnd, _uMsg, _wParam, _lParam))return true;

	auto Base = SysManager().GetSystem<Windows>();

	if (Base)
	{
		Base->WinProcs(_hWnd, _uMsg, _wParam, _lParam);
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

		POINTS Tmp;
		Tmp.y = 0;
		Tmp.x = GET_WHEEL_DELTA_WPARAM(_wParam);
		ChWin::Mouse().WheelUpdate(Tmp);

	}
	break;

	case WM_MOUSEHWHEEL:
	{
		POINTS Tmp;
		Tmp.x = 0;
		Tmp.y = GET_WHEEL_DELTA_WPARAM(_wParam);
		ChWin::Mouse().WheelUpdate(Tmp);

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

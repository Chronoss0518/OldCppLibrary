
#include<windows.h>
#include"../../ChGameIncludeFile.h"
#include"ChWindows.h"


using namespace ChSystem;

Windows* Me = nullptr;


///////////////////////////////////////////////////////////////////////////////////////
//ChWindowsÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void Windows::Init(
	const std::string& _APPName
	, const std::string& _WindClassName
	, const unsigned int _WindWidth
	, const unsigned int _WindHeight
	, const HINSTANCE _hInst
	, const int _nCmdShow)
{

	WindWidth = _WindWidth;
	WindHeight = _WindHeight;


	Me = this;

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

	WMInit();

	ShowWindow(hWnd, _nCmdShow);
	UpdateWindow(hWnd);


	ButtonList.SetSize((256 / 8) + 1);
	IsNowPush.SetSize((256 / 8) + 1);

	FPS = 60;

	SetInitFlg(true);

	//SetWindowLongPtr(hWnd, GWLP_USERDATA, (long)this);
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
		return ChStd::True;
	}
	IsNowPush.SetBitFalse(_Key);
	return ChStd::False;
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
			return ChStd::True;
		}
		return ChStd::False;
	}
	IsNowPush.SetBitFalse(_Key);
	return ChStd::False;
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

ChStd::Bool Windows::CheckWinMessage()
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

		WindWidth = Tmp.right - Tmp.left;
		WindHeight = Tmp.bottom - Tmp.top;

	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////

void Windows::SetKeyCode()
{
	if (IsKeyUpdate)return;
	ChStd::Bool KeyCode[256];
	GetKeyboardState(KeyCode);
	ButtonList.SetAllDownFlg();

	for (unsigned short i = 0; i < 256; i++)
	{
		if (!(KeyCode[i] & ChStd::W_MaxCharBit))continue;

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

	//if (Me->WindProc(_hWnd, _uMsg, _wParam, _lParam))return 0;


	switch (_uMsg)
	{
	case WM_MOUSEWHEEL:

	{

		POINTS Tmp;
		Tmp.y = 0;
		Tmp.x = GET_WHEEL_DELTA_WPARAM(_wParam);
		ChWin::Mouse().WheelUpdate(Tmp);

	}
	return 0;

	case WM_MOUSEHWHEEL:

	{
		POINTS Tmp;
		Tmp.x = 0;
		Tmp.y = GET_WHEEL_DELTA_WPARAM(_wParam);
		ChWin::Mouse().WheelUpdate(Tmp);

	}
	return 0;

	case WM_COMMAND:

		ChWin::ObjUpdate(_wParam);
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;

	default:
		break;
	}


	return DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);

}

ChStd::Bool Windows::WindProc(
	HWND _hWnd
	, UINT _uMsg
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
}

///////////////////////////////////////////////////////////////////////////////////
//WM_Functions//

void Windows::WMInit()
{

	Me->WMFunction[WM_ACTIVATE] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnActivate(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_CHAR] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnChar(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_CHARTOITEM] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnCharToItem(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_CHILDACTIVATE] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnChildActivate(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_CLEAR] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnClear(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_CLOSE] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnClose(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_COMMAND] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnCommand(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_CREATE] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnCreate(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_DELETEITEM] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnDeleteItem(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_DESTROY] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnDestroy(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_ENABLE] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnEnable(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_FONTCHANGE] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnFontChange(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_KEYDOWN] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnKeyDown(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_KEYUP] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnKeyUp(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_LBUTTONDBLCLK] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnLButtonDBClick(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_LBUTTONDOWN] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnLButtonDown(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_LBUTTONUP] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnLButtonUp(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_MBUTTONDBLCLK] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnMButtonDBClick(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_MBUTTONDOWN] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnMButtonDown(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_MBUTTONUP] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnMButtonUp(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_MENUCHAR] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnMenuChar(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_MENUSELECT] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnMenuSelect(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_MOUSEMOVE] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnMouseMove(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_MOUSEWHEEL] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnMouseWheel(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_MOVE] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnMove(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_NCDESTROY] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnNCDestroy(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_NCHITTEST] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnNCHitTest(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_PAINT] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnPaint(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_PASTE] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnPaste(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_QUIT] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnQuit(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_RBUTTONDBLCLK] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnRButtonDBClick(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_RBUTTONDOWN] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnRButtonDown(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_RBUTTONUP] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnRButtonUp(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_SIZE] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnSize(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_SYSCHAR] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnSysChar(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_SYSCOMMAND] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnSysCommand(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_SYSKEYDOWN] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnSysKeyDown(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_SYSKEYUP] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnSysKeyUp(_hWnd, _wParam, _lParam))return false;
		return true;
	};

	Me->WMFunction[WM_TIMER] =
		[](const HWND _hWnd
			, const WPARAM _wParam
			, const LPARAM _lParam)->ChStd::Bool
	{
		if (!Me->OnTimer(_hWnd, _wParam, _lParam))return false;
		return true;
	};

}

///////////////////////////////////////////////////////////////////////////////////
//WM_Functions//


ChStd::Bool Windows::OnActivate(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
};

ChStd::Bool Windows::OnChar(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
};

ChStd::Bool Windows::OnCharToItem(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
};

ChStd::Bool Windows::OnChildActivate(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
};

ChStd::Bool Windows::OnClear(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
};

ChStd::Bool Windows::OnClose(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	PostQuitMessage(0);
	return false;
};

ChStd::Bool Windows::OnCommand(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	ChWin::ObjUpdate(_wParam);
	return true;
};

ChStd::Bool Windows::OnCreate(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
};

ChStd::Bool Windows::OnDeleteItem(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
};

ChStd::Bool Windows::OnDestroy(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	PostQuitMessage(0);
	return false;
};

ChStd::Bool  Windows::OnEnable(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
};

ChStd::Bool  Windows::OnFontChange(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
};

ChStd::Bool  Windows::OnKeyDown(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnKeyUp(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnLButtonDBClick(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnLButtonDown(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnLButtonUp(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnMButtonDBClick(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnMButtonDown(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnMButtonUp(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
}

ChStd::Bool  Windows::OnMenuChar(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnMenuSelect(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnMouseMove(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
}

ChStd::Bool  Windows::OnMouseWheel(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnMove(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnNCDestroy(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
}

ChStd::Bool  Windows::OnNCHitTest(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnPaint(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnPaste(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnQuit(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnRButtonDBClick(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
}

ChStd::Bool  Windows::OnRButtonDown(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnRButtonUp(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnSize(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
}

ChStd::Bool  Windows::OnSysChar(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam) 
{
	return true;
}

ChStd::Bool  Windows::OnSysCommand(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
}

ChStd::Bool  Windows::OnSysKeyDown(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
}

ChStd::Bool  Windows::OnSysKeyUp(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
}

ChStd::Bool  Windows::OnTimer(HWND _hWnd
	, WPARAM _wParam
	, LPARAM _lParam)
{
	return true;
}



#include"../CGameIncludeFile.h"

#ifdef CopyRight_Chronoss_2018Y_08M

///////////////////////////////////////////////////////////////////////////////////////
//ChWindowsSetupÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

ChWin::ChWindowsSetup(
	const char *_APPName
	, const char *_WindClassName
	, const unsigned int _WindWidth
	, const unsigned int _WindHeight
	, HINSTANCE _hInst
	, const int _nCmdShow)
{
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = &ChWin::WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _hInst;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = (LPSTR)NULL;
	wc.lpszClassName = _WindClassName;
	RegisterClass(&wc);

	hWind = CreateWindow(_WindClassName, _APPName, WS_OVERLAPPEDWINDOW
		, 10, 10, WW, WH, NULL, NULL, _hInst, NULL);


	ShowWindow(hWind, _nCmdShow);
	UpdateWindow(hWind);


}

///////////////////////////////////////////////////////////////////////////////////

LRESULT ChWin::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

#endif // !CopyRight_Chronoss_2018Y_08M


#pragma once
#ifndef Ch_Game_Windows_h
#define Ch_Game_Windows_h

typedef class ChWindowsSetup 
{
private:

public:
	HWND hWind;
	MSG msg;

	///////////////////////////////////////////////////////////////////////////////////

	ChWindowsSetup(const char *_APPName
		, const char *_WindClassName
		, const unsigned int _WindWidth
		, const unsigned int _WindHeight
		, HINSTANCE _hInst
		,const int _nCmdShow);

	//ê√ìIä÷êîÇ≈Ç»Ç¢Ç∆WindProcÇ…ìoò^Ç≈Ç´Ç»Ç¢
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam);

	bool CheckWinMessage(void) 
	{
		if (!GetMessage(&msg, NULL, 0, 0))return FALSE;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		return TRUE;
	}



}ChWin,*LpChWin;

#endif
//CopyRight Chronoss0518 2018/08
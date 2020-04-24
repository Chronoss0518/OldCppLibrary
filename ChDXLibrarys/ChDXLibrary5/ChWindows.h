#ifdef _WIN32

#ifndef Ch_Win_Inc_h
#define Ch_Win_Inc_h

#ifdef _WINDEF_
#include <mmsystem.h>
#include <mmreg.h>
#endif

#ifdef _WINDEF_
#pragma comment(lib, "winmm.lib")
#endif

#include"WindowsObject/BaseWind/ChWinBaseWind.h"
#include"ChBaseSystem/ChWindows/ChWindows.h"
#include"WindowsObject/FileDialog/ChWinFileDialog.h"
#include"WindowsObject/Button/ChWinButton.h"
#include"WindowsObject/SubWind/ChWinSubWind.h"
#include"WindowsObject/Mouse/ChWinMouse.h"
#include"WindowsObject/TextBox/ChWinTextBox.h"
#include"WindowsObject/DrawTexter/ChWinDrawTexter.h"


/*

#ifndef Ch_Library_Create
#ifdef _MT
#ifdef _DEBUG
#pragma comment(lib,"ChWin_MTd.lib")
#else
#pragma comment(lib,"ChWin_MT.lib")
#endif//_DEBUG
#endif//_MT
#endif//_DLL
*/


#endif

#endif
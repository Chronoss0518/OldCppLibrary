#ifndef Ch_BGI_h
#define Ch_BGI_h

#include<cstdio>
#include<cstdlib>
#include<cstdarg>
#include<cstring>
#include<ctime>

#include<float.h>
#include<limits.h>

#include<iostream>
#include<vector>
#include<string>
#include<type_traits>
#include<functional>
#include<thread>
#include<map>
#include<memory>
#include<fstream>
#include<sstream>
#include<chrono>

#ifdef __d3d11_h__
#include<windows.h>
#endif

#ifdef _D3D9_H_
#include<windows.h>
#endif

#ifdef _WINDEF_
#include<winsock.h>
#include <mmsystem.h>
#include <mmreg.h>
#include<dsound.h>
#endif

#ifdef _WINDEF_
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dsound.lib")
#endif

#ifndef Ch_Library_Create
extern "C++" {
#endif

#include"../CPP/ChNamespace/ChStd.h"
#include"../CPP/ChNamespace/ChPtr.h"
#include"../CPP/ChNamespace/ChFIO.h"
#include"../CPP/ChNamespace/ChCmd.h"
#include"../CPP/ChNamespace/ChMath.h"

#include"../CPP/ChClassParts/ChCPInitializePack.h"
#include"../CPP/ChClassParts/ChCPClassNameGetter.h"

#ifndef Ch_Library_Create
}
#endif

#endif
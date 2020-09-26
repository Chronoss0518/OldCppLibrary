#ifndef Ch_BGI_h
#define Ch_BGI_h

#include<cstdio>
#include<cstdarg>
#include<cstring>
#include<ctime>
#include<cmath>

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

#ifndef Ch_Library_Create
extern "C++" {
#endif

#include"../BasePack/ChStd.h"
#include"../BasePack/ChPtr.h"
#include"../BasePack/ChFIO.h"

#include"../BasePack/ChMath.h"

#include"CPP/ChClassParts/ChCPInitializePack.h"
#include"CPP/ChClassParts/ChCPClassNameGetter.h"

#ifndef Ch_Library_Create
}
#endif

#endif
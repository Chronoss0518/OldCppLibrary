#ifndef Ch_D3DOI_h
#define Ch_D3DOI_h

#ifdef _WIN32

#include<XInput.h>
#include<xaudio2.h>


#include"../Direct3DObject/XInputController/ChXInputController.h"
#include"../Direct3DObject/XAudios/ChXAudio.h"


#elif _WIN64

#include<XInput.h>
#include<xaudio2.h>


#include"../Direct3DObject/XInputController/ChXInputController.h"
#include"../Direct3DObject/XAudios/ChXAudio.h"

#endif

#ifndef Ch_Library_Create
#ifdef _MT
#ifdef _DLL
#ifdef _DEBUG
#pragma comment(lib,"ChDirect3DObject_MDd.lib")
#else
#pragma comment(lib,"ChDirect3DObject_MD.lib")
#endif//_DEBUG
#else//_DLL
#ifdef _DEBUG
#pragma comment(lib,"ChDirect3DObject_MTd.lib")
#else
#pragma comment(lib,"ChDirect3DObject_MT.lib")
#endif//_DEBUG
#endif//else
#endif//_MT
#endif//Ch_Library_Create

#endif
#ifndef Ch_GIF_h
#define Ch_GIF_h

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////
//includefile
///////////////////////////////////////////////////////////////////////////////////////

#include<windows.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<vector>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

///////////////////////////////////////////////////////////////////////////////////////
//DirectXä÷òA
///////////////////////////////////////////////////////////////////////////////////////
#include<d3d9.h>
#include<d3dx9.h>
#include<d3dx9anim.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

///////////////////////////////////////////////////////////////////////////////////////
//Alldefine
///////////////////////////////////////////////////////////////////////////////////////

#define WW 1280
#define WH 720
#define GetKey(x) if(GetAsyncKeyState(x))
#define WorldMatSet(d,m) d->SetTransform(D3DTS_WORLD, m)
#define LocalMatSet(d,m) d->SetTransform(D3DTS_WORLD, m)
#define LightSet

///////////////////////////////////////////////////////////////////////////////////////
//MyFrameWork
///////////////////////////////////////////////////////////////////////////////////////

#ifdef __D3DX9_H__

//SystemëÄçÏ
#include"ChWindowsSetup/ChWindowsSetup.h"
#include"Direct3D9/ChFileController/ChFileControllerr.h"
//ãÛä‘ëÄçÏ
#include"Direct3D9/ChMouseController/ChMouseController.h"
#include"Direct3D9/ChCamera/ChCamera.h"
#include"Direct3D9/ChLight/ChLight.h"
//Objectñ{ëÃ
#include"Direct3D9/ChTexture/ChTexture.h"
#include"Direct3D9/ChSimplicityXfile/ChSimplicityXfile.h"
//ObjectëÄçÏ
#include"Direct3D9/ChSprite/ChSprite.h"
#include"Direct3D9/ChPolygonBoard/ChPolygonBoard.h"
#include"Direct3D9/ChObjectController/ChObjectController.h"
#include"Direct3D9/ChShader/ChShader.h"
//ñ¢äÆê¨ä÷êî
//#include"Direct3D9/ChBoneMesh/ChBoneMesh.h"
//#include"Direct3D9/ChKeyAnimationMesh/ChKeyAnimationMesh.h"
//#include"Direct3D9/ChAllocateHiearchy/ChAllocateHiearchy.h"




#endif //__D3DX9_H__
#ifdef __d3d11_h__



#endif /__d3d11_h__


#define CopyRight_Chronoss_2018Y_08M
#endif //Ch_GIF_h
//CopyRight Chronoss0518 2018/08
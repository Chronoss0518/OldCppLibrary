#ifndef Ch_ImGui_BAPI_h
#define Ch_ImGui_BAPI_h

#ifndef IMGUI_VERSION

#include"ImGUILibrary/imconfig.h"
#include"ImGUILibrary/imgui.h"

#endif

#include"ChInclude/ChGameBI.h"
#include"CPP/ChBitBool/ChBitBool.h"

#include"ImGUIAPI/ChImBaseWind/ChImBaseWind.h"

#ifdef _WINDOWS_

#include"ImGUILibrary/examples/imgui_impl_win32.h"

#ifdef _D3D9_H_

#include"ImGUILibrary/imgui_impl_dx9.h"

#endif//_D3D9_H_

#ifdef __d3d11_h__

#include"ImGUILibrary/imgui_impl_dx11.h"

#endif//__d3d11_h__

#endif//_WINDOWS_

#endif
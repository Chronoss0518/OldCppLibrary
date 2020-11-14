#ifndef Ch_BD11I_h
#define Ch_BD11I_h

#ifdef _WINDEF_

#include<D3D11.h>
#include<direct.h>
#include<DirectXCollision.h>
#include<d3dcompiler.h>
#include<DirectXMath.h>
#include<DirectXColors.h>
#include<DXGI.h>

#ifndef _XM_NO_INTRINSICS_
#define _XM_NO_INTRINSICS_
#endif

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib, "dxguid.lib")

#include"../Direct3D11/ChPackDate/ChMatrix_11.h"
#include"../Direct3D11/ChPackDate/ChVector3_11.h"
#include"../Direct3D11/ChPackDate/ChQuaternion_11.h"
#include"../Direct3D11/ChDirectX11Controller/ChDirectX11Controller.h"



using IndexBuffer = ID3D11Buffer*;
using VertexBuffer = ID3D11Buffer*;
using ConstantBuffer = ID3D11Buffer*;

#endif

#endif
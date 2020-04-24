#ifndef Ch_D3D9_Inc_h
#define Ch_D3D9_Inc_h



///////////////////////////////////////////////////////////////////////////////////////
//DirectX�֘A
///////////////////////////////////////////////////////////////////////////////////////

#include"ChInclude/ChD3D9I.h"

///////////////////////////////////////////////////////////////////////////////////////
//D3D9AddStruct
///////////////////////////////////////////////////////////////////////////////////////

struct PNTVertex
{
	ChVector3_9 Pos;
	ChVector3_9 Normal;
	D3DXVECTOR2 Tex;
};

//C/C++����ȗ��^�֐��N���X//

//System����//
#include"Direct3D9/ChDSound/ChDSound9.h"
//Object�{��//
#include"Direct3D9/ChMesh/ChBaseMesh9.h"
#include"Direct3D9/ChTexture/ChBaseTexture9.h"
//��ԑ���//
#include"Direct3D9/ChCameraController/ChCameraController9.h"
#include"Direct3D9/ChLight/ChLight9.h"
#include"Direct3D9/ChRenderTargetManager/ChRenderTargetManager9.h"
#include"Direct3D9/ChRenderTargetList/ChRenderTargetList9.h"
//Object����//
#include"Direct3D9/ChAnimationObject/ChAnimationObject9.h"
#include"Direct3D9/ChTextureList/ChTextureList9.h"
#include"Direct3D9/ChTexManager/ChTexManager9.h"
#include"Direct3D9/ChMeshManager/ChMeshManager9.h"
#include"Direct3D9/ChMeshList/ChMeshList9.h"
#include"Direct3D9/ChSprite/ChSprite9.h"
#include"Direct3D9/ChPolygonBoard/ChPolygonBoard9.h"
#include"Direct3D9/ChObjectController/ChObjectController9.h"
#include"Direct3D9/ChShader/ChShader9.h"
#include"Direct3D9/ChStringController/ChStringController9.h"
#include"Direct3D9/ChFont/ChFont9.h"
#include"Direct3D9/ChPhysicalBase/ChPhysicalBase9.h"
#include"Direct3D9/ChBoundingBox/ChBoundingBox9.h"
#include"Direct3D9/ChMesh/ChSkinMesh9.h"
//Component//
#include"Direct3D9/ChComponent/ChComponent9.h"
#include"Direct3D9/ChComponent/ChTextureComponent9.h"
#include"Direct3D9/ChComponent/ChModelComponents9.h"

//�������֐�//

#ifndef _DLL
#ifdef _MT
#ifdef _DEBUG
//#pragma comment(lib,"ChD3D9_MTd.lib")
#else
//#pragma comment(lib,"ChD3D9_MT.lib")
#endif//_DEBUG
#endif//_MT
#endif//_DLL

//CopyRight Chronoss0518 2018/08//
#endif

#endif
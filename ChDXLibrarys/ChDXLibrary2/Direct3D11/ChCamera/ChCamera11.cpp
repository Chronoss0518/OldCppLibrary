
#include"../../ChGameIncludeFile.h"
#include"../../ChBaseSystem/ChBaseSystem/ChBaseSystem.h"
#include<d3d9.h>
#include<d3dx9.h>
#include<d3dx9anim.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include"Direct3D9/ChPackDate/ChMatrix_9.h"
#include"Direct3D9/ChPackDate/ChVector3_9.h"
#include"Direct3D9/ChPackDate/ChQuaternion_9.h"
#include"Direct3D9/ChPackDate/ChMaterial9.h"
#include"Direct3D9/ChDirectX9Controller/ChDirectX9Controller.h"

#include"../ChShader/ChShader9.h"
#include"ChCamera9.h"

///////////////////////////////////////////////////////////////////////////////////////
//ChCamera9メソッド
///////////////////////////////////////////////////////////////////////////////////////

ChCamera9::ChCamera9(const LPDIRECT3DDEVICE9 _Dv,const ChSystem::BaseSystem* _Sys)
{
	System = (ChSystem::BaseSystem*)_Sys;
	CamP = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CamL = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Device = _Dv;
	LookMaxLen = 1000.0f;
	Device->SetRenderState(D3DRS_FOGENABLE, FALSE);
}

///////////////////////////////////////////////////////////////////////////////////

void ChCamera9::SetView(void)
{
	ChMat_9 mView;
	ChMat_9 mProj;

	CamH.MatNormal(CamHMat, ChVec3_9(0.0f, 1.0f, 0.0f));


	// 視点行列の設定
	D3DXMatrixLookAtLH(&mView,
		&CamP,	// カメラの位置
		&CamL,	// カメラの視点
		&CamH	// カメラの頭の方向
	);

	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(
		&mProj
		, D3DXToRadian(ForFalcomDeg)
		, (float)System->GetWindWidth() / (float)System->GetWindHeight()
		, 1.0f, LookMaxLen);

	//行列設定
	Device->SetTransform(D3DTS_VIEW, &mView);
	Device->SetTransform(D3DTS_PROJECTION, &mProj);

	ChD3D9::Shader().SetCamPos(CamP);

}

///////////////////////////////////////////////////////////////////////////////////

void ChCamera9::SetFog(const bool _Flg, const float _LookMin, const float _LookMax, const D3DCOLOR _color)
{
	FogMin = _LookMin;
	FogMax = _LookMax;
	Device->SetRenderState(D3DRS_FOGENABLE, _Flg);
	Device->SetRenderState(D3DRS_FOGCOLOR, _color);
	Device->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);

	Device->SetRenderState(D3DRS_FOGSTART, (DWORD)(FogMin));
	Device->SetRenderState(D3DRS_FOGEND, (DWORD)(FogMax));

}

///////////////////////////////////////////////////////////////////////////////////

void ChCamera9::ZoomUpRadian(const float _UpRad)
{
	ForFalcomDeg += _UpRad;
}


#include"../../ChGameIncludeFile.h"
#include<d3d9.h>
#include<d3dx9.h>
#include<d3dx9anim.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include"Direct3D9/ChPackDate/ChMatrix_9.h"
#include"Direct3D9/ChPackDate/ChVector3_9.h"
#include"Direct3D9/ChPackDate/ChQuaternion_9.h"
#include"Direct3D9/ChPackDate/ChMaterial9.h"
#include"../ChDirectX9Controller/ChDirectX9Controller.h"

#include"ChCameraController9.h"

///////////////////////////////////////////////////////////////////////////////////////
//CameraControllerメソッド
///////////////////////////////////////////////////////////////////////////////////////

D3DXMATRIX ChD3D9::CameraController::MakeViewMatrix(
	const ChD3D9::CamObj& _Cam)
{
	ChMat_9 TmpMat;

	ChVec3_9 TmpHead = _Cam.Head;

	TmpHead.Normalize();

	// 視点行列の設定
	D3DXMatrixLookAtLH(
		&TmpMat,
		&_Cam.Pos,	// カメラの位置
		&_Cam.Look,	// カメラの視点
		&TmpHead	// カメラの頭の方向
	);

	LastCamData = _Cam;

	ViewMat = TmpMat;

	return TmpMat;

}

///////////////////////////////////////////////////////////////////////////////////

D3DXMATRIX ChD3D9::CameraController::MakeViewMatrix(
	const D3DXVECTOR3& _CamPos
	, const D3DXVECTOR3& _CamLook
	, const D3DXVECTOR3& _CamHead)
{

	ChMat_9 TmpMat;
	ChVec3_9 TmpHead = _CamLook - _CamPos;

	if(D3DXVec3Length(&_CamHead) == 0.0f){

		TmpHead.Normalize();

		ChQua_9 TmpQua;

		TmpQua = TmpHead;

		TmpMat = TmpQua;

		TmpHead.MatNormal(TmpMat, ChVec3_9(0.0f, 1.0f, 0.0f));

	}
	else
	{
		TmpHead = _CamHead;
	}


	// 視点行列の設定
	D3DXMatrixLookAtLH(
		&TmpMat,
		&_CamPos,	// カメラの位置
		&_CamLook,	// カメラの視点
		&TmpHead	// カメラの頭の方向
	);

	ViewMat = TmpMat;

	LastCamData.Pos = _CamPos;
	LastCamData.Look = _CamLook;
	LastCamData.Head = TmpHead;

	return TmpMat;
}

///////////////////////////////////////////////////////////////////////////////////

D3DXMATRIX ChD3D9::CameraController::MakeProjectionMatrix(
	const ChD3D9::CamObj& _Cam
	, const float _WindWidth
	, const float _WindHeight
	, const float _ViewAngDeg)
{
	ChMat_9 TmpMat;


	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(
		&TmpMat
		, D3DXToRadian(_ViewAngDeg)
		, _WindWidth / _WindHeight
		, _Cam.LMin, _Cam.LMax);

	ProjectionMat = TmpMat;

	LastCamData = _Cam;

	return TmpMat;

}

///////////////////////////////////////////////////////////////////////////////////

D3DXMATRIX ChD3D9::CameraController::MakeProjectionMatrix(
	const float _LookNear
	, const float _LookDistant
	, const float _WindWidth
	, const float _WindHeight
	, const float _ViewAngDeg)
{

	ChMat_9 TmpMat;

	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(
		&TmpMat
		, D3DXToRadian(_ViewAngDeg)
		, _WindWidth / _WindHeight
		, _LookNear, _LookDistant);

	ProjectionMat = TmpMat;

	LastCamData.LMin = _LookNear;
	LastCamData.LMax = _LookDistant;

	return TmpMat;
}

///////////////////////////////////////////////////////////////////////////////////

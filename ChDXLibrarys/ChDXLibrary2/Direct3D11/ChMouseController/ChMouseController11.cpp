
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
#include"Direct3D9/ChDirectX9Controller/ChDirectX9Controller.h"

#include"../../ChBaseSystem/ChWindows/ChWindows.h"
#include"ChMouseController9.h"

using namespace ChSystem;

///////////////////////////////////////////////////////////////////////////////////////
//ChMouseController9ƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

ChMouseController9::ChMouseController9(
	const ChStd::Bool _MouseCamSetFlg
	,const Windows* _Win)
{
	auto Win = (Windows*)_Win;
	hWind = Win->GethWnd();
	MouseCamLFlg = _MouseCamSetFlg;
	if (MouseCamLFlg) {
		MouSPos.x = Win->GetWindWidth() / 2;
		MouSPos.y = Win ->GetWindHeight() / 2;
		ClientToScreen(hWind, &MouSPos);
		SetCursorPos(MouSPos.x, MouSPos.y);
		ShowCursor(FALSE);
	}

}


///////////////////////////////////////////////////////////////////////////////////

void ChMouseController9::GetMovePos(ChStd::FPOINT *_OutMoveVec)
{
	GetCursorPos(&MouNPos);
	_OutMoveVec->x = (float)(MouNPos.x - MouSPos.x);
	_OutMoveVec->y = (float)(MouNPos.y - MouSPos.y);
	SetCursorPos(MouSPos.x, MouSPos.y);

}

///////////////////////////////////////////////////////////////////////////////////

void ChMouseController9::GetCamCursorPos(
	const D3DXVECTOR3 *_CamPos
	, const D3DXVECTOR3 *_CamLook
	, D3DXVECTOR3 *_OutVec)
{
	D3DXMATRIX TmpMat;
	D3DXVECTOR3 TmpVec,TmpVec2;
	
	float TmpAxis;
	float TmpL1, TmpL2;
	TmpVec = *_CamLook - *_CamPos;
	TmpL1 = D3DXVec3Length(&TmpVec);
	TmpVec2 = TmpVec;
	TmpVec2.y = 0.0f;
	TmpL2 = D3DXVec3Length(&TmpVec);

	TmpAxis = acosf((TmpL2 / TmpL1));

	D3DXVec3Cross(&TmpVec, &TmpVec, &TmpVec2);
	if (_CamPos->y > _CamLook->y)TmpAxis = -TmpAxis;

	D3DXMatrixRotationAxis(&TmpMat, &TmpVec, TmpAxis);

	GetCursorPos(&MouNPos);

	TmpMat._41 = _CamPos->x;
	TmpMat._42 = _CamPos->y;
	TmpMat._43 = _CamPos->z;


	D3DXVec3TransformCoord(_OutVec, &D3DXVECTOR3((float)MouNPos.x,(float)MouNPos.y,0.0f), &TmpMat);

}

///////////////////////////////////////////////////////////////////////////////////

void ChMouseController9::SetCursolOffsetPos(void)
{
	SetCursorPos(MouSPos.x, MouSPos.y);
}

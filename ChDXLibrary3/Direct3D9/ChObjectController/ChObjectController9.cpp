
#include<d3d9.h>
#include<d3dx9.h>
#include<d3dx9anim.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include"../../ChGameIncludeFile.h"

#include"Direct3D9/ChPackDate/ChMatrix_9.h"
#include"Direct3D9/ChPackDate/ChVector3_9.h"
#include"Direct3D9/ChPackDate/ChQuaternion_9.h"
#include"Direct3D9/ChPackDate/ChMaterial9.h"
#include"Direct3D9/ChDirectX9Controller/ChDirectX9Controller.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"../ChMesh/ChBaseMesh9.h"
#include"../ChPolygonBoard/ChPolygonBoard9.h"

#include"ChObjectController9.h"

using namespace ChTex;
using namespace ChMesh;

///////////////////////////////////////////////////////////////////////////////////////
//ChObjectControllerÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChObjectController9::MeshHitRay(
	DWORD& _Index
	, float& _Len
	, const ChPtr::Shared<BaseMesh9>& _Mesh
	, const ChMat_9& _Obj
	, const ChVec3_9& _Pos
	, const ChVec3_9& _Dir)
{

	if (_Mesh->GetMesh() == nullptr)
	{
		return false;
	}

	ChMat_9 TmpMat = _Obj;

	float TmpLen = 0.0f;

	ChVec3_9 TmpPos, TmpDir;

	TmpMat.Inverse();

	TmpPos.MatPos(TmpMat, _Pos);

	TmpDir.MatNormal(TmpMat, _Dir);

	TmpDir.Normalize();

	BOOL TmpBool;

	D3DXIntersect(
		_Mesh->InsMesh()
		, &TmpPos
		, &TmpDir
		, &TmpBool
		, &_Index
		, NULL
		, NULL
		, &TmpLen
		, NULL
		, NULL);

	if (!TmpBool)
	{
		return false;
	}

	_Len = TmpLen;
	return true;


}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChObjectController9::MeshHitRay(
	float& _Len
	, const ChPtr::Shared<ChMesh::BaseMesh9>& _Mesh
	, const ChMat_9& _Obj
	, const ChVec3_9& _Pos
	, const ChVec3_9& _Dir)

{
	DWORD TmpIndex;

	return MeshHitRay(TmpIndex, _Len, _Mesh, _Obj, _Pos, _Dir);

}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChObjectController9::MeshHitRay(
	const ChPtr::Shared<ChMesh::BaseMesh9>& _Mesh
	, const ChMat_9& _Obj
	, const ChVec3_9& _Pos
	, const ChVec3_9& _Dir)

{
	float TmpLen;

	DWORD TmpIndex;

	return MeshHitRay(TmpIndex, TmpLen, _Mesh, _Obj, _Pos, _Dir);


}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChObjectController9::PorygonHitRay(
	float& _Len
	, const ChPtr::Shared<PolygonBoard9> _PoBo
	, const ChVec3_9& _Pos
	, const ChVec3_9& _Dir)
{
	float TmpLen;
	if (D3DXIntersectTri(&_PoBo->GetPosVertex(0)->pos, &_PoBo->GetPosVertex(1)->pos, &_PoBo->GetPosVertex(2)->pos, &_Pos, &_Dir, NULL, NULL, &TmpLen)
		|| D3DXIntersectTri(&_PoBo->GetPosVertex(0)->pos, &_PoBo->GetPosVertex(2)->pos, &_PoBo->GetPosVertex(3)->pos, &_Pos, &_Dir, NULL, NULL, &TmpLen))
	{
		_Len = TmpLen;
		return true;
	}

	_Len = -1;

	return false;

}

///////////////////////////////////////////////////////////////////////////////////

void ChObjectController9::SimpleAnimetion(
	ChMat_9& _NowMat
	, const ChMat_9& _StartMat
	, const ChMat_9& _EndMat
	, const float& _NowTime)
{
	ChQua_9 TmpSQua, TmpEQua, TmpNQua;
	D3DXVECTOR3 TmpSVec, TmpEVec, TmpNVec;

	D3DXQuaternionRotationMatrix(&TmpSQua, &_StartMat);
	D3DXQuaternionRotationMatrix(&TmpEQua, &_EndMat);

	D3DXVec3TransformCoord(&TmpSVec, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &_StartMat);
	D3DXVec3TransformCoord(&TmpEVec, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &_EndMat);

	D3DXQuaternionSlerp(&TmpNQua, &TmpSQua, &TmpEQua, _NowTime);

	D3DXVec3Lerp(&TmpNVec, &TmpSVec, &TmpEVec, _NowTime);

	D3DXMatrixRotationQuaternion(&_NowMat, &TmpNQua);

	_NowMat._41 = TmpNVec.x;
	_NowMat._42 = TmpNVec.y;
	_NowMat._43 = TmpNVec.z;


}

///////////////////////////////////////////////////////////////////////////////////

void ChObjectController9::MatrixBillboard(
	ChMat_9& _OutObj
	, const ChVec3_9& _ObjPos
	, const  ChMat_9& _CamMat)
{

	ChMat_9 TmpMat = _CamMat;

	TmpMat.Inverse();

	_OutObj = TmpMat;

	_OutObj = _ObjPos;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChObjectController9::LengthDecision(
	const ChMat_9 &_Mat1
	, const ChMat_9 &_Mat2
	, const float MatLen
	, const char _MaskDirection)
{
	float TmpLen;
	D3DXVECTOR3 TmpVec1, TmpVec2;
	D3DXVec3TransformCoord(&TmpVec1, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &_Mat1);
	D3DXVec3TransformCoord(&TmpVec2, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &_Mat2);
	switch (_MaskDirection) {
	case 'x':
		TmpVec1.x = 0.0f;
		TmpVec2.x = 0.0f;
		break;
	case 'y':
		TmpVec1.y = 0.0f;
		TmpVec2.y = 0.0f;
		break;
	case 'z':
		TmpVec1.z = 0.0f;
		TmpVec2.z = 0.0f;
		break;
	default:
		break;
	}
	TmpVec1 -= TmpVec2;
	TmpLen = D3DXVec3Length(&TmpVec1);
	if (TmpLen < MatLen)return true;

	return false;

}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChObjectController9::Hit2DDecision(
	const ChMat_9& _Obj1Mat
	, const ChMat_9& _Obj2Mat
	, const ChPtr::Shared<Texture9>&_Obj1Tex
	, const ChPtr::Shared<Texture9>&_Obj2Tex)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////

float ChObjectController9::GetLenToPosTri(
	const D3DXVECTOR3& _Pos
	, const D3DXVECTOR3& _FaceVer1
	, const D3DXVECTOR3& _FaceVer2
	, const D3DXVECTOR3& _FaceVer3)
{
	ChVec3 FaceVer[3] =
	{
		_FaceVer1,
		_FaceVer2,
		_FaceVer3
	};

	float BaseLen = 0.0f;

	BaseLen = GetLenToPosPlane(_Pos, _FaceVer1, _FaceVer2, _FaceVer3);

	ChVec3 Normal;

	Normal = ChMath::GetFaceNormal(
		_FaceVer1
		, _FaceVer2
		, _FaceVer3);

	ChVec3 VPos = _Pos + (Normal * BaseLen);

	char TmpNum = -1;
	unsigned char TmpCnt = 0;

	{
		for (unsigned char i = 0; i < 3; i++)
		{
			ChVec3 TmpVec;
			TmpVec.Cross((FaceVer[(i + 1) % 3] - FaceVer[i])
				, (_Pos - FaceVer[(i + 1) % 3]));

			ChVec3 TTmpVec = TmpVec * Normal;

			for (unsigned char j = 0; j < 3; j++)
			{
				if (ChMath::IsPSign(TTmpVec.Val[j]))continue;

				if(TmpNum <= 0)TmpNum = i;
				TmpCnt++;
				break;
			}


		}
	}

	{


		if (TmpCnt <= 0)
		{

			return BaseLen;
		}

		if (TmpCnt <= 2)
		{
			ChVec3 TTmp;

			TTmp = FaceVer[TmpNum] - _Pos;
			BaseLen = TTmp.Len();


			return BaseLen;
		}
		if (TmpCnt >= 1)
		{

			ChVec3 TmpPos;

			float TmpLen;

			TmpPos = FaceVer[TmpNum] - _Pos;

			TmpLen = TmpPos.Len();

			TmpPos.Cross((FaceVer[TmpNum] - _Pos)
				, (FaceVer[(TmpNum + 1) %3] - FaceVer[TmpNum]));

			BaseLen = GetLenToPosPlane(
				_Pos
				, FaceVer[TmpNum]
				, FaceVer[(TmpNum + 1) % 3]
				, (FaceVer[TmpNum] + TmpPos));

			return BaseLen;

		}



		return -1.0f;
	}


}

///////////////////////////////////////////////////////////////////////////////////

float ChObjectController9::GetLenToPosPlane(
	const D3DXVECTOR3& _Pos
	, const D3DXVECTOR3& _FaceVer1
	, const D3DXVECTOR3& _FaceVer2
	, const D3DXVECTOR3& _FaceVer3)
{

	ChVec3 Normal;

	Normal = ChMath::GetFaceNormal(
		_FaceVer1
		, _FaceVer2
		, _FaceVer3);

	ChVec3 Tmp = _Pos - _FaceVer1;

	return std::abs(Normal.GetDot(Normal,Tmp));

}

///////////////////////////////////////////////////////////////////////////////////

void ChObjectController9::LookObjectAxis(
	ChVec3_9&_OutVec
	, const ChMat_9&_OffsetMat
	, const ChMat_9& _ObjectMat)
{
	ChMat_9 TmpMat;
	ChVec3_9 TmpVec;
	TmpVec = _OffsetMat;

	D3DXMatrixInverse(&TmpMat, NULL, &_ObjectMat);

	D3DXVec3TransformCoord(&TmpVec, &TmpVec, &TmpMat);

	D3DXVec3Cross(&TmpVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &TmpVec);

	_OutVec = TmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

void ChObjectController9::SimpleOffsetAnimation(
	ChMat_9& _NowMat
	, const ChQua_9& _StartQua
	, const ChQua_9& _EndQua
	, const float _EndTime
	, const float _NowTime)
{

	D3DXQUATERNION TmpQua;

	D3DXQuaternionSlerp(&TmpQua, &_StartQua, &_EndQua, _NowTime);

	D3DXMatrixRotationQuaternion(&_NowMat, &TmpQua);

}

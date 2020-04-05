
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
#include"../ChObjectController/ChObjectController9.h"
#include"ChPhysicalBase9.h"

using namespace ChMesh;

///////////////////////////////////////////////////////////////////////////////////
//ChPhysicalBase9メソッド
///////////////////////////////////////////////////////////////////////////////////

void ChPhysicalBase9::SetMesh(const ChPtr::Shared<Mesh9> _SmpX)
{
	if (_SmpX == nullptr)return;
	WpXList.push_back(_SmpX);

}

///////////////////////////////////////////////////////////////////////////////////
//ChGravity9メソッド
///////////////////////////////////////////////////////////////////////////////////

void ChGravity9::Init(const float _FPS)
{
	FPS = _FPS;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChGravity9::UpDate(
	ChVec3_9* _Pos
	, const ChVec3_9* _MoveDir)
{
	Vec = ChVec3_9(0.0f, 0.0f, 0.0f);

	
	for (unsigned short i = 0; i < WpXList.size(); i++)
	{
		if (WpXList.empty())return ChStd::False;

		auto TmpX = WpXList[i].lock();

		if (TmpX == nullptr)
		{
			WpXList.erase(WpXList.begin() + i);
			i--;
			continue;
		}

		float TmpLen;
		ChVec3_9 TmpVec(0.0f, 0.0f, 0.0f);

		Vec = ChVec3_9(0.0f, -1.0f, 0.0f);

		Pow += G / FPS;

		Pow -= _MoveDir->y;

		if (_MoveDir->y > 0.0f)
		{
			TmpSpeed = _MoveDir->y;
			return ChStd::True;
		}

		if (-TmpSpeed >= Pow)Pow = -TmpSpeed;
		TmpSpeed = 0.0f;

		ChVec3_9 TmpPos = *_Pos;
		TmpPos.y += VirtualHeight;
		
		DWORD TmpD;

		if (!ChObjCon9().MeshHitRay(
			TmpD
			, TmpLen
			,TmpX
			, ChMat_9()
			, TmpPos
			, Vec))continue;

		if (TmpLen - BaseLen - VirtualHeight < Pow) {
			Vec *= (TmpLen - BaseLen - VirtualHeight);
			*_Pos = Vec + TmpPos;
			_Pos->y -= _MoveDir->y;
			Pow = 0.0f;

			return ChStd::True;
		}

		Vec *= Pow;
		*_Pos += Vec;
		return ChStd::True;
	}

	return ChStd::False;
}

///////////////////////////////////////////////////////////////////////////////////
//ChPushBack9メソッド
///////////////////////////////////////////////////////////////////////////////////

void ChPushBack9::Init()
{

}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChPushBack9::UpDate(ChVec3_9* _Pos, const ChVec3_9* _Dir)
{
	Vec = ChVec3_9(0.0f, 0.0f, 0.0f);
	ChVec3_9 TmpVec;
	ChVec3_9 TmpPos;
	float Len;



	for (unsigned short i = 0; i < WpXList.size(); i++)
	{

		if (WpXList.empty())return ChStd::False;

		auto TmpX = WpXList[i].lock();

		if (TmpX == nullptr)
		{
			WpXList.erase(WpXList.begin() + i);
			i--;
			continue;
		}

		TmpVec = *_Dir;
		TmpPos = *_Pos;

		Len = TmpVec.GetLen();

		TmpVec.Normalize();

		float TmpLen = 0.0f;
		DWORD FaceNum;

		if (!ObjCon->MeshHitRay(
			FaceNum
			, TmpLen
			, TmpX
			, ChMat_9()
			, TmpPos
			, TmpVec))continue;

		ChVec3_9 TmpDir;

		TmpDir = TmpX->GetFace()[FaceNum]->Normal;
		float TmpDot = D3DXVec3Dot(&TmpDir, &-TmpVec);

		if (TmpDot == 0.0f)continue;

		TmpDot = fabsf(TmpDot);

		float Limit = BackLine / TmpDot;

		if (Limit < 0)Limit *= -1;

		if (TmpLen - Len >= Limit)continue;

		*_Pos += TmpDir * (Limit - TmpLen + Len) * TmpDot;

		return ChStd::True;



	}

	return ChStd::False;

}

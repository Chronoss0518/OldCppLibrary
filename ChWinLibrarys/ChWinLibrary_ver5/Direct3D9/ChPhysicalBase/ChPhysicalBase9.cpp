
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"../ChMesh/ChBaseMesh9.h"
#include"../ChPolygonBoard/ChPolygonBoard9.h"
#include"../ChObjectController/ChObjectController9.h"
#include"ChPhysicalBase9.h"

using namespace ChMesh;

///////////////////////////////////////////////////////////////////////////////////
//ChPhysicalBase9メソッド
///////////////////////////////////////////////////////////////////////////////////

void ChPhysicalBase9::SetMesh(const ChPtr::Shared<Mesh9> _smpX)
{
	if (_smpX == nullptr)return;
	wpXList.push_back(_smpX);

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
	ChVec3_9* _pos
	, const ChVec3_9* _moveDir)
{
	vec = ChVec3_9(0.0f, 0.0f, 0.0f);

	
	for (unsigned short i = 0; i < wpXList.size(); i++)
	{
		if (wpXList.empty())return false;

		auto tmpX = wpXList[i].lock();

		if (tmpX == nullptr)
		{
			wpXList.erase(wpXList.begin() + i);
			i--;
			continue;
		}

		float tmpLen;
		ChVec3_9 tmpVec(0.0f, 0.0f, 0.0f);

		vec = ChVec3_9(0.0f, -1.0f, 0.0f);

		pow += g / FPS;

		pow -= _moveDir->y;

		if (_moveDir->y > 0.0f)
		{
			tmpSpeed = _moveDir->y;
			return true;
		}

		if (-tmpSpeed >= pow)pow = -tmpSpeed;
		tmpSpeed = 0.0f;

		ChVec3_9 tmpPos = *_pos;
		tmpPos.y += virtualHeight;
		
		DWORD tmpD;

		if (!ChObjCon9().MeshHitRay(
			tmpD
			, tmpLen
			,tmpX
			, ChMat_9()
			, tmpPos
			, vec))continue;

		if (tmpLen - baseLen - virtualHeight < pow) {
			vec *= (tmpLen - baseLen - virtualHeight);
			*_pos = vec + tmpPos;
			_pos->y -= _moveDir->y;
			pow = 0.0f;

			return true;
		}

		vec *= pow;
		*_pos += vec;
		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////
//ChPushBack9メソッド
///////////////////////////////////////////////////////////////////////////////////

void ChPushBack9::Init()
{

}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChPushBack9::UpDate(ChVec3_9* _pos, const ChVec3_9* _dir)
{
	vec = ChVec3_9(0.0f, 0.0f, 0.0f);
	ChVec3_9 tmpVec;
	ChVec3_9 tmpPos;
	float len;



	for (unsigned short i = 0; i < wpXList.size(); i++)
	{

		if (wpXList.empty())return false;

		auto tmpX = wpXList[i].lock();

		if (tmpX == nullptr)
		{
			wpXList.erase(wpXList.begin() + i);
			i--;
			continue;
		}

		tmpVec = *_dir;
		tmpPos = *_pos;

		len = tmpVec.GetLen();

		tmpVec.Normalize();

		float tmpLen = 0.0f;
		DWORD faceNum;

		if (!objCon->MeshHitRay(
			faceNum
			, tmpLen
			, tmpX
			, ChMat_9()
			, tmpPos
			, tmpVec))continue;

		ChVec3_9 tmpDir;

		tmpDir = tmpX->GetFace()[faceNum]->normal;

		tmpVec = -tmpVec;

		float tmpDot = D3DXVec3Dot(&tmpDir, &tmpVec);

		tmpVec = -tmpVec;

		if (tmpDot == 0.0f)continue;

		tmpDot = fabsf(tmpDot);

		float Limit = backLine / tmpDot;

		if (Limit < 0)Limit *= -1;

		if (tmpLen - len >= Limit)continue;

		*_pos += tmpDir * (Limit - tmpLen + len) * tmpDot;

		return true;



	}

	return false;

}

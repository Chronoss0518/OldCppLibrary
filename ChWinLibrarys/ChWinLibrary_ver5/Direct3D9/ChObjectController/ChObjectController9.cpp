
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

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
	, float& _len
	, const ChPtr::Shared<BaseMesh9>& _mesh
	, const ChMat_9& _obj
	, const ChVec3_9& _pos
	, const ChVec3_9& _dir)
{

	if (_mesh->GetMesh() == nullptr)
	{
		return false;
	}

	ChMat_9 tmpMat = _obj;

	float tmpLen = 0.0f;

	ChVec3_9 tmpPos, tmpDir;

	tmpMat.Inverse();

	tmpPos.MatPos(tmpMat, _pos);

	tmpDir.MatNormal(tmpMat, _dir);

	tmpDir.Normalize();

	BOOL tmpBool;

	D3DXIntersect(
		_mesh->InsMesh()
		, &tmpPos
		, &tmpDir
		, &tmpBool
		, &_Index
		, NULL
		, NULL
		, &tmpLen
		, NULL
		, NULL);

	if (!tmpBool)
	{
		return false;
	}

	_len = tmpLen;
	return true;


}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChObjectController9::MeshHitRay(
	float& _len
	, const ChPtr::Shared<ChMesh::BaseMesh9>& _mesh
	, const ChMat_9& _obj
	, const ChVec3_9& _pos
	, const ChVec3_9& _dir)

{
	DWORD tmpIndex;

	return MeshHitRay(tmpIndex, _len, _mesh, _obj, _pos, _dir);

}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChObjectController9::MeshHitRay(
	const ChPtr::Shared<ChMesh::BaseMesh9>& _mesh
	, const ChMat_9& _obj
	, const ChVec3_9& _pos
	, const ChVec3_9& _dir)

{
	float tmpLen;

	DWORD tmpIndex;

	return MeshHitRay(tmpIndex, tmpLen, _mesh, _obj, _pos, _dir);


}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChObjectController9::PorygonHitRay(
	float& _len
	, const ChPtr::Shared<PolygonBoard9> _poBo
	, const ChVec3_9& _pos
	, const ChVec3_9& _dir)
{
	float tmpLen;
	if (D3DXIntersectTri(&_poBo->GetPosVertex(0)->pos, &_poBo->GetPosVertex(1)->pos, &_poBo->GetPosVertex(2)->pos, &_pos, &_dir, NULL, NULL, &tmpLen)
		|| D3DXIntersectTri(&_poBo->GetPosVertex(0)->pos, &_poBo->GetPosVertex(2)->pos, &_poBo->GetPosVertex(3)->pos, &_pos, &_dir, NULL, NULL, &tmpLen))
	{
		_len = tmpLen;
		return true;
	}

	_len = -1;

	return false;

}

///////////////////////////////////////////////////////////////////////////////////

void ChObjectController9::SimpleAnimetion(
	ChMat_9& _nowMat
	, const ChMat_9& _startMat
	, const ChMat_9& _endMat
	, const float& _nowTime)
{
	ChQua_9 tmpSQua, tmpEQua, tmpNQua;
	D3DXVECTOR3 tmpSVec, tmpEVec, tmpNVec;

	D3DXQuaternionRotationMatrix(&tmpSQua, &_startMat);
	D3DXQuaternionRotationMatrix(&tmpEQua, &_endMat);

	
	auto tmp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVec3TransformCoord(&tmpSVec, &tmp, &_startMat);
	D3DXVec3TransformCoord(&tmpEVec, &tmp, &_endMat);

	D3DXQuaternionSlerp(&tmpNQua, &tmpSQua, &tmpEQua, _nowTime);

	D3DXVec3Lerp(&tmpNVec, &tmpSVec, &tmpEVec, _nowTime);

	D3DXMatrixRotationQuaternion(&_nowMat, &tmpNQua);

	_nowMat._41 = tmpNVec.x;
	_nowMat._42 = tmpNVec.y;
	_nowMat._43 = tmpNVec.z;


}

///////////////////////////////////////////////////////////////////////////////////

void ChObjectController9::MatrixBillboard(
	ChMat_9& _OutObj
	, const ChVec3_9& _objPos
	, const  ChMat_9& _camMat)
{

	ChMat_9 tmpMat = _camMat;

	tmpMat.Inverse();

	_OutObj = tmpMat;

	_OutObj = _objPos;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChObjectController9::LengthDecision(
	const ChMat_9 &_mat1
	, const ChMat_9 &_mat2
	, const float _matLen
	, const char _maskDirection)
{
	float tmpLen;
	D3DXVECTOR3 tmpVec1, tmpVec2;
	
	auto tmp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVec3TransformCoord(&tmpVec1, &tmp, &_mat1);
	D3DXVec3TransformCoord(&tmpVec2, &tmp, &_mat2);
	switch (_maskDirection) {
	case 'x':
		tmpVec1.x = 0.0f;
		tmpVec2.x = 0.0f;
		break;
	case 'y':
		tmpVec1.y = 0.0f;
		tmpVec2.y = 0.0f;
		break;
	case 'z':
		tmpVec1.z = 0.0f;
		tmpVec2.z = 0.0f;
		break;
	default:
		break;
	}
	tmpVec1 -= tmpVec2;
	tmpLen = D3DXVec3Length(&tmpVec1);
	if (tmpLen < _matLen)return true;

	return false;

}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChObjectController9::Hit2DDecision(
	const ChMat_9& _obj1Mat
	, const ChMat_9& _obj2Mat
	, const ChPtr::Shared<Texture9>&_obj1Tex
	, const ChPtr::Shared<Texture9>&_obj2Tex)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////

float ChObjectController9::GetLenToPosTri(
	const D3DXVECTOR3& _pos
	, const D3DXVECTOR3& _faceVer1
	, const D3DXVECTOR3& _faceVer2
	, const D3DXVECTOR3& _faceVer3)
{
	ChVec3 faceVer[3] =
	{
		_faceVer1,
		_faceVer2,
		_faceVer3
	};

	float baseLen = 0.0f;

	baseLen = GetLenToPosPlane(_pos, _faceVer1, _faceVer2, _faceVer3);

	ChVec3 normal;

	normal = ChMath::GetFaceNormal(
		_faceVer1
		, _faceVer2
		, _faceVer3);

	ChVec3 vPos = _pos + (normal * baseLen);

	char tmpNum = -1;
	unsigned char tmpCnt = 0;

	{
		for (unsigned char i = 0; i < 3; i++)
		{
			ChVec3 tmpVec;
			tmpVec.Cross((faceVer[(i + 1) % 3] - faceVer[i])
				, (_pos - faceVer[(i + 1) % 3]));

			ChVec3 TTmpVec = tmpVec * normal;

			for (unsigned char j = 0; j < 3; j++)
			{
				if (ChMath::IsPSign(TTmpVec.val[j]))continue;

				if(tmpNum <= 0)tmpNum = i;
				tmpCnt++;
				break;
			}


		}
	}

	{


		if (tmpCnt <= 0)
		{

			return baseLen;
		}

		if (tmpCnt <= 2)
		{
			ChVec3 TTmp;

			TTmp = faceVer[tmpNum] - _pos;
			baseLen = TTmp.Len();


			return baseLen;
		}
		if (tmpCnt >= 1)
		{

			ChVec3 tmpPos;

			float tmpLen;

			tmpPos = faceVer[tmpNum] - _pos;

			tmpLen = tmpPos.Len();

			tmpPos.Cross((faceVer[tmpNum] - _pos)
				, (faceVer[(tmpNum + 1) %3] - faceVer[tmpNum]));

			baseLen = GetLenToPosPlane(
				_pos
				, faceVer[tmpNum]
				, faceVer[(tmpNum + 1) % 3]
				, (faceVer[tmpNum] + tmpPos));

			return baseLen;

		}



		return -1.0f;
	}


}

///////////////////////////////////////////////////////////////////////////////////

float ChObjectController9::GetLenToPosPlane(
	const D3DXVECTOR3& _pos
	, const D3DXVECTOR3& _faceVer1
	, const D3DXVECTOR3& _faceVer2
	, const D3DXVECTOR3& _faceVer3)
{

	ChVec3 normal;

	normal = ChMath::GetFaceNormal(
		_faceVer1
		, _faceVer2
		, _faceVer3);

	ChVec3 tmp = _pos - _faceVer1;

	return std::abs(normal.GetDot(normal,tmp));

}

///////////////////////////////////////////////////////////////////////////////////

void ChObjectController9::LookObjectAxis(
	ChVec3_9&_OutVec
	, const ChMat_9&_OffsetMat
	, const ChMat_9& _objectMat)
{
	ChMat_9 tmpMat;
	ChVec3_9 tmpVec;
	tmpVec = _OffsetMat;

	D3DXMatrixInverse(&tmpMat, NULL, &_objectMat);

	D3DXVec3TransformCoord(&tmpVec, &tmpVec, &tmpMat);

	auto tmp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXVec3Cross(&tmpVec, &tmp, &tmpVec);

	_OutVec = tmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

void ChObjectController9::SimpleOffsetAnimation(
	ChMat_9& _nowMat
	, const ChQua_9& _startQua
	, const ChQua_9& _endQua
	, const float _endTime
	, const float _nowTime)
{

	D3DXQUATERNION tmpQua;

	D3DXQuaternionSlerp(&tmpQua, &_startQua, &_endQua, _nowTime);

	D3DXMatrixRotationQuaternion(&_nowMat, &tmpQua);

}

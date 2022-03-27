
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../../CPP/ChBitBool/ChBitBool.h"

#include"../ChAnimationObject/ChAnimationObject9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"../ChMesh/ChBaseMesh9.h"
#include"ChBoundingBox9.h"

using namespace ChMesh;


///////////////////////////////////////////////////////////////////////////////////
//ChBoundingBoxÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////


void BoundingBox9::SetBBox(const ChPtr::Shared<Mesh9>& _mesh)
{
	if (_mesh == nullptr)return;
	if(ChPtr::NullCheck(_mesh->GetMesh()))return;
	ChVec3_9 maxVec;
	ChVec3_9 minVec;

	DWORD vertexNum = _mesh->GetMesh()->GetNumVertices();
	DWORD vSize = _mesh->GetMesh()->GetNumBytesPerVertex();
	BYTE *p;

	_mesh->GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&p);

	D3DXComputeBoundingBox((D3DXVECTOR3*)p, vertexNum, vSize, &minVec, &maxVec);

	_mesh->GetMesh()->UnlockVertexBuffer();

	main = minVec;

	depth = maxVec - minVec;

}

///////////////////////////////////////////////////////////////////////////////////

void BoundingBox9::SetBSphere(const ChPtr::Shared<Mesh9>& _mesh)
{
	if (_mesh == nullptr)return;
	if (ChPtr::NullCheck(_mesh->GetMesh()))return;

	DWORD vertexNum = _mesh->GetMesh()->GetNumVertices();
	DWORD vSize = _mesh->GetMesh()->GetNumBytesPerVertex();
	BYTE *p;

	_mesh->GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&p);

	D3DXComputeBoundingSphere((D3DXVECTOR3*)p, vertexNum, vSize, &main, &radius);

	_mesh->GetMesh()->UnlockVertexBuffer();
}

///////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<ChVec3_9>> BoundingBox9::GetPosition()
{
	std::vector<ChPtr::Shared<ChVec3_9>> tmpPos;
	if (main == depth)return tmpPos;

	tmpPos.push_back(ChPtr::Make_S<ChVec3_9>(main.x, main.y, main.z));

	tmpPos.push_back(ChPtr::Make_S<ChVec3_9>(main.x + depth.x, main.y, main.z));

	tmpPos.push_back(ChPtr::Make_S<ChVec3_9>(main.x, main.y + depth.y, main.z));

	tmpPos.push_back(ChPtr::Make_S<ChVec3_9>(main.x, main.y, main.z + depth.z));

	tmpPos.push_back(ChPtr::Make_S<ChVec3_9>(main.x + depth.x, main.y + depth.y, main.z));

	tmpPos.push_back(ChPtr::Make_S<ChVec3_9>(main.x + depth.x, main.y, main.z + depth.z));

	tmpPos.push_back(ChPtr::Make_S<ChVec3_9>(main.x, main.y + depth.y, main.z + depth.z));

	tmpPos.push_back(ChPtr::Make_S<ChVec3_9>(main.x + depth.x, main.y + depth.y, main.z + depth.z));

	return tmpPos;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool BoundingBox9::IsHitToPos(
	const ChMat_9* _mat
	, const ChVec3_9* _pos)
{

	ChVec3_9 pPos = *_pos;

	ChMat_9 tmpMat = *_mat;

	tmpMat.Inverse();

	pPos.MatPos(tmpMat, pPos);

	if (!(main.y < pPos.y
		&& main.y + depth.y > pPos.y))return false;

	if (!(main.x < pPos.x
		&& main.x + depth.x > pPos.x))return false;

	if (!(main.z < pPos.z
		&& main.z + depth.z > pPos.z))return false;

	return true;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool BoundingBox9::IsHitToB_Box(
	const ChMat_9* _mat
	, const ChB_Box9* _pos)
{

	const unsigned char boxVertex = 8;

	ChB_Box9 pBox = *_pos;

	ChMat_9 tmpMat = *_mat;

	ChVec3_9 tmpPos;

	tmpPos = pBox.main + pBox.depth;

	tmpMat.Inverse();

	tmpPos.MatPos(tmpMat, tmpPos);
	pBox.main.MatPos(tmpMat, pBox.main);

	for (unsigned char i = 0; i < boxVertex; i++)
	{
		if (!(main.y < tmpPos.y + pBox.main.y
			&& main.y + depth.y > tmpPos.y))continue;

		if (!(main.x < tmpPos.x + pBox.main.x
			&& main.x + depth.x > tmpPos.x))continue;

		if (!(main.z < tmpPos.z + pBox.main.z
			&& main.z + depth.z > tmpPos.z))continue;

		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool BoundingBox9::IsHitToBull(
	const ChMat_9* _mat
	, const ChVec3_9* _pos
	, const float _r)
{

	ChMat_9 tmpMat = *_mat;
	ChVec3_9 tmpPos = *_pos;
	ChVec3_9 tmpVec;

	tmpMat.Inverse();

	tmpPos.MatPos(tmpMat, tmpPos);
	tmpVec = tmpPos;

	tmpVec.Normalize();
	tmpVec *= _r;

	if (!(main.y < tmpPos.y + tmpVec.y
		&& main.y + depth.y > tmpPos.y - tmpVec.y))return false;

	if (!(main.x < tmpPos.x + tmpVec.x
		&& main.x + depth.x > tmpPos.x - tmpVec.x))return false;

	if (!(main.z < tmpPos.z + tmpVec.z
		&& main.z + depth.z > tmpPos.z - tmpVec.z))return false;

	return true;

}

///////////////////////////////////////////////////////////////////////////////////

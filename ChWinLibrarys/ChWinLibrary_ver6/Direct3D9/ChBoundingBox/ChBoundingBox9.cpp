
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


void BoundingBox9::SetBBox(const ChPtr::Shared<Mesh9>& _Mesh)
{
	if (_Mesh == nullptr)return;
	if(ChPtr::NullCheck(_Mesh->GetMesh()))return;
	ChVec3_9 MaxVec;
	ChVec3_9 MinVec;

	DWORD VertexNum = _Mesh->GetMesh()->GetNumVertices();
	DWORD VSize = _Mesh->GetMesh()->GetNumBytesPerVertex();
	BYTE *P;

	_Mesh->GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&P);

	D3DXComputeBoundingBox((D3DXVECTOR3*)P, VertexNum, VSize, &MinVec, &MaxVec);

	_Mesh->GetMesh()->UnlockVertexBuffer();

	Main = MinVec;

	Depth = MaxVec - MinVec;

}

///////////////////////////////////////////////////////////////////////////////////

void BoundingBox9::SetBSphere(const ChPtr::Shared<Mesh9>& _Mesh)
{
	if (_Mesh == nullptr)return;
	if (ChPtr::NullCheck(_Mesh->GetMesh()))return;

	DWORD VertexNum = _Mesh->GetMesh()->GetNumVertices();
	DWORD VSize = _Mesh->GetMesh()->GetNumBytesPerVertex();
	BYTE *P;

	_Mesh->GetMesh()->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&P);

	D3DXComputeBoundingSphere((D3DXVECTOR3*)P, VertexNum, VSize, &Main, &Radius);

	_Mesh->GetMesh()->UnlockVertexBuffer();
}

///////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<ChVec3_9>> BoundingBox9::GetPosition()
{
	std::vector<ChPtr::Shared<ChVec3_9>> TmpPos;
	if (Main == Depth)return TmpPos;

	TmpPos.push_back(ChPtr::Make_S<ChVec3_9>(Main.x, Main.y, Main.z));

	TmpPos.push_back(ChPtr::Make_S<ChVec3_9>(Main.x + Depth.x, Main.y, Main.z));

	TmpPos.push_back(ChPtr::Make_S<ChVec3_9>(Main.x, Main.y + Depth.y, Main.z));

	TmpPos.push_back(ChPtr::Make_S<ChVec3_9>(Main.x, Main.y, Main.z + Depth.z));

	TmpPos.push_back(ChPtr::Make_S<ChVec3_9>(Main.x + Depth.x, Main.y + Depth.y, Main.z));

	TmpPos.push_back(ChPtr::Make_S<ChVec3_9>(Main.x + Depth.x, Main.y, Main.z + Depth.z));

	TmpPos.push_back(ChPtr::Make_S<ChVec3_9>(Main.x, Main.y + Depth.y, Main.z + Depth.z));

	TmpPos.push_back(ChPtr::Make_S<ChVec3_9>(Main.x + Depth.x, Main.y + Depth.y, Main.z + Depth.z));

	return TmpPos;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool BoundingBox9::IsHitToPos(
	const ChMat_9* _Mat
	, const ChVec3_9* _Pos)
{

	ChVec3_9 PPos = *_Pos;

	ChMat_9 TmpMat = *_Mat;

	TmpMat.Inverse();

	PPos.MatPos(TmpMat, PPos);

	if (!(Main.y < PPos.y
		&& Main.y + Depth.y > PPos.y))return false;

	if (!(Main.x < PPos.x
		&& Main.x + Depth.x > PPos.x))return false;

	if (!(Main.z < PPos.z
		&& Main.z + Depth.z > PPos.z))return false;

	return true;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool BoundingBox9::IsHitToB_Box(
	const ChMat_9* _Mat
	, const ChB_Box9* _Pos)
{

	const unsigned char BoxVertex = 8;

	ChB_Box9 PBox = *_Pos;

	ChMat_9 TmpMat = *_Mat;

	ChVec3_9 TmpPos;

	TmpPos = PBox.Main + PBox.Depth;

	TmpMat.Inverse();

	TmpPos.MatPos(TmpMat, TmpPos);
	PBox.Main.MatPos(TmpMat, PBox.Main);

	for (unsigned char i = 0; i < BoxVertex; i++)
	{
		if (!(Main.y < TmpPos.y + PBox.Main.y
			&& Main.y + Depth.y > TmpPos.y))continue;

		if (!(Main.x < TmpPos.x + PBox.Main.x
			&& Main.x + Depth.x > TmpPos.x))continue;

		if (!(Main.z < TmpPos.z + PBox.Main.z
			&& Main.z + Depth.z > TmpPos.z))continue;

		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool BoundingBox9::IsHitToBull(
	const ChMat_9* _Mat
	, const ChVec3_9* _Pos
	, const float _R)
{

	ChMat_9 TmpMat = *_Mat;
	ChVec3_9 TmpPos = *_Pos;
	ChVec3_9 TmpVec;

	TmpMat.Inverse();

	TmpPos.MatPos(TmpMat, TmpPos);
	TmpVec = TmpPos;

	TmpVec.Normalize();
	TmpVec *= _R;

	if (!(Main.y < TmpPos.y + TmpVec.y
		&& Main.y + Depth.y > TmpPos.y - TmpVec.y))return false;

	if (!(Main.x < TmpPos.x + TmpVec.x
		&& Main.x + Depth.x > TmpPos.x - TmpVec.x))return false;

	if (!(Main.z < TmpPos.z + TmpVec.z
		&& Main.z + Depth.z > TmpPos.z - TmpVec.z))return false;

	return true;

}

///////////////////////////////////////////////////////////////////////////////////

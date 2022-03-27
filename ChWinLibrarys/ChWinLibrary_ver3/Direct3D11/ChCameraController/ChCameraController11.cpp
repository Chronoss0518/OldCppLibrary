
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"ChCameraController11.h"

using namespace ChD3D11;


ChMat_11 CameraController11::GetViewMat(
	const ChVec3_11& _Pos
	, const ChVec3_11& _Dir
	,const ChVec3_11& _Up)
{

	ChVec3_11 Dir = _Dir;

	ChVec3_11 Up = _Up;

	Dir.Normalize();
	Up.Normalize();

	ChMat_11 TmpMat;

	TmpMat.CreateViewMat(_Pos, Dir, Up);

	CamMat = TmpMat;

	return TmpMat;
}

ChMat_11 CameraController11::GetViewMat(
	const ChVec3_11& _Pos
	, const ChVec3_11& _Dir)
{

	ChVec3_11 Dir = _Dir;

	ChQua_11 TmpQua;

	TmpQua.RotLookAt((Dir + _Pos), _Pos);

	ChMat_11 TmpMat;

	TmpMat.RotQua(TmpQua);

	ChVec3_11 TmpHead = ChVec3_11(0.0f,1.0f,0.0f);

	TmpHead.MatNormal(TmpMat, TmpHead);

	return GetViewMat(_Pos, _Dir, TmpHead);

}

ChMat_11 CameraController11::GetViewMat(
	const ChVec3_11& _Pos
	, const ChQua_11& _Rot)
{

	ChMat_11 TmpMat;

	TmpMat.RotQua(_Rot);

	ChVec3_11 Dir;
	ChVec3_11 Head;

	Dir.MatNormal(TmpMat);
	Head.MatNormal(TmpMat, ChVec3_11(0.0f, 1.0f, 0.0f));

	return GetViewMat(_Pos, Dir, Head);
}
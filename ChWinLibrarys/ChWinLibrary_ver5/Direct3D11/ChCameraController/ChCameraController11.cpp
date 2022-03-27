
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"ChCameraController11.h"

using namespace ChD3D11;


ChMat_11 CameraController11::GetViewMat(
	const ChVec3_11& _pos
	, const ChVec3_11& _dir
	,const ChVec3_11& _up)
{

	ChVec3_11 dir = _dir;

	ChVec3_11 up = _up;

	dir.Normalize();
	up.Normalize();

	ChMat_11 tmpMat;

	tmpMat.CreateViewMat(_pos, dir, up);

	camMat = tmpMat;

	return tmpMat;
}

ChMat_11 CameraController11::GetViewMat(
	const ChVec3_11& _pos
	, const ChVec3_11& _dir)
{

	ChVec3_11 dir = _dir;

	ChQua_11 tmpQua;

	tmpQua.RotLookAt((dir + _pos), _pos);

	ChMat_11 tmpMat;

	tmpMat.RotQua(tmpQua);

	ChVec3_11 tmpHead = ChVec3_11(0.0f,1.0f,0.0f);

	tmpHead.MatNormal(tmpMat, tmpHead);

	return GetViewMat(_pos, _dir, tmpHead);

}

ChMat_11 CameraController11::GetViewMat(
	const ChVec3_11& _pos
	, const ChQua_11& _rot)
{

	ChMat_11 tmpMat;

	tmpMat.RotQua(_rot);

	ChVec3_11 dir;
	ChVec3_11 head;

	dir.MatNormal(tmpMat);
	head.MatNormal(tmpMat, ChVec3_11(0.0f, 1.0f, 0.0f));

	return GetViewMat(_pos, dir, head);
}
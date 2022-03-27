
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"ChCameraController9.h"

///////////////////////////////////////////////////////////////////////////////////////
//CameraController���\�b�h
///////////////////////////////////////////////////////////////////////////////////////

D3DXMATRIX ChD3D9::CameraController::MakeViewMatrix(
	const ChD3D9::CamObj& _cal)
{
	ChMat_9 tmpMat;

	ChVec3_9 tmpHead = _cal.head;

	tmpHead.Normalize();

	// ���_�s��̐ݒ�
	D3DXMatrixLookAtLH(
		&tmpMat,
		&_cal.pos,	// �J�����̈ʒu
		&_cal.look,	// �J�����̎��_
		&tmpHead	// �J�����̓��̕���
	);

	lastCamData = _cal;

	viewMat = tmpMat;

	return tmpMat;

}

///////////////////////////////////////////////////////////////////////////////////

D3DXMATRIX ChD3D9::CameraController::MakeViewMatrix(
	const D3DXVECTOR3& _calPos
	, const D3DXVECTOR3& _calLook
	, const D3DXVECTOR3& _calHead)
{

	ChMat_9 tmpMat;
	ChVec3_9 tmpHead = _calLook - _calPos;

	if(D3DXVec3Length(&_calHead) == 0.0f){

		tmpHead.Normalize();

		ChQua_9 tmpQua;

		tmpQua = tmpHead;

		tmpMat = tmpQua;

		tmpHead.MatNormal(tmpMat, ChVec3_9(0.0f, 1.0f, 0.0f));

	}
	else
	{
		tmpHead = _calHead;
	}


	// ���_�s��̐ݒ�
	D3DXMatrixLookAtLH(
		&tmpMat,
		&_calPos,	// �J�����̈ʒu
		&_calLook,	// �J�����̎��_
		&tmpHead	// �J�����̓��̕���
	);

	viewMat = tmpMat;

	lastCamData.pos = _calPos;
	lastCamData.look = _calLook;
	lastCamData.head = tmpHead;

	return tmpMat;
}

///////////////////////////////////////////////////////////////////////////////////

D3DXMATRIX ChD3D9::CameraController::MakeProjectionMatrix(
	const ChD3D9::CamObj& _cal
	, const float _windWidth
	, const float _windHeight
	, const float _viewAngDeg)
{
	ChMat_9 tmpMat;


	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(
		&tmpMat
		, D3DXToRadian(_viewAngDeg)
		, _windWidth / _windHeight
		, _cal.lMin, _cal.lMax);

	projectionMat = tmpMat;

	lastCamData = _cal;

	return tmpMat;

}

///////////////////////////////////////////////////////////////////////////////////

D3DXMATRIX ChD3D9::CameraController::MakeProjectionMatrix(
	const float _lookNear
	, const float _lookDistant
	, const float _windWidth
	, const float _windHeight
	, const float _viewAngDeg)
{

	ChMat_9 tmpMat;

	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(
		&tmpMat
		, D3DXToRadian(_viewAngDeg)
		, _windWidth / _windHeight
		, _lookNear, _lookDistant);

	projectionMat = tmpMat;

	lastCamData.lMin = _lookNear;
	lastCamData.lMax = _lookDistant;

	return tmpMat;
}

///////////////////////////////////////////////////////////////////////////////////

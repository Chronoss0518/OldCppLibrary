
#include"../../CGameIncludeFile.h"

#ifdef CopyRight_Chronoss_2018Y_08M

///////////////////////////////////////////////////////////////////////////////////////
//ChObjectControllerƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

bool ChObjectController::SmpXFileHitRay(
	const ChSmpX *_XFile
	, const D3DXMATRIX *_Obj
	, const D3DXVECTOR3 * _Pos
	, const D3DXVECTOR3 *_Dir
	, float *_Len)
{
	D3DXMATRIX TmpMat;
	D3DXVECTOR3 TmpPos, TmpDir;
	D3DXMatrixInverse(&TmpMat, NULL, _Obj);
	D3DXVec3TransformCoord(&TmpPos, _Pos, &TmpMat);
	D3DXVec3TransformNormal(&TmpDir, _Dir, &TmpMat);
	BOOL TmpBool;
	D3DXIntersect(_XFile->LpMesh, &TmpPos, &TmpDir, &TmpBool, NULL, NULL, NULL, _Len, NULL, NULL);
	if (TmpBool)return TRUE;
	*_Len = -1.0f;
	return FALSE;

}

///////////////////////////////////////////////////////////////////////////////////

bool ChObjectController::PorygonHitRay(
	const ChPoBo *_PoBo
	, const D3DXVECTOR3 *_Pos
	, D3DXVECTOR3 *_Dir
	, float *_Len)
{

	if (D3DXIntersectTri(&_PoBo->Ver[0].pos, &_PoBo->Ver[1].pos, &_PoBo->Ver[2].pos, _Pos, _Dir, NULL, NULL, _Len)
		|| D3DXIntersectTri(&_PoBo->Ver[0].pos, &_PoBo->Ver[2].pos, &_PoBo->Ver[3].pos, _Pos, _Dir, NULL, NULL, _Len))return TRUE;
	*_Len = -1.0f;
	return FALSE;

}

///////////////////////////////////////////////////////////////////////////////////

bool ChObjectController::SimpleAnimetion(
	const D3DXMATRIX *_StartMat
	, const D3DXMATRIX *_EndMat
	, const float _EndTime
	, float *_NowTime
	, D3DXMATRIX *_NowMat
	, float _FrameSpeed)
{
	if (_FrameSpeed <= 0.0f)return FALSE;
	D3DXQUATERNION TmpSQua, TmpEQua, TmpNQua;
	D3DXVECTOR3 TmpSVec, TmpEVec, TmpNVec;
	float AniTime = (*_NowTime / _EndTime);

	D3DXQuaternionRotationMatrix(&TmpSQua, _StartMat);
	D3DXQuaternionRotationMatrix(&TmpEQua, _EndMat);

	D3DXVec3TransformCoord(&TmpSVec, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), _StartMat);
	D3DXVec3TransformCoord(&TmpEVec, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), _EndMat);

	D3DXQuaternionSlerp(&TmpNQua, &TmpSQua, &TmpEQua, AniTime);

	D3DXVec3Lerp(&TmpNVec, &TmpSVec, &TmpEVec, AniTime);

	D3DXMatrixRotationQuaternion(_NowMat, &TmpNQua);

	_NowMat->_41 = TmpNVec.x;
	_NowMat->_42 = TmpNVec.y;
	_NowMat->_43 = TmpNVec.z;
	
	*_NowTime += (1.0f/_FrameSpeed);
	if (*_NowTime > _EndTime) {
		*_NowTime -= _EndTime;
		return TRUE;
	}
	return FALSE;

}

///////////////////////////////////////////////////////////////////////////////////

void ChObjectController::MatrixBillboard(
	D3DXMATRIX *_OutObj
	, const D3DXVECTOR3 *_ObjPos
	, const D3DXMATRIX *_CamMat)
{
	D3DXMatrixInverse(_OutObj, NULL, _CamMat);
	_OutObj->_41 = _ObjPos->x;
	_OutObj->_42 = _ObjPos->y;
	_OutObj->_43 = _ObjPos->z;
}

///////////////////////////////////////////////////////////////////////////////////

bool ChObjectController::LengthDecision(
	const D3DXMATRIX *_Mat1
	, const D3DXMATRIX *_Mat2
	, const float MatLen
	, const char _MaskDirection)
{
	float TmpLen;
	D3DXVECTOR3 TmpVec1,TmpVec2;
	D3DXVec3TransformCoord(&TmpVec1, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), _Mat1);
	D3DXVec3TransformCoord(&TmpVec2, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), _Mat2);
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
	if (TmpLen < MatLen)return TRUE;

	return FALSE;

}

///////////////////////////////////////////////////////////////////////////////////

bool ChObjectController::Hit2DDecision(
	const D3DXMATRIX *_Obj1Mat
	, const D3DXMATRIX *_Obj2Mat
	, const LpChTex *_Obj1Tex
	, const LpChTex *_Obj2Tex)
{
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////

void ChObjectController::LookObjectAxis(
	D3DXVECTOR3 *_OutVec
	, const D3DXMATRIX *_OffsetMat
	, const D3DXMATRIX *_ObjectMat)
{
	D3DXMATRIX TmpMat;
	D3DXVECTOR3 TmpVec;
	D3DXMatrixInverse(&TmpMat, NULL, _ObjectMat);

	D3DXVec3TransformCoord(&TmpVec, &D3DXVECTOR3(_OffsetMat->_41, _OffsetMat->_42, _OffsetMat->_43),&TmpMat);

	D3DXVec3Cross(&TmpVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &TmpVec);

	*_OutVec = TmpVec;

}

#endif

#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../../BaseIncluder/ChD3D9I.h"

///////////////////////////////////////////////////////////////////////////////////
//ChVector3_9 Operator//
///////////////////////////////////////////////////////////////////////////////////

ChVector3_9& ChVector3_9::operator=(const D3DXVECTOR3& _cm)
{
	if (this == &_cm)return *this;
	D3DXVECTOR3::operator=(_cm);
	return *this;
}

ChVector3_9& ChVector3_9::operator = (const D3DXQUATERNION& _cm)
{
	D3DXMATRIX tmpMat;

	D3DXMatrixRotationQuaternion(&tmpMat, &_cm);

	auto tmp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXVec3TransformNormal(this, &tmp, &tmpMat);

	return *this;
}

ChVector3_9& ChVector3_9::operator =(const D3DXMATRIX& _mat)
{
	x = _mat._41;
	y = _mat._42;
	z = _mat._43;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////
//ChVector3_9 Method//
///////////////////////////////////////////////////////////////////////////////////

float ChVector3_9::GetLen(const D3DXVECTOR3& _vec)
{
	ChVector3_9 tmpVec;
	tmpVec = *this - _vec;

	return D3DXVec3Length(&tmpVec);
}

///////////////////////////////////////////////////////////////////////////////////

float ChVector3_9::GetRadian(const D3DXVECTOR3& _vec)
{
	ChVector3_9 tmpVec1, tmpVec2;
	tmpVec1 = *this;
	tmpVec2 = _vec;
	tmpVec1.Normalize();
	tmpVec2.Normalize();

	return acosf(D3DXVec3Dot(&tmpVec1, &tmpVec2));
}

///////////////////////////////////////////////////////////////////////////////////

float ChVector3_9::GetDegree(const D3DXVECTOR3& _vec)
{
	ChVector3_9 tmpVec1, tmpVec2;

	tmpVec1 = *this;
	tmpVec2 = _vec;

	tmpVec1.Normalize();
	tmpVec2.Normalize();

	return D3DXToDegree(acosf(D3DXVec3Dot(&tmpVec1, &tmpVec2)));
}

///////////////////////////////////////////////////////////////////////////////////

void ChVector3_9::Set0Param()
{
	*this = 0;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChVector3_9::CheckNormals() {

	if (fabsf(x) + fabsf(y) + fabsf(z) == 1.0f)return true;
	return false;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChVector3_9::CheckAll0() 
{

	if (fabsf(x) == 0.0f
		&& fabsf(y) == 0.0f
		&& fabsf(z) == 0.0f)return true;

	return false;
}

///////////////////////////////////////////////////////////////////////////////////

void ChVector3_9::Move(const float _x, const float _y, const float _z)
{
	*this += D3DXVECTOR3(_x, _y, _z);
}

///////////////////////////////////////////////////////////////////////////////////

void ChVector3_9::Move2D(const D3DXVECTOR3* _vec)
{
	D3DXVECTOR3 tmpVec = *_vec;

	tmpVec.x = 0.0f;
	tmpVec.y = 0.0f;

	*this += (*_vec - tmpVec);
}

///////////////////////////////////////////////////////////////////////////////////


void ChVector3_9::MatPos(const D3DXMATRIX& _mat, const D3DXVECTOR3& _vec)
{
	D3DXVec3TransformCoord(this, &_vec, &_mat);
}

///////////////////////////////////////////////////////////////////////////////////

void ChVector3_9::MatNormal(const D3DXMATRIX& _mat, const D3DXVECTOR3& _vec)
{
	D3DXVec3TransformNormal(this, &_vec, &_mat);
}

///////////////////////////////////////////////////////////////////////////////////

void ChVector3_9::Normalize()
{
	if (CheckNormals())return;
	float tmpLen = std::abs(this->x) + std::abs(this->y) + std::abs(this->z);
	if (tmpLen > 0.0f)*this /= tmpLen;
	else *this = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

///////////////////////////////////////////////////////////////////////////////////

void ChVector3_9::Lerp(
	const D3DXVECTOR3& _sVec
	, const D3DXVECTOR3& _eVec
	, const float _nowTime)
{
	D3DXVec3Lerp(this, &_sVec, &_eVec, _nowTime);
}

///////////////////////////////////////////////////////////////////////////////////

void ChVector3_9::CrossVec(const D3DXVECTOR3& _vec1, const D3DXVECTOR3& _vec2)
{
	D3DXVec3Cross(this, &_vec1, &_vec2);
}

///////////////////////////////////////////////////////////////////////////////////

float ChVector3_9::DotVec(const D3DXVECTOR3& _vec)
{
	return D3DXVec3Dot(&_vec, this);
}

///////////////////////////////////////////////////////////////////////////////////
//ChQuaternion_9 Operator//
///////////////////////////////////////////////////////////////////////////////////

ChQuaternion_9::operator D3DXVECTOR3()
{
	D3DXVECTOR3 tmpVec;

	D3DXMATRIX tmpMat;

	D3DXMatrixRotationQuaternion(&tmpMat, this);

	auto tmp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXVec3TransformNormal(&tmpVec, &tmp, &tmpMat);

	return tmpVec;
}

ChQuaternion_9::operator D3DXMATRIX()
{
	D3DXMATRIX tmpMat;

	D3DXMatrixRotationQuaternion(&tmpMat, this);

	return tmpMat;
}

ChQuaternion_9& ChQuaternion_9::operator=(const D3DXQUATERNION& _cm)
{
	if (this == &_cm)return *this;
	D3DXQUATERNION::operator =(_cm);
	return *this;
}

ChQuaternion_9& ChQuaternion_9::operator = (const D3DXMATRIX& _cm)
{
	D3DXQuaternionRotationMatrix(this, &_cm);

	return *this;
}

ChQuaternion_9& ChQuaternion_9::operator =(const D3DXVECTOR3& _cm)
{
	D3DXVECTOR3 tmpVec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 tmpVec2 = _cm;

	D3DXVec3Normalize(&tmpVec, &tmpVec);
	D3DXVec3Normalize(&tmpVec2, &tmpVec2);

	float tmpDot = D3DXVec3Dot(&tmpVec, &tmpVec2);

	D3DXVec3Cross(&tmpVec, &tmpVec, &tmpVec2);

	D3DXQuaternionRotationAxis(this, &tmpVec, tmpDot);

	return *this;

}

///////////////////////////////////////////////////////////////////////////////////
//ChQuaternion_9 Method//
///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_9::RotYPR(const float _x, const float _y, const float _z)
{
	D3DXQuaternionRotationYawPitchRoll(
		this
		, D3DXToRadian(_y)
		, D3DXToRadian(_x)
		, D3DXToRadian(_z));
}

///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_9::RotYPR(const D3DXVECTOR3& _vec)
{
	RotYPR(_vec.x, _vec.y, _vec.z);
}

///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_9::RotAxis(const D3DXVECTOR3* _vec, const float _ang)
{
	D3DXQuaternionRotationAxis(
		this
		, _vec
		, D3DXToRadian(_ang));
}

///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_9::RotMat(const D3DXMATRIX* _mat)
{
	D3DXQuaternionRotationMatrix(this, _mat);
}

///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_9::Lerp(
	const D3DXQUATERNION& _sQua
	, const D3DXQUATERNION& _eQua
	, const float _nowTime)
{
	D3DXQuaternionSlerp(this, &_sQua, &_eQua, _nowTime);
}

///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_9::Identity()
{
	D3DXQuaternionIdentity(this);
}

///////////////////////////////////////////////////////////////////////////////////
//ChMatrix_9 Operator//
///////////////////////////////////////////////////////////////////////////////////

ChMatrix_9::operator D3DXVECTOR3()const
{
	D3DXVECTOR3 tmpVec;

	tmpVec.x = _41;
	tmpVec.y = _42;
	tmpVec.z = _43;

	return tmpVec;
}

ChMatrix_9::operator D3DXQUATERNION()const
{
	D3DXQUATERNION tmpQua;

	D3DXQuaternionRotationMatrix(&tmpQua, this);

	return tmpQua;
}

ChMatrix_9& ChMatrix_9::operator =(const D3DXMATRIX& _cm)
{
	if (this == &_cm)return *this;
	D3DXMATRIX::operator=(_cm);
	return *this;
}

D3DXMATRIX& ChMatrix_9::operator = (const D3DXVECTOR3& _vec)
{
	_41 = _vec.x;
	_42 = _vec.y;
	_43 = _vec.z;
	return *this;
}

D3DXMATRIX& ChMatrix_9::operator = (const D3DXQUATERNION& _qua)
{
	D3DXMatrixRotationQuaternion(this, &_qua);

	return *this;
}

D3DXMATRIX& ChMatrix_9::operator *= (const D3DXMATRIX& _mat)
{
	D3DXMATRIX::operator*=(_mat);
	return *this;
}

ChMatrix_9& ChMatrix_9::operator *= (const D3DXVECTOR3& _vec)
{
	_41 += _vec.x;
	_42 += _vec.y;
	_43 += _vec.z;
	return *this;
}

ChMatrix_9& ChMatrix_9::operator *= (const D3DXQUATERNION& _qua)
{
	D3DXMATRIX tmpMat;
	D3DXMatrixRotationQuaternion(&tmpMat, &_qua);

	*this = tmpMat * *this;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////
//ChMatrix_9 Method//
///////////////////////////////////////////////////////////////////////////////////

D3DXVECTOR3 ChMatrix_9::GetPosition()
{
	D3DXVECTOR3 tmpVec;
	tmpVec.x = _41;
	tmpVec.y = _42;
	tmpVec.z = _43;
	return tmpVec;
}

D3DXQUATERNION ChMatrix_9::GetRotation()
{
	D3DXQUATERNION tmpQua;
	D3DXQuaternionRotationMatrix(&tmpQua, this);
	return tmpQua;
}

D3DXVECTOR3 ChMatrix_9::GetScaleSize()
{
	D3DXMATRIX tmpMat;

	{
		D3DXQUATERNION tmpQua;

		D3DXQuaternionRotationMatrix(&tmpQua, this);

		D3DXMatrixRotationQuaternion(&tmpMat, &tmpQua);

	}

	D3DXMatrixInverse(&tmpMat, NULL, &tmpMat);

	tmpMat = tmpMat * *this;

	return D3DXVECTOR3(tmpMat._11, tmpMat._22, tmpMat._33);

}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_9::Identity() 
{
	D3DXMatrixIdentity(this); 
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_9::Inverse()
{
	D3DXMatrixInverse(this, NULL, this);
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_9::Inverse(const D3DXMATRIX& tmpMat)
{
	D3DXMatrixInverse(this, NULL, &tmpMat);
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_9::RotYPR(const float _x, const float _y, const float _z)
{
	D3DXMATRIX tmpMat;
	D3DXMatrixRotationYawPitchRoll(&tmpMat, D3DXToRadian(_y), D3DXToRadian(_x), D3DXToRadian(_z));
	*this = tmpMat * *this;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_9::RotYPR(const D3DXVECTOR3& _vec)
{
	D3DXMATRIX tmpMat;
	D3DXMatrixRotationYawPitchRoll(&tmpMat, D3DXToRadian(_vec.y), D3DXToRadian(_vec.x), D3DXToRadian(_vec.z));
	*this = tmpMat * *this;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_9::RotQua(const D3DXQUATERNION& _qua)
{
	D3DXMATRIX tmpMat;
	D3DXMatrixRotationQuaternion(&tmpMat, &_qua);
	*this = tmpMat * *this;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_9::RotQua(const float _x, const float _y, const float _z)
{
	D3DXQUATERNION tmpQua;
	D3DXQuaternionRotationYawPitchRoll(&tmpQua, D3DXToRadian(_y), D3DXToRadian(_x), D3DXToRadian(_z));
	D3DXMATRIX tmpMat;
	D3DXMatrixRotationQuaternion(&tmpMat, &tmpQua);
	*this = tmpMat * *this;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_9::RotVec(const D3DXVECTOR3& _vec)
{
	D3DXVECTOR3 tmpCross, tmpVec;
	tmpVec = _vec;
	float tmpRot;

	auto tmp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXVec3Normalize(&tmpVec, &tmpVec);
	D3DXVec3Cross(&tmpCross, &tmp, &tmpVec);
	tmpRot = D3DXVec3Dot(&tmpVec, &tmp);

	D3DXMATRIX tmpMat;
	D3DXMatrixRotationAxis(&tmpMat, &tmpCross, std::acos(tmpRot));
	*this = tmpMat * *this;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_9::RotAxis(const D3DXVECTOR3& _vec, const float _Ang)
{
	D3DXMATRIX tmpMat;
	D3DXMatrixRotationAxis(&tmpMat, &_vec, D3DXToRadian(_Ang));
	*this = tmpMat * *this;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_9::Trans(const float _x, const float _y, const float _z)
{
	D3DXMatrixTranslation(this, _x, _y, _z);
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_9::Trans(const D3DXVECTOR3& _vec)
{
	D3DXMatrixTranslation(this, _vec.x, _vec.y, _vec.z);
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_9::VectorMove(const D3DXVECTOR3& _vec)
{
	_41 += _vec.x;
	_42 += _vec.y;
	_43 += _vec.z;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_9::Move(const float _x, const float _y, const float _z)
{
	ChMatrix_9 tmpMat;
	tmpMat.Trans(_x, _y, _z);
	*this = tmpMat * *this;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_9::Scaling(const float _x, const float _y, const float _z)
{
	D3DXMATRIX tmpMat;
	D3DXMatrixScaling(&tmpMat, _x, _y, _z);
	*this = tmpMat * *this;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_9::Scaling(const D3DXVECTOR3& _tmpVec)
{
	D3DXMATRIX tmpMat;
	D3DXMatrixScaling(&tmpMat, _tmpVec.x, _tmpVec.y, _tmpVec.z);
	*this = tmpMat * *this;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_9::Scaling(const float _scl)
{
	D3DXMATRIX tmpMat;
	D3DXMatrixScaling(&tmpMat, _scl, _scl, _scl);
	*this = tmpMat * *this;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_9::Clear0()
{
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			m[i][j] = 0.0f;
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////
//ChVector4Operator//
///////////////////////////////////////////////////////////////////////////////////

ChVec4::operator const D3DXVECTOR4()const
{
	D3DXVECTOR4 tmpVec;

	tmpVec.x = x;
	tmpVec.y = y;
	tmpVec.z = z;
	tmpVec.w = w;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec4::operator const D3DXVECTOR4*()const
{
	return reinterpret_cast<D3DXVECTOR4*>(const_cast<ChVec4*>(this));
}

///////////////////////////////////////////////////////////////////////////////////

ChVec4& ChVec4::operator= (const D3DXVECTOR4& _vec)
{
	x = _vec.x;
	y = _vec.y;
	z = _vec.z;
	w = _vec.w;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////
//ChVector3Operator//
///////////////////////////////////////////////////////////////////////////////////

ChVec3::operator const D3DXVECTOR3()const
{
	D3DXVECTOR3 tmpVec;

	tmpVec.x = x;
	tmpVec.y = y;
	tmpVec.z = z;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3::operator const D3DXVECTOR3*()const
{
	return reinterpret_cast<D3DXVECTOR3*>(const_cast<ChVec3*>(this));
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3& ChVec3::operator= (const D3DXVECTOR3& _vec)
{
	x = _vec.x;
	y = _vec.y;
	z = _vec.z;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3& ChVec3::operator= (const D3DXQUATERNION& _qua)
{
	D3DXMATRIX tmpMat;
	D3DXVECTOR3 tmpVec;

	D3DXMatrixRotationQuaternion(&tmpMat, &_qua);

	auto tmp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXVec3TransformNormal(&tmpVec, &tmp, &tmpMat);

	*this = tmpVec;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3& ChVec3::operator= (const D3DXMATRIX& _mat)
{
	x = _mat._41;
	y = _mat._42;
	z = _mat._43;

	return *this;

}

///////////////////////////////////////////////////////////////////////////////////
//ChVector2Operator//
///////////////////////////////////////////////////////////////////////////////////

ChVec2::operator const D3DXVECTOR2()const
{
	D3DXVECTOR2 tmpVec;

	tmpVec.x = x;
	tmpVec.y = y;

	return tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec2::operator const D3DXVECTOR2*()const
{
	return reinterpret_cast<D3DXVECTOR2*>(const_cast<ChVec2*>(this));
}

///////////////////////////////////////////////////////////////////////////////////

ChVec2& ChVec2::operator= (const D3DXVECTOR2& _vec)
{
	x = _vec.x;
	y = _vec.y;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////
//ChQuaternionOperator//
///////////////////////////////////////////////////////////////////////////////////

ChQua::operator const D3DXQUATERNION()const
{
	ChQua_9 tmpQua;
	tmpQua.x = x;
	tmpQua.y = y;
	tmpQua.z = z;
	tmpQua.w = w;

	return tmpQua;
}

///////////////////////////////////////////////////////////////////////////////////

ChQua::operator const D3DXQUATERNION*()const
{
	return reinterpret_cast<D3DXQUATERNION*>(const_cast<ChQua*>(this));
}

///////////////////////////////////////////////////////////////////////////////////

ChQua& ChQua::operator= (const D3DXQUATERNION& _qua)
{
	x = _qua.x;
	y = _qua.y;
	z = _qua.z;
	w = _qua.w;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChQua& ChQua::operator= (const D3DXVECTOR3& _vec)
{
	ChQua_9 tmpQua = _vec;
	*this = tmpQua;
	return *this;

}

///////////////////////////////////////////////////////////////////////////////////

ChQua& ChQua::operator= (const D3DXMATRIX& _mat)
{

	ChQua_9 tmpQua = _mat;
	*this = tmpQua;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////
//ChMatrixOperator//
///////////////////////////////////////////////////////////////////////////////////

ChLMat::operator const D3DXMATRIX()const
{
	ChMat_9 tmpMat;
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			tmpMat.m[i][j] = m[i][j];
		}
	}

	return tmpMat;
}

///////////////////////////////////////////////////////////////////////////////////

ChLMat::operator const D3DXMATRIX*()const
{
	return reinterpret_cast<D3DXMATRIX*>(const_cast<ChLMat*>(this));
}

///////////////////////////////////////////////////////////////////////////////////

ChLMat& ChLMat::operator= (const D3DXQUATERNION& _qua)
{
	ChMat_9 tmpMat = _qua;
	*this = tmpMat;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChLMat& ChLMat::operator= (const D3DXVECTOR3& _vec)
{
	ChMat_9 tmpMat = _vec;
	*this = tmpMat;
	return *this;

}

///////////////////////////////////////////////////////////////////////////////////

ChLMat& ChLMat::operator= (const D3DXMATRIX& _mat)
{


	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			m[i][j] = _mat.m[i][j];
		}
	}

	return *this;
}

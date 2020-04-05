#include<Windows.h>
#include"../../ChInclude/ChGameBI.h"

#ifndef _XM_NO_INTRINSICS_
#define _XM_NO_INTRINSICS_
#endif

#include"../../ChInclude/ChD3D11I.h"

#include"ChQuaternion_11.h"


///////////////////////////////////////////////////////////////////////////////////
//ChQuaternion_11 operator//
///////////////////////////////////////////////////////////////////////////////////

ChQuaternion_11& ChQuaternion_11::operator=(const DirectX::XMFLOAT4& _cm)
{
	x = _cm.x;
	y = _cm.y;
	z = _cm.z;
	return *this;
}

ChQuaternion_11& ChQuaternion_11::operator+=(const DirectX::XMFLOAT4& _cm)
{
	x += _cm.x;
	y += _cm.y;
	z += _cm.z;
	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator+(const DirectX::XMFLOAT4& _cm)const
{

	ChQuaternion_11 Tmp;
	Tmp = *this;
	Tmp += _cm;

	return Tmp;
}

ChQuaternion_11& ChQuaternion_11::operator-=(const DirectX::XMFLOAT4& _cm)
{
	x -= _cm.x;
	y -= _cm.y;
	z -= _cm.z;
	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator-(const DirectX::XMFLOAT4& _cm)const
{
	ChQuaternion_11 Tmp;
	Tmp = *this;
	Tmp -= _cm;

	return Tmp;
}

ChQuaternion_11& ChQuaternion_11::operator*=(const DirectX::XMFLOAT4& _cm)
{
	*this = *this * _cm;
	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator*(const DirectX::XMFLOAT4& _cm)const
{
	DirectX::XMVECTOR TmpVec;
	ChQuaternion_11 TmpQua;

	TmpVec = DirectX::XMLoadFloat4(&_cm);

	TmpVec = TmpVec * (DirectX::XMVECTOR)*this;

	TmpQua = TmpVec;

	return TmpQua;
}

ChQuaternion_11& ChQuaternion_11::operator/=(const DirectX::XMFLOAT4& _cm)
{

	*this = *this / _cm;

	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator/(const DirectX::XMFLOAT4& _cm)const
{

	DirectX::XMVECTOR TmpVec;
	ChQuaternion_11 TmpQua;

	TmpVec = DirectX::XMLoadFloat4(&_cm);

	TmpVec = DirectX::XMQuaternionInverse(TmpVec);

	TmpVec = TmpVec * (DirectX::XMVECTOR)*this;

	TmpQua = TmpVec;

	return TmpQua;
}

ChQuaternion_11& ChQuaternion_11::operator=(const float& _cm)
{

	x = _cm;
	y = _cm;
	z = _cm;
	return *this;
}

ChQuaternion_11& ChQuaternion_11::operator+=(const float& _cm)
{

	x += _cm;
	y += _cm;
	z += _cm;
	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator+(const float& _cm)const
{
	ChQuaternion_11 Tmp;

	Tmp = *this;
	Tmp += _cm;
	return Tmp;

}

ChQuaternion_11& ChQuaternion_11::operator-=(const float& _cm)
{

	x -= _cm;
	y -= _cm;
	z -= _cm;
	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator-(const float& _cm)const
{

	ChQuaternion_11 Tmp;

	Tmp = *this;
	Tmp -= _cm;
	return Tmp;

}

ChQuaternion_11& ChQuaternion_11::operator*=(const float& _cm)
{

	x *= _cm;
	y *= _cm;
	z *= _cm;
	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator*(const float& _cm)const
{

	ChQuaternion_11 Tmp;

	Tmp = *this;
	Tmp *= _cm;
	return Tmp;

}

ChQuaternion_11& ChQuaternion_11::operator/=(const float& _cm)
{

	if (_cm > 0.0f)x /= _cm;
	if (_cm > 0.0f)y /= _cm;
	if (_cm > 0.0f)z /= _cm;
	return *this;
}

ChQuaternion_11 ChQuaternion_11::operator/(const float& _cm)const
{

	ChQuaternion_11 Tmp;

	Tmp = *this;
	Tmp /= _cm;
	return Tmp;

}

ChQuaternion_11& ChQuaternion_11::operator=(const DirectX::XMVECTOR& _cm)
{
	DirectX::XMStoreFloat4(this, _cm);
	return *this;
}

ChQuaternion_11::operator DirectX::XMVECTOR()const
{
	DirectX::XMVECTOR Tmp;

	Tmp = DirectX::XMLoadFloat4(this);

	return Tmp;
}

ChQuaternion_11::operator DirectX::XMFLOAT4()const
{

	DirectX::XMFLOAT4 TmpVec;

	TmpVec.x = x;
	TmpVec.y = y;
	TmpVec.z = z;

	return TmpVec;

}

ChQuaternion_11& ChQuaternion_11::operator = (const DirectX::XMFLOAT3&  _Vec)
{

	DirectX::XMVECTOR TmpVec,TmpVec2;
	DirectX::XMVECTOR dot;

	{
		auto Tmp = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
		TmpVec2 = DirectX::XMLoadFloat3(&Tmp);
	}


	TmpVec = DirectX::XMLoadFloat3(&_Vec);

	TmpVec = DirectX::XMVector3Normalize(TmpVec);

	dot = DirectX::XMVector3Dot(TmpVec, TmpVec2);

	TmpVec = DirectX::XMVector3Cross(TmpVec, TmpVec2);

	TmpVec = DirectX::XMVector3Normalize(TmpVec);

	{
		float TmpDot;
		DirectX::XMStoreFloat(&TmpDot, dot);
		TmpVec = DirectX::XMQuaternionRotationAxis(TmpVec, TmpDot);

	}

	*this = TmpVec;

	return *this;
}

ChQuaternion_11& ChQuaternion_11::operator =(const DirectX::XMFLOAT4X4& _Mat)
{
	

	DirectX::XMVECTOR TmpVec;
	DirectX::XMMATRIX TmpMat;


	TmpMat = DirectX::XMLoadFloat4x4(&_Mat);

	TmpVec = DirectX::XMQuaternionRotationMatrix(TmpMat);

	*this = TmpVec;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////
//ChQuaternion_11 ÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_11::RotYPR(const float _x, const float _y, const float _z)
{


	DirectX::XMVECTOR TmpVec;

	TmpVec = DirectX::XMQuaternionRotationRollPitchYaw(y, _x, _z);

	*this = TmpVec;


}

///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_11::RotLookAt(
	const DirectX::XMFLOAT3& _Pos
	, const DirectX::XMFLOAT3& _BasePos)
{
	ChVec3 Tmp = _Pos;

	Tmp -= _BasePos;

	*this = (DirectX::XMFLOAT3)(Tmp);


}

///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_11::RotAxis(const DirectX::XMFLOAT3& _Vec, const float _Ang)
{

	DirectX::XMVECTOR TmpVec;

	TmpVec = DirectX::XMLoadFloat3(&_Vec);


	TmpVec = DirectX::XMQuaternionRotationAxis(TmpVec, _Ang);

	*this = TmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_11::RotMat(const DirectX::XMFLOAT4X4& _Mat)
{

	DirectX::XMVECTOR TmpVec;
	DirectX::XMMATRIX TmpMat;

	TmpMat = DirectX::XMLoadFloat4x4(&_Mat);

	TmpVec = DirectX::XMQuaternionRotationMatrix(TmpMat);

	*this = TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_11::Lerp(
	const ChQuaternion_11& _SVec
	, const ChQuaternion_11& _EVec
	, const float _NowTime)
{
	ChQuaternion_11 Tmp;
	Tmp = _EVec - _SVec;

	Tmp *= _NowTime;

	Tmp = _EVec + Tmp;

	*this = Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_11::Identity()
{
	*this = DirectX::XMQuaternionIdentity();
}

///////////////////////////////////////////////////////////////////////////////////

void ChQuaternion_11::Inverse(const ChQuaternion_11& _Qua)
{
	*this = DirectX::XMQuaternionInverse(_Qua);
}

///////////////////////////////////////////////////////////////////////////////////
//ChQuaternion Operator//
///////////////////////////////////////////////////////////////////////////////////

ChQua::operator const DirectX::XMFLOAT4()const
{
	DirectX::XMFLOAT4 TmpVec;
	TmpVec.x = x;
	TmpVec.y = y;
	TmpVec.z = z;
	TmpVec.w = w;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChQua::operator const DirectX::XMFLOAT4*()const
{
	return reinterpret_cast<DirectX::XMFLOAT4*>(const_cast<ChQua*>(this));
}

///////////////////////////////////////////////////////////////////////////////////

ChQua& ChQua::operator= (const DirectX::XMFLOAT4& _Qua)
{
	x = _Qua.x;
	y = _Qua.y;
	z = _Qua.z;
	w = _Qua.w;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChQua& ChQua::operator= (const DirectX::XMFLOAT3& _Vec)
{
	ChQuaternion_11 Tmp;
	Tmp = _Vec;

	*this = Tmp;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChQua& ChQua::operator= (const DirectX::XMFLOAT4X4& _Mat)
{
	ChQuaternion_11 Tmp;
	Tmp = _Mat;

	*this = Tmp;

	return *this;

}

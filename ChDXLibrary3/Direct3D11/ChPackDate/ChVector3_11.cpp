#include"../../ChGameIncludeFile.h"

#ifndef _XM_NO_INTRINSICS_
#define _XM_NO_INTRINSICS_
#endif

#include<D3D11.h>
#include<direct.h>
#include<DirectXCollision.h>
#include<DirectXMath.h>
#include<DirectXColors.h>

#pragma comment(lib,"d3d11.lib")

#include"ChVector3_11.h"


///////////////////////////////////////////////////////////////////////////////////
//ChVector3_11 operator//
///////////////////////////////////////////////////////////////////////////////////

ChVector3_11& ChVector3_11::operator=(const DirectX::XMFLOAT3& _cm)
{
	x = _cm.x;
	y = _cm.y;
	z = _cm.z;
	return *this;
}

ChVector3_11& ChVector3_11::operator+=(const DirectX::XMFLOAT3& _cm)
{
	x += _cm.x;
	y += _cm.y;
	z += _cm.z;
	return *this;
}

ChVector3_11 ChVector3_11::operator+(const DirectX::XMFLOAT3& _cm)const
{

	ChVector3_11 Tmp;
	Tmp = *this;
	Tmp += _cm;

	return Tmp;
}

ChVector3_11& ChVector3_11::operator-=(const DirectX::XMFLOAT3& _cm)
{
	x -= _cm.x;
	y -= _cm.y;
	z -= _cm.z;
	return *this;
}

ChVector3_11 ChVector3_11::operator-(const DirectX::XMFLOAT3& _cm)const
{
	ChVector3_11 Tmp;
	Tmp = *this;
	Tmp -= _cm;

	return Tmp;
}

ChVector3_11& ChVector3_11::operator*=(const DirectX::XMFLOAT3& _cm)
{
	x *= _cm.x;
	y *= _cm.y;
	z *= _cm.z;

	return *this;
}

ChVector3_11 ChVector3_11::operator*(const DirectX::XMFLOAT3& _cm)const
{
	ChVector3_11 Tmp;
	Tmp = *this;
	Tmp *= _cm;

	return Tmp;
}

ChVector3_11& ChVector3_11::operator/=(const DirectX::XMFLOAT3& _cm)
{

	if (_cm.x > 0.0f)x /= _cm.x;
	if (_cm.y > 0.0f)y /= _cm.y;
	if (_cm.z > 0.0f)z /= _cm.z;

	return *this;
}

ChVector3_11 ChVector3_11::operator/(const DirectX::XMFLOAT3& _cm)const
{

	ChVector3_11 Tmp;
	Tmp = *this;
	Tmp /= _cm;

	return Tmp;
}

ChVector3_11& ChVector3_11::operator=(const float& _cm)
{

	x = _cm;
	y = _cm;
	z = _cm;
	return *this;
}

ChVector3_11& ChVector3_11::operator+=(const float& _cm)
{

	x += _cm;
	y += _cm;
	z += _cm;
	return *this;
}

ChVector3_11 ChVector3_11::operator+(const float& _cm)const
{
	ChVector3_11 Tmp;

	Tmp = *this;
	Tmp += _cm;
	return Tmp;

}

ChVector3_11& ChVector3_11::operator-=(const float& _cm)
{

	x -= _cm;
	y -= _cm;
	z -= _cm;
	return *this;
}

ChVector3_11 ChVector3_11::operator-(const float& _cm)const
{

	ChVector3_11 Tmp;

	Tmp = *this;
	Tmp -= _cm;
	return Tmp;

}

ChVector3_11& ChVector3_11::operator*=(const float& _cm)
{

	x *= _cm;
	y *= _cm;
	z *= _cm;
	return *this;
}

ChVector3_11 ChVector3_11::operator*(const float& _cm)const
{

	ChVector3_11 Tmp;

	Tmp = *this;
	Tmp *= _cm;
	return Tmp;

}

ChVector3_11& ChVector3_11::operator/=(const float& _cm)
{

	if (_cm > 0.0f)x /= _cm;
	if (_cm > 0.0f)y /= _cm;
	if (_cm > 0.0f)z /= _cm;
	return *this;
}

ChVector3_11 ChVector3_11::operator/(const float& _cm)const
{

	ChVector3_11 Tmp;

	Tmp = *this;
	Tmp /= _cm;
	return Tmp;

}

ChVector3_11& ChVector3_11::operator=(const DirectX::XMVECTOR& _cm)
{
	DirectX::XMStoreFloat3(this, _cm);
}

ChVector3_11::operator DirectX::XMVECTOR()const
{
	DirectX::XMVECTOR Tmp;

	Tmp = DirectX::XMLoadFloat3(this);

	return Tmp;
}

ChVector3_11::operator DirectX::XMFLOAT3()const
{

	DirectX::XMFLOAT3 TmpVec;

	TmpVec.x = x;
	TmpVec.y = y;
	TmpVec.z = z;

	return TmpVec;

}

ChVector3_11& ChVector3_11::operator = (const DirectX::XMFLOAT4&  _Qua)
{
	DirectX::XMMATRIX TmpMat;

	DirectX::XMVECTOR TmpVec;

	TmpVec = DirectX::XMLoadFloat4(&_Qua);

	TmpMat = DirectX::XMMatrixRotationQuaternion(TmpVec);

	*this = DirectX::XMVector3TransformNormal(ChVector3_11(0.0f, 0.0f, 1.0f), TmpMat);

	return *this;
}

ChVector3_11& ChVector3_11::operator =(const DirectX::XMFLOAT4X4& _Mat)
{
	x = _Mat._41;
	y = _Mat._42;
	z = _Mat._43;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////
//ChVector3_11 ƒƒ\ƒbƒh//
///////////////////////////////////////////////////////////////////////////////////

float ChVector3_11::GetLen(const DirectX::XMFLOAT3& _Vec = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f))const
{
	DirectX::XMVECTOR TmpVec;
	TmpVec = *this - _Vec;

	float Tmp;
	TmpVec = DirectX::XMVector3Length(TmpVec);
	DirectX::XMStoreFloat(&Tmp, DirectX::XMVector3Length(TmpVec));

	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

float ChVector3_11::GetRadian(
	const ChVector3_11& _Vec1
	, const ChVector3_11& _Vec2)const
{
	ChVector3_11 TmpVec1, TmpVec2;
	TmpVec1 = _Vec1;
	TmpVec2 = _Vec2;

	TmpVec1 = DirectX::XMVector3Normalize(TmpVec1);
	TmpVec2 = DirectX::XMVector3Normalize(TmpVec2);

	return acosf(Dot(TmpVec1, TmpVec2));
}

///////////////////////////////////////////////////////////////////////////////////

float ChVector3_11::GetDegree(
	const ChVector3_11& _Vec1
	, const ChVector3_11& _Vec2)const
{
	ChVector3_11 TmpVec1, TmpVec2;
	TmpVec1 = _Vec1;
	TmpVec2 = _Vec2;

	TmpVec1 = DirectX::XMVector3Normalize(TmpVec1);
	TmpVec2 = DirectX::XMVector3Normalize(TmpVec2);

	return ChMath::ToDegree(acosf(Dot(TmpVec1, TmpVec2)));
}

///////////////////////////////////////////////////////////////////////////////////

void ChVector3_11::Set0Param()
{
	*this = 0;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChVector3_11::IsNormals()const {

	if (std::abs(this->x)
		+ std::abs(this->y)
		+ std::abs(this->z) == 1.0f)return true;
	return false;
}

///////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChVector3_11::IsAll0()const {

	if (this->x == 0.0f
		&& this->y == 0.0f
		&& this->z == 0.0f)return ChStd::True;

	return ChStd::False;
}

///////////////////////////////////////////////////////////////////////////////////

void ChVector3_11::MatPos(const DirectX::XMMATRIX& _Mat, const ChVector3_11&  _Vec)
{
	DirectX::XMVECTOR TmpVec;
	TmpVec = _Vec;
	auto Tmp = DirectX::XMVector3TransformCoord(TmpVec, _Mat);

	*this = Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

void ChVector3_11::MatNormal(const DirectX::XMMATRIX& _Mat, const ChVector3_11&  _Vec = ChVector3_11(0.0f, 0.0f, 1.0f))
{
	DirectX::XMVECTOR TmpVec;
	TmpVec = _Vec;
	auto Tmp = DirectX::XMVector3TransformNormal(TmpVec, _Mat);

	*this = Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

void ChVector3_11::Normalize()
{
	float TmpLen = fabsf(this->x) + fabsf(this->y) + fabsf(this->z);

	if (TmpLen <= 0.0f) {
		*this = ChVector3_11(0.0f, 0.0f, 1.0f);
		return;
	}
	if (IsNormals() || !(TmpLen > 0.0f))return;

	DirectX::XMVECTOR TmpVec;
	TmpVec = *this;

	*this = DirectX::XMVector3Normalize(TmpVec);
}

///////////////////////////////////////////////////////////////////////////////////

void ChVector3_11::Lerp(
	const ChVector3_11& _SVec
	, const ChVector3_11& _EVec
	, const float _NowTime)
{
	ChVector3_11 Tmp;
	Tmp = _EVec - _SVec;

	Tmp *= _NowTime;

	Tmp = _EVec + Tmp;

	*this = Tmp;

}

///////////////////////////////////////////////////////////////////////////////////

void ChVector3_11::CrossVec(const ChVector3_11& _Vec1, const ChVector3_11& _Vec2)
{
	DirectX::XMVECTOR TmpVec1, TmpVec2;
	TmpVec1 = _Vec1;
	TmpVec2 = _Vec2;

	auto Tmp = DirectX::XMVector3Cross(TmpVec1, TmpVec2);

	*this = Tmp;


}

///////////////////////////////////////////////////////////////////////////////////

float ChVector3_11::Dot(
	const ChVector3_11& _Vec1
	, const ChVector3_11&  _Vec2)const
{
	DirectX::XMVECTOR TmpVec1, TmpVec2;
	TmpVec1 = _Vec1;
	TmpVec2 = _Vec2;

	float Tmp;
	DirectX::XMStoreFloat(&Tmp, DirectX::XMVector3Dot(TmpVec1, TmpVec2));

	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////
//ChVector3Operator//
///////////////////////////////////////////////////////////////////////////////////

ChVec3::operator const DirectX::XMFLOAT3()const
{
	DirectX::XMFLOAT3 TmpVec;
	TmpVec.x = x;
	TmpVec.y = y;
	TmpVec.z = z;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3::operator const DirectX::XMFLOAT3*()const
{
	return reinterpret_cast<DirectX::XMFLOAT3*>(const_cast<ChVec3*>(this));
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3& ChVec3::operator= (const DirectX::XMFLOAT3& _Vec)
{
	x = _Vec.x;
	y = _Vec.y;
	z = _Vec.z;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3& ChVec3::operator= (const DirectX::XMFLOAT4& _Qua)
{
	ChVector3_11 Tmp;
	Tmp = _Qua;

	*this = Tmp;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3& ChVec3::operator= (const DirectX::XMFLOAT4X4& _Mat)
{
	ChVector3_11 Tmp;
	Tmp = _Mat;

	*this = Tmp;

	return *this;

}

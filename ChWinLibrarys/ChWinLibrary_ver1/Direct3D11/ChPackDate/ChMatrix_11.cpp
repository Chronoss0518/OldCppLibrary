#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#ifndef _XM_NO_INTRINSICS_
#define _XM_NO_INTRINSICS_
#endif

#include"../../BaseIncluder/ChD3D11I.h"

#include"ChMatrix_11.h"


///////////////////////////////////////////////////////////////////////////////////
//ChMatrix_11 Operator//
///////////////////////////////////////////////////////////////////////////////////


ChMatrix_11&ChMatrix_11::operator=(const DirectX::XMFLOAT4X4& _cm)
{
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			m[i][j] = _cm.m[i][j];
		}
	}

	return *this;
}

ChMatrix_11&ChMatrix_11::operator+=(const DirectX::XMFLOAT4X4& _cm)
{
	*this = *this + _cm;

	return *this;
}

ChMatrix_11 ChMatrix_11::operator+(const DirectX::XMFLOAT4X4& _cm)const
{
	DirectX::XMFLOAT4X4 TmpMat;
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			TmpMat.m[i][j] += _cm.m[i][j];
		}
	}

	return TmpMat;
}

ChMatrix_11&ChMatrix_11::operator-=(const DirectX::XMFLOAT4X4& _cm)
{

	*this = *this - _cm;

	return *this;
}

ChMatrix_11 ChMatrix_11::operator-(const DirectX::XMFLOAT4X4& _cm)const
{
	ChMatrix_11 TmpMat;
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			TmpMat.m[i][j] += _cm.m[i][j];
		}
	}

	return TmpMat;
}

ChMatrix_11&ChMatrix_11::operator*=(const DirectX::XMFLOAT4X4& _cm)
{
	*this = *this * _cm;
	return *this;
}

ChMatrix_11 ChMatrix_11::operator*(const DirectX::XMFLOAT4X4& _cm)const
{

	ChMatrix_11 TmpMat;
	DirectX::XMMATRIX TmpMat1, TmpMat2;

	TmpMat1 = DirectX::XMLoadFloat4x4(&_cm);
	TmpMat2 = *this;

	TmpMat = TmpMat1 * TmpMat2;

	

	return TmpMat;

}

ChMatrix_11&ChMatrix_11::operator/=(const DirectX::XMFLOAT4X4& _cm)
{
	*this = *this / _cm;
	return *this;
}

ChMatrix_11 ChMatrix_11::operator/(const DirectX::XMFLOAT4X4& _cm)const
{

	ChMatrix_11 TmpMat;
	DirectX::XMMATRIX TmpMat1, TmpMat2;

	TmpMat1 = DirectX::XMLoadFloat4x4(&_cm);
	TmpMat2 = *this;

	TmpMat2 = DirectX::XMMatrixInverse(nullptr, TmpMat2);

	TmpMat = TmpMat2 * TmpMat1;

	return TmpMat;

}

ChMatrix_11&ChMatrix_11::ChMatrix_11::operator=(const float& _cm)
{

	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			m[i][j] = _cm;
		}
	}
	return *this;
}

ChMatrix_11&ChMatrix_11::ChMatrix_11::operator*=(const float& _cm)
{
	*this = *this * _cm;
	return *this;
}

ChMatrix_11 ChMatrix_11::ChMatrix_11::operator*(const float& _cm)const
{

	ChMatrix_11 TmpMat;
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			TmpMat.m[i][j] *= _cm;
		}
	}

	return TmpMat;
}

ChMatrix_11&ChMatrix_11::ChMatrix_11::operator/=(const float& _cm)
{

	*this = *this / _cm;
	return *this;
}

ChMatrix_11 ChMatrix_11::ChMatrix_11::operator/(const float& _cm)const
{

	ChMatrix_11 TmpMat;
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			if (_cm == 0.0f)continue;
			TmpMat.m[i][j] /= _cm;
		}
	}

	return TmpMat;
}

ChMatrix_11&ChMatrix_11::operator=(const DirectX::XMMATRIX& _cm)
{

	DirectX::XMStoreFloat4x4(this, _cm);
	return *this;
}

ChMatrix_11::operator DirectX::XMMATRIX()const
{
	DirectX::XMMATRIX TmpMat;
	TmpMat = DirectX::XMLoadFloat4x4(this);
	return TmpMat;
}

ChMatrix_11::operator DirectX::XMFLOAT4X4()const
{

	DirectX::XMFLOAT4X4 TmpMat;
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			TmpMat.m[i][j] = m[i][j];
		}
	}
	return TmpMat;
}

ChMatrix_11&ChMatrix_11::operator = (const DirectX::XMFLOAT3& _Vec)
{
	*this = DirectX::XMMatrixTranslation(_Vec.x, _Vec.y, _Vec.z);

	return *this;
}

ChMatrix_11&ChMatrix_11::operator =(const DirectX::XMFLOAT4& _Qua)
{


	DirectX::XMVECTOR TmpVec;
	TmpVec = DirectX::XMLoadFloat4(&_Qua);
	*this = DirectX::XMMatrixRotationQuaternion(TmpVec);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////
//ChMatrix_11 ƒƒ\ƒbƒh//
///////////////////////////////////////////////////////////////////////////////////


DirectX::XMFLOAT3 ChMatrix_11::GetPosition()const
{
	DirectX::XMFLOAT3 TmpVec;
	TmpVec.x = _41;
	TmpVec.y = _42;
	TmpVec.z = _43;
	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

DirectX::XMFLOAT4 ChMatrix_11::GetRotation()const
{
	DirectX::XMFLOAT4 TmpQua;
	
	DirectX::XMVECTOR TmpVec;

	TmpVec = DirectX::XMQuaternionRotationMatrix(*this);


	DirectX::XMStoreFloat4(&TmpQua, TmpVec);

	return TmpQua;
}

///////////////////////////////////////////////////////////////////////////////////

DirectX::XMFLOAT3 ChMatrix_11::GetScaleSize()const
{

	ChMatrix_11 TmpMat;

	{
		DirectX::XMVECTOR TmpQua;

		TmpQua = DirectX::XMQuaternionRotationMatrix(*this);

		TmpMat = DirectX::XMMatrixRotationQuaternion(TmpQua);

	}

	TmpMat.Inverse();

	TmpMat = TmpMat * *this;

	return DirectX::XMFLOAT3(TmpMat._11, TmpMat._22, TmpMat._33);

}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_11::Inverse(const DirectX::XMFLOAT4X4& _Mat)
{
	DirectX::XMMATRIX TmpMat;
	TmpMat = DirectX::XMLoadFloat4x4(&_Mat);

	*this = DirectX::XMMatrixInverse(nullptr, TmpMat);
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_11::RotYPR(
	const float _x
	, const float _y
	, const float _z)
{
	ChMatrix_11 TmpMat;
	
	TmpMat = DirectX::XMMatrixRotationRollPitchYaw(
		ChMath::ToRadian(_y)
		, ChMath::ToRadian(_x)
		, ChMath::ToRadian(_z));

	*this = TmpMat * *this;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_11::RotYPR(const DirectX::XMFLOAT3& _Vec)
{
	ChMatrix_11 TmpMat;

	TmpMat = DirectX::XMMatrixRotationRollPitchYaw(
		ChMath::ToRadian(_Vec.y)
		, ChMath::ToRadian(_Vec.x)
		, ChMath::ToRadian(_Vec.z));

	*this = TmpMat * *this;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_11::RotQua(const DirectX::XMFLOAT4& _Qua)
{
	ChMatrix_11 TmpMat;
	{
		DirectX::XMVECTOR TmpVec;
		TmpVec = DirectX::XMLoadFloat4(&_Qua);
		TmpMat = DirectX::XMMatrixRotationQuaternion(TmpVec);
	}
	*this = TmpMat * *this;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_11::RotQua(
	const float _x
	, const float _y
	, const float _z)
{
	ChMatrix_11 TmpMat;
	{
		DirectX::XMVECTOR TmpVec;
		TmpVec = DirectX::XMQuaternionRotationRollPitchYaw(_x, _y, _z);
		TmpMat = DirectX::XMMatrixRotationQuaternion(TmpVec);
	}
	*this = TmpMat * *this;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_11::RotVec(const DirectX::XMFLOAT3& _Vec)
{
	DirectX::XMVECTOR TmpVec,TmpBase;
	TmpVec = DirectX::XMLoadFloat3(&_Vec);
	float TmpRot;
	{
		auto Tmp = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
		TmpBase = DirectX::XMLoadFloat3(&Tmp);
	}

	TmpVec = DirectX::XMVector3Normalize(TmpVec);
	{
		DirectX::XMVECTOR TmpDot;
		TmpDot = DirectX::XMVector3Dot(TmpVec, TmpBase);
		DirectX::XMStoreFloat(&TmpRot, TmpDot);
	}

	TmpVec = DirectX::XMVector3Cross(TmpVec,TmpBase);

	DirectX::XMFLOAT3 Tmp;
	DirectX::XMStoreFloat3(&Tmp, TmpVec);

	RotAxis(Tmp, TmpRot);
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_11::RotAxis(
	const DirectX::XMFLOAT3& _Vec
	, const float _Ang)
{
	ChMatrix_11 TmpMat;

	{
		DirectX::XMVECTOR TmpVec;
		TmpVec = DirectX::XMLoadFloat3(&_Vec);
		TmpMat = DirectX::XMMatrixRotationAxis(TmpVec, (ChMath::ToRadian(_Ang)));
	}
	*this = TmpMat * *this;
}

///////////////////////////////////////////////////////////////////////////////////

void ChMatrix_11::Scaling(
	const float _x
	, const float _y
	, const float _z)
{

	ChMatrix_11 TmpMat;
	TmpMat = DirectX::XMMatrixScaling(_x, _y, _z);
	*this = TmpMat * *this;
}

///////////////////////////////////////////////////////////////////////////////////////
//ChMatrix operator
///////////////////////////////////////////////////////////////////////////////////////

ChLMatrix::operator const DirectX::XMFLOAT4X4()const
{
	ChMatrix_11 TmpMat;
	

	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			TmpMat.m[i][j] = m[i][j];
		}
	}

	return TmpMat;
}

ChLMatrix::operator const DirectX::XMFLOAT4X4*()const
{

	return reinterpret_cast<DirectX::XMFLOAT4X4*>(const_cast<ChLMat*>(this));
}

ChLMatrix& ChLMatrix::operator= (const DirectX::XMFLOAT3& _Vec)
{

	ChMat_11 TmpMat;

	TmpMat = _Vec;

	*this = TmpMat;

	return *this;
}

ChLMatrix& ChLMatrix::operator= (const DirectX::XMFLOAT4& _Qua)
{
	ChMat_11 TmpMat;

	TmpMat = _Qua;

	*this = TmpMat;

	return *this;
}

ChLMatrix& ChLMatrix::operator= (const DirectX::XMFLOAT4X4& _Mat)
{
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			m[i][j] = _Mat.m[i][j];
		}
	}

	return *this;
}

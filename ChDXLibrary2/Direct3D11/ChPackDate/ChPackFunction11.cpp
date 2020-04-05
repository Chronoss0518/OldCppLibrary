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
#include"ChQuaternion_11.h"
#include"ChMatrix_11.h"


///////////////////////////////////////////////////////////////////////////////////
//ChQuaternionOperator//
///////////////////////////////////////////////////////////////////////////////////

ChQua::operator const D3DXQUATERNION()const
{
	ChQua_9 TmpQua;
	TmpQua.x = x;
	TmpQua.y = y;
	TmpQua.z = z;
	TmpQua.w = w;

	return TmpQua;
}

///////////////////////////////////////////////////////////////////////////////////

ChQua::operator const D3DXQUATERNION*()const
{
	return reinterpret_cast<D3DXQUATERNION*>(const_cast<ChQua*>(this));
}

///////////////////////////////////////////////////////////////////////////////////

ChQua& ChQua::operator= (const D3DXQUATERNION& _Qua)
{
	x = _Qua.x;
	y = _Qua.y;
	z = _Qua.z;
	w = _Qua.w;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChQua& ChQua::operator= (const D3DXVECTOR3& _Vec)
{
	ChQua_9 TmpQua = _Vec;
	*this = TmpQua;
	return *this;

}

///////////////////////////////////////////////////////////////////////////////////

ChQua& ChQua::operator= (const D3DXMATRIX& _Mat)
{

	ChQua_9 TmpQua = _Mat;
	*this = TmpQua;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////
//ChMatrixOperator//
///////////////////////////////////////////////////////////////////////////////////

ChMat::operator const D3DXMATRIX()const
{
	ChMat_9 TmpMat;
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			TmpMat.m[i][j] = m[i][j];
		}
	}

	return TmpMat;
}

///////////////////////////////////////////////////////////////////////////////////

ChMat::operator const D3DXMATRIX*()const
{
	return reinterpret_cast<D3DXMATRIX*>(const_cast<ChMat*>(this));
}

///////////////////////////////////////////////////////////////////////////////////

ChMat& ChMat::operator= (const D3DXQUATERNION& _Qua)
{
	ChMat_9 TmpMat = _Qua;
	*this = TmpMat;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMat& ChMat::operator= (const D3DXVECTOR3& _Vec)
{
	ChMat_9 TmpMat = _Vec;
	*this = TmpMat;
	return *this;

}

///////////////////////////////////////////////////////////////////////////////////

ChMat& ChMat::operator= (const D3DXMATRIX& _Mat)
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
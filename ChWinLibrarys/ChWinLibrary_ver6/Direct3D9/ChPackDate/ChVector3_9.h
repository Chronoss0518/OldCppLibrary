#ifndef Ch_D3D9_Vec3_h
#define Ch_D3D9_Vec3_h

//ƒpƒbƒN‰»‚µ‚½D3DXVECTOR3Œ^//
typedef class ChVector3_9 :public D3DXVECTOR3
{
public:

	ChVector3_9&operator=(const D3DXVECTOR3& _cm)
	{
		x = _cm.x;
		y = _cm.y;
		z = _cm.z;

		return *this;
	}

	ChVector3_9&operator = (const D3DXQUATERNION& _cm)
	{
		D3DXMATRIX TmpMat;

		D3DXMatrixRotationQuaternion(&TmpMat, &_cm);

		auto Tmp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		D3DXVec3TransformNormal(this, &Tmp, &TmpMat);

		return *this;
	}

	ChVector3_9&operator =(const D3DXMATRIX& _Mat)
	{
		x = _Mat._41;
		y = _Mat._42;
		z = _Mat._43;
		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	ChVector3_9(const D3DXVECTOR3&_cm)
	{
		*this = _cm;
	}

	ChVector3_9()
	{
		Set0Param();
	}

	ChVector3_9(const D3DXMATRIX& _Mat)
	{
		*this = _Mat;
	}

	ChVector3_9(const D3DXQUATERNION& _Qua)
	{
		*this = _Qua;
	}

	ChVector3_9(const float _x, const float _y, const float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	ChVector3_9(const float _Num)
	{
		x = _Num;
		y = _Num;
		z = _Num;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	inline float GetLen(const D3DXVECTOR3& _Vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		ChVector3_9 TmpVec;
		TmpVec = *this - _Vec;

		return D3DXVec3Length(&TmpVec);
	}

	inline float GetRadian(const D3DXVECTOR3& _Vec)
	{
		ChVector3_9 TmpVec1, TmpVec2;
		TmpVec1 = *this;
		TmpVec2 = _Vec;
		TmpVec1.Normalize();
		TmpVec2.Normalize();

		return acosf(D3DXVec3Dot(&TmpVec1, &TmpVec2));
	}

	inline float GetDegree(const D3DXVECTOR3& _Vec)
	{
		ChVector3_9 TmpVec1, TmpVec2;

		TmpVec1 = *this;
		TmpVec2 = _Vec;

		TmpVec1.Normalize();
		TmpVec2.Normalize();

		return D3DXToDegree(acosf(D3DXVec3Dot(&TmpVec1, &TmpVec2)));
	}

	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	inline void Set0Param()
	{
		*this = 0;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline ChStd::Bool CheckNormals() {

		if (fabsf(this->x) + fabsf(this->y) + fabsf(this->z) == 1.0f)return true;
		return false;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline ChStd::Bool CheckAll0() {

		if (fabsf(this->x) == 0.0f
			&& fabsf(this->y) == 0.0f
			&& fabsf(this->z) == 0.0f)return true;

		return false;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Move(const float _x, const float _y, const float _z)
	{
		*this += D3DXVECTOR3(_x, _y, _z);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Move2D(const D3DXVECTOR3 *_Vec)
	{
		D3DXVECTOR3 TmpVec = *_Vec;

		TmpVec.x = 0.0f;
		TmpVec.y = 0.0f;

		*this += (*_Vec - TmpVec);
	}

	///////////////////////////////////////////////////////////////////////////////////


	inline void MatPos(const D3DXMATRIX& _Mat, const D3DXVECTOR3& _Vec)
	{
		D3DXVec3TransformCoord(this, &_Vec, &_Mat);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void MatNormal(const D3DXMATRIX& _Mat, const D3DXVECTOR3& _Vec = D3DXVECTOR3(0.0f, 0.0f, 1.0f))
	{
		D3DXVec3TransformNormal(this, &_Vec, &_Mat);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Normalize()
	{
		if (CheckNormals())return;
		float TmpLen = std::abs(this->x) + std::abs(this->y) + std::abs(this->z);
		if (TmpLen > 0.0f)*this /= TmpLen;
		else *this = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Lerp(
		const D3DXVECTOR3& _SVec
		,const D3DXVECTOR3& _EVec
		,const float _NowTime)
	{
		D3DXVec3Lerp(this, &_SVec, &_EVec, _NowTime);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void CrossVec(const D3DXVECTOR3& _Vec1, const D3DXVECTOR3& _Vec2)
	{
		D3DXVec3Cross(this, &_Vec1, &_Vec2);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline float DotVec(const D3DXVECTOR3& _Vec)
	{
		return D3DXVec3Dot(&_Vec, this);
	}

	///////////////////////////////////////////////////////////////////////////////////


}ChVec3_9;



#endif
#ifndef Ch_D3D11_Qua_h
#define Ch_D3D11_Qua_h

//D3DXQUATERNIONをパック化したクラス//
typedef class ChQuaternion_11 :public DirectX::XMFLOAT4
{
public:

	operator D3DXVECTOR3()
	{
		D3DXVECTOR3 TmpVec;

		D3DXMATRIX TmpMat;

		D3DXMatrixRotationQuaternion(&TmpMat, this);

		D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &TmpMat);

		return TmpVec;
	}

	operator D3DXMATRIX()
	{
		D3DXMATRIX TmpMat;

		D3DXMatrixRotationQuaternion(&TmpMat, this);

		return TmpMat;
	}

	ChQuaternion_9&operator=(const D3DXQUATERNION& _cm)
	{
		if (this == &_cm)return *this;
		D3DXQUATERNION::operator =(_cm);
		return *this;
	}

	ChQuaternion_9&operator = (const D3DXMATRIX& _cm)
	{
		D3DXQuaternionRotationMatrix(this, &_cm);

		return *this;
	}

	ChQuaternion_9&operator =(const D3DXVECTOR3& _cm)
	{
		D3DXVECTOR3 TmpVec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		D3DXVECTOR3 TmpVec2 = _cm;

		D3DXVec3Normalize(&TmpVec, &TmpVec);
		D3DXVec3Normalize(&TmpVec2, &TmpVec2);

		float TmpDot = D3DXVec3Dot(&TmpVec, &TmpVec2);

		D3DXVec3Cross(&TmpVec, &TmpVec, &TmpVec2);

		D3DXQuaternionRotationAxis(this, &TmpVec, TmpDot);

		return *this;

	}

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer

	ChQuaternion_9(D3DXQUATERNION &_cm) :D3DXQUATERNION(_cm) {};

	ChQuaternion_9()
	{
		Identity();
	}

	ChQuaternion_9(const D3DXMATRIX& _cm)
	{
		D3DXQuaternionRotationMatrix(this, &_cm);

	}

	ChQuaternion_9(const D3DXVECTOR3& _cm)
	{
		D3DXVECTOR3 TmpVec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		D3DXVECTOR3 TmpVec2 = _cm;

		D3DXVec3Normalize(&TmpVec, &TmpVec);
		D3DXVec3Normalize(&TmpVec2, &TmpVec2);

		float TmpDot = D3DXVec3Dot(&TmpVec, &TmpVec2);

		D3DXVec3Cross(&TmpVec, &TmpVec, &TmpVec2);

		D3DXQuaternionRotationAxis(this, &TmpVec, TmpDot);

	}

	ChQuaternion_9(
		const float _x
		, const float _y
		, const float _z
		, const float _w = 0.0f)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	///////////////////////////////////////////////////////////////////////////////////
	
	inline void RotYPR(const float _x, const float _y, const float _z)
	{
		D3DXQuaternionRotationYawPitchRoll(
			this
			, D3DXToRadian(_y)
			, D3DXToRadian(_x)
			, D3DXToRadian(_z));
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotAxis(const D3DXVECTOR3 *_Vec,const float _Ang)
	{
		D3DXQuaternionRotationAxis(
			this
			, _Vec
			, D3DXToRadian(_Ang));
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotMat(const D3DXMATRIX *_Mat)
	{
		D3DXQuaternionRotationMatrix(this, _Mat);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Lerp(
		const D3DXQUATERNION& _SQua
		, const D3DXQUATERNION& _EQua
		, const float _NowTime)
	{
		D3DXQuaternionSlerp(this, &_SQua, &_EQua, _NowTime);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Identity()
	{
		D3DXQuaternionIdentity(this);
	}

private:

}ChQua_9;

#endif
#ifndef Ch_D3D9_ChMat_h
#define Ch_D3D9_ChMat_h

//D3DXMATRIXをパック化したクラス//
typedef class ChMatrix_9 :public D3DXMATRIX
{
public:

	operator D3DXVECTOR3()const
	{
		D3DXVECTOR3 TmpVec;

		TmpVec.x = _41;
		TmpVec.y = _42;
		TmpVec.z = _43;

		return TmpVec;
	}

	operator D3DXQUATERNION()const
	{
		D3DXQUATERNION TmpQua;

		D3DXQuaternionRotationMatrix(&TmpQua, this);

		return TmpQua;
	}

	ChMatrix_9&operator =(const D3DXMATRIX&_cm)
	{
		for (unsigned i = 0; i < 4; i++)
		{
			for (unsigned j = 0; j < 4; j++)
			{
				m[i][j] = _cm.m[i][j];
			}
		}
		return *this;
	}

	D3DXMATRIX&operator = (const D3DXVECTOR3& _Vec)
	{
		_41 = _Vec.x;
		_42 = _Vec.y;
		_43 = _Vec.z;
		return *this;
	}

	D3DXMATRIX&operator = (const D3DXQUATERNION& _Qua)
	{
		D3DXMatrixRotationQuaternion(this, &_Qua);

		return *this;
	}

	D3DXMATRIX&operator *= (const D3DXMATRIX& _Mat) 
	{
		*this = _Mat * *this;
		return *this;
	}

	ChMatrix_9&operator *= (const D3DXVECTOR3& _Vec)
	{
		_41 += _Vec.x;
		_42 += _Vec.y;
		_43 += _Vec.z;
		return *this;
	}

	ChMatrix_9&operator *= (const D3DXQUATERNION& _Qua)
	{
		D3DXMATRIX TmpMat;
		D3DXMatrixRotationQuaternion(&TmpMat, &_Qua);

		*this = TmpMat * *this;

		return *this;
	}

	ChMatrix_9&operator *= (const float& _Num)
	{
		_11 *= _Num;
		_12 *= _Num;
		_13 *= _Num;
		_14 *= _Num;
		_21 *= _Num;
		_22 *= _Num;
		_23 *= _Num;
		_24 *= _Num;
		_31 *= _Num;
		_32 *= _Num;
		_33 *= _Num;
		_34 *= _Num;
		_41 *= _Num;
		_42 *= _Num;
		_43 *= _Num;
		_44 *= _Num;

		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	ChMatrix_9(D3DXMATRIX &_cm) :D3DXMATRIX(_cm) {};

	ChMatrix_9(const D3DXMATRIX &_cm)
	{
		*this = _cm;
	}

	ChMatrix_9()
	{
		Identity();
	}

	ChMatrix_9(const D3DXVECTOR3& _Vec)
	{
		_41 = _Vec.x;
		_42 = _Vec.y;
		_43 = _Vec.z;
	}

	ChMatrix_9(const D3DXQUATERNION& _Qua)
	{
		D3DXMatrixRotationQuaternion(this, &_Qua);
	}

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//


	D3DXVECTOR3 GetPosition()
	{
		D3DXVECTOR3 TmpVec;
		TmpVec.x = _41;
		TmpVec.y = _42;
		TmpVec.z = _43;
		return TmpVec;
	}

	D3DXQUATERNION GetRotation()
	{
		D3DXQUATERNION TmpQua;
		D3DXQuaternionRotationMatrix(&TmpQua, this);
		return TmpQua;
	}

	D3DXVECTOR3 GetScaleSize()
	{
		D3DXMATRIX TmpMat;

		{
			D3DXQUATERNION TmpQua;

			D3DXQuaternionRotationMatrix(&TmpQua, this);

			D3DXMatrixRotationQuaternion(&TmpMat, &TmpQua);

		}

		D3DXMatrixInverse(&TmpMat, NULL, &TmpMat);

		TmpMat = TmpMat * *this;

		return D3DXVECTOR3(TmpMat._11, TmpMat._22, TmpMat._33);

	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Identity() { D3DXMatrixIdentity(this); }

	///////////////////////////////////////////////////////////////////////////////////

	inline void Inverse() 
	{
		D3DXMatrixInverse(this, NULL, this);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Inverse(const D3DXMATRIX& TmpMat)
	{
		D3DXMatrixInverse(this, NULL, &TmpMat);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotYPR(const float _x, const float _y, const float _z)
	{
		D3DXMATRIX TmpMat;
		D3DXMatrixRotationYawPitchRoll(&TmpMat, D3DXToRadian(_y), D3DXToRadian(_x), D3DXToRadian(_z));
		*this = TmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotYPR(const D3DXVECTOR3& _Vec)
	{
		D3DXMATRIX TmpMat;
		D3DXMatrixRotationYawPitchRoll(&TmpMat, D3DXToRadian(_Vec.y), D3DXToRadian(_Vec.x), D3DXToRadian(_Vec.z)); 
		*this = TmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotQua(const D3DXQUATERNION& _Qua)
	{
		D3DXMATRIX TmpMat;
		D3DXMatrixRotationQuaternion(&TmpMat, &_Qua); 
		*this = TmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotQua(const float _x, const float _y, const float _z)
	{
		D3DXQUATERNION TmpQua;
		D3DXQuaternionRotationYawPitchRoll(&TmpQua, D3DXToRadian(_y), D3DXToRadian(_x), D3DXToRadian(_z));
		D3DXMATRIX TmpMat;
		D3DXMatrixRotationQuaternion(&TmpMat, &TmpQua);
		*this = TmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotVec(const D3DXVECTOR3& _Vec)
	{
		D3DXVECTOR3 TmpCross ,TmpVec;
		TmpVec = _Vec;
		float TmpRot;

		auto Tmp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		D3DXVec3Normalize(&TmpVec, &TmpVec);
		D3DXVec3Cross(&TmpCross, &Tmp, &TmpVec);
		TmpRot = D3DXVec3Dot(&TmpVec, &Tmp);

		D3DXMATRIX TmpMat;
		D3DXMatrixRotationAxis(&TmpMat, &TmpCross, std::acos(TmpRot));
		*this = TmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotAxis(const D3DXVECTOR3& _Vec,const float _Ang)
	{
		D3DXMATRIX TmpMat;
		D3DXMatrixRotationAxis(&TmpMat, &_Vec, D3DXToRadian(_Ang));
		*this = TmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Trans(const float _x, const float _y, const float _z)
	{
		D3DXMatrixTranslation(this, _x, _y, _z);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Trans(const D3DXVECTOR3& _Vec)
	{
		D3DXMatrixTranslation(this, _Vec.x, _Vec.y, _Vec.z);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void VectorMove(const D3DXVECTOR3& _Vec)
	{
		this->_41 += _Vec.x;
		this->_42 += _Vec.y;
		this->_43 += _Vec.z;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Move(const float _x, const float _y, const float _z)
	{
		ChMatrix_9 TmpMat;
		TmpMat.Trans(_x, _y, _z);
		*this = TmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Scaling(const float _x, const float _y, const float _z)
	{
		D3DXMATRIX TmpMat;
		D3DXMatrixScaling(&TmpMat, _x, _y, _z);
		*this = TmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Scaling(const D3DXVECTOR3& _TmpVec)
	{
		D3DXMATRIX TmpMat;
		D3DXMatrixScaling(&TmpMat, _TmpVec.x, _TmpVec.y, _TmpVec.z);
		*this = TmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Scaling(const float _Scl)
	{
		D3DXMATRIX TmpMat;
		D3DXMatrixScaling(&TmpMat, _Scl, _Scl, _Scl);
		*this = TmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Clear0()
	{
		for (unsigned char i = 0; i < 4; i++)
		{
			for (unsigned char j = 0; j < 4; j++)
			{
				m[i][j] = 0.0f;
			}
		}
	}

private:

}ChMat_9;


#endif
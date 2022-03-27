#ifndef Ch_D3D11_ChMat_h
#define Ch_D3D11_ChMat_h


//D3DXMATRIXをパック化したクラス//
typedef class ChMatrix_11 :public DirectX::XMFLOAT4X4
{
public:

	ChMatrix_11&operator=(const DirectX::XMFLOAT4X4& _cm);

	ChMatrix_11&operator+=(const DirectX::XMFLOAT4X4& _cm);
	ChMatrix_11 operator+(const DirectX::XMFLOAT4X4& _cm)const;
	ChMatrix_11&operator-=(const DirectX::XMFLOAT4X4& _cm);
	ChMatrix_11 operator-(const DirectX::XMFLOAT4X4& _cm)const;
	ChMatrix_11&operator*=(const DirectX::XMFLOAT4X4& _cm);
	ChMatrix_11 operator*(const DirectX::XMFLOAT4X4& _cm)const;
	ChMatrix_11&operator/=(const DirectX::XMFLOAT4X4& _cm);
	ChMatrix_11 operator/(const DirectX::XMFLOAT4X4& _cm)const;

	ChMatrix_11&operator=(const float& _cm);
	ChMatrix_11&operator*=(const float& _cm);
	ChMatrix_11 operator*(const float& _cm)const;
	ChMatrix_11&operator/=(const float& _cm);
	ChMatrix_11 operator/(const float& _cm)const;

	ChMatrix_11&operator=(const DirectX::XMMATRIX& _cm);

	operator DirectX::XMMATRIX()const;

	operator DirectX::XMFLOAT4X4()const;

	ChMatrix_11&operator = (const DirectX::XMFLOAT3& _Vec);

	ChMatrix_11&operator =(const DirectX::XMFLOAT4& _Qua);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChMatrix_11(const DirectX::XMFLOAT4X4 &_cm)
	{
		*this = _cm;
	}

	inline ChMatrix_11(const DirectX::XMMATRIX &_cm)
	{
		*this = _cm;
	}

	inline ChMatrix_11()
	{
		Identity();
	}

	inline ChMatrix_11(const DirectX::XMFLOAT3& _Vec)
	{
		*this = _Vec;
	}

	inline ChMatrix_11(const DirectX::XMFLOAT4& _Qua)
	{
		*this = _Qua;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//


	DirectX::XMFLOAT3 GetPosition()const;

	DirectX::XMFLOAT4 GetRotation()const;

	DirectX::XMFLOAT3 GetScaleSize()const;

	///////////////////////////////////////////////////////////////////////////////////

	inline void Identity()
	{
		*this = DirectX::XMMatrixIdentity();
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Inverse()
	{
		Inverse(*this);
	}

	///////////////////////////////////////////////////////////////////////////////////

	void Inverse(const DirectX::XMFLOAT4X4& _Mat);

	///////////////////////////////////////////////////////////////////////////////////

	void RotYPR(const float _x, const float _y, const float _z);

	///////////////////////////////////////////////////////////////////////////////////

	void RotYPR(const DirectX::XMFLOAT3& _Vec);

	///////////////////////////////////////////////////////////////////////////////////

	void RotQua(const DirectX::XMFLOAT4& _Qua);

	///////////////////////////////////////////////////////////////////////////////////

	void RotQua(const float _x, const float _y, const float _z);

	///////////////////////////////////////////////////////////////////////////////////

	void RotVec(const DirectX::XMFLOAT3& _Vec);

	///////////////////////////////////////////////////////////////////////////////////

	void RotAxis(const DirectX::XMFLOAT3& _Vec, const float _Ang);

	///////////////////////////////////////////////////////////////////////////////////

	inline void Trans(const float _x, const float _y, const float _z)
	{
		*this = DirectX::XMMatrixTranslation(_x, _y, _z);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Trans(const DirectX::XMFLOAT3& _Vec)
	{
		*this = DirectX::XMMatrixTranslation(_Vec.x, _Vec.y, _Vec.z);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void VectorMove(const DirectX::XMFLOAT3& _Vec)
	{
		this->_41 += _Vec.x;
		this->_42 += _Vec.y;
		this->_43 += _Vec.z;
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Move(const float _x, const float _y, const float _z)
	{
		ChMatrix_11 TmpMat;
		TmpMat.Trans(_x, _y, _z);
		*this = TmpMat * *this;
	}

	///////////////////////////////////////////////////////////////////////////////////

	void Scaling(
		const float _x
		, const float _y
		, const float _z);

	///////////////////////////////////////////////////////////////////////////////////

	inline void Scaling(const DirectX::XMFLOAT3& _TmpVec)
	{
		Scaling(_TmpVec.x, _TmpVec.y, _TmpVec.z);
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Scaling(const float _Scl)
	{

		Scaling(_Scl, _Scl, _Scl);
	}

	///////////////////////////////////////////////////////////////////////////////////

private:

}ChMat_11;


#endif
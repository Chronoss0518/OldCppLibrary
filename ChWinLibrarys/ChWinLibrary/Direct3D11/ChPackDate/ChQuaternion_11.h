#ifndef Ch_D3D11_Qua_h
#define Ch_D3D11_Qua_h

//D3DXQUATERNIONをパック化したクラス//
typedef class ChQuaternion_11 :public DirectX::XMFLOAT4
{
public:

	ChQuaternion_11&operator=(const DirectX::XMFLOAT4& _cm);

	ChQuaternion_11&operator+=(const DirectX::XMFLOAT4& _cm);
	ChQuaternion_11 operator+(const DirectX::XMFLOAT4& _cm)const;
	ChQuaternion_11&operator-=(const DirectX::XMFLOAT4& _cm);
	ChQuaternion_11 operator-(const DirectX::XMFLOAT4& _cm)const;
	ChQuaternion_11&operator*=(const DirectX::XMFLOAT4& _cm);
	ChQuaternion_11 operator*(const DirectX::XMFLOAT4& _cm)const;
	ChQuaternion_11&operator/=(const DirectX::XMFLOAT4& _cm);
	ChQuaternion_11 operator/(const DirectX::XMFLOAT4& _cm)const;

	ChQuaternion_11&operator=(const float& _cm);
	ChQuaternion_11&operator+=(const float& _cm);
	ChQuaternion_11 operator+(const float& _cm)const;
	ChQuaternion_11&operator-=(const float& _cm);
	ChQuaternion_11 operator-(const float& _cm)const;
	ChQuaternion_11&operator*=(const float& _cm);
	ChQuaternion_11 operator*(const float& _cm)const;
	ChQuaternion_11&operator/=(const float& _cm);
	ChQuaternion_11 operator/(const float& _cm)const;

	ChQuaternion_11&operator=(const DirectX::XMVECTOR& _cm);

	operator DirectX::XMVECTOR()const;

	operator DirectX::XMFLOAT4()const;

	ChQuaternion_11&operator = (const DirectX::XMFLOAT3& _Vec);

	ChQuaternion_11&operator =(const DirectX::XMFLOAT4X4& _Mat);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer

	ChQuaternion_11()
	{
		Identity();
	}

	ChQuaternion_11(const DirectX::XMFLOAT4X4& _cm)
	{
		*this = _cm;

	}

	ChQuaternion_11(const  DirectX::XMFLOAT3& _cm)
	{
		*this = _cm;

	}

	ChQuaternion_11(
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
	
	void RotYPR(const float _x, const float _y, const float _z);

	inline void RotYPR(const ChVec3& _Vec)
	{
		RotYPR(_Vec.x, _Vec.y, _Vec.z);
	}

	inline void RotYPR(const DirectX::XMFLOAT3& _Vec)
	{
		RotYPR(_Vec.x, _Vec.y, _Vec.z);
	}

	///////////////////////////////////////////////////////////////////////////////////

	void RotLookAt(
		const DirectX::XMFLOAT3& _Pos
		, const DirectX::XMFLOAT3& _BasePos);

	///////////////////////////////////////////////////////////////////////////////////

	void RotAxis(const DirectX::XMFLOAT3& _Vec, const float _Ang);

	///////////////////////////////////////////////////////////////////////////////////

	void RotMat(const DirectX::XMFLOAT4X4& _Mat);

	///////////////////////////////////////////////////////////////////////////////////

	void Lerp(
		const ChQuaternion_11& _SQua
		, const ChQuaternion_11& _EQua
		, const float _NowTime);

	///////////////////////////////////////////////////////////////////////////////////

	void Identity();

	///////////////////////////////////////////////////////////////////////////////////

	void Inverse()
	{
		Inverse(*this);
	}

	void Inverse(const DirectX::XMFLOAT4& _Qua)
	{
		ChQuaternion_11 TmpQua;
		TmpQua = _Qua;
		Inverse(TmpQua);
	}

	void Inverse(const ChQuaternion_11& _Qua);

private:

}ChQua_11;

#endif
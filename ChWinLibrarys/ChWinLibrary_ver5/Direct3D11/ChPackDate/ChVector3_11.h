#ifndef Ch_D3D11_Vec3_h
#define Ch_D3D11_Vec3_h

//ƒpƒbƒN‰»‚µ‚½XFLOAT3(D3D11Vector)Œ^//
typedef class ChVector3_11 :public DirectX::XMFLOAT3
{
public:

	ChVector3_11&operator=(const DirectX::XMFLOAT3& _cm);

	ChVector3_11&operator+=(const DirectX::XMFLOAT3& _cm);
	ChVector3_11 operator+(const DirectX::XMFLOAT3& _cm)const;
	ChVector3_11&operator-=(const DirectX::XMFLOAT3& _cm);
	ChVector3_11 operator-(const DirectX::XMFLOAT3& _cm)const;
	ChVector3_11&operator*=(const DirectX::XMFLOAT3& _cm);
	ChVector3_11 operator*(const DirectX::XMFLOAT3& _cm)const;
	ChVector3_11&operator/=(const DirectX::XMFLOAT3& _cm);
	ChVector3_11 operator/(const DirectX::XMFLOAT3& _cm)const;

	ChVector3_11&operator=(const float& _cm);
	ChVector3_11&operator+=(const float& _cm);
	ChVector3_11 operator+(const float& _cm)const;
	ChVector3_11&operator-=(const float& _cm);
	ChVector3_11 operator-(const float& _cm)const;
	ChVector3_11&operator*=(const float& _cm);
	ChVector3_11 operator*(const float& _cm)const;
	ChVector3_11&operator/=(const float& _cm);
	ChVector3_11 operator/(const float& _cm)const;

	ChVector3_11&operator=(const DirectX::XMVECTOR& _cm);

	operator DirectX::XMVECTOR()const;

	ChVector3_11&operator = (const DirectX::XMFLOAT4& _qua);
	ChVector3_11&operator =(const DirectX::XMFLOAT4X4& _mat);


	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	ChVector3_11(const DirectX::XMFLOAT3& _cm) :DirectX::XMFLOAT3(_cm){}

	ChVector3_11()
	{
		Set0Param();
	}

	ChVector3_11(const DirectX::XMMATRIX& _mat)
	{
		*this = _mat;
	}

	ChVector3_11(const DirectX::XMFLOAT4& _qua)
	{
		*this = _qua;
	}

	ChVector3_11(const float _x, const float _y, const float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	ChVector3_11(const float _num)
	{
		x = _num;
		y = _num;
		z = _num;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	float GetLen(
		const DirectX::XMFLOAT3& _Vec
		= DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f))const;

	float GetRadian(
		const ChVector3_11& _vec1
		, const ChVector3_11& _vec2)const;

	float GetDegree(
		const ChVector3_11& _vec1
		, const ChVector3_11& _vec2)const;

	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	void Set0Param();

	///////////////////////////////////////////////////////////////////////////////////
	//IsFunction//

	ChStd::Bool IsNormals()const;
	
	ChStd::Bool IsAll0()const;

	///////////////////////////////////////////////////////////////////////////////////

	void MatPos(
		const DirectX::XMMATRIX& _mat
		, const ChVector3_11&  _vec = ChVector3_11(0.0f, 0.0f, 0.0f));

	///////////////////////////////////////////////////////////////////////////////////

	void MatNormal(
		const DirectX::XMMATRIX& _mat
		, const ChVector3_11&  _vec = ChVector3_11(0.0f, 0.0f, 1.0f));

	///////////////////////////////////////////////////////////////////////////////////

	void Normalize();

	///////////////////////////////////////////////////////////////////////////////////

	void Lerp(
		const ChVector3_11& _sVec
		, const ChVector3_11& _eVec
		, const float _nowTime);

	///////////////////////////////////////////////////////////////////////////////////

	void CrossVec(
		const ChVector3_11& _vec1
		, const ChVector3_11& _vec2);

	///////////////////////////////////////////////////////////////////////////////////

	float Dot(
		const ChVector3_11& _vec1
		, const ChVector3_11&  _vec2)const;

	///////////////////////////////////////////////////////////////////////////////////


}ChVec3_11;



#endif
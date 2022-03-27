#ifndef Ch_D3D9_Qua_h
#define Ch_D3D9_Qua_h

//D3DXQUATERNIONをパック化したクラス//
typedef class ChQuaternion_9 :public D3DXQUATERNION
{
public:

	operator D3DXVECTOR3();

	operator D3DXMATRIX();

	ChQuaternion_9& operator=(const D3DXQUATERNION& _cm);

	ChQuaternion_9& operator = (const D3DXMATRIX& _cm);

	ChQuaternion_9& operator =(const D3DXVECTOR3& _cm);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer

	ChQuaternion_9(const D3DXQUATERNION &_cm) :D3DXQUATERNION(_cm) {};

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
		D3DXVECTOR3 tmpVec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		D3DXVECTOR3 tmpVec2 = _cm;

		D3DXVec3Normalize(&tmpVec, &tmpVec);
		D3DXVec3Normalize(&tmpVec2, &tmpVec2);

		float tmpDot = D3DXVec3Dot(&tmpVec, &tmpVec2);

		D3DXVec3Cross(&tmpVec, &tmpVec, &tmpVec2);

		D3DXQuaternionRotationAxis(this, &tmpVec, tmpDot);

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
	
	void RotYPR(const float _x, const float _y, const float _z);

	///////////////////////////////////////////////////////////////////////////////////

	void RotYPR(const D3DXVECTOR3& _vec);

	///////////////////////////////////////////////////////////////////////////////////

	void RotAxis(const D3DXVECTOR3* _vec, const float _ang);

	///////////////////////////////////////////////////////////////////////////////////

	void RotMat(const D3DXMATRIX* _mat);

	///////////////////////////////////////////////////////////////////////////////////

	void Lerp(
		const D3DXQUATERNION& _sQua
		, const D3DXQUATERNION& _eQua
		, const float _nowTime);

		///////////////////////////////////////////////////////////////////////////////////

	void Identity();

private:

}ChQua_9;

#endif
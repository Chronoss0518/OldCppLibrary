#ifndef Ch_CPP_Math_h
#define Ch_CPP_Math_h


#include"ChMathBase/ChMatrixBase.h"

struct D3DXVECTOR4;
struct D3DXVECTOR3;
struct D3DXVECTOR2;

struct D3DXMATRIX;
struct D3DXQUATERNION;

namespace DirectX
{
	struct XMFLOAT3;
	struct XMFLOAT4;
	struct XMFLOAT4X4;
} // namespace DirectX

struct ChVector4;
struct ChVector3;
struct ChVector2;
struct ChRMatrix;
struct ChLMatrix;
struct ChUIMatrix;

namespace ChMath
{
	template<typename T>
	struct ChVector4Base
	{

		union {
			struct
			{
				T x, y, z, w;
			};
			struct
			{
				T r, g, b, a;
			};
			struct
			{
				T left, top, right, down;
			};
			VectorBase<T,4> Val;
		};
	};

	template<typename T>
	struct ChVector3Base
	{

		union {
			struct
			{
				T x, y, z;
			};
			struct
			{
				T r, g, b;
			};
			VectorBase<T, 3> Val;
		};
	};

	template<typename T>
	struct ChVector2Base
	{

		union {
			struct
			{
				T x, y;
			};
			struct
			{
				T w, h;
			};
			VectorBase<T, 2> Val;
		};
	};
	
	struct ChQuaternionBase
	{

		union {
			struct
			{
				float x, y, z, w;
			};
			float Val[4]{ 0, 0, 0, 0 };
		};
	};

	template<typename T>
	struct ChBaseHMatrix2x2
	{
		union
		{
			struct
			{

				T _11, _12;
				T _21, _22;

			};
			T m[2][2];
		};

	};

	template<typename T>
	struct ChBaseVMatrix2x2
	{
		union
		{
			struct
			{

				T _11, _21;
				T _12, _22;

			};
			T m[2][2];
		};

	};

	template<typename T>
	struct ChBaseHMatrix3x3
	{
		union
		{
			struct
			{

				T _11, _12, _13;
				T _21, _22, _23;
				T _31, _32, _33;

			};
			T m[3][3];
		};

	};

	template<typename T>
	struct ChBaseVMatrix3x3
	{
		union
		{
			struct
			{

				T _11, _21, _31;
				T _12, _22, _32;
				T _13, _23, _33;

			};
			T m[3][3];
		};

	};

	template<typename T>
	struct ChBaseHMatrix4x4
	{
		union
		{
			struct
			{
				T _11, _12, _13, _14;
				T _21, _22, _23, _24;
				T _31, _32, _33, _34;
				T _41, _42, _43, _44;
			};
			MatrixBase<T, 4, 4> m;
		};

	};

	template<typename T>
	struct ChBaseVMatrix4x4
	{
		union
		{
			struct
			{

				T _11, _21, _31, _41;
				T _12, _22, _32, _42;
				T _13, _23, _33, _43;
				T _14, _24, _34, _44;
			};
			MatrixBase<T, 4, 4> m;
		};

	};

} // namespace ChMath

struct ChVector4 : public ChMath::ChVector4Base<float>
{

	///////////////////////////////////////////////////////////////////////////////////
	//StaticFunction//


	///////////////////////////////////////////////////////////////////////////////////
	//Operator//

	ChVector4& operator*=(const float& _Num);
	ChVector4 operator*(const float& _Num) const;
	ChVector4& operator/=(const float& _Num);
	ChVector4 operator/(const float& _Num) const;
	ChVector4& operator=(const float& _Num);

	ChVector4& operator=(const ChVector4& _Vec);
	ChVector4& operator-=(const ChVector4& _Vec);
	ChVector4 operator-(const ChVector4& _Vec) const;
	ChVector4& operator+=(const ChVector4& _Vec);
	ChVector4 operator+(const ChVector4& _Vec) const;
	ChVector4& operator*=(const ChVector4& _Vec);
	ChVector4 operator*(const ChVector4& _Vec) const;
	ChVector4& operator/=(const ChVector4& _Vec);
	ChVector4 operator/(const ChVector4& _Vec) const;

	bool operator==(const ChVector4& _Vec)const
	{
		return Val == _Vec.Val;
	}

	bool operator!=(const ChVector4& _Vec)const
	{
		return Val != _Vec.Val;
	}

	operator const ChVector3() const;
	operator const ChVector2() const;

	operator const D3DXVECTOR4() const;
	operator const D3DXVECTOR4* () const;

	ChVector4& operator=(const D3DXVECTOR4&);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChVector4()
	{
		Val.Identity();
	}

	inline ChVector4(const float _Num)
	{

		Val.Set(_Num);

		if (w < -1.0f)
			w = -1.0f;
		if (w > 1.0f)
			w = 1.0f;
	}

	inline ChVector4(
		const float _x, const float _y, const float _z, const float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
		if (w < -1.0f)
			w = -1.0f;
		if (w > 1.0f)
			w = 1.0f;
	}

	inline ChVector4(const ChVector4& _Vec) { *this = _Vec; }

	inline ChVector4(const D3DXVECTOR4& _Vec) { *this = _Vec; }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _CutChar = ","
		, const std::string& _EndChar = ";");

	std::string SerializeARGB(
		const std::string& _CutChar = ","
		, const std::string& _EndChar = ";");

	void Deserialize(
		const std::string& _Str
		, const size_t _FPos = 0
		, const std::string& _CutChar = ","
		, const std::string& _EndChar = ";"
		, const unsigned int _Digit = 6);

	void DeserializeARGB(
		const std::string& _Str
		, const size_t _FPos = 0
		, const std::string& _CutChar = ","
		, const std::string& _EndChar = ";"
		, const unsigned int _Digit = 6);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	static ChVector4 GetCross(
		const ChVector4& _Vec1, const ChVector4& _Vec2);

	static float GetCos(
		const ChVector4& _Vec1, const ChVector4& _Vec2);

	static float GetRadian(
		const ChVector4& _Vec1, const ChVector4& _Vec2);

	static float GetDot(
		const ChVector4& _Vec1, const ChVector4& _Vec2);

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	static ChVector4 GetCorrection(
		const ChVector4& _Start, const ChVector4& _End, const float _Now);

	static float GetLen(
		const ChVector4& _Vec1, const ChVector4& _Vec2);

	///////////////////////////////////////////////////////////////////////////////////

	inline float Len() const
	{
		return GetLen(*this, ChVector4());
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Abs()
	{
		Val.Abs();
	}

	inline void Abs(const ChVector4& _Vec)
	{
		Val.Abs(_Vec.Val);
	}

	///////////////////////////////////////////////////////////////////////////////////

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	inline void Correction(
		const ChVector4& _Start, const ChVector4& _End, const float _Now)
	{
		*this = GetCorrection(_Start, _End, _Now);
	}

	///////////////////////////////////////////////////////////////////////////////////

	void Normalize();

	///////////////////////////////////////////////////////////////////////////////////

	void Cross(const ChVector4& _Vec1, const ChVector4& _Vec2);

};

using ChVec4 = ChVector4;

///////////////////////////////////////////////////////////////////////////////////

struct ChVector3 : public ChMath::ChVector3Base<float>
{

	ChVector3& operator*=(const float& _Num);
	ChVector3 operator*(const float& _Num) const;
	ChVector3& operator/=(const float& _Num);
	ChVector3 operator/(const float& _Num) const;
	ChVector3& operator=(const float& _Num);

	ChVector3& operator=(const ChVector3& _Vec);
	ChVector3& operator-=(const ChVector3& _Vec);
	ChVector3 operator-(const ChVector3& _Vec) const;
	ChVector3& operator+=(const ChVector3& _Vec);
	ChVector3 operator+(const ChVector3& _Vec) const;
	ChVector3& operator*=(const ChVector3& _Vec);
	ChVector3 operator*(const ChVector3& _Vec) const;
	ChVector3& operator/=(const ChVector3& _Vec);
	ChVector3 operator/(const ChVector3& _Vec) const;

	bool operator==(const ChVector3& _Vec)const
	{
		return Val == _Vec.Val;
	}

	bool operator!=(const ChVector3& _Vec)const
	{
		return Val != _Vec.Val;
	}

	operator const ChVector4() const;
	operator const ChVector2() const;

	operator const D3DXVECTOR3() const;
	operator const D3DXVECTOR3* () const;

	operator const DirectX::XMFLOAT3() const;
	operator const DirectX::XMFLOAT3* () const;

	ChVector3& operator=(const D3DXVECTOR3&);
	ChVector3& operator=(const DirectX::XMFLOAT3&);

	ChVector3& operator=(const D3DXQUATERNION&);
	ChVector3& operator=(const DirectX::XMFLOAT4&);

	ChVector3& operator=(const D3DXMATRIX&);
	ChVector3& operator=(const DirectX::XMFLOAT4X4&);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChVector3()
	{
		Val.Identity();
	}

	inline ChVector3(const float _Num)
	{
		Val.Set(_Num);
	}

	inline ChVector3(
		const float _x, const float _y, const float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	inline ChVector3(const ChVector3& _Vec) { *this = _Vec; }

	inline ChVector3(const D3DXVECTOR3& _Vec) { *this = _Vec; }
	inline ChVector3(const DirectX::XMFLOAT3& _Vec) { *this = _Vec; }

	inline ChVector3(const D3DXQUATERNION& _Qua) { *this = _Qua; }
	inline ChVector3(const DirectX::XMFLOAT4& _Qua) { *this = _Qua; }

	inline ChVector3(const D3DXMATRIX& _Mat) { *this = _Mat; }
	inline ChVector3(const DirectX::XMFLOAT4X4& _Mat) { *this = _Mat; }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _CutChar = ","
		, const std::string& _EndChar = ";");

	void Deserialize(
		const std::string& _Str
		, const size_t _FPos = 0
		, const std::string& _CutChar = ","
		, const std::string& _EndChar = ";"
		, const unsigned int _Digit = 6);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	static ChVector3 GetCross(
		const ChVector3& _Vec1, const ChVector3& _Vec2);

	static float GetCos(
		const ChVector3& _Vec1, const ChVector3& _Vec2);

	static float GetRadian(
		const ChVector3& _Vec1, const ChVector3& _Vec2);

	static float GetDot(
		const ChVector3& _Vec1, const ChVector3& _Vec2);

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	static ChVector3 GetCorrection(
		const ChVector3& _Start, const ChVector3& _End, const float _Now);

	static float GetLen(
		const ChVector3& _Vec1, const ChVector3& _Vec2);

	///////////////////////////////////////////////////////////////////////////////////

	inline float Len() const
	{
		return GetLen(*this, ChVector3());
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Abs()
	{
		Val.Abs();
	}

	inline void Abs(const ChVector3& _Vec)
	{
		Val.Abs(_Vec.Val);
	}

	///////////////////////////////////////////////////////////////////////////////////

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	inline void Correction(
		const ChVector3& _Start, const ChVector3& _End, const float _Now)
	{
		*this = GetCorrection(_Start, _End, _Now);
	}

	///////////////////////////////////////////////////////////////////////////////////

	void Normalize();

	///////////////////////////////////////////////////////////////////////////////////

	void Cross(const ChVector3& _Vec1, const ChVector3& _Vec2);

};

using ChVec3 = ChVector3;

///////////////////////////////////////////////////////////////////////////////////

struct ChVector2 : public ChMath::ChVector2Base<float>
{

	ChVector2& operator*=(const float& _Num);
	ChVector2 operator*(const float& _Num) const;
	ChVector2& operator/=(const float& _Num);
	ChVector2 operator/(const float& _Num) const;
	ChVector2& operator=(const float& _Num);

	ChVector2& operator=(const ChVector2& _Vec);
	ChVector2& operator-=(const ChVector2& _Vec);
	ChVector2 operator-(const ChVector2& _Vec) const;
	ChVector2& operator+=(const ChVector2& _Vec);
	ChVector2 operator+(const ChVector2& _Vec) const;
	ChVector2& operator*=(const ChVector2& _Vec);
	ChVector2 operator*(const ChVector2& _Vec) const;
	ChVector2& operator/=(const ChVector2& _Vec);
	ChVector2 operator/(const ChVector2& _Vec) const;

	bool operator==(const ChVector2& _Vec)const
	{
		return Val == _Vec.Val;
	}

	bool operator!=(const ChVector2& _Vec)const
	{
		return Val != _Vec.Val;
	}

	operator const ChVector4() const;
	operator const ChVector3() const;

	operator const D3DXVECTOR2() const;
	operator const D3DXVECTOR2* () const;

	ChVector2& operator=(const D3DXVECTOR2&);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChVector2()
	{
		Val.Identity();
	}

	inline ChVector2(const float _Num)
	{
		Val.Set(_Num);
	}

	inline ChVector2(
		const float _x, const float _y)
	{
		x = _x;
		y = _y;
	}

	inline ChVector2(const ChVector2& _Vec) { *this = _Vec; }

	inline ChVector2(const D3DXVECTOR2& _Vec) { *this = _Vec; }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _CutChar = ","
		, const std::string& _EndChar = ";");

	void Deserialize(
		const std::string& _Str
		, const size_t _FPos = 0
		, const std::string& _CutChar = ","
		, const std::string& _EndChar = ";"
		, const unsigned int _Digit = 6);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	static ChVector2 GetCross(
		const ChVector2& _Vec1, const ChVector2& _Vec2);

	static float GetCos(
		const ChVector2& _Vec1, const ChVector2& _Vec2);

	static float GetRadian(
		const ChVector2& _Vec1, const ChVector2& _Vec2);

	static float GetDot(
		const ChVector2& _Vec1, const ChVector2& _Vec2);

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	static ChVector2 GetCorrection(
		const ChVector2& _Start, const ChVector2& _End, const float _Now);

	static float GetLen(
		const ChVector2& _Vec1, const ChVector2& _Vec2);

	///////////////////////////////////////////////////////////////////////////////////

	inline float Len() const
	{
		return GetLen(*this, ChVector2());
	}

	///////////////////////////////////////////////////////////////////////////////////

	inline void Abs()
	{
		Val.Abs();
	}

	inline void Abs(const ChVector2& _Vec)
	{
		Val.Abs(_Vec.Val);
	}

	///////////////////////////////////////////////////////////////////////////////////

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	inline void Correction(
		const ChVector2& _Start, const ChVector2& _End, const float _Now)
	{
		*this = GetCorrection(_Start, _End, _Now);
	}

	///////////////////////////////////////////////////////////////////////////////////

	void Normalize();

	///////////////////////////////////////////////////////////////////////////////////

	void Cross(const ChVector2& _Vec1, const ChVector2& _Vec2);

};

using ChVec2 = ChVector2;

///////////////////////////////////////////////////////////////////////////////////

struct ChQuaternion : public ChMath::ChQuaternionBase
{

	operator const D3DXQUATERNION() const;
	operator const D3DXQUATERNION* () const;

	operator const DirectX::XMFLOAT4() const;
	operator const DirectX::XMFLOAT4* () const;

	ChQuaternion& operator=(const D3DXVECTOR3&);
	ChQuaternion& operator=(const DirectX::XMFLOAT3&);

	ChQuaternion& operator=(const D3DXQUATERNION&);
	ChQuaternion& operator=(const DirectX::XMFLOAT4&);

	ChQuaternion& operator=(const D3DXMATRIX&);
	ChQuaternion& operator=(const DirectX::XMFLOAT4X4&);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChQuaternion()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	inline ChQuaternion(const float _Num)
	{
		x = _Num;
		y = _Num;
		z = _Num;
	}

	inline ChQuaternion(
		const float _x, const float _y, const float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	inline ChQuaternion(const ChQuaternion& _Qua) { *this = _Qua; }

	inline ChQuaternion(const D3DXVECTOR3& _Vec) { *this = _Vec; }
	inline ChQuaternion(const DirectX::XMFLOAT3& _Vec) { *this = _Vec; }

	inline ChQuaternion(const D3DXQUATERNION& _Qua) { *this = _Qua; }
	inline ChQuaternion(const DirectX::XMFLOAT4& _Qua) { *this = _Qua; }

	inline ChQuaternion(const D3DXMATRIX& _Mat) { *this = _Mat; }
	inline ChQuaternion(const DirectX::XMFLOAT4X4& _Mat) { *this = _Mat; }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _CutChar = ","
		, const std::string& _EndChar = ";");

	void Deserialize(
		const std::string& _Str
		, const size_t _FPos = 0,
		const std::string& _CutChar = ","
		, const std::string& _EndChar = ";"
		, const unsigned int _Digit = 6);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	ChVec3 GetEulerAngleForVec3() const;

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotYPR(const ChVec3& _Vec)
	{
		RotYPR(_Vec.x, _Vec.y, _Vec.z);
	}

	void RotYPR(
		const float _x, const float _y, const float _z);

};

using ChQua = ChQuaternion;

struct ChLMatrix;
struct ChRMatrix;

//LeftHandAxisMatrix//
struct ChLMatrix : public ChMath::ChBaseHMatrix4x4<float>
{
	///////////////////////////////////////////////////////////////////////////////////
	//Operator//

	ChLMatrix& operator =(const ChLMatrix _Mat);

	ChLMatrix& operator *= (const ChLMatrix _Mat);
	ChLMatrix const operator * (const ChLMatrix _Mat)const;

	ChLMatrix& operator += (const ChLMatrix _Mat);
	ChLMatrix const operator + (const ChLMatrix _Mat)const;

	ChLMatrix& operator -= (const ChLMatrix _Mat);
	ChLMatrix const operator - (const ChLMatrix _Mat)const;

	operator const D3DXMATRIX() const;
	operator const D3DXMATRIX* () const;

	operator const DirectX::XMFLOAT4X4() const;
	operator const DirectX::XMFLOAT4X4* () const;

	ChLMatrix& operator=(const D3DXVECTOR3&);
	ChLMatrix& operator=(const DirectX::XMFLOAT3&);

	ChLMatrix& operator=(const D3DXQUATERNION&);
	ChLMatrix& operator=(const DirectX::XMFLOAT4&);

	ChLMatrix& operator=(const D3DXMATRIX&);
	ChLMatrix& operator=(const DirectX::XMFLOAT4X4&);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChLMatrix()
	{
		Identity();
	}

	inline ChLMatrix(const ChLMatrix& _Mat) { m.Set(_Mat.m); }

	inline ChLMatrix(const D3DXVECTOR3& _Vec) { *this = _Vec; }
	inline ChLMatrix(const DirectX::XMFLOAT3& _Vec) { *this = _Vec; }

	inline ChLMatrix(const D3DXQUATERNION& _Qua) { *this = _Qua; }
	inline ChLMatrix(const DirectX::XMFLOAT4& _Qua) { *this = _Qua; }

	inline ChLMatrix(const D3DXMATRIX& _Mat) { *this = _Mat; }
	inline ChLMatrix(const DirectX::XMFLOAT4X4& _Mat) { *this = _Mat; }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _CutChar = ","
		, const std::string& _EndChar = ";");

	std::string SerializeUpper(
		const std::string& _CutChar = ","
		, const std::string& _EndChar = ";"
		, const std::string& _CutTo4Char = "\n");

	void Deserialize(
		const std::string& _Str
		, const size_t _FPos = 0
		, const std::string& _CutChar = ","
		, const std::string& _EndChar = ";"
		, const unsigned int _Digit = 6);


	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	void SetPosition(const ChVec3& _Vec);

	void SetPosition(const float _x, const float _y, const float _z);

	void SetRotation(const ChVec3& _Vec);

	void SetRotation(const float _x, const float _y, const float _z);

	void SetRotationXAxis(const float _x);

	void SetRotationYAxis(const float _y);

	void SetRotationZAxis(const float _z);

	void SetScalling(const ChVec3& _Vec);

	void SetScalling(const float _x, const float _y, const float _z);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	ChVec3 GetPosition()const;

	ChVec3 GetRotation()const;

	ChVec3 GetScalling()const;

	ChMath::MatrixBase<float,3,3> GetRotMatrix()const;

	///////////////////////////////////////////////////////////////////////////////////

	void LookAt(const ChVec3& _Dir, const ChVec3& _Up = ChVec3(0.0f,1.0f,0.0f));

	///////////////////////////////////////////////////////////////////////////////////

	ChVec4 Transform(const ChVec4 _Base)const;

	ChVec4 TransformCoord(const ChVec4 _Base)const;

	///////////////////////////////////////////////////////////////////////////////////

	void Identity()
	{

		for (unsigned char i = 0; i < 4; i++)
		{
			for (unsigned char j = 0; j < 4; j++)
			{
				m[i][j] = (i != j ? 0.0f : 1.0f);
			}
		}

	}

	///////////////////////////////////////////////////////////////////////////////////

	void Inverse()
	{
	/*
		ChLMatrix TmpMat = *this;
		ChLMatrix Addl;
	
		float Tmp[24];
	
		unsigned char Count = 0;
	*/
		//for (unsigned char i = 0; i < 4; i++)
		//{
		//	for (unsigned char j = 0; j < 4; j++)
		//	{
		//		for (unsigned char k = 0; k < 4; k++)
		//		{
		//			for (unsigned char l = 0; l < 4; l++)
		//			{
	
		//				if (j != i && j != k && i != k && j != l && i != l && k != l)
		//				{
		//					Tmp[Count] = m[0][i] * m[1][j] * m[2][k] * m[3][l];
	
		//					Count++;
		//				}
		//				
	
	
	
		//			}
		//		}
		//	}
		//}
	/*
		for (unsigned char i = 0; i < 4; i++)
		{
			for (unsigned char j = 0; j < 3; j++)
			{
				for (unsigned char k = 0; k < 2; k++)
				{
					Tmp[Count] = m[0][j] *
						m[1][j] *
						m[2][k] *
						m[3][0];
	
					Count++;
				}
			}
		}
	
		float Sum = Tmp[0];
		ChStd::Bool Flg = true;
	
		for (unsigned char i = 0; i < 23; i++)
		{
			Sum = (Flg) ? Sum - Tmp[i + 1] : Sum + Tmp[i + 1];
	
			Flg = (i + 1 % 2 == 0) ? -Flg : Flg;
	
		}
	
		if (Sum == 0.0f)return;
	*/
	}

	///////////////////////////////////////////////////////////////////////////////////

	ChRMatrix ConvertAxis();

};

//RightHandAxisMatrix//
struct ChRMatrix : public ChMath::ChBaseVMatrix4x4<float>
{
	ChRMatrix& operator =(const ChRMatrix& _Mat);

	//ChRMatrix& operator=(const D3DXVECTOR3&);
	//ChRMatrix& operator=(const DirectX::XMFLOAT3&);

	//ChRMatrix& operator=(const D3DXQUATERNION&);
	//ChRMatrix& operator=(const DirectX::XMFLOAT4&);

	//ChRMatrix& operator=(const D3DXMATRIX&);
	//ChRMatrix& operator=(const DirectX::XMFLOAT4X4&);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChRMatrix()
	{
		for (unsigned char i = 0; i < 4; i++)
		{
			for (unsigned char j = 0; j < 4; j++)
			{
				m[i][j] = i!=j ? 0.0f : 1.0f;
			}
		}
	}

	inline ChRMatrix(const ChRMatrix& _Mat) { *this = _Mat; }

	//inline ChRMatrix(const D3DXVECTOR3& _Vec) { *this = _Vec; }
	//inline ChRMatrix(const DirectX::XMFLOAT3& _Vec) { *this = _Vec; }

	//inline ChRMatrix(const D3DXQUATERNION& _Qua) { *this = _Qua; }
	//inline ChRMatrix(const DirectX::XMFLOAT4& _Qua) { *this = _Qua; }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _CutChar = ","
		, const std::string& _EndChar = ";");

	std::string SerializeUpper(
		const std::string& _CutChar = ","
		, const std::string& _EndChar = ";"
		, const std::string& _CutTo4Char = "\n");

	void Deserialize(
		const std::string& _Str
		, const size_t _FPos = 0
		, const std::string& _CutChar = ","
		, const std::string& _EndChar = ";"
		, const unsigned int _Digit = 6);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	ChVec3 GetPosition();

	ChVec3 GetRotation();

	ChVec3 GetScalling();


	ChLMatrix ConvertAxis();

};

using ChRMat = ChRMatrix;
using ChLMat = ChLMatrix;

struct ChUIMatrix
{
	///////////////////////////////////////////////////////////////////////////////////
	//Operator//

	ChUIMatrix& operator =(const ChUIMatrix _Mat);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChUIMatrix()
	{
		m.Set(0UL);
	}

	inline ChUIMatrix(const ChUIMatrix& _Mat) { m.Set(_Mat.m); }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _CutChar = ","
		, const std::string& _EndChar = ";");

	std::string SerializeUpper(
		const std::string& _CutChar = ","
		, const std::string& _EndChar = ";"
		, const std::string& _CutTo4Char = "\n");

	void Deserialize(
		const std::string& _Str
		, const size_t _FPos = 0
		, const std::string& _CutChar = ","
		, const std::string& _EndChar = ";");

	///////////////////////////////////////////////////////////////////////////////////

	ChMath::MatrixBase<unsigned long, 4, 4> m;

};

using ChUIMat = ChUIMatrix;

namespace ChMath
{
	static const float Pi = 3.1415f;

	static inline float ToDegree(const float _Radian) { return (_Radian * 180.0f / Pi); }

	static inline float ToRadian(const float _Degree) { return (_Degree * Pi / 180.0f); }

	static inline ChStd::Bool IsPSign(const int _Val) { return _Val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const char _Val) { return _Val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const short _Val) { return _Val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const long _Val) { return _Val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const float _Val) { return _Val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const double _Val) { return _Val >= 0.0f ? true : false; }

	ChVector3 GetFaceNormal(
		const ChVec3& _Pos1, const ChVec3& _Pos2, const ChVec3& _Pos3);
}


#endif
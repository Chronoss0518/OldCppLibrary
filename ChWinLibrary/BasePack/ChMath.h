#ifndef Ch_CPP_Math_h
#define Ch_CPP_Math_h

#include <float.h>
#include <cmath>



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
			T Val[4]{ 0, 0, 0, 0 };
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
			T Val[3]{ 0, 0, 0 };
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
			T Val[2]{ 0, 0 };
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
	struct ChBaseMatrix2x2
	{
		union
		{
			struct
			{

				T l_11, l_12;
				T l_21, l_22;

			};
			struct
			{

				T r_11, r_21;
				T r_12, r_22;

			};
			T m[2][2];
		};

		/*
		T& GetValue(const unsigned long _Column, const unsigned long _Row) { return m[_Column][_Row]; };
		T GetCValue(const unsigned long _Column, const unsigned long _Row)const { return m[_Column][_Row]; };

		unsigned long GetColumn()const override { return 2; }
		unsigned long GetRow()const override { return 2; };

		*/
	};

	template<typename T>
	struct ChBaseMatrix3x3
	{


		union
		{
			struct
			{

				T l_11, l_12, l_13;
				T l_21, l_22, l_23;
				T l_31, l_32, l_33;

			};
			struct
			{

				T r_11, r_21, r_31;
				T r_12, r_22, r_32;
				T r_13, r_23, r_33;

			};
			T m[3][3];
		};

		/*
		T& GetValue(const unsigned long _Column, const unsigned long _Row) { return m[_Column][_Row]; };
		T GetCValue(const unsigned long _Column, const unsigned long _Row)const { return m[_Column][_Row]; };

		unsigned long GetColumn()const override { return 3; }
		unsigned long GetRow()const override { return 3; };

		*/

	};

	template<typename T>
	struct ChBaseMatrix4x4
	{
		union
		{
			struct
			{

				T l_11, l_12, l_13, l_14;
				T l_21, l_22, l_23, l_24;
				T l_31, l_32, l_33, l_34;
				T l_41, l_42, l_43, l_44;

			};
			struct
			{

				T r_11, r_21, r_31, r_41;
				T r_12, r_22, r_32, r_42;
				T r_13, r_23, r_33, r_43;
				T r_14, r_24, r_34, r_44;

			};
			T m[4][4];
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

	ChVector4& operator-=(const ChVector4& _Vec);
	ChVector4 operator-(const ChVector4& _Vec) const;
	ChVector4& operator+=(const ChVector4& _Vec);
	ChVector4 operator+(const ChVector4& _Vec) const;
	ChVector4& operator*=(const ChVector4& _Vec);
	ChVector4 operator*(const ChVector4& _Vec) const;

	bool operator==(const ChVector4& _Vec)const
	{
		return (x == _Vec.x && y == _Vec.y && z == _Vec.z && w == _Vec.w);
	}

	bool operator!=(const ChVector4& _Vec)const
	{
		return (x != _Vec.x || y != _Vec.y || z != _Vec.z || w != _Vec.w);
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
		*this = 0.0f;
		w = 1.0f;
	}

	inline ChVector4(const float _Num)
	{
		*this = _Num;

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
		x = x < 0.0f ? x * -1.0f : x;
		y = y < 0.0f ? y * -1.0f : y;
		z = z < 0.0f ? z * -1.0f : z;
		w = w < 0.0f ? w * -1.0f : w;
	}

	inline void Abs(const ChVector4& _Vec)
	{
		x = _Vec.x < 0.0f ? _Vec.x * -1.0f : _Vec.x;
		y = _Vec.y < 0.0f ? _Vec.y * -1.0f : _Vec.y;
		z = _Vec.z < 0.0f ? _Vec.z * -1.0f : _Vec.z;
		w = _Vec.w < 0.0f ? _Vec.w * -1.0f : _Vec.w;
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

	ChVector3& operator-=(const ChVector3& _Vec);
	ChVector3 operator-(const ChVector3& _Vec) const;
	ChVector3& operator+=(const ChVector3& _Vec);
	ChVector3 operator+(const ChVector3& _Vec) const;
	ChVector3& operator*=(const ChVector3& _Vec);
	ChVector3 operator*(const ChVector3& _Vec) const;

	bool operator==(const ChVector3& _Vec)const
	{
		return (x == _Vec.x && y == _Vec.y && z == _Vec.z);
	}

	bool operator!=(const ChVector3& _Vec)const
	{
		return (x != _Vec.x || y != _Vec.y || z != _Vec.z);
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
		*this = 0.0f;
	}

	inline ChVector3(const float _Num)
	{
		*this = _Num;
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
		x = x < 0.0f ? x * -1.0f : x;
		y = y < 0.0f ? y * -1.0f : y;
		z = z < 0.0f ? z * -1.0f : z;
	}

	inline void Abs(const ChVector3& _Vec)
	{

		x = _Vec.x < 0.0f ? _Vec.x * -1.0f : _Vec.x;
		y = _Vec.y < 0.0f ? _Vec.y * -1.0f : _Vec.y;
		z = _Vec.z < 0.0f ? _Vec.z * -1.0f : _Vec.z;
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

	ChVector2& operator-=(const ChVector2& _Vec);
	ChVector2 operator-(const ChVector2& _Vec) const;
	ChVector2& operator+=(const ChVector2& _Vec);
	ChVector2 operator+(const ChVector2& _Vec) const;
	ChVector2& operator*=(const ChVector2& _Vec);
	ChVector2 operator*(const ChVector2& _Vec) const;

	bool operator==(const ChVector2& _Vec)const
	{
		return (x == _Vec.x && y == _Vec.y);
	}

	bool operator!=(const ChVector2& _Vec)const
	{
		return (x != _Vec.x || y != _Vec.y);
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
		*this = 0.0f;
	}

	inline ChVector2(const float _Num)
	{
		*this = _Num;
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
		x = x < 0.0f ? x * -1.0f : x;
		y = y < 0.0f ? y * -1.0f : y;
	}

	inline void Abs(const ChVector2& _Vec)
	{

		x = _Vec.x < 0.0f ? _Vec.x * -1.0f : _Vec.x;
		y = _Vec.y < 0.0f ? _Vec.y * -1.0f : _Vec.y;
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
struct ChLMatrix : public ChMath::ChBaseMatrix4x4<float>
{

	float& operator[](const int Num);
	float operator[](const int Num)const;

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
		//Identity();
	}

	inline ChLMatrix(const ChLMatrix& _Mat) { *this = _Mat; }

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

	void SetScalling(const ChVec3& _Vec);

	void SetScalling(const float _x, const float _y, const float _z);

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	ChVec3 GetPosition()const;

	ChVec3 GetRotation()const;

	ChVec3 GetScalling()const;

	ChMath::MatrixBase<float,3,3> GetRotMatrix()const;

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
	
		ChLMatrix TmpMat = *this;
		ChLMatrix Addl;
	
		float Tmp[24];
	
		unsigned char Count = 0;
	
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
	
	}

	///////////////////////////////////////////////////////////////////////////////////

	ChRMatrix ConvertAxis();

};

//RightHandAxisMatrix//
struct ChRMatrix : public ChMath::ChBaseMatrix4x4<float>
{
	float& operator[](const int Num);

	float operator[](const int Num)const;

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

struct ChUIMatrix : public ChMath::ChBaseMatrix4x4<unsigned long>
{

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChUIMatrix()
	{
		for (unsigned char i = 0; i < 4; i++)
		{
			for (unsigned char j = 0; j < 4; j++)
			{
				m[i][j] = 0;
			}
		}

	}

	inline ChUIMatrix(const ChUIMatrix& _Mat) { *this = _Mat; }

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

};

using ChUIMat = ChUIMatrix;

namespace ChMath
{

	static inline std::string ConvertNum10to64(unsigned long _Num)
	{  
		return "";
	}

	float Round(const float& _Val, const unsigned int _Digit);
	double Round(const double& _Val, const unsigned int _Digit);


	//â~é¸ó¶//
	static const float Pi = 3.1415f;

	class Degree;
	class Radian;

	//ìxêîñ@Ç≈Ç†ÇÁÇÌÇ≥ÇÍÇΩäpìxÇéÊÇËÇ‹Ç∆ÇﬂÇÈÉNÉâÉX//
	class Degree
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//operator
		///////////////////////////////////////////////////////////////////////////////////

		inline Degree& operator=(const Degree _Num)
		{
			Val = _Num;
			return *this;
		}

		Degree& operator=(const float _Num);
		Degree& operator=(const Radian _Num);

		Degree& operator+=(const float _Num);
		Degree operator+(const float _Num) const;

		Degree& operator-=(const float _Num);
		Degree operator-(const float _Num) const;

		Degree& operator*=(const float _Num);
		Degree operator*(const float _Num) const;

		Degree& operator/=(const float _Num);
		Degree operator/(const float _Num) const;

		operator float() const;

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer
		///////////////////////////////////////////////////////////////////////////////////

		Degree();

		Degree(const float _Val);

		Degree(const Degree& _Val);

		Degree(const Radian& _Val);

		///////////////////////////////////////////////////////////////////////////////////

	private:
		void Math();

		float Val;
	};

	//å ìxñ@(â~é¸ó¶)Ç≈Ç†ÇÁÇÌÇ≥ÇÍÇΩäpìxÇéÊÇËÇ‹Ç∆ÇﬂÇÈÉNÉâÉX//
	class Radian
	{

	public:
		///////////////////////////////////////////////////////////////////////////////////
		//operator
		///////////////////////////////////////////////////////////////////////////////////

		inline Radian operator=(const Radian _Num)
		{
			Val = _Num;
			return *this;
		}

		Radian& operator=(const float _Num);
		Radian& operator=(const Degree _Num);

		Radian& operator+=(const float _Num);
		Radian operator+(const float _Num) const;

		Radian& operator-=(const float _Num);
		Radian operator-(const float _Num) const;

		Radian& operator*=(const float _Num);
		Radian operator*(const float _Num) const;

		Radian& operator/=(const float _Num);
		Radian operator/(const float _Num) const;

		operator float() const;

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer
		///////////////////////////////////////////////////////////////////////////////////

		Radian();

		Radian(const float _Val);

		Radian(const Radian& _Val);

		Radian(const Degree& _Val);

		///////////////////////////////////////////////////////////////////////////////////

	private:
		void Math();

		float Val;
	};

	//éOäpñ Çç\ê¨Ç∑ÇÈ3í∏ì_ÇÇ‹Ç∆ÇﬂÇΩÇ‡ÇÃ//
	typedef struct TriVertex
	{
		ChVec3 Ver1, Ver2, Ver3;
		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		inline TriVertex() {}

		inline TriVertex(
			const ChVec3& _1, const ChVec3& _2, const ChVec3& _3)
		{
			Ver1 = _1;
			Ver2 = _2;
			Ver3 = _3;
		}

	} TriVer;

	//3í∏ì_ÇÊÇËñ@ê¸ÇçÏê¨Ç∑ÇÈ//
	//ñ@ê¸ÇÕéOí∏ì_ÇÃäOêœ(åç∑Ç∑ÇÈÉxÉNÉgÉã)ÇéZèoÇµÇƒçÏê¨Ç≥ÇÍÇÈ//
	ChVector3 GetFaceNormal(const TriVertex& _PlEq);

	ChVector3 GetFaceNormal(
		const ChVec3& _Pos1, const ChVec3& _Pos2, const ChVec3& _Pos3);

	//RadianäpÇ©ÇÁDegreeäpÇ÷//
	static inline float ToDegree(const float _Radian) { return (_Radian * 180.0f / Pi); }

	//DegreeäpÇ©ÇÁRadianäpÇ÷//
	static inline float ToRadian(const float _Degree) { return (_Degree * Pi / 180.0f); }

	//ê≥ÇÃïÑçÜÇ©Ç«Ç§Ç©ÇämîFÇ∑ÇÈ//
	static inline ChStd::Bool IsPSign(const int _Val) { return _Val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const char _Val) { return _Val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const short _Val) { return _Val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const long _Val) { return _Val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const float _Val) { return _Val >= 0.0f ? true : false; }
	static inline ChStd::Bool IsPSign(const double _Val) { return _Val >= 0.0f ? true : false; }

} // namespace ChMath

#endif
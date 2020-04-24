#ifndef Ch_CPP_Math_h
#define Ch_CPP_Math_h

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
}

struct ChVector4;
struct ChVector3;
struct ChVector2;
struct ChQuaternion;
struct ChMatrix;

 typedef struct ChVector4
{
	union
	{
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			float r, g, b, a;
		};
		float Val[4];
	};

	ChVector4& operator *= (const float& _Num);
	ChVector4 operator * (const float& _Num)const;
	ChVector4& operator /= (const float& _Num);
	ChVector4 operator / (const float& _Num)const;
	ChVector4& operator = (const float& _Num);

	ChVector4& operator = (const ChVector3& _Vec);
	ChVector4& operator = (const ChVector2& _Vec);

	ChVector4& operator -= (const ChVector4& _Vec);
	ChVector4 operator - (const ChVector4& _Vec)const;
	ChVector4& operator += (const ChVector4& _Vec);
	ChVector4 operator + (const ChVector4& _Vec)const;
	ChVector4& operator *= (const ChVector4& _Vec);
	ChVector4 operator * (const ChVector4& _Vec)const;

	operator const D3DXVECTOR4()const;
	operator const D3DXVECTOR4*()const;

	ChVector4& operator= (const D3DXVECTOR4&);

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

		if (w < -1.0f)w = -1.0f;
		if (w > 1.0f)w = 1.0f;
	}

	inline ChVector4(
		const float _x
		, const float _y
		, const float _z
		, const float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
		if (w < -1.0f)w = -1.0f;
		if (w > 1.0f)w = 1.0f;
	}

	inline ChVector4(const ChVector4& _Vec) { *this = _Vec; }

	inline ChVector4(const D3DXVECTOR4&_Vec) { *this = _Vec; }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _CutChar = ","
		, const std::string& _EndChar = ";");

	void Deserialize(
		const std::string& _Str
		, const size_t _FPos = 0
		, const std::string& _CutChar = ","
		, const std::string& _EndChar = ";");

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	static ChVector4 GetCross(
		const ChVector4& _Vec1
		, const ChVector4& _Vec2);

	static float GetCos(
		const ChVector4& _Vec1
		, const ChVector4& _Vec2);

	static float GetRadian(
		const ChVector4& _Vec1
		, const ChVector4& _Vec2);

	static float GetDot(
		const ChVector4& _Vec1
		, const ChVector4& _Vec2);

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	static ChVector4 GetCorrection(
		const ChVector4& _Start
		, const ChVector4& _End
		, const float _Now);

	static float GetLen(
		const ChVector4& _Vec1
		, const ChVector4& _Vec2);

	///////////////////////////////////////////////////////////////////////////////////

	inline float Len()const
	{
		return GetLen(*this, ChVec4());
	}

	///////////////////////////////////////////////////////////////////////////////////

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	inline void Correction(
		const ChVector4& _Start
		, const ChVector4& _End
		, const float _Now)
	{
		*this = GetCorrection(_Start, _End, _Now);
	}

	///////////////////////////////////////////////////////////////////////////////////

	void Normalize();

	///////////////////////////////////////////////////////////////////////////////////

	void Cross(const ChVector4& _Vec1, const ChVector4& _Vec2);

}ChVec4;

///////////////////////////////////////////////////////////////////////////////////

 typedef struct ChVector3
{
	union
	{
		struct
		{
			float x, y, z;
		};
		struct
		{
			float r, g, b;
		};
		float Val[3];
	};

	ChVector3& operator *= (const float& _Num);
	ChVector3 operator * (const float& _Num)const;
	ChVector3& operator /= (const float& _Num);
	ChVector3 operator / (const float& _Num)const;
	ChVector3& operator = (const float& _Num);

	ChVector3& operator = (const ChVector4& _Vec);
	ChVector3& operator = (const ChVector2& _Vec);

	ChVector3& operator -= (const ChVector3& _Vec);
	ChVector3 operator - (const ChVector3& _Vec)const;
	ChVector3& operator += (const ChVector3& _Vec);
	ChVector3 operator + (const ChVector3& _Vec)const;
	ChVector3& operator *= (const ChVector3& _Vec);
	ChVector3 operator * (const ChVector3& _Vec)const;

	operator const D3DXVECTOR3()const;
	operator const D3DXVECTOR3*()const;

	operator const DirectX::XMFLOAT3()const;
	operator const DirectX::XMFLOAT3*()const;

	ChVector3& operator= (const D3DXVECTOR3&);
	ChVector3& operator= (const DirectX::XMFLOAT3&);

	ChVector3& operator= (const D3DXQUATERNION&);
	ChVector3& operator= (const DirectX::XMFLOAT4&);

	ChVector3& operator= (const D3DXMATRIX&);
	ChVector3& operator= (const DirectX::XMFLOAT4X4&);

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
		const float _x
		, const float _y
		, const float _z)
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
		, const std::string& _EndChar = ";");

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	static ChVector3 GetCross(
		const ChVector3& _Vec1
		, const ChVector3& _Vec2);

	static float GetCos(
		const ChVector3& _Vec1
		, const ChVector3& _Vec2);

	static float GetRadian(
		const ChVector3& _Vec1
		, const ChVector3& _Vec2);

	static float GetDot(
		const ChVector3& _Vec1
		, const ChVector3& _Vec2);

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	static ChVector3 GetCorrection(
		const ChVector3& _Start
		, const ChVector3& _End
		, const float _Now);

	static float GetLen(
		const ChVector3& _Vec1
		, const ChVector3& _Vec2);

	///////////////////////////////////////////////////////////////////////////////////

	inline float Len()const
	{
		return GetLen(*this,ChVec3());
	}

	///////////////////////////////////////////////////////////////////////////////////

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	inline void Correction(
		const ChVector3& _Start
		, const ChVector3& _End
		, const float _Now)
	{
		*this = GetCorrection(_Start, _End, _Now);
	}

	///////////////////////////////////////////////////////////////////////////////////

	void Normalize();

	///////////////////////////////////////////////////////////////////////////////////

	void Cross(const ChVector3& _Vec1, const ChVector3& _Vec2);

}ChVec3;

///////////////////////////////////////////////////////////////////////////////////

 typedef struct ChVector2
{
	union
	{
		struct
		{
			float x, y;
		};
		float Val[2];
	};

	ChVector2& operator *= (const float& _Num);
	ChVector2 operator * (const float& _Num)const;
	ChVector2& operator /= (const float& _Num);
	ChVector2 operator / (const float& _Num)const;
	ChVector2& operator = (const float& _Num);

	ChVector2& operator = (const ChVector4& _Vec);
	ChVector2& operator = (const ChVector3& _Vec);

	ChVector2& operator -= (const ChVector2& _Vec);
	ChVector2 operator - (const ChVector2& _Vec)const;
	ChVector2& operator += (const ChVector2& _Vec);
	ChVector2 operator + (const ChVector2& _Vec)const;
	ChVector2& operator *= (const ChVector2& _Vec);
	ChVector2 operator * (const ChVector2& _Vec)const;

	operator const D3DXVECTOR2()const;
	operator const D3DXVECTOR2*()const;

	ChVector2& operator= (const D3DXVECTOR2&);

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
		const float _x
		, const float _y)
	{
		x = _x;
		y = _y;
	}

	inline ChVector2(const ChVector2& _Vec) { *this = _Vec; }

	inline ChVector2(const D3DXVECTOR2&_Vec) { *this = _Vec; }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _CutChar = ","
		, const std::string& _EndChar = ";");

	void Deserialize(
		const std::string& _Str
		, const size_t _FPos = 0
		, const std::string& _CutChar = ","
		, const std::string& _EndChar = ";");

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	static ChVector2 GetCross(
		const ChVector2& _Vec1
		, const ChVector2& _Vec2);

	static float GetCos(
		const ChVector2& _Vec1
		, const ChVector2& _Vec2);

	static float GetRadian(
		const ChVector2& _Vec1
		, const ChVector2& _Vec2);

	static float GetDot(
		const ChVector2& _Vec1
		, const ChVector2& _Vec2);

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	static ChVector2 GetCorrection(
		const ChVector2& _Start
		, const ChVector2& _End
		, const float _Now);

	static float GetLen(
		const ChVector2& _Vec1
		, const ChVector2& _Vec2);

	///////////////////////////////////////////////////////////////////////////////////

	inline float Len()const
	{
		return GetLen(*this, ChVec2());
	}

	///////////////////////////////////////////////////////////////////////////////////

	//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
	inline void Correction(
		const ChVector2& _Start
		, const ChVector2& _End
		, const float _Now)
	{
		*this = GetCorrection(_Start, _End, _Now);
	}

	///////////////////////////////////////////////////////////////////////////////////

	void Normalize();

	///////////////////////////////////////////////////////////////////////////////////

	void Cross(const ChVector2& _Vec1, const ChVector2& _Vec2);

}ChVec2;

///////////////////////////////////////////////////////////////////////////////////

 typedef struct ChQuaternion
{
	union
	{
		struct{
			float x, y, z, w;
		};
		float Val[4];
	};

	operator const D3DXQUATERNION()const;
	operator const D3DXQUATERNION*()const;

	operator const DirectX::XMFLOAT4()const;
	operator const DirectX::XMFLOAT4*()const;

	ChQuaternion& operator= (const D3DXVECTOR3&);
	ChQuaternion& operator= (const DirectX::XMFLOAT3&);

	ChQuaternion& operator= (const D3DXQUATERNION&);
	ChQuaternion& operator= (const DirectX::XMFLOAT4&);

	ChQuaternion& operator= (const D3DXMATRIX&);
	ChQuaternion& operator= (const DirectX::XMFLOAT4X4&);

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
		const float _x
		, const float _y
		, const float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	inline ChQuaternion(const ChQuaternion& _Vec) { *this = _Vec; }

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
		, const std::string& _EndChar = ";");

	///////////////////////////////////////////////////////////////////////////////////
	//GetFunction//

	ChVec3 GetEulerAngleForVec3()const;

	///////////////////////////////////////////////////////////////////////////////////

	inline void RotYPR(const ChVec3& _Vec)
	{
		RotYPR(_Vec.x, _Vec.y, _Vec.z);
	}

	void RotYPR(
		const float _x
		, const float _y
		, const float _z);

}ChQua;

 typedef struct ChMatrix
{
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};

		float m[4][4];
	};

	operator const D3DXMATRIX() const;
	operator const D3DXMATRIX*() const;

	operator const DirectX::XMFLOAT4X4() const;
	operator const DirectX::XMFLOAT4X4*() const;

	ChMatrix& operator= (const D3DXVECTOR3&);
	ChMatrix& operator= (const DirectX::XMFLOAT3&);

	ChMatrix& operator= (const D3DXQUATERNION&);
	ChMatrix& operator= (const DirectX::XMFLOAT4&);

	ChMatrix& operator= (const D3DXMATRIX&);
	ChMatrix& operator= (const DirectX::XMFLOAT4X4&);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	inline ChMatrix()
	{
		for (unsigned char i = 0; i < 4; i++)
		{
			for(unsigned char j = 0; j < 4; j++)
			{
				m[i][j] = 0;
			}
		}
	}

	inline ChMatrix(const ChMatrix& _Mat) { *this = _Mat; }

	inline ChMatrix(const D3DXVECTOR3& _Vec) { *this = _Vec; }
	inline ChMatrix(const DirectX::XMFLOAT3& _Vec) { *this = _Vec; }

	inline ChMatrix(const D3DXQUATERNION& _Qua) { *this = _Qua; }
	inline ChMatrix(const DirectX::XMFLOAT4& _Qua) { *this = _Qua; }

	inline ChMatrix(const D3DXMATRIX& _Mat) { *this = _Mat; }
	inline ChMatrix(const DirectX::XMFLOAT4X4& _Mat) { *this = _Mat; }

	///////////////////////////////////////////////////////////////////////////////////
	//SerializeDeserialize//

	std::string Serialize(
		const std::string& _CutChar = ","
		, const std::string& _EndChar = ";");

	void Deserialize(
		const std::string& _Str
		, const size_t _FPos = 0
		, const std::string& _CutChar = ","
		, const std::string& _EndChar = ";");

}ChMat;


namespace ChMath
{
	//â~é¸ó¶//
	static const float Pi = 3.1415f;

	class Degree;
	class Radian;

	//ìxêîñ@Ç≈Ç†ÇÁÇÌÇ≥ÇÍÇΩäpìxÇéÊÇËÇ‹Ç∆ÇﬂÇÈÉNÉâÉX//
	 class Degree
	{
	public:

		inline Degree& operator=(const Degree _Num)
		{
			Val = _Num;
			return *this;
		}

		Degree& operator=(const float _Num);
		Degree& operator=(const Radian _Num);

		Degree& operator+=(const float _Num);
		Degree operator+(const float _Num)const;

		Degree& operator-=(const float _Num);
		Degree operator-(const float _Num)const;

		Degree& operator*=(const float _Num);
		Degree operator*(const float _Num)const;

		Degree& operator/=(const float _Num);
		Degree operator/(const float _Num)const;

		operator float()const;

		inline Degree()
		{
			Val = 0.0f;
		}

		inline Degree(const float _Val)
		{
			*this = _Val;
		}

		inline Degree(const Degree& _Val)
		{
			Val = _Val;
		}

		inline Degree(const Radian& _Val)
		{
			*this = _Val;
		}

	private:

		void Math();

		float Val;

	};

	//å ìxñ@(â~é¸ó¶)Ç≈Ç†ÇÁÇÌÇ≥ÇÍÇΩäpìxÇéÊÇËÇ‹Ç∆ÇﬂÇÈÉNÉâÉX//
	 class Radian
	{

	public:

		inline Radian operator=(const Radian _Num)
		{
			Val = _Num;
			return *this;
		}

		Radian& operator=(const float _Num);
		Radian& operator=(const Degree _Num);

		Radian& operator+=(const float _Num);
		Radian operator+(const float _Num)const;

		Radian& operator-=(const float _Num);
		Radian operator-(const float _Num)const;

		Radian& operator*=(const float _Num);
		Radian operator*(const float _Num)const;

		Radian& operator/=(const float _Num);
		Radian operator/(const float _Num)const;

		operator float()const;

		inline Radian()
		{
			Val = 0.0f;
		}

		inline Radian(const float _Val)
		{
			*this = _Val;
		}

		inline Radian(const Radian& _Val)
		{
			Val = _Val;
		}

		inline Radian(const Degree& _Val)
		{
			*this = _Val;
		}

	private:

		void Math();

		float Val;

	};

	//éOäpñ Çç\ê¨Ç∑ÇÈ3í∏ì_ÇÇ‹Ç∆ÇﬂÇΩÇ‡ÇÃ//
	typedef struct TriVertex
	{
		union
		{
			struct { ChVec3 _1, _2, _3; };
			ChVec3 Ver[3];
		};

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		inline TriVertex() {}

		inline TriVertex(
			const ChVec3& _1
			, const ChVec3& _2
			, const ChVec3& _3)
		{
			Ver[0] = _1;
			Ver[1] = _2;
			Ver[2] = _3;

		}

	}TriVer;

	//3í∏ì_ÇÊÇËñ@ê¸ÇçÏê¨Ç∑ÇÈ//
	//ñ@ê¸ÇÕéOí∏ì_ÇÃäOêœ(åç∑Ç∑ÇÈÉxÉNÉgÉã)ÇéZèoÇµÇƒçÏê¨Ç≥ÇÍÇÈ//
	ChVector3 GetFaceNormal(const TriVertex& _PlEq);

	 ChVector3 GetFaceNormal(
		const ChVec3& _Pos1
		, const ChVec3& _Pos2
		, const ChVec3& _Pos3);

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

}

#endif
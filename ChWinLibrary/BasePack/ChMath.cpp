
#include"ChStd.h"
#include"ChMath.h"

///////////////////////////////////////////////////////////////////////////////////
//ChVector4 Method//
///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator*= (const float& _Num)
{

	x *= _Num;
	y *= _Num;
	z *= _Num;
	w *= _Num;

	if (w < -1.0f)w = -1.0f;
	if (w > 1.0f)w = 1.0f;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4 ChVec4::operator * (const float& _Num)const
{

	ChVector4 TmpVec = *this;

	TmpVec *= _Num;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator/= (const float& _Num)
{
	x /= _Num;
	y /= _Num;
	z /= _Num;
	w /= _Num;

	if (w < -1.0f)w = -1.0f;
	if (w > 1.0f)w = 1.0f;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4 ChVec4::operator / (const float& _Num)const
{

	ChVector4 TmpVec = *this;

	TmpVec /= _Num;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator= (const float& _Num)
{

	x = _Num;
	y = _Num;
	z = _Num;
	w = _Num;

	if (w < -1.0f)w = -1.0f;
	if (w > 1.0f)w = 1.0f;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator = (const ChVector3& _Vec)
{
	x = _Vec.x;
	y = _Vec.y;
	z = _Vec.z;
	w = 1.0f;
	return *this;

}

///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator = (const ChVector2& _Vec)
{

	x = _Vec.x;
	y = _Vec.y;
	z = 0.0f;
	w = 1.0f;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator *= (const ChVector4& _Vec)
{

	x *= _Vec.x;
	y *= _Vec.y;
	z *= _Vec.z;
	w *= _Vec.w;

	if (w < -1.0f)w = -1.0f;
	if (w > 1.0f)w = 1.0f;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4 ChVec4::operator * (const ChVector4& _Vec)const
{
	ChVector4 TmpVec = *this;

	TmpVec *= _Vec;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator -= (const ChVector4& _Vec)
{
	x -= _Vec.x;
	y -= _Vec.y;
	z -= _Vec.z;
	w -= _Vec.w;

	if (w < -1.0f)w = -1.0f;
	if (w > 1.0f)w = 1.0f;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4 ChVec4::operator - (const ChVector4& _Vec)const
{
	ChVector4 TmpVec = *this;

	TmpVec -= _Vec;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator += (const ChVector4& _Vec)
{
	x += _Vec.x;
	y += _Vec.y;
	z += _Vec.z;
	w += _Vec.w;

	if (w < -1.0f)w = -1.0f;
	if (w > 1.0f)w = 1.0f;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4 ChVec4::operator + (const ChVector4& _Vec)const
{
	ChVector4 TmpVec = *this;

	TmpVec += _Vec;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

std::string ChVec4::Serialize(
	const std::string& _CutChar
	, const std::string& _EndChar)
{
	std::string Tmp = "";
	for (unsigned char i = 0; i < 4; i++)
	{
		if (i == 3)break;
		Tmp += std::to_string(Val[i]);
		Tmp += _CutChar;
	}

	Tmp += std::to_string(Val[3]);
	Tmp += _EndChar;

	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec4::Deserialize(
	const std::string& _Str
	, const size_t _FPos
	, const std::string& _CutChar
	, const std::string& _EndChar)
{

	std::string TmpStr = _Str;

	size_t TmpFPos = _FPos;

	size_t Tmp = _FPos;

	size_t EPos = TmpStr.find(_EndChar, Tmp);

	if (EPos == TmpStr.npos)EPos = TmpStr.size();

	for (unsigned char i = 0; i < 4; i++)
	{
		size_t Test = TmpStr.find(_CutChar, Tmp);
		if (Test > EPos)Test = EPos;
		{
			TmpFPos = Test;

			std::string Num = TmpStr.substr(Tmp, TmpFPos - Tmp);

			Val[i] = (float)std::atof(Num.c_str());
			Tmp += Num.length();
			Tmp += 1;

		}

		if (Test >= EPos)return;
	}


}

///////////////////////////////////////////////////////////////////////////////////

ChVector4 ChVec4::GetCross(const ChVector4& _Vec1, const ChVector4& _Vec2)
{
	ChVector4 TmpVec;


	for (unsigned char i = 0; i < 4; i++)
	{
		TmpVec.Val[i] =
			(_Vec1.Val[(i + 1) % 4] * _Vec2.Val[(i + 2) % 4])
			- (_Vec1.Val[(i + 2) % 4] * _Vec2.Val[(i + 1) % 4]);
	}

	TmpVec.Normalize();

	return TmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec4::GetCos(const ChVector4& _Vec1, const ChVector4& _Vec2)
{

	if (_Vec1.Len() <= 0.0f || _Vec2.Len() <= 0.0f)return 0.0f;

	ChVec4 Tmp1 = _Vec1, Tmp2 = _Vec2;

	Tmp1.Normalize();
	Tmp2.Normalize();

	float Cos = 0.0f;

	for (unsigned char i = 0; i < 4; i++)
	{
		Cos += (Tmp1.Val[i] * Tmp2.Val[i]);
	}

	return Cos;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec4::GetRadian(const ChVector4& _Vec1, const ChVector4& _Vec2)
{

	if (_Vec1.Len() <= 0.0f || _Vec2.Len() <= 0.0f)return 0.0f;

	return std::acos(GetCos(_Vec1, _Vec2));

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec4::GetDot(const ChVector4& _Vec1, const ChVector4& _Vec2)
{

	if (_Vec1.Len() <= 0.0f || _Vec2.Len() <= 0.0f)return 0.0f;

	float TmpLen;

	TmpLen = (_Vec1.x *  _Vec2.x)
		+ (_Vec1.y * _Vec2.y)
		+ (_Vec1.z * _Vec2.z)
		+ (_Vec1.w * _Vec2.w);

	return TmpLen;


}

///////////////////////////////////////////////////////////////////////////////////

//•â³‚ðs‚¤(Now‚Í0`1)
ChVector4 ChVec4::GetCorrection(const ChVector4& _Start, const ChVector4& _End, const float _Now)
{
	if (_Now <= 0.0f)return _Start;
	if (_Now >= 1.0f)return _End;
	ChVector4 TmpVec;

	TmpVec = _End - _Start;

	TmpVec = _Start + (TmpVec * _Now);

	return TmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec4::GetLen(
	const ChVector4& _Vec1
	, const ChVector4& _Vec2)
{

	float BaseLen;

	ChVec4 TmpVec = _Vec1 - _Vec2;

	BaseLen =
		std::abs(TmpVec.x)
		+ std::abs(TmpVec.y)
		+ std::abs(TmpVec.z)
		+ std::abs(TmpVec.w);

	return  BaseLen;
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec4::Normalize()
{
	if (Len() == 1.0f)return;

	float Val = Len();

	if (Val <= 0.0f)
	{
		x = 1.0f;
		return;
	}

	*this /= Val;

}

///////////////////////////////////////////////////////////////////////////////////

void ChVec4::Cross(
	const ChVector4& _Vec1
	, const ChVector4& _Vec2)
{
	*this = GetCross(_Vec1, _Vec2);

	Normalize();
}

///////////////////////////////////////////////////////////////////////////////////
//ChVector3 Method//
///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator*= (const float& _Num)
{

	x *= _Num;
	y *= _Num;
	z *= _Num;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChVec3::operator * (const float& _Num)const
{

	ChVector3 TmpVec = *this;

	TmpVec *= _Num;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator/= (const float& _Num)
{
	x /= _Num;
	y /= _Num;
	z /= _Num;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChVec3::operator / (const float& _Num)const
{

	ChVector3 TmpVec = *this;

	TmpVec /= _Num;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator= (const float& _Num)
{

	x = _Num;
	y = _Num;
	z = _Num;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator = (const ChVector4& _Vec)
{
	x = _Vec.x;
	y = _Vec.y;
	z = _Vec.z;
	return *this;

}

///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator = (const ChVector2& _Vec)
{

	x = _Vec.x;
	y = _Vec.y;
	z = 0.0f;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator *= (const ChVector3& _Vec)
{

	x *= _Vec.x;
	y *= _Vec.y;
	z *= _Vec.z;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChVec3::operator * (const ChVector3& _Vec)const
{
	ChVector3 TmpVec = *this;

	TmpVec *= _Vec;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator -= (const ChVector3& _Vec)
{
	x -= _Vec.x;
	y -= _Vec.y;
	z -= _Vec.z;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChVec3::operator - (const ChVector3& _Vec)const
{
	ChVector3 TmpVec = *this;

	TmpVec -= _Vec;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator += (const ChVector3& _Vec)
{
	x += _Vec.x;
	y += _Vec.y;
	z += _Vec.z;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChVec3::operator + (const ChVector3& _Vec)const
{
	ChVector3 TmpVec = *this;

	TmpVec += _Vec;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

std::string ChVec3::Serialize(
	const std::string& _CutChar
	, const std::string& _EndChar)
{
	std::string Tmp = "";
	for (unsigned char i = 0; i < 3; i++)
	{
		if (i == 2)break;
		Tmp += std::to_string(Val[i]);
		Tmp += _CutChar;
	}

	Tmp += std::to_string(Val[2]);
	Tmp += _EndChar;

	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec3::Deserialize(
	const std::string& _Str
	, const size_t _FPos
	, const std::string& _CutChar
	, const std::string& _EndChar)
{

	std::string TmpStr = _Str;

	size_t TmpFPos = _FPos;

	size_t Tmp = _FPos;

	size_t EPos = TmpStr.find(_EndChar, Tmp);

	if (EPos == TmpStr.npos)EPos = TmpStr.size();

	for (unsigned char i = 0; i < 3; i++)
	{
		size_t Test = TmpStr.find(_CutChar, Tmp);
		if (Test > EPos)Test = EPos;
		{
			TmpFPos = Test;

			std::string Num = TmpStr.substr(Tmp, TmpFPos - Tmp);

			Val[i] = (float)std::atof(Num.c_str());
			Tmp += Num.length();
			Tmp += 1;

		}

		if (Test >= EPos)return;
	}


}

///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChVec3::GetCross(const ChVector3& _Vec1, const ChVector3& _Vec2)
{
	ChVector3 TmpVec;


	for (unsigned char i = 0; i < 3; i++)
	{
		TmpVec.Val[i] =
			(_Vec1.Val[(i + 1) % 3] * _Vec2.Val[(i + 2) % 3])
			- (_Vec1.Val[(i + 2) % 3] * _Vec2.Val[(i + 1) % 3]);
	}

	TmpVec.Normalize();

	return TmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec3::GetCos(const ChVector3& _Vec1, const ChVector3& _Vec2)
{

	if (_Vec1.Len() <= 0.0f || _Vec2.Len() <= 0.0f)return 0.0f;

	ChVec3 Tmp1 = _Vec1, Tmp2 = _Vec2;

	Tmp1.Normalize();
	Tmp2.Normalize();

	float Cos = 0.0f;

	for (unsigned char i = 0; i < 3; i++)
	{
		Cos += (Tmp1.Val[i] * Tmp2.Val[i]);
	}

	return Cos;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec3::GetRadian(const ChVector3& _Vec1, const ChVector3& _Vec2)
{

	if (_Vec1.Len() <= 0.0f || _Vec2.Len() <= 0.0f)return 0.0f;

	return std::acos(GetCos(_Vec1, _Vec2));

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec3::GetDot(const ChVector3& _Vec1, const ChVector3& _Vec2)
{

	if (_Vec1.Len() <= 0.0f || _Vec2.Len() <= 0.0f)return 0.0f;

	float TmpLen;

	TmpLen = (_Vec1.x *  _Vec2.x)
		+ (_Vec1.y * _Vec2.y)
		+ (_Vec1.z * _Vec2.z);

	return TmpLen;


}

///////////////////////////////////////////////////////////////////////////////////

//•â³‚ðs‚¤(Now‚Í0`1)
ChVector3 ChVec3::GetCorrection(const ChVector3& _Start, const ChVector3& _End, const float _Now)
{
	if (_Now <= 0.0f)return _Start;
	if (_Now >= 1.0f)return _End;
	ChVector3 TmpVec;

	TmpVec = _End - _Start;

	TmpVec = _Start + (TmpVec * _Now);

	return TmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec3::GetLen(
	const ChVector3& _Vec1
	, const ChVector3& _Vec2)
{

	float BaseLen;

	ChVec3 TmpVec = _Vec1 - _Vec2;

	BaseLen = 
		std::abs(TmpVec.x)
		+ std::abs(TmpVec.y)
		+ std::abs(TmpVec.z);

	return  BaseLen;
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec3::Normalize()
{
	if (Len() == 1.0f)return;

	float Val = Len();

	if (Val <= 0.0f)
	{
		z = 1.0f;
		return;
	}

	*this /= Val;

}

///////////////////////////////////////////////////////////////////////////////////

void ChVec3::Cross(
	const ChVector3& _Vec1
	, const ChVector3& _Vec2)
{
	*this = GetCross(_Vec1, _Vec2);

	Normalize();
}

///////////////////////////////////////////////////////////////////////////////////
//ChVector2 Method//
///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVec2::operator*= (const float& _Num)
{

	x *= _Num;
	y *= _Num;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2 ChVec2::operator * (const float& _Num)const
{

	ChVector2 TmpVec = *this;

	TmpVec *= _Num;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVec2::operator/= (const float& _Num)
{
	x /= _Num;
	y /= _Num;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2 ChVec2::operator / (const float& _Num)const
{

	ChVector2 TmpVec = *this;

	TmpVec /= _Num;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVec2::operator= (const float& _Num)
{

	x = _Num;
	y = _Num;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVec2::operator = (const ChVector4& _Vec)
{
	x = _Vec.x;
	y = _Vec.y;
	return *this;

}

///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVec2::operator = (const ChVector3& _Vec)
{

	x = _Vec.x;
	y = _Vec.y;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVec2::operator *= (const ChVector2& _Vec)
{

	x *= _Vec.x;
	y *= _Vec.y;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2 ChVec2::operator * (const ChVector2& _Vec)const
{
	ChVector2 TmpVec = *this;

	TmpVec *= _Vec;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVec2::operator -= (const ChVector2& _Vec)
{
	x -= _Vec.x;
	y -= _Vec.y;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2 ChVec2::operator - (const ChVector2& _Vec)const
{
	ChVector2 TmpVec = *this;

	TmpVec -= _Vec;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVec2::operator += (const ChVector2& _Vec)
{
	x += _Vec.x;
	y += _Vec.y;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2 ChVec2::operator + (const ChVector2& _Vec)const
{
	ChVector2 TmpVec = *this;

	TmpVec += _Vec;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

std::string ChVec2::Serialize(
	const std::string& _CutChar
	, const std::string& _EndChar)
{
	std::string Tmp = "";
	for (unsigned char i = 0; i < 2; i++)
	{
		if (i == 1)break;
		Tmp += std::to_string(Val[i]);
		Tmp += _CutChar;
	}

	Tmp += std::to_string(Val[1]);
	Tmp += _EndChar;

	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec2::Deserialize(
	const std::string& _Str
	, const size_t _FPos
	, const std::string& _CutChar
	, const std::string& _EndChar)
{

	std::string TmpStr = _Str;

	size_t TmpFPos = _FPos;

	size_t Tmp = _FPos;

	size_t EPos = TmpStr.find(_EndChar, Tmp);

	if (EPos == TmpStr.npos)EPos = TmpStr.size();

	for (unsigned char i = 0; i < 2; i++)
	{
		size_t Test = TmpStr.find(_CutChar, Tmp);
		if (Test > EPos)Test = EPos;
		{
			TmpFPos = Test;

			std::string Num = TmpStr.substr(Tmp, TmpFPos - Tmp);

			Val[i] = (float)std::atof(Num.c_str());
			Tmp += Num.length();
			Tmp += 1;

		}

		if (Test >= EPos)return;
	}


}

///////////////////////////////////////////////////////////////////////////////////

ChVector2 ChVec2::GetCross(const ChVector2& _Vec1, const ChVector2& _Vec2)
{
	ChVector2 TmpVec;


	for (unsigned char i = 0; i < 2; i++)
	{
		TmpVec.Val[i] =
			(_Vec1.Val[(i + 1) % 2] * _Vec2.Val[(i + 2) % 2])
			- (_Vec1.Val[(i + 2) % 2] * _Vec2.Val[(i + 1) % 2]);
	}

	TmpVec.Normalize();

	return TmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec2::GetCos(const ChVector2& _Vec1, const ChVector2& _Vec2)
{

	if (_Vec1.Len() <= 0.0f || _Vec2.Len() <= 0.0f)return 0.0f;

	ChVec2 Tmp1 = _Vec1, Tmp2 = _Vec2;

	Tmp1.Normalize();
	Tmp2.Normalize();

	float Cos = 0.0f;

	for (unsigned char i = 0; i < 2; i++)
	{
		Cos += (Tmp1.Val[i] * Tmp2.Val[i]);
	}

	return Cos;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec2::GetRadian(const ChVector2& _Vec1, const ChVector2& _Vec2)
{

	if (_Vec1.Len() <= 0.0f || _Vec2.Len() <= 0.0f)return 0.0f;

	return std::acos(GetCos(_Vec1, _Vec2));

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec2::GetDot(const ChVector2& _Vec1, const ChVector2& _Vec2)
{

	if (_Vec1.Len() <= 0.0f || _Vec2.Len() <= 0.0f)return 0.0f;

	float TmpLen;

	TmpLen = (_Vec1.x *  _Vec2.x)
		+ (_Vec1.y * _Vec2.y);

	return TmpLen;


}

///////////////////////////////////////////////////////////////////////////////////

//•â³‚ðs‚¤(Now‚Í0`1)
ChVector2 ChVec2::GetCorrection(const ChVector2& _Start, const ChVector2& _End, const float _Now)
{
	if (_Now <= 0.0f)return _Start;
	if (_Now >= 1.0f)return _End;
	ChVector2 TmpVec;

	TmpVec = _End - _Start;

	TmpVec = _Start + (TmpVec * _Now);

	return TmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec2::GetLen(
	const ChVector2& _Vec1
	, const ChVector2& _Vec2)
{

	float BaseLen;

	ChVec2 TmpVec = _Vec1 - _Vec2;

	BaseLen =
		std::abs(TmpVec.x)
		+ std::abs(TmpVec.y);

	return  BaseLen;
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec2::Normalize()
{
	if (Len() == 1.0f)return;

	float Val = Len();

	if (Val <= 0.0f)
	{
		x = 1.0f;
		return;
	}

	*this /= Val;

}

///////////////////////////////////////////////////////////////////////////////////

void ChVec2::Cross(
	const ChVector2& _Vec1
	, const ChVector2& _Vec2)
{
	*this = GetCross(_Vec1, _Vec2);

	Normalize();
}

///////////////////////////////////////////////////////////////////////////////////
//ChQuaternion Method//
///////////////////////////////////////////////////////////////////////////////////

std::string ChQua::Serialize(
	const std::string& _CutChar
	, const std::string& _EndChar)
{
	std::string Tmp = "";
	for (unsigned char i = 0; i < 4; i++)
	{
		if (i == 3)break;
		Tmp += std::to_string(Val[i]);
		Tmp += _CutChar;
	}

	Tmp += std::to_string(Val[3]);
	Tmp += _EndChar;

	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

void ChQua::Deserialize(
	const std::string& _Str
	, const size_t _FPos
	, const std::string& _CutChar
	, const std::string& _EndChar)
{

	std::string TmpStr = _Str;

	size_t TmpFPos = _FPos;

	size_t Tmp = _FPos;

	size_t EPos = TmpStr.find(_EndChar, Tmp);

	if (EPos == TmpStr.npos)EPos = TmpStr.size();

	for (unsigned char i = 0; i < 4; i++)
	{
		size_t Test = TmpStr.find(_CutChar, Tmp);
		if (Test > EPos)Test = EPos;
		{
			TmpFPos = Test;

			std::string Num = TmpStr.substr(Tmp, TmpFPos - Tmp);

			Val[i] = (float)std::atof(Num.c_str());
			Tmp += Num.length();
			Tmp += 1;

		}

		if (Test >= EPos)return;
	}


}

///////////////////////////////////////////////////////////////////////////////////

ChVec3 ChQua::GetEulerAngleForVec3()const
{

	float xx = x * x;
	float xy = x * y;
	float xz = x * z;
	float xw = x * w;
	float yy = y * y;
	float yz = y * z;
	float yw = y * w;
	float zz = z * z;
	float zw = z * w;
	float ww = w * w;

	ChVec3 Out;

	Out.x = std::asin(2.0f * (xz - yw));
	Out.y = std::atan2(2.0f * (yz + xw), xx + yy - zz - ww);
	Out.z = std::atan2(2.0f * (zw + xy), xx - yy - zz + ww);

	return Out;
}

///////////////////////////////////////////////////////////////////////////////////

void ChQua::RotYPR(
	const float _x
	, const float _y
	, const float _z)
{

	ChVec3 Cos;
	ChVec3 Sin;

	Cos.x = cos(_x / 2.0f);
	Sin.x = sin(_x / 2.0f);

	Cos.y = cos(_y / 2.0f);
	Sin.y = sin(_y / 2.0f);

	Cos.z = cos(_z / 2.0f);
	Sin.z = sin(_z / 2.0f);

	x = (Cos.y * Cos.x * Cos.z) + (Sin.y * Sin.x * Sin.z);
	y = (Cos.y * Cos.x * Sin.z) - (Sin.y * Sin.x * Cos.z);
	z = (Cos.y * Sin.x * Cos.z) + (Sin.y * Cos.x * Sin.z);
	w = (Sin.y * Cos.x * Cos.z) + (Cos.y * Sin.x * Sin.z);

}

///////////////////////////////////////////////////////////////////////////////////
//ChLMatrix Method//
///////////////////////////////////////////////////////////////////////////////////

std::string ChLMatrix::Serialize(
	const std::string& _CutChar
	, const std::string& _EndChar)
{
	std::string Tmp = "";
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			if (i == 3 && j == 3)break;
			Tmp += std::to_string(m[i][j]);
			Tmp += _CutChar;
		}
	}

	Tmp += std::to_string(m[3][3]);
	Tmp += _EndChar;

	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::Deserialize(
	const std::string& _Str
	, const size_t _FPos
	, const std::string& _CutChar
	, const std::string& _EndChar)
{

	std::string TmpStr = _Str;

	size_t TmpFPos = _FPos;

	size_t Tmp = _FPos;

	size_t EPos = TmpStr.find(_EndChar, Tmp);

	if (EPos == TmpStr.npos)EPos = TmpStr.size();

	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			size_t Test = TmpStr.find(_CutChar, Tmp);
			if (Test > EPos)Test = EPos;
			{
				TmpFPos = Test;

				std::string Num = TmpStr.substr(Tmp, TmpFPos - Tmp);

				m[i][j] = (float)std::atof(Num.c_str());
				Tmp += Num.length();
				Tmp += 1;

			}

			if (Test >= EPos)return;
		}

		Tmp += 1;
	}

}

ChRMatrix ChLMatrix::ConvertAxis()
{
	ChRMatrix Tmp;


	return Tmp;
}


///////////////////////////////////////////////////////////////////////////////////
//Degree Method//
///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree& ChMath::Degree::operator=(const float _Num)
{
	Val = _Num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree& ChMath::Degree::operator+=(const float _Num)
{

	Val += _Num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree ChMath::Degree::operator+(const float _Num)const
{
	Degree Tmp = *this;
	Tmp += _Num;
	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree& ChMath::Degree::operator-=(const float _Num)
{
	Val -= _Num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree ChMath::Degree::operator-(const float _Num)const
{

	Degree Tmp = *this;
	Tmp -= _Num;
	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree& ChMath::Degree::operator*=(const float _Num)
{
	Val *= _Num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree ChMath::Degree::operator*(const float _Num)const
{

	Degree Tmp = *this;
	Tmp *= _Num;
	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree& ChMath::Degree::operator/=(const float _Num)
{
	Val /= _Num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree ChMath::Degree::operator/(const float _Num)const
{

	Degree Tmp = *this;
	Tmp /= _Num;
	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree::operator float()const
{
	float Tmp;
	Tmp = Val;
	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree& ChMath::Degree::operator=(const ChMath::Radian _Num)
{
	*this = ToDegree(_Num);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

	ChMath::Degree::Degree()
	{
		Val = 0.0f;
	}

///////////////////////////////////////////////////////////////////////////////////

	ChMath::Degree::Degree(const float _Val)
	{
		*this = _Val;
	}

///////////////////////////////////////////////////////////////////////////////////

	ChMath::Degree::Degree(const Degree &_Val)
	{
		Val = _Val;
	}

///////////////////////////////////////////////////////////////////////////////////

	ChMath::Degree::Degree(const Radian &_Val)
	{
		*this = _Val;
	}

///////////////////////////////////////////////////////////////////////////////////

void ChMath::Degree::Math()
{
	if (Val < 0.0f) 
	{
		unsigned int Tmp;
		Tmp = static_cast<unsigned int>(std::floor((Val / -360.0f)));
		Val += (Tmp + 1) * 360.0f;
		return;
	}

	if (Val >= 360.0f)
	{
		unsigned int Tmp;
		Tmp = static_cast<unsigned int>(std::floor((Val / 360.0f)));
		Val -= (Tmp) * 360.0f;
		return;
	}

}

///////////////////////////////////////////////////////////////////////////////////
//Radian Method//
///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian& ChMath::Radian::operator=(const float _Num)
{
	Val = _Num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian& ChMath::Radian::operator+=(const float _Num)
{

	Val += _Num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian ChMath::Radian::operator+(const float _Num)const
{
	Radian Tmp = *this;
	Tmp += _Num;
	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian& ChMath::Radian::operator-=(const float _Num)
{
	Val -= _Num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian ChMath::Radian::operator-(const float _Num)const
{

	Radian Tmp = *this;
	Tmp -= _Num;
	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian& ChMath::Radian::operator*=(const float _Num)
{
	Val *= _Num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian ChMath::Radian::operator*(const float _Num)const
{

	Radian Tmp = *this;
	Tmp *= _Num;
	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian& ChMath::Radian::operator/=(const float _Num)
{
	Val /= _Num;
	Math();
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian ChMath::Radian::operator/(const float _Num)const
{

	Radian Tmp = *this;
	Tmp /= _Num;
	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian::operator float()const
{
	float Tmp;
	Tmp = Val;
	return Tmp;
}


///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian& ChMath::Radian::operator=(const Degree _Num)
{
	*this = ToRadian(_Num);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

	ChMath::Radian::Radian()
	{
		Val = 0.0f;
	}

///////////////////////////////////////////////////////////////////////////////////

	ChMath::Radian::Radian(const float _Val)
	{
		*this = _Val;
	}

///////////////////////////////////////////////////////////////////////////////////

	ChMath::Radian::Radian(const Radian &_Val)
	{
		Val = _Val;
	}

///////////////////////////////////////////////////////////////////////////////////

	ChMath::Radian::Radian(const Degree &_Val)
	{
		*this = _Val;
	}

///////////////////////////////////////////////////////////////////////////////////

void ChMath::Radian::Math()
{
	float TmpVal;
	TmpVal = (Val / Pi);
	if (TmpVal < 0.0f)
	{
		unsigned int Tmp;
		Tmp = static_cast<unsigned int>(std::floor((TmpVal / -2.0f)));
		Val += (Tmp + 1) * 2.0f * Pi;
		return;
	}

	if (TmpVal >= 360.0f)
	{
		unsigned int Tmp;
		Tmp = static_cast<unsigned int>(std::floor((TmpVal / 2.0f)));
		Val -= (Tmp) * 2.0f * Pi;
		return;
	}

}

///////////////////////////////////////////////////////////////////////////////////
//Math Function//
///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChMath::GetFaceNormal(
	const ChVec3& _Pos1
	, const ChVec3& _Pos2
	, const ChVec3& _Pos3)
{

	ChVec3 TmpVec, TmpVec2;

	TmpVec = _Pos1 - _Pos2;
	TmpVec2 = _Pos2 - _Pos3;

	TmpVec.Cross(TmpVec, TmpVec2);

	TmpVec.Normalize();

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChMath::GetFaceNormal(const TriVertex& _PlEq)
{
	return GetFaceNormal(_PlEq.Ver1, _PlEq.Ver2, _PlEq.Ver3);
}

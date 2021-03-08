#include"../BaseIncluder/ChBase.h"

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

ChVec4::operator const ChVector3() const
{
	ChVec3 Out;

	Out.x = x;
	Out.y = y;
	Out.z = z;

	return Out;

}

///////////////////////////////////////////////////////////////////////////////////

ChVec4::operator const ChVector2() const
{

	ChVec2 Out;

	Out.x = x;
	Out.y = y;

	return Out;
}

///////////////////////////////////////////////////////////////////////////////////

std::string ChVec4::Serialize(
	const std::string& _CutChar
	, const std::string& _EndChar)
{
	std::string Tmp = "";
	for (unsigned char i = 0; i < 4; i++)
	{
		Tmp += std::to_string(Val[i]);
		if (i == 3)break;
		Tmp += _CutChar;
	}

	Tmp += _EndChar;

	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

std::string ChVec4::SerializeARGB(
	const std::string& _CutChar
	, const std::string& _EndChar)
{
	ChVec4 TmpVec;

	for (unsigned char i = 0; i < 4; i++)
	{
		TmpVec.Val[(i + 1) % 4] = Val[i];
	}


	return TmpVec.Serialize(_CutChar, _EndChar);
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec4::Deserialize(
	const std::string& _Str
	, const size_t _FPos
	, const std::string& _CutChar
	, const std::string& _EndChar
	, const unsigned int _Digit)
{

	std::string TmpStr = _Str;

	size_t TmpFPos = _FPos;

	size_t EPos = TmpStr.find(_EndChar, TmpFPos);

	if (EPos == TmpStr.npos)EPos = TmpStr.size();

	TmpStr = TmpStr.substr(TmpFPos, EPos - TmpFPos);

	TmpStr = ChStr::RemoveToWhiteSpaceChars(TmpStr);

	TmpFPos = 0;

	EPos = TmpStr.length();

	size_t Tmp = TmpFPos;

	for (unsigned char i = 0; i < 4; i++)
	{
		size_t Test = TmpStr.find(_CutChar, Tmp);
		if (Test > EPos)Test = EPos;
		{
			TmpFPos = Test;

			std::string Num = TmpStr.substr(Tmp, TmpFPos - Tmp);

			Val[i] = (float)std::atof(Num.c_str());

			Val[i] = ChMath::Round(Val[i], _Digit);

			Tmp += Num.length();
			Tmp += 1;

		}

		if (Test >= EPos)return;
	}


}


///////////////////////////////////////////////////////////////////////////////////

void ChVec4::DeserializeARGB(
	const std::string& _Str
	, const size_t _FPos
	, const std::string& _CutChar
	, const std::string& _EndChar
	, const unsigned int _Digit)
{

	ChVec4 TmpVec;
	TmpVec.Deserialize(_Str, _FPos, _CutChar, _EndChar, _Digit);

	for (unsigned char i = 0; i < 4; i++)
	{
		Val[i] = TmpVec.Val[(i + 1) % 4];
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

	TmpLen = (_Vec1.x * _Vec2.x)
		+ (_Vec1.y * _Vec2.y)
		+ (_Vec1.z * _Vec2.z)
		+ (_Vec1.w * _Vec2.w);

	return TmpLen;


}

///////////////////////////////////////////////////////////////////////////////////

//�␳���s��(Now��0�`1)
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

ChVec3::operator const ChVector4() const
{
	ChVec4 Out;

	Out.x = x;
	Out.y = y;
	Out.z = z;
	Out.w = 0.0f;

	return Out;

}

///////////////////////////////////////////////////////////////////////////////////

ChVec3::operator const ChVector2() const
{

	ChVec2 Out;

	Out.x = x;
	Out.y = y;

	return Out;
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
	, const std::string& _EndChar
	, const unsigned int _Digit)
{

	std::string TmpStr = _Str;

	size_t TmpFPos = _FPos;

	size_t EPos = TmpStr.find(_EndChar, TmpFPos);

	if (EPos == TmpStr.npos)EPos = TmpStr.size();

	TmpStr = TmpStr.substr(TmpFPos, EPos - TmpFPos);

	TmpStr = ChStr::RemoveToWhiteSpaceChars(TmpStr);

	TmpFPos = 0;

	EPos = TmpStr.length();

	size_t Tmp = TmpFPos;

	for (unsigned char i = 0; i < 3; i++)
	{
		size_t Test = TmpStr.find(_CutChar, Tmp);
		if (Test > EPos)Test = EPos;
		{
			TmpFPos = Test;

			std::string Num = TmpStr.substr(Tmp, TmpFPos - Tmp);

			Val[i] = (float)std::atof((Num).c_str());

			Val[i] = ChMath::Round(Val[i], _Digit);

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

	TmpLen = (_Vec1.x * _Vec2.x)
		+ (_Vec1.y * _Vec2.y)
		+ (_Vec1.z * _Vec2.z);

	return TmpLen;


}

///////////////////////////////////////////////////////////////////////////////////

//�␳���s��(Now��0�`1)
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

ChVec2::operator const ChVector4() const
{
	ChVec4 Out;

	Out.x = x;
	Out.y = y;
	Out.z = 0.0f;
	Out.w = 0.0f;

	return Out;

}

///////////////////////////////////////////////////////////////////////////////////

ChVec2::operator const ChVector3() const
{

	ChVec3 Out;

	Out.x = x;
	Out.y = y;
	Out.z = 0.0f;

	return Out;
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
	, const std::string& _EndChar
	, const unsigned int _Digit)
{

	std::string TmpStr = _Str;

	size_t TmpFPos = _FPos;

	size_t EPos = TmpStr.find(_EndChar, TmpFPos);

	if (EPos == TmpStr.npos)EPos = TmpStr.size();

	TmpStr = TmpStr.substr(TmpFPos, EPos - TmpFPos);

	TmpStr = ChStr::RemoveToWhiteSpaceChars(TmpStr);

	TmpFPos = 0;

	EPos = TmpStr.length();

	size_t Tmp = TmpFPos;

	for (unsigned char i = 0; i < 2; i++)
	{
		size_t Test = TmpStr.find(_CutChar, Tmp);
		if (Test > EPos)Test = EPos;
		{
			TmpFPos = Test;

			std::string Num = TmpStr.substr(Tmp, TmpFPos - Tmp);

			Val[i] = (float)std::atof(Num.c_str());

			Val[i] = ChMath::Round(Val[i], _Digit);

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

	TmpLen = (_Vec1.x * _Vec2.x)
		+ (_Vec1.y * _Vec2.y);

	return TmpLen;


}

///////////////////////////////////////////////////////////////////////////////////

//�␳���s��(Now��0�`1)
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
	, const std::string& _EndChar
	, const unsigned int _Digit)
{

	std::string TmpStr = _Str;

	size_t TmpFPos = _FPos;

	size_t EPos = TmpStr.find(_EndChar, TmpFPos);

	if (EPos == TmpStr.npos)EPos = TmpStr.size();

	TmpStr = TmpStr.substr(TmpFPos, EPos - TmpFPos);

	TmpStr = ChStr::RemoveToWhiteSpaceChars(TmpStr);

	TmpFPos = 0;

	EPos = TmpStr.length();

	size_t Tmp = TmpFPos;

	for (unsigned char i = 0; i < 4; i++)
	{
		size_t Test = TmpStr.find(_CutChar, Tmp);
		if (Test > EPos)Test = EPos;
		{
			TmpFPos = Test;

			std::string Num = TmpStr.substr(Tmp, TmpFPos - Tmp);

			Val[i] = (float)std::atof(Num.c_str());

			Val[i] = ChMath::Round(Val[i], _Digit);

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

ChLMatrix& ChLMatrix::operator *= (const ChLMatrix _Mat)
{


	for (unsigned char i = 0; i < 4; i++)
	{
		float Tmp[4];
		for (unsigned char j = 0; j < 4; j++)
		{
			Tmp[j] = m[i][j];
		}
		for (unsigned char j = 0; j < 4; j++)
		{
			m[i][j] = Tmp[0] * _Mat.m[0][j];

			for (unsigned char k = 1; k < 4; k++)
			{
				m[i][j] += Tmp[k] * _Mat.m[k][j];
			}
		}
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChLMatrix const ChLMatrix::operator * (const ChLMatrix _Mat)const
{
	ChLMatrix Out = *this;

	Out *= _Mat;

	return Out;
}

///////////////////////////////////////////////////////////////////////////////////

ChLMatrix& ChLMatrix::operator += (const ChLMatrix _Mat)
{

	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			m[i][j] += _Mat.m[i][j];
		}
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChLMatrix const ChLMatrix::operator + (const ChLMatrix _Mat)const
{

	ChLMatrix Out = *this;

	Out += _Mat;

	return Out;
}

///////////////////////////////////////////////////////////////////////////////////

ChLMatrix& ChLMatrix::operator -= (const ChLMatrix _Mat)
{

	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			m[i][j] -= _Mat.m[i][j];
		}
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChLMatrix const ChLMatrix::operator - (const ChLMatrix _Mat)const
{

	ChLMatrix Out = *this;

	Out -= _Mat;

	return Out;
}

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

std::string ChLMatrix::SerializeUpper(
	const std::string& _CutChar
	, const std::string& _EndChar
	, const std::string& _CutTo4Char)
{
	std::string Tmp = "";
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			if (i == 3 && j == 3)break;
			Tmp += std::to_string(m[i][j]);
			Tmp += _CutChar;

			if (j < 3)continue;
			Tmp += _CutTo4Char;
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
	, const std::string& _EndChar
	, const unsigned int _Digit)
{

	std::string TmpStr = _Str;

	size_t TmpFPos = _FPos;

	size_t EPos = TmpStr.find(_EndChar, TmpFPos);

	if (EPos == TmpStr.npos)EPos = TmpStr.size() - 1;

	TmpStr = TmpStr.substr(TmpFPos, EPos - TmpFPos);

	TmpStr = ChStr::RemoveToWhiteSpaceChars(TmpStr);

	TmpFPos = 0;

	EPos = TmpStr.length();

	size_t Tmp = TmpFPos;

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

				Tmp = Test + 1;

			}

			if (Test >= EPos)return;
		}

	}

}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetPosition(const ChVec3& _Vec)
{
	SetPosition(_Vec.x, _Vec.y, _Vec.z);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetPosition(const float _x, const float _y, const float _z)
{

	l_41 = _x;
	l_42 = _y;
	l_43 = _z;
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::ChLMatrix::SetRotation(const ChVec3& _Vec)
{
	SetRotation(_Vec.x, _Vec.y, _Vec.z);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetRotation(const float _x, const float _y, const float _z)
{
	float x = -std::fmod(_x, 2.0f), y = -std::fmod(_y, 2.0f), z = -std::fmod(_z, 2.0f);


	ChLMat XAxis, YAxis, ZAxis;

	XAxis.l_22 = std::cos(x);
	XAxis.l_23 = std::sin(x);

	XAxis.l_32 = -std::sin(x);
	XAxis.l_33 = std::cos(x);

	YAxis.l_11 = std::cos(y);
	YAxis.l_13 = -std::sin(y);

	YAxis.l_31 = std::sin(y);
	YAxis.l_33 = std::cos(y);

	ZAxis.l_11 = std::cos(z);
	ZAxis.l_12 = std::sin(z);

	ZAxis.l_21 = -std::sin(z);
	ZAxis.l_22 = std::cos(z);

	YAxis = XAxis * YAxis;

	YAxis = ZAxis * YAxis;

	YAxis.SetPosition(GetPosition());
	YAxis.SetScalling(GetScalling());

	*this = YAxis;


}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetScalling(const ChVec3& _Vec)
{
	SetScalling(_Vec.x, _Vec.y, _Vec.z);

}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetScalling(const float _x, const float _y, const float _z)
{
	for (unsigned char i = 0; i < 3; i++)
	{
		m[0][i] *= _x;
	}
	for (unsigned char i = 0; i < 3; i++)
	{
		m[1][i] *= _y;
	}
	for (unsigned char i = 0; i < 3; i++)
	{
		m[2][i] *= _z;
	}
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3 ChLMatrix::GetPosition()const
{
	return ChVec3(l_41, l_42, l_43);
}

///////////////////////////////////////////////////////////////////////////////////

ChVec3 ChLMatrix::GetRotation()const
{
	ChVec3 TmpScl = GetScalling();

	float OutM[4][4];

	for (unsigned char i = 0; i < 3; i++)
	{
		for (unsigned char j = 0; j < 3; j++)
		{
			OutM[i][j] = m[i][j];
			OutM[i][j] /= TmpScl.Val[i] != 0.0f ? TmpScl.Val[i] : 1.0f;
		}
	}


	ChVec3 Out = ChVec3(
		(std::atan2f(OutM[2][1], OutM[2][2])),
		(std::asinf(-OutM[2][0])),
		(std::atan2f(OutM[1][0], OutM[0][0])));

	//ChVec3 Out = ChVec3(
	//	(std::atan2f(_32,_33)),
	//	(std::asinf(_31)),
	//	(std::atan2f(_21,_11)));


	return Out;

}

///////////////////////////////////////////////////////////////////////////////////

ChVec3 ChLMatrix::GetScalling()const
{
	ChVec3 XS = ChVec3(l_11, l_12, l_13);
	ChVec3 YS = ChVec3(l_21, l_22, l_23);
	ChVec3 ZS = ChVec3(l_31, l_32, l_33);

	return ChVec3(XS.Len(), YS.Len(), ZS.Len());
}

///////////////////////////////////////////////////////////////////////////////////
//
//ChMath::MatrixBase3x3 ChLMatrix::GetRotMatrix()const
//{
//	ChMath::MatrixBase3x3 Out;
//
//	for (unsigned char i = 0; i < 3; i++)
//	{
//		for (unsigned char j = 0; j < 3; j++)
//		{
//			Out[i][j] = m[i][j];
//		}
//	}
//
//	return Out;
//
//}

///////////////////////////////////////////////////////////////////////////////////

ChVec4 ChLMatrix::Transform(const ChVec4 _Base)const
{
	ChVec4 Out;

	Out.x = _Base.x * l_11 + _Base.y * l_21 + _Base.z * l_31 + _Base.w * l_41;
	Out.y = _Base.x * l_12 + _Base.y * l_22 + _Base.z * l_32 + _Base.w * l_42;
	Out.z = _Base.x * l_13 + _Base.y * l_23 + _Base.z * l_33 + _Base.w * l_43;
	Out.w = _Base.x * l_14 + _Base.y * l_24 + _Base.z * l_34 + _Base.w * l_44;

	return Out;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec4 ChLMatrix::TransformCoord(const ChVec4 _Base)const
{

	ChVec4 Out;
	Out.x = _Base.x * l_11 + _Base.y * l_21 + _Base.z * l_31;
	Out.y = _Base.x * l_12 + _Base.y * l_22 + _Base.z * l_32;
	Out.z = _Base.x * l_13 + _Base.y * l_23 + _Base.z * l_33;
	Out.w = _Base.x * l_14 + _Base.y * l_24 + _Base.z * l_34 + _Base.w * l_44;
	return Out;
}

///////////////////////////////////////////////////////////////////////////////////

ChRMatrix ChLMatrix::ConvertAxis()
{
	ChRMatrix Tmp;


	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////
//ChUIMatrix Method//
///////////////////////////////////////////////////////////////////////////////////

std::string ChUIMatrix::Serialize(
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

std::string ChUIMatrix::SerializeUpper(
	const std::string& _CutChar
	, const std::string& _EndChar
	, const std::string& _CutTo4Char)
{

	std::string Tmp = "";
	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			if (i == 3 && j == 3)break;
			Tmp += std::to_string(m[i][j]);
			Tmp += _CutChar;

			if (j < 3)continue;
			Tmp += _CutTo4Char;
		}
	}

	Tmp += std::to_string(m[3][3]);
	Tmp += _EndChar;

	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

void ChUIMatrix::Deserialize(
	const std::string& _Str
	, const size_t _FPos
	, const std::string& _CutChar
	, const std::string& _EndChar)
{

	std::string TmpStr = _Str;

	size_t TmpFPos = _FPos;

	size_t EPos = TmpStr.find(_EndChar, TmpFPos);

	if (EPos == TmpStr.npos)EPos = TmpStr.size() - 1;

	TmpStr = TmpStr.substr(TmpFPos, EPos - TmpFPos);

	TmpStr = ChStr::RemoveToWhiteSpaceChars(TmpStr);

	TmpFPos = 0;

	EPos = TmpStr.length();

	size_t Tmp = TmpFPos;

	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			size_t Test = TmpStr.find(_CutChar, Tmp);

			if (Test > EPos)Test = EPos;

			{
				TmpFPos = Test;

				std::string Num = TmpStr.substr(Tmp, TmpFPos - Tmp);

				m[i][j] = (unsigned long)std::atoll(Num.c_str());

				Tmp = Test + 1;

			}

			if (Test >= EPos)return;
		}

	}

}

///////////////////////////////////////////////////////////////////////////////////
//Math Function//
///////////////////////////////////////////////////////////////////////////////////

float ChMath::Round(const float& _Val, const unsigned int _Digit)
{
	float Out = _Val * std::powf(10.0f, static_cast<float>(_Digit - 1));
	Out = std::round(Out);
	Out = Out * std::powf(0.1f, static_cast<float>(_Digit - 1));


	return Out;
}

///////////////////////////////////////////////////////////////////////////////////

double ChMath::Round(const double& _Val, const unsigned int _Digit)
{
	double Out = _Val * std::powl(10, static_cast<double>(_Digit - 1));
	Out = std::round(Out);
	Out = Out * std::powl(0.1, static_cast<double>(_Digit - 1));


	return Out;

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

ChMath::Degree::Degree(const Degree& _Val)
{
	Val = _Val;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Degree::Degree(const Radian& _Val)
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

ChMath::Radian::Radian(const Radian& _Val)
{
	Val = _Val;
}

///////////////////////////////////////////////////////////////////////////////////

ChMath::Radian::Radian(const Degree& _Val)
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

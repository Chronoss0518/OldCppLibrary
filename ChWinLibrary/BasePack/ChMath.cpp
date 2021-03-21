#include"../BaseIncluder/ChBase.h"

///////////////////////////////////////////////////////////////////////////////////
//ChVector4 Method//
///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator*= (const float& _Num)
{

	Val.Mul(_Num);

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
	Val.Div(_Num);

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

	Val.Set(_Num);

	if (w < -1.0f)w = -1.0f;
	if (w > 1.0f)w = 1.0f;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVector4::operator=(const ChVector4& _Vec)
{
	Val.Set(_Vec.Val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator *= (const ChVector4& _Vec)
{
	Val.Mul(_Vec.Val);

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

ChVector4& ChVec4::operator /= (const ChVector4& _Vec)
{
	Val.Div(_Vec.Val);

	if (w < -1.0f)w = -1.0f;
	if (w > 1.0f)w = 1.0f;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4 ChVec4::operator / (const ChVector4& _Vec)const
{
	ChVector4 TmpVec = *this;

	TmpVec /= _Vec;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector4& ChVec4::operator -= (const ChVector4& _Vec)
{

	Val.Sub(_Vec.Val);

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

	Val.Add(_Vec.Val);

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

	Out.Val = Val;

	return Out;

}

///////////////////////////////////////////////////////////////////////////////////

ChVec4::operator const ChVector2() const
{

	ChVec2 Out;

	Out.Val = Val;

	return Out;
}

///////////////////////////////////////////////////////////////////////////////////

std::string ChVec4::Serialize(
	const std::string& _CutChar
	, const std::string& _EndChar)
{
	return Val.Serialize(_CutChar, _EndChar);
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
	Val.Deserialize(_Str, _FPos, _CutChar, _EndChar, _Digit);
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

	TmpVec.Val.Cross(_Vec1.Val, _Vec2.Val);

	return TmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec4::GetCos(const ChVector4& _Vec1, const ChVector4& _Vec2)
{
	return _Vec1.Val.GetCos(_Vec2.Val);
}

///////////////////////////////////////////////////////////////////////////////////

float ChVec4::GetRadian(const ChVector4& _Vec1, const ChVector4& _Vec2)
{
	return _Vec1.Val.GetRadian(_Vec2.Val);
}

///////////////////////////////////////////////////////////////////////////////////

float ChVec4::GetDot(const ChVector4& _Vec1, const ChVector4& _Vec2)
{
	return _Vec1.Val.GetDot(_Vec2.Val);
}

///////////////////////////////////////////////////////////////////////////////////

//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
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

	ChVec4 TmpVec = _Vec1 - _Vec2;

	return  TmpVec.Val.GetLen();
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec4::Normalize()
{
	if (Len() == 1.0f)return;

	Val.Normalize();

}

///////////////////////////////////////////////////////////////////////////////////

void ChVec4::Cross(
	const ChVector4& _Vec1
	, const ChVector4& _Vec2)
{
	Val.Cross(_Vec1.Val, _Vec2.Val);
}

///////////////////////////////////////////////////////////////////////////////////
//ChVector3 Method//
///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator*= (const float& _Num)
{

	Val.Mul(_Num);

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
	Val.Div(_Num);

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

	Val.Set(_Num);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVector3::operator=(const ChVector3& _Vec)
{
	Val.Set(_Vec.Val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator *= (const ChVector3& _Vec)
{
	Val.Mul(_Vec.Val);

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

ChVector3& ChVec3::operator /= (const ChVector3& _Vec)
{
	Val.Div(_Vec.Val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChVec3::operator / (const ChVector3& _Vec)const
{
	ChVector3 TmpVec = *this;

	TmpVec /= _Vec;

	return TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3& ChVec3::operator -= (const ChVector3& _Vec)
{
	Val.Sub(_Vec.Val);

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
	Val.Add(_Vec.Val);

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

	Out.Val = Val;

	return Out;

}

///////////////////////////////////////////////////////////////////////////////////

ChVec3::operator const ChVector2() const
{

	ChVec2 Out;

	Out.Val = Val;

	return Out;
}

///////////////////////////////////////////////////////////////////////////////////

std::string ChVec3::Serialize(
	const std::string& _CutChar
	, const std::string& _EndChar)
{
	return Val.Serialize(_CutChar, _EndChar);
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec3::Deserialize(
	const std::string& _Str
	, const size_t _FPos
	, const std::string& _CutChar
	, const std::string& _EndChar
	, const unsigned int _Digit)
{
	Val.Deserialize(_Str, _FPos, _CutChar, _EndChar, _Digit);
}

///////////////////////////////////////////////////////////////////////////////////

ChVector3 ChVec3::GetCross(const ChVector3& _Vec1, const ChVector3& _Vec2)
{
	ChVector3 TmpVec;

	TmpVec.Val.Cross(_Vec1.Val, _Vec2.Val);

	return TmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec3::GetCos(const ChVector3& _Vec1, const ChVector3& _Vec2)
{
	return _Vec1.Val.GetCos(_Vec2.Val);
}

///////////////////////////////////////////////////////////////////////////////////

float ChVec3::GetRadian(const ChVector3& _Vec1, const ChVector3& _Vec2)
{
	return _Vec1.Val.GetRadian(_Vec2.Val);
}

///////////////////////////////////////////////////////////////////////////////////

float ChVec3::GetDot(const ChVector3& _Vec1, const ChVector3& _Vec2)
{
	return _Vec1.Val.GetDot(_Vec2.Val);
}

///////////////////////////////////////////////////////////////////////////////////

//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
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

	ChVec3 TmpVec = _Vec1 - _Vec2;

	return  TmpVec.Val.GetLen();
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec3::Normalize()
{
	Val.Normalize();
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec3::Cross(
	const ChVector3& _Vec1
	, const ChVector3& _Vec2)
{
	*this = GetCross(_Vec1, _Vec2);
}

///////////////////////////////////////////////////////////////////////////////////
//ChVector2 Method//
///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVector2::operator=(const ChVector2& _Vec)
{
	Val.Set(_Vec.Val);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVec2::operator*= (const float& _Num)
{
	Val.Mul(_Num);

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
	Val.Div(_Num);

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

	Val.Set(_Num);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2& ChVec2::operator *= (const ChVector2& _Vec)
{
	Val.Mul(_Vec.Val);

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
	Val.Sub(_Vec.Val);

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
	Val.Add(_Vec.Val);

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

	Out.Val = Val;

	return Out;

}

///////////////////////////////////////////////////////////////////////////////////

ChVec2::operator const ChVector3() const
{

	ChVec3 Out;

	Out.Val = Val;

	return Out;
}

///////////////////////////////////////////////////////////////////////////////////

std::string ChVec2::Serialize(
	const std::string& _CutChar
	, const std::string& _EndChar)
{
	return Val.Serialize(_CutChar,_EndChar);
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec2::Deserialize(
	const std::string& _Str
	, const size_t _FPos
	, const std::string& _CutChar
	, const std::string& _EndChar
	, const unsigned int _Digit)
{
	Val.Deserialize(_Str, _FPos, _CutChar, _EndChar, _Digit);
}

///////////////////////////////////////////////////////////////////////////////////

ChVector2 ChVec2::GetCross(const ChVector2& _Vec1, const ChVector2& _Vec2)
{
	ChVector2 TmpVec;

	TmpVec.Val.Cross(_Vec1.Val, _Vec2.Val);

	return TmpVec;

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec2::GetCos(const ChVector2& _Vec1, const ChVector2& _Vec2)
{

	return _Vec1.Val.GetCos(_Vec2.Val);

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec2::GetRadian(const ChVector2& _Vec1, const ChVector2& _Vec2)
{

	return _Vec1.Val.GetRadian(_Vec2.Val);

}

///////////////////////////////////////////////////////////////////////////////////

float ChVec2::GetDot(const ChVector2& _Vec1, const ChVector2& _Vec2)
{
	return _Vec1.Val.GetDot(_Vec2.Val);
}

///////////////////////////////////////////////////////////////////////////////////

//ï‚ê≥ÇçsÇ§(NowÇÕ0Å`1)
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

	ChVec2 TmpVec = _Vec1 - _Vec2;

	return  TmpVec.Val.GetLen();
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec2::Normalize()
{
	Val.Normalize();
}

///////////////////////////////////////////////////////////////////////////////////

void ChVec2::Cross(
	const ChVector2& _Vec1
	, const ChVector2& _Vec2)
{
	*this = GetCross(_Vec1, _Vec2);

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

ChLMatrix& ChLMatrix::operator =(const ChLMatrix _Mat)
{
	m.Set(_Mat.m);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

ChLMatrix& ChLMatrix::operator *= (const ChLMatrix _Mat)
{

	m.Mul(_Mat.m);

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

	m.Add(_Mat.m);

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

	m.Sub(_Mat.m);

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
	return m.Serialize(_CutChar);
}

///////////////////////////////////////////////////////////////////////////////////

std::string ChLMatrix::SerializeUpper(
	const std::string& _CutChar
	, const std::string& _EndChar
	, const std::string& _CutTo4Char)
{
	return m.SerializeUpper(_CutChar, _EndChar, _CutTo4Char);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::Deserialize(
	const std::string& _Str
	, const size_t _FPos
	, const std::string& _CutChar
	, const std::string& _EndChar
	, const unsigned int _Digit)
{
	m.Deserialize(_Str, _FPos, _CutChar, _EndChar, _Digit);
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

	ChLMat XAxis, YAxis, ZAxis;

	XAxis.SetRotationXAxis(_x);
	YAxis.SetRotationYAxis(_y);
	ZAxis.SetRotationZAxis(_z);

	YAxis = XAxis * YAxis;

	YAxis = ZAxis * YAxis;

	YAxis.SetPosition(GetPosition());
	YAxis.SetScalling(GetScalling());

	m.Set(YAxis.m);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetRotationXAxis(const float _x)
{
	float x = -std::fmod(_x, 2.0f);

	l_22 = std::cos(x);
	l_23 = std::sin(x);

	l_32 = -std::sin(x);
	l_33 = std::cos(x);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetRotationYAxis(const float _y)
{
	float  y = -std::fmod(_y, 2.0f);

	l_11 = std::cos(y);
	l_13 = -std::sin(y);

	l_31 = std::sin(y);
	l_33 = std::cos(y);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetRotationZAxis(const float _z)
{
	float z = -std::fmod(_z, 2.0f);

	l_11 = std::cos(z);
	l_12 = std::sin(z);

	l_21 = -std::sin(z);
	l_22 = std::cos(z);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetScalling(const ChVec3& _Vec)
{
	SetScalling(_Vec.x, _Vec.y, _Vec.z);
}

///////////////////////////////////////////////////////////////////////////////////

void ChLMatrix::SetScalling(const float _x, const float _y, const float _z)
{
	m[0].Normalize();
	m[0].Mul(_x);

	m[1].Normalize();
	m[1].Mul(_y);

	m[2].Normalize();
	m[2].Mul(_z);
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
	return ChVec3(m[0].GetLen(), m[1].GetLen(), m[2].GetLen());
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

	Out.Val = m.VerticalMul(_Base.Val);

	return Out;
}

///////////////////////////////////////////////////////////////////////////////////

ChVec4 ChLMatrix::TransformCoord(const ChVec4 _Base)const
{
	ChLMatrix Tmp = *this;

	Tmp.l_41 = 0.0f;
	Tmp.l_42 = 0.0f;
	Tmp.l_43 = 0.0f;

	return Tmp.Transform(_Base);
}

///////////////////////////////////////////////////////////////////////////////////

ChRMatrix ChLMatrix::ConvertAxis()
{
	ChRMatrix Tmp;

	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////
//ChRMatrix Method//
///////////////////////////////////////////////////////////////////////////////////

ChRMatrix& ChRMatrix::operator =(const ChRMatrix& _Mat)
{
	m.Set(_Mat.m);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////
//ChUIMatrix Method//
///////////////////////////////////////////////////////////////////////////////////

ChUIMatrix& ChUIMatrix::operator =(const ChUIMatrix _Mat)
{
	m.Set(_Mat.m);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////

std::string ChUIMatrix::Serialize(
	const std::string& _CutChar
	, const std::string& _EndChar)
{
	return m.Serialize(_CutChar, _EndChar);
}

///////////////////////////////////////////////////////////////////////////////////

std::string ChUIMatrix::SerializeUpper(
	const std::string& _CutChar
	, const std::string& _EndChar
	, const std::string& _CutTo4Char)
{
	return m.SerializeUpper(_CutChar, _EndChar, _CutTo4Char);
}

///////////////////////////////////////////////////////////////////////////////////

void ChUIMatrix::Deserialize(
	const std::string& _Str
	, const size_t _FPos
	, const std::string& _CutChar
	, const std::string& _EndChar)
{
	m.Deserialize(_Str, _FPos, _CutChar, _EndChar);
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

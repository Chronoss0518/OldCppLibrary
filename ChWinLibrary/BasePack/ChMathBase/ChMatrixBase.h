#ifndef Ch_CPP_BMatrix_h
#define Ch_CPP_BMatrix_h

namespace ChMath
{
	template<typename T, unsigned long Array>
	using VectorTest = typename std::enable_if<(Array > 0) && (std::is_integral<T>::value || std::is_floating_point<T>::value), T>::type;

	template<typename T, unsigned long Row, unsigned long Column>
	using MatrixTest = typename std::enable_if<(Row > 0 && Column > 0) && (std::is_integral<T>::value || std::is_floating_point<T>::value), T>::type;


	
	template<typename T, unsigned long Array>
	class VectorBase
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//Operator//

		template<unsigned long _ArrayCount>
		operator VectorBase<T, _ArrayCount>()const
		{
			VectorBase<T, _ArrayCount> Out;

			unsigned long MaxVal = _ArrayCount > Array ? Array : _ArrayCount;
			
			Out.Set(*this);

			return Out;
		}

		VectorBase& operator =(const VectorBase& _Array)
		{
			Set(_Array);
			return *this;
		}

		VectorBase& operator =(const T& _Val)
		{
			Set(_Val);
			return *this;
		}

		VectorBase& operator +=(const VectorBase& _Array)
		{
			Add(_Array);
			return *this;
		}
		VectorBase& operator -=(const VectorBase& _Array)
		{
			Sub(_Array);
			return *this;
		}
		VectorBase& operator *=(const VectorBase& _Array)
		{
			Mul(_Array);
			return *this;
		}
		VectorBase& operator /=(const VectorBase& _Array)
		{
			Div(_Array);
			return *this;
		}

		VectorBase operator +(const VectorBase& _Array)const
		{
			VectorBase Out;

			Out = *this;
			Out.Add(_Array);

			return Out;
		}
		VectorBase operator -(const VectorBase& _Array)const
		{
			VectorBase Out;

			Out = *this;
			Out.Sub(_Array);

			return Out;
		}
		VectorBase operator *(const VectorBase& _Array)const
		{
			VectorBase Out;

			Out = *this;
			Out.Mul(_Array);

			return Out;
		}
		VectorBase operator /(const VectorBase& _Array)const
		{
			VectorBase<T, Array> Out;

			Out = *this;
			Out.Div(_Array);

			return Out;
		}

		VectorBase& operator +=(const T& _Val)
		{
			Add(_Val);
			return *this;
		}
		VectorBase& operator -=(const T& _Val)
		{
			Sub(_Val);
			return *this;
		}
		VectorBase& operator *=(const T& _Val)
		{
			Mul(_Val);
			return *this;
		}
		VectorBase& operator /=(const T& _Val)
		{
			Div(_Val);
			return *this;
		}

		VectorBase operator +(const T& _Val)const
		{
			VectorBase<T, Array> Out;
			Out = *this;
			Out.Add(_Val);

			return Out;
		}
		VectorBase operator -(const T& _Val)const
		{
			VectorBase<T, Array> Out;
			Out = *this;
			Out.Sub(_Val);

			return Out;
		}
		VectorBase operator *(const T& _Val)const
		{
			VectorBase<T, Array> Out;
			Out = *this;
			Out.Mul(_Val);

			return Out;
		}
		VectorBase operator /(const T& _Val)const
		{
			VectorBase<T, Array> Out;
			Out = *this;
			Out.Div(_Val);

			return Out;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//ConstructorDestructor//

		VectorBase(T(& _Val)[Array]):Val(_Val){}

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		///////////////////////////////////////////////////////////////////////////////////
		//OperatorMathFunction//

		void Set(const VectorBase& _Vec)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				Val[i] = _Vec.Val[i];
			}
		}

		void Set(const T& _Val)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				Val[i] = _Val;
			}
		}
		
		void Set(const T* const _ArrayVal)
		{

			for (unsigned long i = 0; i < Array; i++)
			{
				Val[i] = *(_ArrayVal + i);
			}
		}

		void Add(const VectorBase& _Vec)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				Val[i] += _Vec.Val[i];
			}
		}

		void Add(const T& _Val)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				Val[i] += _Val;
			}
		}

		void Sub(const VectorBase& _Vec)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				Val[i] -= _Vec.Val[i];
			}
		}

		void Sub(const T& _Val)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				Val[i] -= _Val;
			}
		}

		void Mul(const VectorBase& _Vec)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				Val[i] *= _Vec.Val[i];
			}
		}

		void Mul(const T& _Val)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				Val[i] *= _Val;
			}
		}

		void Div(const VectorBase& _Vec)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				Val[i] /= _Vec.Val[i] != static_cast<T>(0.0f) ? _Vec.Val[i] : static_cast<T>(1.0f);
			}
		}

		void Div(const T& _Val)
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				Val[i] /= _Val != static_cast<T>(0.0f) ? _Val : static_cast<T>(1.0f);
			}
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SerializeDesirialize//

		std::string Serialize(
			const std::string& _CutChar = ","
			, const std::string& _EndChar = ";")
		{

			std::string Tmp = "";
			for (unsigned char i = 0; i < Array; i++)
			{
				Tmp += std::to_string(Val[i]);
				if (i == (Array - 1))break;
				Tmp += _CutChar;
			}

			Tmp += _EndChar;

			return Tmp;
		}

		void Deserialize(
			const std::string& _Str
			, const size_t _FPos = 0
			, const std::string& _CutChar = ","
			, const std::string& _EndChar = ";"
			, const unsigned int _Digit = 6)
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

			for (unsigned char i = 0; i < Array; i++)
			{
				size_t Test = TmpStr.find(_CutChar, Tmp);
				if (Test > EPos)Test = EPos;
				{
					TmpFPos = Test;

					std::string Num = TmpStr.substr(Tmp, TmpFPos - Tmp);

					Val[i] = (float)std::atof(Num.c_str());

//					Val[i] = ChMath::Round(Val[i], _Digit);

					Tmp += Num.length();
					Tmp += 1;

				}

				if (Test >= EPos)return;
			}

		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//


		unsigned long GetArray() { return Array; }

		float GetLen()const
		{
			T Len = static_cast<T>(0.0f);

			for (unsigned long i = 0; i < Array; i++)
			{
				Len += std::abs(Val[i]);
			}

			return Len;

		}

		float GetCos(
			const VectorBase& _Vec)const
		{

			if (GetLen() <= 0.0f || _Vec.GetLen() <= 0.0f)return 0.0f;

			VectorBase Tmp1, Tmp2;

			Tmp1 = *this;
			Tmp2 = _Vec;

			Tmp1.Normalize();
			Tmp2.Normalize();

			float Cos = 0.0f;

			for (unsigned char i = 0; i < 4; i++)
			{
				Cos += (Tmp1.Val[i] * Tmp2.Val[i]);
			}

			return Cos;
		}

		float GetRadian(
			const VectorBase& _Vec)const
		{

			if (GetLen() <= 0.0f || _Vec.GetLen() <= 0.0f)return 0.0f;

			return std::acos(GetCos(_Vec, *this));
		}

		float GetDot(
			const VectorBase& _Vec)const
		{

			if (GetLen() <= 0.0f || _Vec.GetLen() <= 0.0f)return 0.0f;

			float TmpLen = 0.0f;

			for (unsigned long i = 0; i < Array; i++)
			{
				TmpLen += Val[i] * _Vec.Val[i];
			}

			return TmpLen;

		}

		///////////////////////////////////////////////////////////////////////////////////

		inline void Abs()
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				Val[i] = Val[i] < 0.0f ? Val[i] * -1.0f : Val[i];
			}
		}

		inline void Abs(const VectorBase& _Vec)
		{

			for (unsigned long i = 0; i < Array; i++)
			{
				Val[i] = _Vec.Val[i] < 0.0f ? _Vec.Val[i] * -1.0f : _Vec.Val[i];
			}
		}
		///////////////////////////////////////////////////////////////////////////////////

		void Cross(
			const VectorBase& _Vec)
		{

			VectorBase TmpVec;

			TmpVec = *this;

			for (unsigned char i = 0; i < 4; i++)
			{
				Val[i] =
					(TmpVec.Val[(i + 1) % 4] * _Vec.Val[(i + 2) % 4])
					- (TmpVec.Val[(i + 2) % 4] * _Vec.Val[(i + 1) % 4]);
			}

			Normalize();

			return;

		}

		void Cross(
			const VectorBase& _Vec1, const VectorBase& _Vec2)
		{

			for (unsigned char i = 0; i < 4; i++)
			{
				Val[i] =
					(_Vec1.Val[(i + 1) % 4] * _Vec2.Val[(i + 2) % 4])
					- (_Vec1.Val[(i + 2) % 4] * _Vec2.Val[(i + 1) % 4]);
			}

			Normalize();

			return;
		}

		///////////////////////////////////////////////////////////////////////////////////

		//•â³‚ðs‚¤(Now‚Í0`1)
		void Correction(
			const VectorBase& _Start, const VectorBase& _End, const float _Now)
		{
			if (_Now <= 0.0f)
			{
				return;
			}

			if (_Now >= 1.0f)
			{
				return;
			}

			VectorBase TmpVec;

			TmpVec = _End - _Start;

			TmpVec = _Start + (TmpVec * _Now);

			
		}


		///////////////////////////////////////////////////////////////////////////////////

		void Identity()
		{
			for (unsigned long i = 0; i < Array; i++)
			{
				Val[i] = static_cast<T>(i != 3 ? 0.0f : 1.0f);
			}
		}

		///////////////////////////////////////////////////////////////////////////////////

		void Normalize()
		{

			T Len = GetLen();

			if (Len == static_cast<T>(0.0f))return;

			for (unsigned long i = 0; i < Array; i++)
			{
				Val[i] /= Len;
			}
		}


	private:

		VectorTest<T, Array> (&Val)[Array];

	};


	template<typename T, unsigned long Row, unsigned long Column>
	class MatrixBase
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//Operator//

		template<unsigned long _Row, unsigned long _Column>
		operator MatrixBase<T, _Row, _Column>()const
		{
			MatrixBase<T, _Row, _Column> Out;

			unsigned long MinRow = _Row > Row ? Row : _Row;
			unsigned long MinColumn = _Column > Column ? Column : _Column;

			for (unsigned long i = 0; i < MinColumn; i++)
			{
				for (unsigned long j = 0; j < MinRow; j++)
				{
					Out[Column][Row] = m[Column][Row];
				}
			}

			return Out;
		}

		MatrixBase& operator =(const MatrixBase& _Mat)
		{

			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{
					m[i][j] = _Mat.m[i][j];
				}

			}

			return *this;
		}

		MatrixBase& operator +=(const MatrixBase& _Mat)
		{

			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{
					m[i][j] += _Mat.m[i][j];
				}

			}

			return *this;
		}

		MatrixBase operator +(const MatrixBase& _Array)const
		{
			MatrixBase Out;

			Out = *this;
			Out += _Array;

			return Out;
		}

		MatrixBase& operator -=(const MatrixBase& _Mat)
		{

			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{
					m[i][j] -= _Mat.m[i][j];
				}
			}

			return *this;
		}

		MatrixBase operator -(const MatrixBase& _Array)const
		{
			MatrixBase Out;

			Out = *this;
			Out -= _Array;

			return Out;
		}

		MatrixBase& operator *=(const MatrixBase& _Mat)
		{

			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{
					m[i][j] *= _Mat.m[i][j];
				}
			}

			return *this;
		}

		MatrixBase operator *(const MatrixBase& _Mat)const
		{
			MatrixBase Out;

			Out = *this;
			Out *= _Mat;

			return Out;
		}

		MatrixBase& operator /=(const MatrixBase& _Mat)
		{

			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{
					m[i][j] /= _Mat.m[i][j] != 0.0f ? _Mat.m[i][j] : 1.0f;
				}
			}

			return *this;
		}

		MatrixBase operator /(const MatrixBase& _Mat)const
		{
			MatrixBase Out;
			Out = *this;
			Out /= _Mat;

			return Out;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//ConstructorDestructor//

		MatrixBase(T(&_Mat)[Column][Row]):m(_Mat) {}

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		///////////////////////////////////////////////////////////////////////////////////////
		//SerializeDesirialize//

		std::string Serialize(
			const std::string& _CutChar = ","
			, const std::string& _EndChar = ";")
		{

		}

		std::string SerializeUpper(
			const std::string& _CutChar = ","
			, const std::string& _EndChar = ";"
			, const std::string& _CutTo4Char = "\n")
		{

		}

		void Deserialize(
			const std::string& _Str
			, const size_t _FPos = 0
			, const std::string& _CutChar = ","
			, const std::string& _EndChar = ";"
			, const unsigned int _Digit = 6)
		{

		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		float GetLen()const
		{

		}

		float GetDef(const int _Row, const int _Col)const
		{

		}

		float GetCofactor()const
		{

		}

		unsigned long GetColumn() { return Column; }

		unsigned long GetRow() { return Row; }

		///////////////////////////////////////////////////////////////////////////////////

		void Identity()
		{

			for (unsigned char i = 0; i < Column; i++)
			{
				for (unsigned char j = 0; j < Row; j++)
				{
					m[i][j] = (i != j ? 0.0f : 1.0f);
				}
			}

		}

		///////////////////////////////////////////////////////////////////////////////////

		void Inverse()
		{

		}

	private:

		MatrixTest<T, Row, Column> (&m)[Column][Row];

	};



}

#endif
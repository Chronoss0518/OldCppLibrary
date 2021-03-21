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
			
			for (unsigned long i = 0; i < MaxVal; i++)
			{
				Out[i] = Val[i];
			}

			return Out;
		}

		T& operator [](const unsigned long _Val)
		{
			return Val[_Val % Array];
		}

		T operator [](const unsigned long _Val)const
		{
			return Val[_Val % Array];
		}

		explicit operator const T* const ()const
		{
			return Val;
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

		VectorBase() = default;

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
		
		void Set(const T (&_ArrayVal)[Array])
		{

			for (unsigned long i = 0; i < Array; i++)
			{
				Val[i] = _ArrayVal[i];
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

		T GetLen()const
		{
			T Len = static_cast<T>(0.0f);

			for (unsigned long i = 0; i < Array; i++)
			{
				Len += std::abs(Val[i]);
			}

			return Len;

		}

		T GetCos(
			const VectorBase& _Vec)const
		{

			if (GetLen() <= 0.0f || _Vec.GetLen() <= 0.0f)return 0.0f;

			VectorBase Tmp1, Tmp2;

			Tmp1 = *this;
			Tmp2 = _Vec;

			Tmp1.Normalize();
			Tmp2.Normalize();

			return Tmp1.GetDot(Tmp2);
		}

		T GetRadian(
			const VectorBase& _Vec)const
		{

			if (GetLen() <= 0.0f || _Vec.GetLen() <= 0.0f)return 0.0f;

			return static_cast<T>(std::acos(GetCos(_Vec)));
		}

		T GetDot(
			const VectorBase& _Vec)const
		{

			if (GetLen() <= 0.0f || _Vec.GetLen() <= 0.0f)return 0.0f;

			T TmpLen = 0.0f;

			for (unsigned long i = 0; i < Array; i++)
			{
				TmpLen += Val[i] * _Vec.Val[i];
			}

			return TmpLen;

		}

		const T* const GetVal()const
		{
			return Val;
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

			for (unsigned char i = 0; i < Array; i++)
			{
				Val[i] =
					(TmpVec.Val[(i + 1) % Array] * _Vec.Val[(i + 2) % Array])
					- (TmpVec.Val[(i + 2) % Array] * _Vec.Val[(i + 1) % Array]);
			}

			Normalize();

			return;

		}

		void Cross(
			const VectorBase& _Vec1, const VectorBase& _Vec2)
		{

			for (unsigned char i = 0; i < Array; i++)
			{
				Val[i] =
					(_Vec1.Val[(i + 1) % Array] * _Vec2.Val[(i + 2) % Array])
					- (_Vec1.Val[(i + 2) % Array] * _Vec2.Val[(i + 1) % Array]);
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

		VectorTest<T, Array> Val[Array];

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

		VectorBase<T, Row>& operator [](const unsigned long _Col)
		{
			return m[_Col % Column];
		}

		VectorBase<T, Row> operator [](const unsigned long _Col)const
		{
			return m[_Col % Column];
		}

		explicit operator const T** const ()const
		{
			return m;
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

		MatrixBase() = default;

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		///////////////////////////////////////////////////////////////////////////////////
		//OperatorMathFunction//

		void Set(const MatrixBase& _Mat)
		{
			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{
					m[i][j] = _Mat.m[i][j];
				}
			}
		}

		void Set(const T& _Val)
		{
			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{
					m[i][j] = _Val;
				}
			}
		}

		void Add(const MatrixBase& _Mat)
		{
			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{
					m[i][j] += _Mat.m[i][j];
				}
			}
		}

		void Sub(const MatrixBase& _Mat)
		{
			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{
					m[i][j] -= _Mat.m[i][j];
				}
			}
		}

		void Mul(const MatrixBase& _Mat)
		{
			for (unsigned long i = 0; i < Column; i++)
			{
				float Tmp[Column];
				for (unsigned char j = 0; j < Column; j++)
				{
					Tmp[j] = m[i][j];
				}

				for (unsigned char j = 0; j < Column; j++)
				{
					m[i][j] = Tmp[0] * _Mat.m[0][j];

					for (unsigned char k = 1; k < Row; k++)
					{
						m[i][j] += Tmp[k] * _Mat.m[k][j];
					}
				}
			}

		}

		//cŽ²‚ÌŠ|‚¯ŽZ//
		template<unsigned long _Arrarys>
		VectorBase<T, _Arrarys> VerticalMul(const VectorBase<T, _Arrarys> _Vec)const
		{

			unsigned long MaxSize = _Arrarys;

			MaxSize = MaxSize >= Column ? Column : MaxSize;

			VectorBase<T, _Arrarys> Out;

			Out.Set(static_cast<T>(0.0f));

			for (unsigned long i = 0; i < MaxSize; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{
					Out[i] += _Vec[i] * m[i][j];
				}
			}

			return Out;
		}

		//‰¡Ž²‚ÌŠ|‚¯ŽZ//
		template<unsigned long _Arrarys>
		VectorBase<T, _Arrarys>HorizontalMul(const VectorBase<T, _Arrarys> _Vec)const
		{
			unsigned long MaxSize = _Arrarys;

			MaxSize = MaxSize >= Row ? Row : MaxSize;

			VectorBase<T, _Arrarys> Out;

			Out.Set(static_cast<T>(0.0f));

			for (unsigned long i = 0; i < MaxSize; i++)
			{
				for (unsigned long j = 0; j < Column; j++)
				{
					Out[i] += _Vec[i] * m[j][i];
				}
			}

			return Out;

		}

		void Div(const MatrixBase& _Mat)
		{
			MatrixBase TmpMat;
			TmpMat = _Mat;

			TmpMat.Inverse();

			Mul(TmpMat);

		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SerializeDesirialize//

		std::string Serialize(
			const std::string& _CutChar = ","
			, const std::string& _EndChar = ";")
		{
			std::string Tmp = "";
			for (unsigned char i = 0; i < Column; i++)
			{
				for (unsigned char j = 0; j < Row; j++)
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

		std::string SerializeUpper(
			const std::string& _CutChar = ","
			, const std::string& _EndChar = ";"
			, const std::string& _CutTo4Char = "\n")
		{
			std::string Tmp = "";
			for (unsigned char i = 0; i < Column; i++)
			{
				for (unsigned char j = 0; j < Row; j++)
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

			if (EPos == TmpStr.npos)EPos = TmpStr.size() - 1;

			TmpStr = TmpStr.substr(TmpFPos, EPos - TmpFPos);

			TmpStr = ChStr::RemoveToWhiteSpaceChars(TmpStr);

			TmpFPos = 0;

			EPos = TmpStr.length();

			size_t Tmp = TmpFPos;

			for (unsigned char i = 0; i < Column; i++)
			{
				for (unsigned char j = 0; j < Row; j++)
				{
					size_t Test = TmpStr.find(_CutChar, Tmp);

					if (Test > EPos)Test = EPos;

					{
						TmpFPos = Test;

						std::string Num = TmpStr.substr(Tmp, TmpFPos - Tmp);

						m[i][j] = static_cast<T>(std::atof(Num.c_str()));

						Tmp = Test + 1;

					}

					if (Test >= EPos)return;
				}

			}

		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		T GetLen()const
		{
			T Out = static_cast<T>(0.0f);

			for (unsigned long i = 0; i < Column; i++)
			{
				T add = static_cast<T>(1.0f);
				T sub = static_cast<T>(1.0f);

				for (unsigned long j = 0; j < Row; j++)
				{
					if (i == j)continue;

					add *= m[j % Column][(i + j) % Row];
					sub *= m[j % Column][std::abs(i - j) % Row];
				}

				Out = Out + add - sub;

			}

			return Out;
		}

		MatrixBase<T,Row,Column> GetCofactor(const unsigned long _Row, const unsigned long _Col)const
		{
			MatrixBase<T, Row - 1, Column - 1> Out;

			if (_Row >= Row || _Col >= Column)return Out;

			ChStd::Bool ColFlg = false;

			for (unsigned long i = 0; i < Column - 1; i++)
			{
				if (i == _Col)ColFlg = true;

				ChStd::Bool RowFlg = false;

				for (unsigned long j = 0; j < Row - 1; j++)
				{
					if (j == _Row)RowFlg = true;
					Out.m[i][j] = m[ColFlg ? i + 1 : i][RowFlg ? j + 1 : j];
				}
			}
		}

		//s—ñŽ®//
		T GetDeterminant()const
		{
			return GetLen();
		}

		MatrixBase<T, Row, Column> GetInverse()const
		{
			T Len = GetCofactor();

			if (GetLen() == static_cast<T>(0.0f))return;

			MatrixBase<T, Row - 1, Column - 1> TmpDetMat[Row][Column];

			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{

				}
			}
		}

		//ƒhƒD[ƒŠƒgƒ‹–@ãŽOŠps—ñ//
		MatrixBase<T, Row, Column> GetDLUMatrix()const
		{
			MatrixBase<T, Row, Column> LUMat;

			{
				unsigned long MaxNum = (Row > Column) ? Row : Column;

				T Tmp = static_cast<T>(0.0f);

				for (unsigned long i = 0; i < MaxNum; i++)
				{
					Tmp *= m[i % Column][i % Row];
				}

				if (Tmp == 0.0f)return LUMat;
			}

			MatrixBase<T, Row, Column> LMat;
			MatrixBase<T, Row, Column> UMat;

			LMat.Set(static_cast<T>(0.0f));
			UMat.Set(static_cast<T>(0.0f));

			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{
					for (unsigned long k = i; k < Row - 1; k++)
					{
						UMat.m[i][j] += LMat.m[i][k] * UMat.m[k % Column][j];
					}

					UMat.m[i][j] = m[i][j] - UMat.m[i][j];

					for (unsigned long k = j + 1; k < Column - 1; k++)
					{
						LMat.m[i][j] += LMat.m[i][k % Row] * UMat.m[k][j];
					}

					LMat.m[i][j] /= UMat[i][i % Row];
					LMat.m[i][j] = m[i][j] - LMat.m[i][j];
				}
			}
			LUMat.Set(LMat + UMat);
		}

		/*
		//ƒNƒ‰ƒEƒg–@ãŽOŠps—ñ//
		MatrixBase<T, Row, Column> GetLUMatrix()const
		{
			MatrixBase<T, Row, Column> TmpDetMat;

			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{

				}
			}
		}
		*/

		unsigned long GetColumn() { return Column; }

		unsigned long GetRow() { return Row; }

		///////////////////////////////////////////////////////////////////////////////////

		void Identity()
		{

			for (unsigned char i = 0; i < Column; i++)
			{
				for (unsigned char j = 0; j < Row; j++)
				{
					m[i][j] = static_cast<T>(i != j ? 0.0f : 1.0f);
				}
			}

		}

		///////////////////////////////////////////////////////////////////////////////////

		void Inverse()
		{
			Inverse(*this);
		}

		///////////////////////////////////////////////////////////////////////////////////

		void Inverse(const MatrixBase<T, Row, Column>& _Mat)
		{
			T Len = GetCofactor();

			if (GetLen() == static_cast<T>(0.0f))return;

			MatrixBase<T, Row - 1, Column - 1> TmpDetMat[Row][Column];

			for (unsigned long i = 0; i < Column; i++)
			{
				for (unsigned long j = 0; j < Row; j++)
				{

				}
			}
		}

	private:

		VectorBase<MatrixTest<T, Row, Column>, Row> m[Column];

	};



}

#endif
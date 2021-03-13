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

		T& operator [](const unsigned long _Array)
		{
			return Val[_Array % Array];
		}

		T operator [](const unsigned long _Array)const
		{
			return Val[_Array % Array];
		}

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

		VectorBase()
		{
			Identity();
		}

		VectorBase(const T _Val)
		{
			Set(_Val);
		}

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

		VectorTest<T, Array> Val[Array];

	};


	template<typename T, unsigned long Row, unsigned long Column>
	class MatrixBase
	{
	public:

		VectorBase<T, Row>& operator [](const unsigned long _Column)
		{
			return m[_Column % Column];
		}

		VectorBase<T, Row> operator [](const unsigned long _Column)const
		{
			return m[_Column % Column];
		}

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

		MatrixBase()
		{
			Identity();
		}

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

		VectorBase<MatrixTest<T, Row, Column>, Row> m[Column];

	};


	/*
	template<typename T>
	class VectorBase
	{
	public:

		virtual unsigned long GetSize()const = 0;

		virtual T& GetValue(const unsigned long _Array) = 0;
		virtual T GetCValue(const unsigned long _Array)const = 0;
	};

	template<typename T, unsigned long Column,unsigned long Row>
	class MatrixBase
	{
	public:

		virtual unsigned long GetColumn()const = 0;
		virtual unsigned long GetRow()const = 0;

		virtual T& GetValue(const unsigned long _Column,const unsigned long _Row) = 0;
		virtual T GetCValue(const unsigned long _Column, const unsigned long _Row)const = 0;
	};

	*/

	template<typename T>
	struct MatrixValues2x2
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

			MatrixBase<T, 2, 2> m;
		};

		/*
		T& GetValue(const unsigned long _Column, const unsigned long _Row) { return m[_Column][_Row]; };
		T GetCValue(const unsigned long _Column, const unsigned long _Row)const { return m[_Column][_Row]; };

		unsigned long GetColumn()const override { return 2; }
		unsigned long GetRow()const override { return 2; };

		*/
	};

	template<typename T>
	struct MatrixValues3x3 
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
			MatrixBase<T, 3, 3> m;
		};

		/*
		T& GetValue(const unsigned long _Column, const unsigned long _Row) { return m[_Column][_Row]; };
		T GetCValue(const unsigned long _Column, const unsigned long _Row)const { return m[_Column][_Row]; };

		unsigned long GetColumn()const override { return 3; }
		unsigned long GetRow()const override { return 3; };

		*/

	};

	template<typename T>
	struct MatrixValues4x4
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
			MatrixBase<T, 4, 4> m[3][3];
		};

	};

	template<typename T, unsigned long Row, unsigned long Column>
	struct DefMatrix
	{
		MatrixBase<T, Row - 1, Column - 1>Mat;
	};

	template<typename T, unsigned long Row, unsigned long Column>
	std::string Serialize(
		MatrixBase<T, Row, Column>& _Matrix
		, const std::string& _CutChar = ","
		, const std::string& _EndChar = ";")
	{
		std::string Tmp = "";
		for (unsigned char i = 0; i < 4; i++)
		{
			for (unsigned char j = 0; j < 4; j++)
			{
				if (i == 3 && j == 3)break;
				Tmp += std::to_string(_Matrix[i][j]);
				Tmp += _CutChar;
			}
		}

		Tmp += std::to_string(_Matrix[3][3]);
		Tmp += _EndChar;

		return Tmp;
	}

	template<typename T, unsigned long Row, unsigned long Column>
	std::string SerializeUpper(
		MatrixBase<T, Row, Column>& _Matrix
		, const std::string& _CutChar = ","
		, const std::string& _EndChar = ";"
		, const std::string& _CutTo4Char = "\n")
	{

	}

	template<typename T, unsigned long Row, unsigned long Column>
	void Deserialize(
		MatrixBase<T, Row, Column>& _Matrix
		, const std::string& _Str
		, const size_t _FPos = 0
		, const std::string& _CutChar = ","
		, const std::string& _EndChar = ";"
		, const unsigned int _Digit = 6)
	{

	}


	template<typename T, unsigned long Row, unsigned long Column>
	T GetLen(MatrixBase<T, Row, Column>& _Matrix)
	{

	}

	template<typename T, unsigned long Row, unsigned long Column>
	T GetDef(MatrixBase<T, Row, Column>& _Matrix, const int _Row, const int _Col)
	{

	}

	template<typename T, unsigned long Row, unsigned long Column>
	DefMatrix<T, Row, Column> GetDefAll(MatrixBase<T, Row, Column>& _Matrix, const int _Row, const int _Col)
	{

	}

	template<typename T, unsigned long Row, unsigned long Column>
	T GetCofactor(MatrixBase<T, Row, Column>& _Matrix)
	{

	}

	template<typename T, unsigned long Row, unsigned long Column>
	void Identity(MatrixBase<T, Row, Column>& _Matrix)
	{

	}

	template<typename T, unsigned long Row, unsigned long Column>
	void Inverse(MatrixBase<T, Row, Column>& _Matrix)
	{

	}


	struct MatrixBase2x2 :public MatrixValues2x2<float>
	{

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

		///////////////////////////////////////////////////////////////////////////////////

		void Identity()
		{

		}

		///////////////////////////////////////////////////////////////////////////////////

		void Inverse()
		{

		}

	};

	struct MatrixBase3x3 :public MatrixValues3x3<float>
	{

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

		MatrixValues2x2<float> GetDef(const int _Row, const int _Col)const
		{

		}

		float GetCofactor()const
		{

		}

		///////////////////////////////////////////////////////////////////////////////////

		void Identity()
		{

			for (unsigned char i = 0; i < 3; i++)
			{
				for (unsigned char j = 0; j < 3; j++)
				{
					m[i][j] = (i != j ? 0.0f : 1.0f);
				}
			}

		}

		///////////////////////////////////////////////////////////////////////////////////

		void Inverse()
		{

		}

	};

	struct MatrixBase4x4 :public MatrixValues4x4<float>
	{

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

		MatrixValues3x3<float> GetDef(const int _Row, const int _Col)const
		{

		}

		float GetCofactor()const
		{

		}

		///////////////////////////////////////////////////////////////////////////////////

		void Identity()
		{

			//for (unsigned char i = 0; i < 4; i++)
			//{
			//	for (unsigned char j = 0; j < 4; j++)
			//	{
			//		m[i][j] = (i != j ? 0.0f : 1.0f);
			//	}
			//}

		}

		///////////////////////////////////////////////////////////////////////////////////

		//void Inverse()
		//{
		//
		//	ChMath::MatrixBase4x4 TmpMat = *this;
		//	ChMath::MatrixBase4x4 Addl;
		//
		//	float Tmp[24];
		//
		//	unsigned char Count = 0;
		//
		//	//for (unsigned char i = 0; i < 4; i++)
		//	//{
		//	//	for (unsigned char j = 0; j < 4; j++)
		//	//	{
		//	//		for (unsigned char k = 0; k < 4; k++)
		//	//		{
		//	//			for (unsigned char l = 0; l < 4; l++)
		//	//			{
		//
		//	//				if (j != i && j != k && i != k && j != l && i != l && k != l)
		//	//				{
		//	//					Tmp[Count] = m[0][i] * m[1][j] * m[2][k] * m[3][l];
		//
		//	//					Count++;
		//	//				}
		//	//				
		//
		//
		//
		//	//			}
		//	//		}
		//	//	}
		//	//}
		//
		//	for (unsigned char i = 0; i < 4; i++)
		//	{
		//		for (unsigned char j = 0; j < 3; j++)
		//		{
		//			for (unsigned char k = 0; k < 2; k++)
		//			{
		//				Tmp[Count] = m[0][j] *
		//					m[1][j] *
		//					m[2][k] *
		//					m[3][0];
		//
		//				Count++;
		//			}
		//		}
		//	}
		//
		//	float Sum = Tmp[0];
		//	ChStd::Bool Flg = true;
		//
		//	for (unsigned char i = 0; i < 23; i++)
		//	{
		//		Sum = (Flg) ? Sum - Tmp[i + 1] : Sum + Tmp[i + 1];
		//
		//		Flg = (i + 1 % 2 == 0) ? -Flg : Flg;
		//
		//	}
		//
		//	if (Sum == 0.0f)return;
		//
		//}

	};

	//template<typename T>
	//void Set(VectorBase<T>& _Out,const VectorBase<T>& _In )
	//{
	//	unsigned long Min = _In.GetSize() >= _Out.GetSize() ? _Out.GetSize() : _In.GetSize();

	//	for (unsigned long i = 0; i < Min; i++)
	//	{
	//		_Out.GetValue(i) = _In.GetCValue(i);
	//	}

	//}

	//void Set(const T& _Val)
	//{
	//	for (unsigned long i = 0; i < Array; i++)
	//	{
	//		Val[i] = _Val;
	//	}
	//}

	//void Add(const VectorBase& _Vec)
	//{
	//	for (unsigned long i = 0; i < Array; i++)
	//	{
	//		Val[i] += _Vec.Val[i];
	//	}
	//}

	//void Add(const T& _Val)
	//{
	//	for (unsigned long i = 0; i < Array; i++)
	//	{
	//		Val[i] += _Val;
	//	}
	//}

	//void Sub(const VectorBase& _Vec)
	//{
	//	for (unsigned long i = 0; i < Array; i++)
	//	{
	//		Val[i] -= _Vec.Val[i];
	//	}
	//}

	//void Sub(const T& _Val)
	//{
	//	for (unsigned long i = 0; i < Array; i++)
	//	{
	//		Val[i] -= _Val;
	//	}
	//}

	//void Mul(const VectorBase& _Vec)
	//{
	//	for (unsigned long i = 0; i < Array; i++)
	//	{
	//		Val[i] *= _Vec.Val[i];
	//	}
	//}

	//void Mul(const T& _Val)
	//{
	//	for (unsigned long i = 0; i < Array; i++)
	//	{
	//		Val[i] *= _Val;
	//	}
	//}

	//void Div(const VectorBase& _Vec)
	//{
	//	for (unsigned long i = 0; i < Array; i++)
	//	{
	//		Val[i] /= _Vec.Val[i] != static_cast<T>(0.0f) ? _Vec.Val[i] : static_cast<T>(1.0f);
	//	}
	//}

	//void Div(const T& _Val)
	//{
	//	for (unsigned long i = 0; i < Array; i++)
	//	{
	//		Val[i] /= _Val != static_cast<T>(0.0f) ? _Val : static_cast<T>(1.0f);
	//	}
	//}

	/////////////////////////////////////////////////////////////////////////////////////////
	////SerializeDesirialize//

	//std::string Serialize(
	//	const std::string& _CutChar = ","
	//	, const std::string& _EndChar = ";")
	//{

	//	std::string Tmp = "";
	//	for (unsigned char i = 0; i < Array; i++)
	//	{
	//		Tmp += std::to_string(Val[i]);
	//		if (i == (Array - 1))break;
	//		Tmp += _CutChar;
	//	}

	//	Tmp += _EndChar;

	//	return Tmp;
	//}

	//void Deserialize(
	//	const std::string& _Str
	//	, const size_t _FPos = 0
	//	, const std::string& _CutChar = ","
	//	, const std::string& _EndChar = ";"
	//	, const unsigned int _Digit = 6)
	//{

	//	std::string TmpStr = _Str;

	//	size_t TmpFPos = _FPos;

	//	size_t EPos = TmpStr.find(_EndChar, TmpFPos);

	//	if (EPos == TmpStr.npos)EPos = TmpStr.size();

	//	TmpStr = TmpStr.substr(TmpFPos, EPos - TmpFPos);

	//	TmpStr = ChStr::RemoveToWhiteSpaceChars(TmpStr);

	//	TmpFPos = 0;

	//	EPos = TmpStr.length();

	//	size_t Tmp = TmpFPos;

	//	for (unsigned char i = 0; i < Array; i++)
	//	{
	//		size_t Test = TmpStr.find(_CutChar, Tmp);
	//		if (Test > EPos)Test = EPos;
	//		{
	//			TmpFPos = Test;

	//			std::string Num = TmpStr.substr(Tmp, TmpFPos - Tmp);

	//			Val[i] = (float)std::atof(Num.c_str());

	//			//					Val[i] = ChMath::Round(Val[i], _Digit);

	//			Tmp += Num.length();
	//			Tmp += 1;

	//		}

	//		if (Test >= EPos)return;
	//	}

	//}

	/////////////////////////////////////////////////////////////////////////////////////
	////GetFunction//

	//float GetLen()const
	//{
	//	T Len = static_cast<T>(0.0f);

	//	for (unsigned long i = 0; i < Array; i++)
	//	{
	//		Len += std::abs(Val[i]);
	//	}

	//	return Len;

	//}

	//float GetCos(
	//	const VectorBase& _Vec)const
	//{

	//	if (GetLen() <= 0.0f || _Vec.GetLen() <= 0.0f)return 0.0f;

	//	VectorBase Tmp1, Tmp2;

	//	Tmp1 = *this;
	//	Tmp2 = _Vec;

	//	Tmp1.Normalize();
	//	Tmp2.Normalize();

	//	float Cos = 0.0f;

	//	for (unsigned char i = 0; i < 4; i++)
	//	{
	//		Cos += (Tmp1.Val[i] * Tmp2.Val[i]);
	//	}

	//	return Cos;
	//}

	//float GetRadian(
	//	const VectorBase& _Vec)const
	//{

	//	if (GetLen() <= 0.0f || _Vec.GetLen() <= 0.0f)return 0.0f;

	//	return std::acos(GetCos(_Vec, *this));
	//}

	//float GetDot(
	//	const VectorBase& _Vec)const
	//{

	//	if (GetLen() <= 0.0f || _Vec.GetLen() <= 0.0f)return 0.0f;

	//	float TmpLen = 0.0f;

	//	for (unsigned long i = 0; i < Array; i++)
	//	{
	//		TmpLen += Val[i] * _Vec.Val[i];
	//	}

	//	return TmpLen;

	//}

	/////////////////////////////////////////////////////////////////////////////////////

	//inline void Abs()
	//{
	//	for (unsigned long i = 0; i < Array; i++)
	//	{
	//		Val[i] = Val[i] < 0.0f ? Val[i] * -1.0f : Val[i];
	//	}
	//}

	//inline void Abs(const VectorBase& _Vec)
	//{

	//	for (unsigned long i = 0; i < Array; i++)
	//	{
	//		Val[i] = _Vec.Val[i] < 0.0f ? _Vec.Val[i] * -1.0f : _Vec.Val[i];
	//	}
	//}
	/////////////////////////////////////////////////////////////////////////////////////

	//void Cross(
	//	const VectorBase& _Vec)
	//{

	//	VectorBase TmpVec;

	//	TmpVec = *this;

	//	for (unsigned char i = 0; i < 4; i++)
	//	{
	//		Val[i] =
	//			(TmpVec.Val[(i + 1) % 4] * _Vec.Val[(i + 2) % 4])
	//			- (TmpVec.Val[(i + 2) % 4] * _Vec.Val[(i + 1) % 4]);
	//	}

	//	Normalize();

	//	return;

	//}

	//void Cross(
	//	const VectorBase& _Vec1, const VectorBase& _Vec2)
	//{

	//	for (unsigned char i = 0; i < 4; i++)
	//	{
	//		Val[i] =
	//			(_Vec1.Val[(i + 1) % 4] * _Vec2.Val[(i + 2) % 4])
	//			- (_Vec1.Val[(i + 2) % 4] * _Vec2.Val[(i + 1) % 4]);
	//	}

	//	Normalize();

	//	return;
	//}

	/////////////////////////////////////////////////////////////////////////////////////

	////•â³‚ðs‚¤(Now‚Í0`1)
	//void Correction(
	//	const VectorBase& _Start, const VectorBase& _End, const float _Now)
	//{
	//	if (_Now <= 0.0f)
	//	{
	//		return;
	//	}

	//	if (_Now >= 1.0f)
	//	{
	//		return;
	//	}

	//	VectorBase TmpVec;

	//	TmpVec = _End - _Start;

	//	TmpVec = _Start + (TmpVec * _Now);


	//}


	/////////////////////////////////////////////////////////////////////////////////////

	//void Identity()
	//{
	//	for (unsigned long i = 0; i < Array; i++)
	//	{
	//		Val[i] = static_cast<T>(i != 3 ? 0.0f : 1.0f);
	//	}
	//}

	/////////////////////////////////////////////////////////////////////////////////////

	//void Normalize()
	//{

	//	T Len = GetLen();

	//	if (Len == static_cast<T>(0.0f))return;

	//	for (unsigned long i = 0; i < Array; i++)
	//	{
	//		Val[i] /= Len;
	//	}
	//}


}

#endif
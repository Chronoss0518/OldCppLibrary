#ifndef Ch_CPP_Std_h
#define Ch_CPP_Std_h

#ifndef _INC_STDLIB
#include<cstdlib>
#endif

#ifndef _STRING_
#include<string>
#endif

#ifndef _VCRUNTIME_H
#ifdef _WIN64

using size_t = unsigned long long;

#elif

using size_t = unsigned int;

#endif

#endif

//ChLibraryのベースとなる関数、変数群のまとまり//
namespace ChStd
{

	//Xファイルなど多くのオブジェクトを利用する際に識別子として利用する。//
	using DataNo = unsigned short;

	//通常のbool型より1～3Byte軽くしたもの//
	//現在ではbool = 1Byteの可能性あり//
	using Bool = unsigned char;

	static const Bool True = true;
	static const Bool False = false;

#ifdef _WIN32
	
	//Windowsで使用される相対パス・絶対パスの最大文字数//
	static const unsigned short W_MaxPathLen = 258;

#endif

	struct COLOR255;
	struct COLOR1f;

	///////////////////////////////////////////////////////////////////////////////////////
	//MyAddStruct
	///////////////////////////////////////////////////////////////////////////////////////

	//Windows内で定義されているPOINTのfloat版//
	struct FPOINT
	{

		inline FPOINT& operator =(const FPOINT _Pos)
		{
			x = _Pos.x;
			y = _Pos.y;
			return *this;
		}

		inline FPOINT& operator +=(const FPOINT _Pos)
		{
			x += _Pos.x;
			y += _Pos.y;
			return *this;
		}

		inline FPOINT& operator -=(const FPOINT _Pos)
		{
			x -= _Pos.x;
			y -= _Pos.y;
			return *this;
		}

		inline FPOINT& operator *=(const FPOINT _Pos)
		{
			x *= _Pos.x;
			y *= _Pos.y;
			return *this;
		}

		inline FPOINT& operator /=(const FPOINT _Pos)
		{
			if (_Pos.x != 0.0f)x /= _Pos.x;
			if (_Pos.y != 0.0f)y /= _Pos.y;
			return *this;
		}

		inline FPOINT operator +(const FPOINT _Pos)const
		{
			FPOINT Tmp = *this;
			Tmp += _Pos;
			return Tmp;
		}

		inline FPOINT operator -(const FPOINT _Pos)const
		{
			FPOINT Tmp = *this;

			Tmp -= _Pos;
			return Tmp;
		}

		inline FPOINT operator *(const FPOINT _Pos)const
		{
			FPOINT Tmp = *this;

			Tmp *= _Pos;
			return Tmp;
		}

		inline FPOINT operator /(const FPOINT _Pos)const
		{
			FPOINT Tmp = *this;

			Tmp /= _Pos;
			return Tmp;
		}

		inline FPOINT operator =(const float _Num)const
		{
			FPOINT Tmp = *this;

			Tmp.x = _Num;
			Tmp.y = _Num;
			return Tmp;
		}

		inline FPOINT operator + (const float _Num)const
		{
			FPOINT Tmp = *this;

			Tmp.x += _Num;
			Tmp.y += _Num;
			return Tmp;
		}

		inline FPOINT operator - (const float _Num)const
		{
			FPOINT Tmp = *this;

			Tmp.x -= _Num;
			Tmp.y -= _Num;
			return Tmp;
		}

		inline FPOINT operator * (const float _Num)const
		{
			FPOINT Tmp = *this;

			Tmp.x *= _Num;
			Tmp.y *= _Num;
			return Tmp;
		}

		inline FPOINT operator /=(const float _Num)const
		{
			FPOINT Tmp = *this;

			if (_Num == 0.0f)return Tmp;
			Tmp.x /= _Num;
			Tmp.y /= _Num;
			return Tmp;
		}

		inline FPOINT() { x = y = 0.0f; };

		inline FPOINT(const float _x, const float _y)
		{
			x = _x;
			y = _y;
		};

		union
		{
			struct { float x, y; };
			struct { float w, h; };
		};


	};

	///////////////////////////////////////////////////////////////////////////////////

	//Windows内で定義されているRECTのfloat版//
	struct FRECT
	{
		inline FRECT() { x = y = w = h = 0.0f; }

		inline FRECT(
			const float _x
			, const float _y
			, const float _w
			, const float _h)
		{
			x = _x;
			y = _y;
			w = _w;
			h = _h;
		}

		float x;
		float y;
		float w;
		float h;
	};

	///////////////////////////////////////////////////////////////////////////////////

	struct COLOR1f;
	struct COLOR255;

	//色を定義する際に使用される変数。基本的に最大数値は1.0f//
	//最低数値は固定で0.0f//
	struct COLOR1f
	{
		inline COLOR1f& operator= (const float _Num)
		{
			a = r = g = b = _Num;
			return *this;
		}

		inline COLOR1f& operator=(const COLOR255&);

		inline COLOR1f& operator= (const COLOR1f& _Col)
		{
			a = _Col.a;
			r = _Col.r;
			g = _Col.g;
			b = _Col.b;
			return *this;
		}

		inline COLOR1f() { a = r = g = b = 0.0f; };

		inline COLOR1f(
			const float _a
			, const float _r
			, const float _g
			, const float _b)
		{
			a = _a;
			r = _r;
			g = _g;
			b = _b;
		}

		inline COLOR1f(
			const float _Num)
		{
			a = r = g = b = _Num;
		}

		float r;
		float g;
		float b;
		float a;
	};

	///////////////////////////////////////////////////////////////////////////////////

	//色を定義する際に使用される変数。基本的に最大数値は255//
	//最低数値は固定で0//
	struct COLOR255
	{
		inline COLOR255& operator= (const unsigned char _Num)
		{
			a = r = g = b = _Num;
			return *this;
		}

		inline COLOR255& operator=(const COLOR1f&);

		inline COLOR255& operator= (const COLOR255& _Col)
		{
			a = _Col.a;
			r = _Col.r;
			g = _Col.g;
			b = _Col.b;
			return *this;
		}

		inline COLOR255() { a = r = g = b = 0; };

		inline COLOR255(
			const unsigned char _a
			, const unsigned char _r
			, const unsigned char _g
			, const unsigned char _b)
		{
			a = _a;
			r = _r;
			g = _g;
			b = _b;
		}

		inline COLOR255(
			const unsigned char _Num)
		{
			a = r = g = b = _Num;
		}

		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;

	};

	inline COLOR1f& COLOR1f::operator=(const COLOR255& _Col)
	{

		a = static_cast<unsigned char>(_Col.a / 255.0f);
		r = static_cast<unsigned char>(_Col.r / 255.0f);
		g = static_cast<unsigned char>(_Col.g / 255.0f);
		b = static_cast<unsigned char>(_Col.b / 255.0f);

		return *this;

	}

	inline COLOR255& COLOR255::operator=(const COLOR1f& _Col)
	{

		a = static_cast<unsigned char>(_Col.a * 255.0f);
		r = static_cast<unsigned char>(_Col.r * 255.0f);
		g = static_cast<unsigned char>(_Col.g * 255.0f);
		b = static_cast<unsigned char>(_Col.b * 255.0f);

		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	//AllFunction
	///////////////////////////////////////////////////////////////////////////////////////

	const static unsigned char MaxCharBit = 0x80;
	const static unsigned short MaxShortBit = 0x8000;
	const static unsigned long MaxLongBit = 0x80000000;
	const static unsigned long long MaxLLongBit = 0x8000000000000000;

#ifdef _WIN32
	const static unsigned int W_MaxIntBit = 0x80000000;
#else
	const static unsigned int W_MaxIntBit = 0x8000;
#endif

	//開始時に使用し、ランダムな値をセットする//
	static inline void SetRand(const unsigned long _UseNo) { srand(_UseNo); }

	//SetRand使用後rand関数から値を取り出す//
	static inline unsigned short GetRand(const unsigned short _Max)
	{
		return rand() % _Max;
	}

	//文字列をバイナリデータにして//
	//整数型に変換する//
	template<typename T>
	static inline void StrBinaryToNum(
		T &_SetData
		, const std::string& _Str
		, const size_t& _SPos = 0)
	{
		_SetData = 0;
		for (unsigned char i = 0; i < sizeof(T); i++)
		{
			unsigned char Test = _Str[_SPos + i];
			if (Test <= 0)continue;
			_SetData += (T)(Test << 8 * ((sizeof(T) - 1) - i));
		}

	}

	//クラス名を取得する関数//
	template<class T = int>
	static inline std::string GetTypeName()
	{
		std::string TmpStr = typeid(T).name();


		size_t Tmp = TmpStr.find(" ");
		if (Tmp == std::string::npos)Tmp = 0;
		else Tmp += 1;

		return &TmpStr[Tmp];
	}

	//EnumClassを基底型へキャストするためのクラス//
	template<typename Enum>
	static inline auto EnumCast(Enum _Enum)->typename std::enable_if
		<std::is_enum<Enum>::value, typename std::underlying_type< Enum >::type>::type
	{
		return static_cast<typename std::underlying_type<Enum>::type>(_Enum);
	}

	template<typename Enum>
	static inline auto EnumCast(Enum _Enum)->typename std::enable_if
		<!std::is_enum<Enum>::value, int>::type
	{
		return 0;
	}

	//指定したアドレス先を値0で初期化する//
	template<class T>
	static inline void All0Memory(T* _Val)
	{
		void* Tmp = static_cast<void*>(_Val);

		for (unsigned long i = 0; i < sizeof(T); i++)
		{
			* (static_cast<char*>(Tmp) + i) = 0;
		}
	}

	static inline std::string StrReplase(
		const std::string& _Base
		, const std::string _Before
		, const std::string _After = ""
	)
	{
		if (_Base.find(_Before) == _Base.npos)return _Base;

		std::string Out = "";

		size_t TmpPos = 0;
		size_t TestPos = 0;

		while (true)
		{
			TestPos = _Base.find(_Before, TmpPos);

			if (TestPos == _Base.npos)break;
			
			Out += _Base.substr(TmpPos, TestPos - TmpPos);

			Out += _After;

			TmpPos = TestPos + _Before.length();

		}

		return Out;
	}

	static inline char* RemoveToWhiteSpaceChars(const char const* _Str)
	{

		char* str = nullptr;

		char* Tmp = (char*)malloc(sizeof(char) * LONG_MAX);

		unsigned long Count = 0;

		const char WhiteSpaceInterfaceChar = 32;
		const char DelCharNum = 127;

		for (unsigned long i = 0; i < std::strlen(_Str); i++)
		{
			Count = std::strlen(Tmp);
			if (_Str[i] < WhiteSpaceInterfaceChar)continue;
			if (_Str[i] == DelCharNum)continue;

			Tmp[Count] = _Str[i];

		}

		std::strcpy(str, Tmp);

		std::free(Tmp);

		return str;
	}
	
}

#endif
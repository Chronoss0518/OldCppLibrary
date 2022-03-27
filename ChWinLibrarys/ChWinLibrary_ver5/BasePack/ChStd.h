#ifndef Ch_CPP_Std_h
#define Ch_CPP_Std_h

//ChLibraryのベースとなる関数、変数群のまとまり//
namespace ChStd
{

	//Xファイルなど多くのオブジェクトを利用する際に識別子として利用する。//
	using DataNo = unsigned short;

	//通常のbool型より1～3Byte軽くしたもの//
	//現在ではbool = 1Byte//
	//ビット演算子も利用できるためこちらは残しておく//
	using Bool = unsigned char;

#ifdef _WIN32
	
	//Windowsで使用される相対パス・絶対パスの最大文字数//
	static const unsigned short W_MAX_PATH_LEN = 258;

#elif _WIN64

	//Windowsで使用される相対パス・絶対パスの最大文字数//
	static const unsigned short W_MAX_PATH_LEN = 258;

#endif

	///////////////////////////////////////////////////////////////////////////////////////
	//StanderdFunction
	///////////////////////////////////////////////////////////////////////////////////////

	const static unsigned char MAX_CHAR_BIT = 0x80;
	const static unsigned short MAX_SHORT_BIT = 0x8000;
	const static unsigned long MAX_LONG_BIT = 0x80000000;
	const static unsigned long long MAX_LLONG_BIT = 0x8000000000000000;

#ifdef _WIN64
	const static unsigned int W_MAX_INT_BIT = MAX_LONG_BIT;
#else
	const static unsigned int W_MAX_INT_BIT = MAX_SHORT_BIT;
#endif

	//EnumClassを基底型へキャストするためのクラス//
	template<typename Enum>
	static inline auto EnumCast(Enum _enum)->typename std::enable_if
		<std::is_enum<Enum>::value, typename std::underlying_type< Enum >::type>::type
	{
		return static_cast<typename std::underlying_type<Enum>::type>(_enum);
	}

	//指定したアドレス先を値0で初期化する//
	template<class T>
	static inline void MZero(T* _val)
	{
		void* tmp = static_cast<void*>(_val);

		for (unsigned long i = 0; i < sizeof(T); i++)
		{
			*(static_cast<char*>(tmp) + i) = 0;
		}
	}

	//指定したアドレス先を値0で初期化する//
	template<class T>
	static inline void MCopy(T* _copy, const T* _base)
	{
		void* tmpCopy = static_cast<void*>(_copy);
		const void* tmpBase = static_cast<const void*>(_base);

		for (unsigned long i = 0; i < sizeof(T); i++)
		{
			*(static_cast<char*>(tmpCopy) + i) = *(static_cast<char*>(tmpBase) + i);
		}
	}

	template<typename Type>
	static inline Type BinaryToNumWithLittleEndian(const std::vector<char>& _binary, unsigned long _filePos = 0)
	{

		Type Num = 0;

		if (_filePos + sizeof(Type) >= _binary.size())return Num;

		void* tmp = &Num;

		for (unsigned long i = 0; i < sizeof(Type); i++)
		{
			auto& test = reinterpret_cast<char*>(tmp)[i];

			test = (_binary[i + _filePos]);
		}

		return Num;

	}

	template<typename Type>
	static inline Type BinaryToNumWithBigEndian(const std::vector<char>& _binary, unsigned long _filePos = 0)
	{

		Type Num = 0;

		if (_filePos + sizeof(Type) >= _binary.size())return Num;

		void* tmp = &Num;

		for (unsigned long i = sizeof(Type) - 1; i >= 0; i--)
		{
			auto& test = reinterpret_cast<char*>(tmp)[sizeof(Type) - i - 1];

			test = (_binary[i + _filePos]);

			if (i == 0)break;
		}

		return Num;

	}

}

#endif
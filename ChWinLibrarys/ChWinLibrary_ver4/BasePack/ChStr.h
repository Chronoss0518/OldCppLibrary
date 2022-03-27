#ifndef Ch_CPP_Str_h
#define Ch_CPP_Str_h

namespace ChStr
{

	//文字列をバイナリデータにして//
	//整数型に変換する//
	template<typename T>
	static inline void StrBinaryToNum(
		T& _SetData
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

	static inline std::string RemoveToWhiteSpaceChars(const std::string& _Str)
	{

		std::string Tmp = "";

		unsigned long Count = 0;

		const char WhiteSpaceInterfaceChar = 32;
		const char DelCharNum = 127;

		for (unsigned long i = 0; i < _Str.length(); i++)
		{
			Count = Tmp.length();
			if (_Str[i] <= WhiteSpaceInterfaceChar)continue;
			if (_Str[i] == DelCharNum)continue;

			Tmp = Tmp + _Str[i];

		}

		std::string str;

		str = Tmp;


		return str;
	}

	static inline std::wstring RemoveToWhiteSpaceChars(const std::wstring& _Str)
	{

		std::wstring Tmp = L"";

		unsigned long Count = 0;

		const char WhiteSpaceInterfaceChar = 32;
		const char DelCharNum = 127;

		for (unsigned long i = 0; i < _Str.length(); i++)
		{
			Count = Tmp.length();
			if (_Str[i] < WhiteSpaceInterfaceChar)continue;
			if (_Str[i] == DelCharNum)continue;

			Tmp = Tmp + _Str[i];

		}

		std::wstring str;

		str = Tmp;


		return str;
	}

	static inline std::string RemoveToChars(const std::string& _Str, const char _RempveChars)
	{

		std::string Tmp = "";

		unsigned long Count = 0;

		const char WhiteSpaceInterfaceChar = 32;
		const char DelCharNum = 127;

		for (unsigned long i = 0; i < _Str.length(); i++)
		{
			Count = Tmp.length();
			if (_Str[i] == _RempveChars)continue;

			Tmp = Tmp + _Str[i];

		}

		std::string str;

		str = Tmp;


		return str;
	}

	static inline std::wstring RemoveToChars(const std::wstring& _Str, const wchar_t _RempveChars)
	{

		std::wstring Tmp = L"";

		unsigned long Count = 0;

		const char WhiteSpaceInterfaceChar = 32;
		const char DelCharNum = 127;

		for (unsigned long i = 0; i < _Str.length(); i++)
		{
			Count = Tmp.length();
			if (_Str[i] == _RempveChars)continue;

			Tmp = Tmp + _Str[i];

		}

		std::wstring str;

		str = Tmp;

		return str;
	}

	static inline std::string GetCharsToRangeCode(
		const std::string& _Str
		, const char _Min
		, const char _Max)
	{

		std::string Tmp = "";

		unsigned long Count = 0;

		const char WhiteSpaceInterfaceChar = 32;
		const char DelCharNum = 127;

		for (unsigned long i = 0; i < _Str.length(); i++)
		{
			Count = Tmp.length();
			if (_Str[i] > _Max || _Str[i] < _Min)continue;

			Tmp = Tmp + _Str[i];

		}

		std::string str;

		str = Tmp;


		return str;
	}

	static inline std::wstring GetCharsToRangeCode(
		const std::wstring& _Str
		, const wchar_t _Min
		, const wchar_t _Max)
	{

		std::wstring Tmp = L"";

		unsigned long Count = 0;

		const char WhiteSpaceInterfaceChar = 32;
		const char DelCharNum = 127;

		for (unsigned long i = 0; i < _Str.length(); i++)
		{
			Count = Tmp.length();
			if (_Str[i] > _Max || _Str[i] < _Min)continue;

			Tmp = Tmp + _Str[i];

		}

		std::wstring str;

		str = Tmp;

		return str;
	}

	template<typename BaseType>
	inline auto GetIntegialFromText(
		const std::string& _Text
		, const size_t& _StartPos = 0
		, const size_t& _EndPos = std::string::npos)
		->typename std::enable_if<
		std::is_integral<BaseType>::value
		&& !std::is_same<bool, BaseType>::value, BaseType>::type

	{
		size_t EndPos = _EndPos;

		if (_Text.size() <= EndPos)
		{
			EndPos = _Text.size();
		}

		std::string UseText = _Text.substr(_StartPos, EndPos - _StartPos);

		UseText = GetCharsToRangeCode(UseText, 0x30, 0x40);

		long long Tmp = std::atoll(UseText.c_str());

		return static_cast<BaseType>(Tmp);

	}

	template<typename BaseType>
	inline auto GetFloatingFromText(
		const std::string& _Text
		, const size_t& _StartPos = 0
		, const size_t& _EndPos = std::string::npos)
		->typename std::enable_if<
		std::is_floating_point<BaseType>::value, BaseType>::type

	{
		size_t EndPos = _EndPos;

		if (_Text.size() <= EndPos)
		{
			EndPos = _Text.size();
		}

		std::string UseText = _Text.substr(_StartPos, EndPos - _StartPos);

		UseText = GetCharsToRangeCode(UseText, 0x30, 0x40);

		double Tmp = std::atof(UseText.c_str());

		return static_cast<BaseType>(Tmp);

	}

	template<typename BaseType>
	inline auto GetIntegialFromText(
		const std::wstring& _Text
		, const size_t& _StartPos = 0
		, const size_t& _EndPos = std::string::npos)
		->typename std::enable_if<
		std::is_integral<BaseType>::value
		&& !std::is_same<bool, BaseType>::value, BaseType>::type

	{
		size_t EndPos = _EndPos;

		if (_Text.size() <= EndPos)
		{
			EndPos = _Text.size();
		}

		std::string UseText = _Text.substr(_StartPos, EndPos - _StartPos);

		UseText = GetCharsToRangeCode(UseText, 0x30, 0x40);

		long long Tmp = std::atoll(UseText.c_str());

		return static_cast<BaseType>(Tmp);

	}

	template<typename BaseType>
	inline auto GetFloatingFromText(
		const std::wstring& _Text
		, const size_t& _StartPos = 0
		, const size_t& _EndPos = std::wstring::npos)
		->typename std::enable_if<
		std::is_floating_point<BaseType>::value, BaseType>::type

	{
		size_t EndPos = _EndPos;

		if (_Text.size() <= EndPos)
		{
			EndPos = _Text.size();
		}

		std::string UseText = _Text.substr(_StartPos, EndPos - _StartPos);

		UseText = GetCharsToRangeCode(UseText, 0x30, 0x40);

		double Tmp = std::atof(UseText.c_str());

		return static_cast<BaseType>(Tmp);

	}


	using convert_t = std::codecvt_utf8<wchar_t>;

	static std::wstring_convert<convert_t, wchar_t> strconverter;

	inline std::wstring ToWString(const std::string _Str)
	{
		return strconverter.from_bytes(_Str);
	}

	inline std::string ToString(const std::wstring _Str)
	{
		return strconverter.to_bytes(_Str);
	}

	///////////////////////////////////////////////////////////////////////////////////////
	//StanderdClass
	///////////////////////////////////////////////////////////////////////////////////////

	class StringObject
	{
	public:

		StringObject& operator = (const char* _Str);
		StringObject& operator = (const wchar_t* _Str);
		StringObject& operator = (const std::string& _Str);
		StringObject& operator = (const std::wstring& _Str);
		StringObject& operator = (const StringObject _Str);

		StringObject& operator +=(const char* _Str);
		StringObject& operator +=(const wchar_t* _Str);
		StringObject& operator +=(const std::string& _Str);
		StringObject& operator +=(const std::wstring& _Str);
		StringObject& operator +=(const StringObject& _Str);

		StringObject& operator -=(const char* _Str);
		StringObject& operator -=(const wchar_t* _Str);
		StringObject& operator -=(const std::string& _Str);
		StringObject& operator -=(const std::wstring& _Str);
		StringObject& operator -=(const StringObject& _Str);

		operator const char* const()const;
		operator const wchar_t* const()const;
		operator const unsigned long()const;

		StringObject();
		StringObject(const StringObject& _Str);
		StringObject(const char* _Str);
		StringObject(const wchar_t* _Str);
		StringObject(const std::string& _Str);
		StringObject(const std::wstring& _Str);

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		~StringObject() { textFree(); }

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline size_t Length()const
		{
			return length;
		}

	protected:

		///////////////////////////////////////////////////////////////////////////////////

		void textFree();

		///////////////////////////////////////////////////////////////////////////////////

		void setString(const char* _Str);
		void setString(const wchar_t* _Str);

		void addString(const char* _Str);
		void addString(const wchar_t* _Str);

		void decString(const char* _Str);
		void decString(const wchar_t* _Str);

		///////////////////////////////////////////////////////////////////////////////////


	private:

		wchar_t* text = nullptr;
		unsigned long length = 0;
	};


	using String = StringObject;
}


#endif
#ifndef Ch_CPP_Str_h
#define Ch_CPP_Str_h

namespace ChStr
{

	///////////////////////////////////////////////////////////////////////////////////

	//文字列をバイナリデータにして//
	//整数型に変換する//
	template<typename T>
	static inline void StrBinaryToNum(
		T& _setData
		, const char* const _str
		, const size_t& _sPos = 0)
	{
		_setData = 0;
		for (unsigned char i = 0; i < sizeof(T); i++)
		{
			if (_str[_sPos + i] == '\0')break;

			unsigned char Test = _str[_sPos + i];
			if (Test <= 0)continue;
			_setData += (T)(Test << 8 * ((sizeof(T) - 1) - i));
		}

	}

	///////////////////////////////////////////////////////////////////////////////////

	//クラス名を取得する関数//
	template<class T = int>
	static inline std::string GetTypeName()
	{
		std::string tmpStr = typeid(T).name();


		size_t tmp = tmpStr.find(" ");
		if (tmp == std::string::npos)tmp = 0;
		else tmp += 1;

		return &tmpStr[tmp];
	}

	///////////////////////////////////////////////////////////////////////////////////

	//文字の置き換え//
	std::string StrReplase(
		const std::string& _base
		, const std::string _before
		, const std::string _after = "");

	///////////////////////////////////////////////////////////////////////////////////

	//空文字を取り除く//
	std::string RemoveToWhiteSpaceChars(const std::string& _str);

	//空文字を取り除く//
	std::wstring RemoveToWhiteSpaceChars(const std::wstring& _str);

	///////////////////////////////////////////////////////////////////////////////////

	//指定した文字を取り除く//
	std::string RemoveToChars(const std::string& _str, const char _rempveChars);

	//指定した文字を取り除く//
	std::wstring RemoveToChars(const std::wstring& _str, const wchar_t _rempveChars);

	///////////////////////////////////////////////////////////////////////////////////

	//数値に変換可能な文字以外の文字を取り除く//
	std::string RemoveToUnNums(const std::string& _str);

	//数値に変換可能な文字以外の文字を取り除く//
	std::wstring RemoveToUnNums(const std::wstring& _str);

	///////////////////////////////////////////////////////////////////////////////////

	//指定されたコード値の範囲の文字のみを返す//
	std::string GetCharsToRangeCode(
		const std::string& _str
		, const char _min
		, const char _max);

	//指定されたコード値の範囲の文字のみを返す//
	std::wstring GetCharsToRangeCode(
		const std::wstring& _str
		, const wchar_t _min
		, const wchar_t _max);

	///////////////////////////////////////////////////////////////////////////////////

	template<typename BaseType>
	inline auto GetIntegialFromText(
		const std::string& _text
		, const size_t& _startPos = 0
		, const size_t& _endPos = std::string::npos)
		->typename std::enable_if<
		std::is_integral<BaseType>::value
		&& !std::is_same<bool, BaseType>::value, BaseType>::type

	{
		size_t endPos = _endPos;

		if (_text.size() <= endPos)
		{
			endPos = _text.size();
		}

		std::string useText = _text.substr(_startPos, endPos - _startPos);

		useText = RemoveToUnNums(useText);

		long long tmp = std::atoll(useText.c_str());

		return static_cast<BaseType>(tmp);

	}

	///////////////////////////////////////////////////////////////////////////////////

	template<typename BaseType>
	inline auto GetFloatingFromText(
		const std::string& _text
		, const size_t& _startPos = 0
		, const size_t& _endPos = std::string::npos)
		->typename std::enable_if<
		std::is_floating_point<BaseType>::value, BaseType>::type

	{
		size_t endPos = _endPos;

		if (_text.size() <= endPos)
		{
			endPos = _text.size();
		}

		std::string useText = _text.substr(_startPos, endPos - _startPos);

		useText = RemoveToUnNums(useText);

		double tmp = std::atof(useText.c_str());

		return static_cast<BaseType>(tmp);
	}

	///////////////////////////////////////////////////////////////////////////////////

	template<typename BaseType>
	inline auto GetIntegialFromText(
		const std::wstring& _text
		, const size_t& _startPos = 0
		, const size_t& _endPos = std::string::npos)
		->typename std::enable_if<
		std::is_integral<BaseType>::value
		&& !std::is_same<bool, BaseType>::value, BaseType>::type

	{


		size_t endPos = _endPos;

		if (_text.size() <= endPos)
		{
			endPos = _text.size();
		}

		std::wstring useText = _text.substr(_startPos, endPos - _startPos);

		useText = RemoveToUnNums(useText);

		long long tmp = std::atoll(useText.c_str());

		return static_cast<BaseType>(tmp);
	}

	///////////////////////////////////////////////////////////////////////////////////

	template<typename BaseType>
	inline auto GetFloatingFromText(
		const std::wstring& _text
		, const size_t& _startPos = 0
		, const size_t& _endPos = std::wstring::npos)
		->typename std::enable_if<
		std::is_floating_point<BaseType>::value, BaseType>::type

	{
		size_t endPos = _endPos;

		if (_text.size() <= endPos)
		{
			endPos = _text.size();
		}

		std::wstring useText = _text.substr(_startPos, endPos - _startPos);

		useText = RemoveToUnNums(useText);

		double tmp = std::atof(useText.c_str());

		return static_cast<BaseType>(tmp);

	}

	using ConvertUTF8 = std::codecvt_utf8<wchar_t>;
	using ConvertUTF16 = std::codecvt_utf16<wchar_t>;

	//文字列からUTF8のワイド文字列へ変換する//
	std::wstring UTF8ToWString(const std::string& _str);

	//ワイド文字列から文字列へ変換する//
	std::string UTF8ToString(const std::wstring& _str);

	//文字列からUTF16のワイド文字列へ変換する//
	std::wstring UTF16ToWString(const std::string& _str);

	//ワイド文字列から文字列へ変換する//
	std::string UTF16ToString(const std::wstring& _str);

}


#endif
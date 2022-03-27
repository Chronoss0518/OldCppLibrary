
#include<cstdlib>
#include<cstring>
#include<wchar.h>
#include"../BaseIncluder/ChBase.h"
#include"ChStr.h"

namespace ChStr
{

	//文字の置き換え//
	std::string StrReplase(
		const std::string& _base
		, const std::string _before
		, const std::string _after
	)
	{
		if (_base.find(_before) == _base.npos)return _base;

		std::string out = "";

		size_t tmpPos = 0;
		size_t testPos = 0;

		while (true)
		{
			testPos = _base.find(_before, tmpPos);

			if (testPos == _base.npos)break;

			out += _base.substr(tmpPos, testPos - tmpPos);

			out += _after;

			tmpPos = testPos + _before.length();

		}

		return out;
	}

	std::string RemoveToWhiteSpaceChars(const std::string& _str)
	{

		std::string out = "";

		const char WhiteSpaceInterfaceChar = 32;
		const char DelCharNum = 127;

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			if (_str[i] <= WhiteSpaceInterfaceChar)continue;
			if (_str[i] == DelCharNum)continue;

			out = out + _str[i];

		}

		return out;
	}

	static inline std::wstring RemoveToWhiteSpaceChars(const std::wstring& _str)
	{

		std::wstring out = L"";

		const char WhiteSpaceInterfaceChar = 32;
		const char DelCharNum = 127;

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			if (_str[i] < WhiteSpaceInterfaceChar)continue;
			if (_str[i] == DelCharNum)continue;

			out = out + _str[i];

		}

		return out;
	}

	std::string RemoveToChars(const std::string& _str, const char _rempveChars)
	{

		std::string out = "";

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			if (_str[i] == _rempveChars)continue;

			out = out + _str[i];

		}

		return out;
	}

	std::wstring RemoveToChars(const std::wstring& _str, const wchar_t _rempveChars)
	{

		std::wstring out = L"";

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			if (_str[i] == _rempveChars)continue;

			out = out + _str[i];

		}

		return out;
	}

	std::string RemoveToUnNums(const std::string& _str)
	{

		std::string out = "";

		const char StartNum = '0';
		const char EndNum = '9';

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			ChStd::Bool ConFlg = false;

			if (_str[i] < StartNum)ConFlg = true;
			if (_str[i] > EndNum)ConFlg = true;

			if (_str[i] == '.')ConFlg = false;
			if (_str[i] == '-')ConFlg = false;

			if (ConFlg)continue;

			out = out + _str[i];

		}

		return out;
	}

	std::wstring RemoveToUnNums(const std::wstring& _str)
	{

		std::wstring out = L"";

		const wchar_t StartNum = L'0';
		const wchar_t EndNum = L'9';

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			ChStd::Bool conFlg = false;

			if (_str[i] < StartNum)conFlg = true;
			if (_str[i] > EndNum)conFlg = true;

			if (_str[i] == L'.')conFlg = false;
			if (_str[i] == L'-')conFlg = false;

			if (conFlg)continue;
			out = out + _str[i];

		}
		return out;
	}

	std::string GetCharsToRangeCode(
		const std::string& _str
		, const char _min
		, const char _max)
	{

		std::string out = "";

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			if (_str[i] > _max || _str[i] < _min)continue;

			out = out + _str[i];

		}

		return out;
	}

	static inline std::wstring GetCharsToRangeCode(
		const std::wstring& _str
		, const wchar_t _min
		, const wchar_t _max)
	{

		std::wstring out = L"";

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			if (_str[i] > _max || _str[i] < _min)continue;

			out = out + _str[i];

		}
		return out;
	}

	std::wstring_convert<ConvertUTF8, wchar_t>& GetU8Converter()
	{

		static std::wstring_convert<ConvertUTF8, wchar_t> strconverter;

		return strconverter;
	}

	std::wstring_convert<ConvertUTF16, wchar_t>& GetU16Converter()
	{

		static std::wstring_convert<ConvertUTF16, wchar_t> strconverter;

		return strconverter;
	}



	//文字列からUTF8のワイド文字列へ変換する//
	std::wstring UTF8ToWString(const std::string& _str)
	{

		return GetU8Converter().from_bytes(_str);
	}

	//ワイド文字列から文字列へ変換する//
	std::string UTF8ToString(const std::wstring& _str)
	{
		return GetU8Converter().to_bytes(_str);
	}

	//文字列からUTF16のワイド文字列へ変換する//
	std::wstring UTF16ToWString(const std::string& _str)
	{

		return GetU16Converter().from_bytes(_str);
	}

	//ワイド文字列から文字列へ変換する//
	std::string UTF16ToString(const std::wstring& _str)
	{
		return GetU16Converter().to_bytes(_str);
	}

}

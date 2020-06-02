#ifndef Ch_CPP_Str_h
#define Ch_CPP_Str_h

#include<Windows.h>

namespace ChCpp
{

	class StringObject
	{
	public:

		enum class LocalizeName : unsigned char
		{
			USA, Count
		};

		enum class StringCode : unsigned char
		{
			UTF8 ,Ascii,ShiftJis,Unicode
		};

		StringObject()
		{

#ifdef _UNICODE

			CodeType = StringCode::Unicode;

#elif _WIN32

			CodeType = StringCode::ShiftJis;

#else

			CodeType = StringCode::UTF8;
#endif
		}

		static void SetGlobalLocale();

		static void SetLocal();

		std::basic_string<char> ASC_To_UTF8(const std::basic_string<char>& _str);

		std::basic_string<char> UTF8_To_ASC(const std::basic_string<char>& _str);

		std::basic_string<char> UTF8_To_SJ(const std::basic_string<unsigned short>& _str);

		std::basic_string<unsigned short> SJ_To_UTF8(const std::basic_string<char>& _str);

	private:


		static std::string localName[(unsigned char)LocalizeName::Count];

		StringCode CodeType;


		static ChStd::Bool InitFlgs;
	};

};

#endif
#ifndef Ch_CPP_Str_h
#define Ch_CPP_Str_h

#ifdef _Windows

#pragma execution_character_set("UTF-8")

#endif

namespace ChCpp
{

	class StringObject
	{
	public:

		StringObject& operator = (const char* _Str);
		StringObject& operator = (const std::string& _Str);
		StringObject& operator = (const std::wstring& _Str);
		StringObject& operator = (const StringObject _Str);

		StringObject& operator +=(const char* _Str);
		StringObject& operator +=(const std::string& _Str);
		StringObject& operator +=(const std::wstring& _Str);
		StringObject& operator +=(const StringObject& _Str);

		StringObject& operator -=(const char* _Str);
		StringObject& operator -=(const std::string& _Str);
		StringObject& operator -=(const std::wstring& _Str);
		StringObject& operator -=(const StringObject& _Str);

		operator const char* ()const;
		operator const std::string ()const;
		operator const std::wstring ()const;

		StringObject();
		StringObject(const StringObject& _Str);
		StringObject(const char* _Str);
		StringObject(const std::string& _Str);
		StringObject(const std::wstring& _Str);

		size_t Length()const
		{
			size_t Tmp = 0;
			while (*(text +Tmp) != '\0')
			{
				Tmp++;
			}
			return Tmp;
		}

	protected:

		void textFree();

		void setString(const char* _Str);
		void setString(const wchar_t* _Str);

	private:

		char* text = nullptr;

	};


	using String = StringObject;
	using Str = StringObject;
};

#endif
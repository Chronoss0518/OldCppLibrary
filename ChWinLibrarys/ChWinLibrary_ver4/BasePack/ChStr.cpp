
#include<cstdlib>
#include<cstring>
#include<wchar.h>
#include"../BaseIncluder/ChBase.h"
#include"ChStr.h"

using namespace ChStr;

///////////////////////////////////////////////////////////////////////////////////////
//StringObjectOperator//
///////////////////////////////////////////////////////////////////////////////////////

StringObject& StringObject::operator = (const char* _Str)
{

	setString(_Str);
	return *this;
}

StringObject& StringObject::operator = (const wchar_t* _Str)
{

	setString(_Str);
	return *this;
}

StringObject& StringObject::operator = (const std::string& _Str)
{

	setString(_Str.c_str());
	return *this;
}

StringObject& StringObject::operator = (const std::wstring& _Str)
{
	setString(_Str.c_str());
	return *this;
}

StringObject& StringObject::operator = (const StringObject _Str)
{

	setString(_Str.text);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////

StringObject& StringObject::operator +=(const char* _Str)
{

	addString(_Str);
	return *this;
}

StringObject& StringObject::operator +=(const wchar_t* _Str)
{

	addString(_Str);
	return *this;
}

StringObject& StringObject::operator +=(const std::string& _Str)
{

	addString(_Str.c_str());
	return *this;
}

StringObject& StringObject::operator +=(const std::wstring& _Str)
{

	addString(_Str.c_str());
	return *this;
}

StringObject& StringObject::operator +=(const StringObject& _Str)
{

	addString(_Str.text);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////

StringObject& StringObject::operator -=(const char* _Str)
{
	decString(_Str);

	return *this;
}

StringObject& StringObject::operator -=(const wchar_t* _Str)
{
	decString(_Str);

	return *this;
}

StringObject& StringObject::operator -=(const std::string& _Str)
{
	decString(_Str.c_str());

	return *this;
}

StringObject& StringObject::operator -=(const std::wstring& _Str)
{
	decString(_Str.c_str());

	return *this;
}

StringObject& StringObject::operator -=(const StringObject& _Str)
{
	decString(_Str.text);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////

StringObject::operator const char* const()const
{	
	return ToString(text).c_str();
}

StringObject::operator const wchar_t* const()const
{
	return text;
}

StringObject::operator const unsigned long()const
{
	return length;
}

StringObject::StringObject()
{
	setString(L"\0");
}

StringObject::StringObject(const StringObject& _Str)
{
	setString(_Str.text);
}

StringObject::StringObject(const char* _Str)
{

	setString(_Str);
}

StringObject::StringObject(const wchar_t* _Str)
{

	setString(_Str);
}

StringObject::StringObject(const std::string& _Str)
{

	setString(_Str.c_str());
}

StringObject::StringObject(const std::wstring& _Str)
{

	setString(_Str.c_str());
}

///////////////////////////////////////////////////////////////////////////////////////
//StringObjectMethod//
///////////////////////////////////////////////////////////////////////////////////////

void StringObject::textFree()
{
	if(ChPtr::NullCheck(text))return;

	delete[] text;

	text = nullptr;
	length = 0;
}

void StringObject::setString(const char* _Str)
{
	setString(ToWString(_Str).c_str());
}

void StringObject::setString(const wchar_t* _Str)
{

	std::wstring Tmp = _Str;

	if (Tmp.empty())return;

	textFree();
	
	length = Tmp.length();

	text = new wchar_t[length + 1];

	for (unsigned long i = 0; i < Tmp.length(); i++)
	{
		text[i] = Tmp[i];
	}

	text[length] = L'\0';

}

void StringObject::addString(const char* _Str)
{
	addString(ToWString(_Str).c_str());
}

void StringObject::addString(const wchar_t* _Str)
{
	std::wstring Tmp = _Str;

	if (Tmp.empty())return;

	std::wstring out = text;

	out += Tmp;

	textFree();
	
	setString(out.c_str());

}

void StringObject::decString(const char* _Str)
{
	decString(ToWString(_Str).c_str());
}

void StringObject::decString(const wchar_t* _Str)
{

	std::wstring Tmp = _Str;

	if (Tmp.empty())return;
	if (Tmp.length() > length)return;

	std::wstring Test = L"\0";


	for (unsigned long i = 0; i < length; i++)
	{
		unsigned long count = 0;

		for (unsigned long j = 0; j < Tmp.length(); j++)
		{
			if (text[i + j] != Tmp[j])break;
			count++;
		}

		if (count >= Tmp.length()) 
		{
			i += count - 1;
			continue;
		}

		Test += text[i];

	}

	textFree();

	setString(Test.c_str());

}

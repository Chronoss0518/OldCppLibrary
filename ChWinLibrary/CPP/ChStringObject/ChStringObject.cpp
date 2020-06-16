
#include<cstdlib>
#include<cstring>
#include<wchar.h>
#include"../../BaseIncluder/ChBase.h"
#include"ChStringObject.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//StringObjectMethod//
///////////////////////////////////////////////////////////////////////////////////////

StringObject& StringObject::operator = (const char* _Str)
{
	textFree();
	setString(_Str);
	return *this;
}

StringObject& StringObject::operator = (const std::string& _Str)
{
	textFree();
	setString(_Str.c_str());
	return *this;
}

StringObject& StringObject::operator = (const std::wstring& _Str)
{
	textFree();
	setString(_Str.c_str());
	return *this;
}

StringObject& StringObject::operator = (const StringObject _Str)
{
	textFree();
	size_t Tmp = _Str.Length();

	text = static_cast<char*>(std::malloc(Tmp + 1));

	for (size_t i = 0; i < Tmp; i++)
	{
		*(i + text) = *(i + _Str.text);
	}

	return *this;
}


void StringObject::textFree()
{
	if (ChPtr::NullCheck(text))return;
	std::free(text);
}

void setString(const char* _Str)
{

	char* Tmp = nullptr;
	size_t tmpLen = std::strlen(_Str);
	Tmp = static_cast<char*>(std::malloc(tmpLen + 1));
	size_t i;
	for ( i = 0; i < tmpLen + 1; i++)
	{
		*(Tmp + i) = *(_Str + i);
	}

	*(Tmp + i) = '\0';
}

void setString(const wchar_t* _Str)
{

	char* Tmp = nullptr;
	size_t tmpLen = std::wcslen(_Str) * sizeof(wchar_t);
	Tmp = static_cast<char*>(std::malloc(tmpLen + sizeof(wchar_t)));

	void* Base = (void*)(_Str);
	size_t i;
	for (i = 0; i < tmpLen + 1; i++)
	{
		*(Tmp + i) = *(((char*)Base) + i);
	}

	*(Tmp + i) = '\0';

}


#include"../../BaseIncluder/ChBase.h"
#include"ChStringObject.h"

using namespace ChCpp;

ChStd::Bool StringObject::InitFlgs = false;

std::string  StringObject::localName[(unsigned char)LocalizeName::Count] = 
{
	"ja-JP"
};


void StringObject::SetGlobalLocale()
{
	std::locale loc("");
	std::locale::global(loc);
	InitFlgs = true;
}

void StringObject::SetLocal()
{
	setlocale(LC_ALL, localName[(unsigned char)LocalizeName::USA].c_str());
	InitFlgs = true;
}
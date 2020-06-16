
#include"../../BaseIncluder/ChBase.h"
#include"ChStringController.h"

using namespace ChCpp;

ChStd::Bool StringController::InitFlgs = false;

std::string  StringController::localName[(unsigned char)LocalizeName::Count] =
{
	"ja-JP"
};


void StringController::SetGlobalLocale()
{
	std::locale loc("");
	std::locale::global(loc);
	InitFlgs = true;
}

void StringController::SetLocal()
{
	setlocale(LC_ALL, localName[(unsigned char)LocalizeName::USA].c_str());
	InitFlgs = true;
}
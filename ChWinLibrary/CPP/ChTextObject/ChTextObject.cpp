
#include"../../BaseIncluder/ChBase.h"
#include"ChTextObject.h"

using namespace ChCpp;


///////////////////////////////////////////////////////////////////////////////////////
//FileObjectƒƒ\ƒbƒh//
///////////////////////////////////////////////////////////////////////////////////////

std::string FileObject::GetText()const
{
	std::string Out = "";

	for (auto Text : FileText)
	{
		Out += Text + "\n";
	}

	return Out;

}

///////////////////////////////////////////////////////////////////////////////////////

std::string FileObject::GetTextLine(const unsigned int _Index)const
{
	int Tmp = _Index + 1;
	if (Tmp >= FileText.size())return "";

	return FileText[Tmp];
}

///////////////////////////////////////////////////////////////////////////////////////

void FileObject::SetText(const std::string _Str)
{
	FileText.clear();
	if (_Str.find("\n") == _Str.npos)
	{
		FileText.push_back(_Str);
		return;
	}

	size_t TmpPos = 0;
	size_t testPos = 0;

	while (true)
	{
		testPos = _Str.find("\n");

		if (testPos == _Str.npos)break;

		FileText.push_back(_Str.substr(TmpPos, testPos));
		TmpPos = testPos + 2;


	}

}

///////////////////////////////////////////////////////////////////////////////////////

void FileObject::SetTextLine(
	const std::string _Str
	, const unsigned int _SetIndex)
{
	if (_Str.find("\n") != std::string::npos)return;
	if (_SetIndex > FileText.size())return;

	if (_SetIndex == FileText.size())
	{
		FileText.push_back(_Str);
		return;
	}

	FileText.insert(FileText.begin() + (FileText.size() - _SetIndex - 1), _Str);
}

///////////////////////////////////////////////////////////////////////////////////////

unsigned long FileObject::FindLine(const std::string& _FindStr, const size_t _StartPos = 0)const
{

	std::string Str = GetText();

	size_t Tmp = _StartPos;
	size_t Base = Str.find(_FindStr);

	if (Base == Str.npos)return 0;
	unsigned long count = 1;
	while (1)
	{
		Tmp = Str.find("\n", Tmp);

		if (Tmp >= Base)return count;

		count++;

		Tmp++;

	}

}

///////////////////////////////////////////////////////////////////////////////////////

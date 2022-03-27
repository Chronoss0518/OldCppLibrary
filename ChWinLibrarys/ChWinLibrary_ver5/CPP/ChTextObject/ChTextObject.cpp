
#include"../../BaseIncluder/ChBase.h"
#include"ChTextObject.h"

using namespace ChCpp;


///////////////////////////////////////////////////////////////////////////////////////
//FileObjectƒƒ\ƒbƒh//
///////////////////////////////////////////////////////////////////////////////////////

std::string TextObject::GetText()const
{
	std::string out = "";

	for (auto text : textLines)
	{
		out += text + "\n";
	}

	return out;

}

///////////////////////////////////////////////////////////////////////////////////////

std::string TextObject::GetTextLine(const size_t _index)const
{
	size_t tmp = _index + 1;
	if (tmp >= textLines.size())return "";

	return textLines[tmp];
}

///////////////////////////////////////////////////////////////////////////////////////

void TextObject::SetText(const std::string _str)
{
	textLines.clear();
	if (_str.find("\n") == _str.npos)
	{
		textLines.push_back(_str);
		return;
	}

	size_t tmpPos = 0;
	size_t testPos = 0;

	while (true)
	{
		testPos = _str.find("\n", tmpPos);

		if (testPos == _str.npos)break;

		textLines.push_back(_str.substr(tmpPos, testPos - tmpPos));
		tmpPos = testPos + 1;


	}

}

///////////////////////////////////////////////////////////////////////////////////////

void TextObject::SetTextLine(
	const std::string _str
	, const unsigned int _setIndex)
{
	if (_str.find("\n") != std::string::npos)return;
	if (_setIndex > textLines.size())return;

	if (_setIndex == textLines.size())
	{
		textLines.push_back(_str);
		return;
	}

	textLines.insert(textLines.begin() + (textLines.size() - _setIndex - 1), _str);
}

///////////////////////////////////////////////////////////////////////////////////////

unsigned long TextObject::FindLine(
	const std::string& _findStr
	, const size_t _startPos)const
{

	std::string str = GetText();

	size_t tmp = _startPos;
	size_t Base = str.find(_findStr);

	if (Base == str.npos)return 0;
	unsigned long count = 1;
	while (1)
	{
		tmp = str.find("\n", tmp);

		if (tmp >= Base)return count;

		count++;

		tmp++;

	}

}

///////////////////////////////////////////////////////////////////////////////////////

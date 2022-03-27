#ifndef Ch_CPP_BaFr_h
#define Ch_CPP_BaFr_h

namespace ChCpp
{

	class TextObject
	{
	public:

		std::string operator[](size_t _index)const
		{

			if (textLines.size() <= _index)return "";

			return textLines[_index];
		}


		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Text�S�̂�ǂݎ��//
		std::string GetText()const;

		//Text�����s�ǂݎ��//
		std::string GetTextLine(const size_t _index = 0)const;

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//Text�S�̂���������//
		void SetText(const std::string _str);

		//Text�Ɉ�s��������//
		void SetTextLine(
			const std::string _str
			, const unsigned int _setIndex = 0);

		///////////////////////////////////////////////////////////////////////////////////////

		//�w�肵�������������當������擾//
		std::string SubStr(
			const unsigned int _startPos = 0
			, const unsigned int _endPos = std::string::npos)const
		{
			return GetText().substr(_startPos, _endPos);
		}

		///////////////////////////////////////////////////////////////////////////////////////

		//�w�肵�������������當������擾//
		TextObject SubStrToFileObject(
			const unsigned int _startPos = 0
			, const unsigned int _endPos = std::string::npos)const
		{
			TextObject out;

			std::string str = GetText().substr(_startPos, _endPos);

			out.SetText(str);

			return out;

		}

		///////////////////////////////////////////////////////////////////////////////////////

		size_t Length()const
		{
			return GetText().length();
		}

		///////////////////////////////////////////////////////////////////////////////////////

		size_t Count()const
		{
			return GetText().length();
		}

		///////////////////////////////////////////////////////////////////////////////////////

		size_t LineCount()const
		{
			return textLines.size();
		}

		///////////////////////////////////////////////////////////////////////////////////////

		//Text�̒��Ɏw�肵���������擪���T��//
		//���߂Ɍ������s�̗v�f�����擾//
		unsigned long FindLine(
			const std::string& _findStr
			, const size_t _startPos = 0)const;

		///////////////////////////////////////////////////////////////////////////////////////

		//Text�̒��Ɏw�肵���������擪���T��//
		//���߂Ɍ������ʒu���擾//
		unsigned long Find(
			const std::string& _findStr
			, const size_t _startPos = 0)const
		{

			std::string str = GetText();

			return str.find(_findStr, _startPos);
		}

		///////////////////////////////////////////////////////////////////////////////////////


	private:

		std::vector<std::string> textLines;

	};

}

#endif
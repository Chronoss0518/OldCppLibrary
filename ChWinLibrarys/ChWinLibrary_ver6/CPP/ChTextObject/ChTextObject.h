#ifndef Ch_CPP_BaFr_h
#define Ch_CPP_BaFr_h

namespace ChCpp
{

	class TextObject
	{
	public:

		std::string operator[](size_t _Index)const
		{

			if (FileText.size() <= _Index)return "";

			return FileText[_Index];
		}


		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Text�S�̂�ǂݎ��//
		std::string GetText()const;

		//Text�����s�ǂݎ��//
		std::string GetTextLine(const size_t _Index = 0)const;

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//Text�S�̂���������//
		void SetText(const std::string _Str);

		//Text�Ɉ�s��������//
		void SetTextLine(
			const std::string _Str
			, const unsigned int _SetIndex = 0);

		///////////////////////////////////////////////////////////////////////////////////////

		//�w�肵�������������當������擾//
		std::string SubStr(
			const unsigned int _StartPos = 0
			, const unsigned int _EndPos = std::string::npos)const
		{
			return GetText().substr(_StartPos, _EndPos);
		}

		///////////////////////////////////////////////////////////////////////////////////////

		//�w�肵�������������當������擾//
		TextObject SubStrToFileObject(
			const unsigned int _StartPos = 0
			, const unsigned int _EndPos = std::string::npos)const
		{
			TextObject out;

			std::string str = GetText().substr(_StartPos, _EndPos);

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
			return FileText.size();
		}

		///////////////////////////////////////////////////////////////////////////////////////

		//Text�̒��Ɏw�肵���������擪���T��//
		//���߂Ɍ������s�̗v�f�����擾//
		unsigned long FindLine(
			const std::string& _FindStr
			, const size_t _StartPos = 0)const;

		///////////////////////////////////////////////////////////////////////////////////////

		//Text�̒��Ɏw�肵���������擪���T��//
		//���߂Ɍ������ʒu���擾//
		unsigned long Find(
			const std::string& _FindStr
			, const size_t _StartPos = 0)const
		{

			std::string Str = GetText();

			return Str.find(_FindStr, _StartPos);
		}

		///////////////////////////////////////////////////////////////////////////////////////


	private:

		std::vector<std::string> FileText;

	};

}

#endif
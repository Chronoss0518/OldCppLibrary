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

		//Text全体を読み取る//
		std::string GetText()const;

		//Textから一行読み取る//
		std::string GetTextLine(const size_t _Index = 0)const;

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//Text全体を書き込む//
		void SetText(const std::string _Str);

		//Textに一行書き込む//
		void SetTextLine(
			const std::string _Str
			, const unsigned int _SetIndex = 0);

		///////////////////////////////////////////////////////////////////////////////////////

		//指定した文字数分から文字列を取得//
		std::string SubStr(
			const unsigned int _StartPos = 0
			, const unsigned int _EndPos = std::string::npos)const
		{
			return GetText().substr(_StartPos, _EndPos);
		}

		///////////////////////////////////////////////////////////////////////////////////////

		//指定した文字数分から文字列を取得//
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

		//Textの中に指定した文字列を先頭より探し//
		//初めに見つけた行の要素数を取得//
		unsigned long FindLine(
			const std::string& _FindStr
			, const size_t _StartPos = 0)const;

		///////////////////////////////////////////////////////////////////////////////////////

		//Textの中に指定した文字列を先頭より探し//
		//初めに見つけた位置を取得//
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
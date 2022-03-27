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

		//Text全体を読み取る//
		std::string GetText()const;

		//Textから一行読み取る//
		std::string GetTextLine(const size_t _index = 0)const;

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//Text全体を書き込む//
		void SetText(const std::string _str);

		//Textに一行書き込む//
		void SetTextLine(
			const std::string _str
			, const unsigned int _setIndex = 0);

		///////////////////////////////////////////////////////////////////////////////////////

		//指定した文字数分から文字列を取得//
		std::string SubStr(
			const unsigned int _startPos = 0
			, const unsigned int _endPos = std::string::npos)const
		{
			return GetText().substr(_startPos, _endPos);
		}

		///////////////////////////////////////////////////////////////////////////////////////

		//指定した文字数分から文字列を取得//
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

		//Textの中に指定した文字列を先頭より探し//
		//初めに見つけた行の要素数を取得//
		unsigned long FindLine(
			const std::string& _findStr
			, const size_t _startPos = 0)const;

		///////////////////////////////////////////////////////////////////////////////////////

		//Textの中に指定した文字列を先頭より探し//
		//初めに見つけた位置を取得//
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
#ifndef Ch_CPP_FIO_h
#define Ch_CPP_FIO_h

namespace ChFIO
{

	static const std::string Key_Stop = "St;";
	static const std::string Key_Loop = "Lp:";
	static const std::string Key_Vec = "Vec:";


	class FileObject
	{
	public:

		std::string operator[](int _Index)
		{
			if (FileText.size() <= _Index)return "";

			return FileText[_Index];
		}

		std::string operator[](int _Index)const
		{
			
			if (FileText.size() <= _Index)return "";

			return FileText[_Index];
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Text全体を読み取る//
		std::string GetText()const
		{
			std::string Out = "";

			for (auto Text : FileText)
			{
				Out += Text + "\n";
			}

			return Out;

		}

		//Textから一行読み取る//
		std::string GetTextLine(const unsigned int _Index = 0)const
		{
			int Tmp = _Index + 1;
			if (Tmp >= FileText.size())return "";

			return FileText[Tmp];
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//Text全体を書き込む//
		void SetText(const std::string _Str)
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

		//Textに一行書き込む//
		void SetTextLine(const std::string _Str, const unsigned int _SetIndex = 0)
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

		//指定した文字数分から文字列を取得//
		std::string SubStr(
			const unsigned int _StartPos = 0
			, const unsigned int _EndPos = std::string::npos)const
		{
			return GetText().substr(_StartPos, _EndPos);
		}

		///////////////////////////////////////////////////////////////////////////////////////

		//指定した文字数分から文字列を取得//
		FileObject SubStrToFileObject(
			const unsigned int _StartPos = 0
			, const unsigned int _EndPos = std::string::npos)const
		{
			FileObject Out;

			std::string Str = GetText().substr(_StartPos,_EndPos);

			Out.SetText(Str);

			return Out;

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
		unsigned long FindLine(const std::string& _FindStr, const size_t _StartPos = 0)const
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

		//Textの中に指定した文字列を先頭より探し//
		//初めに見つけた位置を取得//
		unsigned long Find(const std::string& _FindStr, const size_t _StartPos = 0)const
		{

			std::string Str = GetText();

			return Str.find(_FindStr, _StartPos);
		}

		///////////////////////////////////////////////////////////////////////////////////////


	private:

		std::vector<std::string> FileText;

	};

	class File
	{

	public:

		inline File() {}

		inline File(
			const std::string& _FileName)
		{
			FileOpen(_FileName);
		}

		inline ~File()
		{
			FileClose();
		}

		///////////////////////////////////////////////////////////////////////////////////////

		//Fileを開く//
		inline void FileOpen(
			const std::string& _FileName
			, unsigned int _OpenMode = std::ios::in | std::ios::out)
		{
			if (_FileName.length() <= 0)return;

			{

				if (_OpenMode & std::ios::in)
				{

					std::ofstream Tmp;
					Tmp.open(_FileName, std::ios::app);
					Tmp.close();
				}

			}

			Flg = _OpenMode;
			OpenFileName = _FileName;
			Stream.open(_FileName, static_cast<std::ios_base::openmode>(Flg));
		}

		///////////////////////////////////////////////////////////////////////////////////////

		//Fileを閉じる(Destructerでも起動する)//
		inline void FileClose()
		{
			if (!Stream.is_open())return;
			Stream.close();
		}

		///////////////////////////////////////////////////////////////////////////////////

		//Fileから読み出す//
		inline void FileRead(std::string& _Out)
		{
			if (!Stream.is_open())return;

			std::stringstream TmpSS;

			TmpSS << Stream.rdbuf();

			_Out = TmpSS.str();

			Stream.clear();
			Stream.seekp(std::ios::beg, static_cast<std::ios_base::seekdir>(0));

			return;

		}

		//FileObjectを用いてFileから読み出す//
		inline void FileRead(FileObject& _Out)
		{

			if (!Stream.is_open())return;

			std::string TmpStr = "";

			std::stringstream TmpSS;

			TmpSS << Stream.rdbuf();

			TmpStr = TmpSS.str();



			_Out.SetText(TmpStr);

			Stream.clear();
			Stream.seekp(std::ios::beg, static_cast<std::ios_base::seekdir>(0));

			return;

		}

		///////////////////////////////////////////////////////////////////////////////////

		//Fileに書き込む//
		template<class... _Types>
		inline std::string FileWrite(
			const std::string& _WriteStr
			, _Types&&... _Args)
		{

			if (!Stream.is_open())return "";

			if (Flg & std::ios::binary)return "";

			if (!(Flg & std::ios::app))
			{
				Stream.close();
				Stream.open(OpenFileName.c_str(), std::ios::out | std::ios::trunc);

				Stream.close();
				Stream.open(OpenFileName.c_str(), static_cast<std::ios_base::openmode>(Flg));
			}

			std::string TmpStr = _WriteStr;
#ifdef _WIN32
			::sscanf_s(&TmpStr[0], &TmpStr[0], _Args...);
#else
			std::sscanf(TmpStr.c_str(), TmpStr.c_str(), _Args...);
#endif
			
			return Writer(TmpStr);

		}

		//FileObjectを用いてFileに書き込む//
		inline std::string FileWrite(const FileObject& _FText)
		{

			if (!Stream.is_open())return "";

			if (Flg & std::ios::binary)return "";

			if (!(Flg & std::ios::app))
			{
				Stream.close();
				Stream.open(OpenFileName.c_str(), std::ios::out | std::ios::trunc);

				Stream.close();
				Stream.open(OpenFileName.c_str(), static_cast<std::ios_base::openmode>(Flg));
			}

			return Writer(_FText.GetText());

		}

		///////////////////////////////////////////////////////////////////////////////////

	private:

		std::string Writer(const std::string& _Str)
		{

			std::ofstream TmpStream;

			TmpStream.set_rdbuf(Stream.rdbuf());

			TmpStream << _Str.c_str();

			return _Str;
		}

	protected:

		unsigned int Flg{ 0 };
		std::string OpenFileName{ "" };
		std::fstream Stream;


	};

	const enum class OTEAddType :unsigned char
	{
		None, AfterFirst, All
	};

	///////////////////////////////////////////////////////////////////////////////////

	//専用エラーファイルを出力する//
	inline static void OutToErrorText(
		const std::string& _ErrorName
		, const std::string& _ErrorDitails
		, const OTEAddType _AddFlg = OTEAddType::None)
	{
		File OutFiles;
		std::string OutData = "";
		std::string OutFileName = "";
		OutFileName = _ErrorName + ".txt";
		OutFiles.FileOpen(OutFileName);

		if (_AddFlg == OTEAddType::All)
		{
			OutFiles.FileRead(OutData);
			OutData = OutData + "\n";
		}

		if (_AddFlg == OTEAddType::AfterFirst)
		{
			static ChStd::Bool Flgs = false;
			if (Flgs)
			{
				OutFiles.FileRead(OutData);
				OutData = OutData + "\n";
			}
			Flgs = true;
		}

		OutData = OutData + _ErrorDitails;

		OutFiles.FileWrite(OutData);

		return;


	}
}


#endif
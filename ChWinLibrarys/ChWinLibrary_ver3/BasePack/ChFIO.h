#ifndef Ch_CPP_FIO_h
#define Ch_CPP_FIO_h

namespace ChFIO
{
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
#ifndef Ch_CPP_FIO_h
#define Ch_CPP_FIO_h

namespace ChFIO
{

	static const std::string Key_Stop = "St;";
	static const std::string Key_Loop = "Lp:";
	static const std::string Key_Vec = "Vec:";

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

		inline void FileOpen(
			const std::string& _FileName
			, unsigned int _OpenMode = std::ios::in | std::ios::out)
		{
			if (_FileName.length() <= 0)return;

			{

				if (_OpenMode &  std::ios::in)
				{

					std::ofstream Tmp;
					Tmp.open(_FileName, std::ios::app);
					Tmp.close();
				}

			}

			Flg = _OpenMode;
			OpenFileName = _FileName;
			Stream.open(_FileName, _OpenMode);
		}

		inline void FileClose()
		{
			if (!Stream.is_open())return;
			Stream.close();
		}

		///////////////////////////////////////////////////////////////////////////////////

		inline std::string FileRead()
		{
			if (!Stream.is_open())return "";

			std::string TmpStr = "";

			std::stringstream TmpSS;

			TmpSS << Stream.rdbuf();

			TmpStr = TmpSS.str();

			Stream.clear();
			Stream.seekp(std::ios::beg, 0);

			return TmpStr;

		}

		///////////////////////////////////////////////////////////////////////////////////

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
				Stream.open(OpenFileName.c_str(),std::ios::out | std::ios::trunc);

				Stream.close();
				Stream.open(OpenFileName.c_str(), Flg);
			}

			std::string TmpStr = _WriteStr;
#ifdef _WINDOWS_
			::sscanf_s(&TmpStr[0], &TmpStr[0], _Args...);
#else
			std::sscanf(TmpStr.c_str(), TmpStr.c_str(), _Args...);
#endif
			std::ofstream TmpStream;

			TmpStream.set_rdbuf(Stream.rdbuf());

			TmpStream << TmpStr.c_str();

			return TmpStr;

		}

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		unsigned int Flg;
		std::string OpenFileName;
		std::fstream Stream;


	};

}


#endif
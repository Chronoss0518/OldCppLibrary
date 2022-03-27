#ifndef Ch_CPP_File_h
#define Ch_CPP_File_h

namespace ChCpp
{
	template<typename chara_set = char>
	class File :public ChCp::Releaser
	{

	public:

		const enum class OTEAddType :unsigned char
		{
			None, AfterFirst, All
		};

		///////////////////////////////////////////////////////////////////////////////////
		//StaticFunction//

		//専用エラーファイルを出力する//
		static inline void OutToErrorText(
			const std::basic_string<chara_set>& _errorName
			, const std::basic_string<chara_set>& _errorDitails
			, const OTEAddType _addFlg = OTEAddType::None)
		{
			File outFiles;
			std::basic_string<chara_set> outData = "";
			std::basic_string<chara_set> outFileName = "";
			outFileName = _errorName + ".txt";
			outFiles.FileOpen(outFileName);

			if (_addFlg == OTEAddType::All)
			{
				outData = outFiles.FileReadText();
				outData = outData + "\n";
			}

			if (_addFlg == OTEAddType::AfterFirst)
			{
				static ChStd::Bool Flgs = false;
				if (Flgs)
				{
					outData = outFiles.FileReadText();
					outData = outData + "\n";
				}
				Flgs = true;
			}

			outData = outData + _errorDitails;

			outFiles.FileWriteText(outData);

			return;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructorDestructor//

		inline File() {}

		inline File(
			const std::basic_string<chara_set>& _fileName)
		{
			FileOpen(_fileName);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Release()override
		{
			FileClose();
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline unsigned long GetLength()
		{
			unsigned long out = 0;

			if (!stream.is_open())return out;

			auto istream = dynamic_cast<std::basic_istream<chara_set>*>(&stream);
			istream->seekg(0,std::ios::end);

			out = static_cast<unsigned long>(istream->tellg());

			istream->seekg(0, std::ios::beg);

			return out;
			

		}

		///////////////////////////////////////////////////////////////////////////////////////

		//Fileを開く//
		inline void FileOpen(
			const std::basic_string<chara_set>& _fileName
			, unsigned int _openMode = std::ios::in | std::ios::out)

		{
			if (_fileName.length() <= 0)return;

			if (_openMode & std::ios::in)
			{

				std::basic_ofstream<chara_set> tmp;
				tmp.open(_fileName, std::ios::app);
				tmp.close();
			}

			flg = _openMode;
			openFileName = _fileName;
			stream.open(_fileName, flg);
		}


		///////////////////////////////////////////////////////////////////////////////////////

		//Fileを閉じる(Destructerでも起動する)//
		inline void FileClose()
		{
			if (!stream.is_open())return;
			stream.close();
		}

		///////////////////////////////////////////////////////////////////////////////////

		//Fileから読み出す//
		inline std::basic_string<chara_set> FileReadText()
		{
			std::basic_string<chara_set> out = "";

			if (!stream.is_open())return out;

			if ((flg & std::ios::binary))return out;

			std::stringstream tmpSS;

			tmpSS << stream.rdbuf();

			out = tmpSS.str();

			stream.clear();
			stream.seekp(0, std::ios::beg);

			return out;

		}

		//Fileから読み出す//
		inline void FileReadBinary(std::vector<char>& _binary)
		{

			if (!stream.is_open())return;

			if (!(flg & std::ios::binary))return;

			_binary.resize(GetLength());

			auto istream = dynamic_cast<std::basic_istream<chara_set>*>(&stream);

			istream->read(&_binary[0], GetLength());

			istream->seekg(0, std::ios::beg);

			return;

		}

		///////////////////////////////////////////////////////////////////////////////////

		//Fileに書き込む//
		template<class... _Types>
		inline std::basic_string<chara_set> FileWriteText(
			const std::basic_string<chara_set>& _writeStr
			, _Types&&... _args)
		{

			if (!stream.is_open())return "";

			if (flg & std::ios::binary)return "";

			if (!(flg & std::ios::app))
			{
				stream.close();
				stream.open(openFileName.c_str(), std::ios::out | std::ios::trunc);
				
				stream.close();
				stream.open(openFileName.c_str(),flg);
			}

			std::basic_string<chara_set> tmpStr = _writeStr;
#ifdef _WIN32
			::sscanf_s(&tmpStr[0], &tmpStr[0], _args...);
#elif _WIN64
			::sscanf_s(&tmpStr[0], &tmpStr[0], _args...);
#else
			std::sscanf(tmpStr.c_str(), tmpStr.c_str(), _Args...);
#endif
			
			return Writer(tmpStr);

		}

		//Fileに書き込む//
		inline std::basic_string<chara_set> FileWriteBinary(
			const std::basic_string<chara_set>& _writeStr)
		{

			if (!stream.is_open())return "";

			if (flg & std::ios::binary)return "";

			if (!(flg & std::ios::app))
			{
				stream.close();
				stream.open(openFileName.c_str(), std::ios::out | std::ios::trunc);

				stream.close();
				stream.open(openFileName.c_str(), flg);
			}

			std::basic_string<chara_set> tmpStr = _writeStr;

			return Writer(tmpStr);

		}

		///////////////////////////////////////////////////////////////////////////////////

	private:

		std::basic_string<chara_set> Writer(const std::basic_string<chara_set>& _str)
		{

			std::basic_ofstream<chara_set> tmpStream;

			tmpStream.set_rdbuf(stream.rdbuf());

			tmpStream << _str.c_str();

			return _str;
		}

	protected:

		std::ios_base::openmode flg{ 0 };
		std::basic_string<chara_set> openFileName{ "" };
		std::basic_fstream<chara_set> stream;


	};
	template class File<char>;

}


#endif
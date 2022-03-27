#ifdef _WINDOWS_

#ifndef Ch_Win_FiDl_h
#define Ch_Win_FiDl_h

#include"../BaseWind/ChWinBaseWind.h"

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{

	typedef class FileDialog:ChCpp::ChCp::Initializer,public ChCpp::ChCp::Releaser
	{
	public:

		struct Filter
		{
			std::string Name = "";
			std::string Type = "";
		};


		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(const HWND& _HWnd);

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		std::string GetFileName() 
		{
			if (!OpenFlg)return "";
			OpenFlg = false;
			return PathToRerative();
		}

		std::string GetFileNameFullPath()
		{
			if (!OpenFlg)return "";
			OpenFlg = false;
			return FileName;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetTitle(const std::string& _Title) { Title = _Title; }

		void SetStartDir(const std::string& _Dir) { StartDir = _Dir; }

		void SetPathLen(const unsigned short _PathLength = 500) 
		{
			if (_PathLength < 2)return;
			PathLength = _PathLength;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		ChStd::Bool IsOpen() { return OpenFlg; }

		///////////////////////////////////////////////////////////////////////////////////////

		void AddFilter(const Filter& _Fil);

		void AddFilter(
			const std::string& _Name
			, const std::string& _Type);

		///////////////////////////////////////////////////////////////////////////////////////

		void DelFilter(const std::string& _Name);

		///////////////////////////////////////////////////////////////////////////////////////

		void OpenFileDialog();

		///////////////////////////////////////////////////////////////////////////////////////

		void SaveFileDialog();

		///////////////////////////////////////////////////////////////////////////////////////

	protected:

		void CreateFilterStr();

		///////////////////////////////////////////////////////////////////////////////////////

		std::string PathToRerative();

		///////////////////////////////////////////////////////////////////////////////////////

		std::string Title = "";

		std::string FileName = "";

		std::string StartDir = "";

		std::string BaseDir = "";

		std::map<std::string,std::string> Filters;

		ChStd::Bool OpenFlg = true;

		unsigned short PathLength = 256;

		enum class FlgType { Open, Save };

		static const char CutChar;
		static const DWORD Flgs[];

		HWND HOwn = nullptr;
		
		static std::string TmpType;

	}FDialog;

}

#endif

#endif
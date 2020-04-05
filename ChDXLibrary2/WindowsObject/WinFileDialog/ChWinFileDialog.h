#ifdef _WINDOWS_

#ifndef Ch_Win_FiDl_h
#define Ch_Win_FiDl_h

#include"../WinBaseWind/ChWinBaseWind.h"

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{

	typedef class FileDialog
	{
	public:

		struct Filter
		{
			std::string Name = "";
			std::string Type = "";
		};

		///////////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		FileDialog(const HWND& _HWnd) { Init(_HWnd); };

		~FileDialog() { Release(); };

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(const HWND& _HWnd);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		std::string GetFileName() 
		{
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

		void PathToRerative();

		///////////////////////////////////////////////////////////////////////////////////////

		std::string Title = "";

		std::string FileName = "";

		std::string StartDir = "";

		std::map<std::string,std::string> Filters;

		ChStd::Bool OpenFlg = true;

		ChStd::Bool RerativePathFlg = true;

		unsigned short PathLength = 500;

		enum class FlgType { Open, Save };

		static const char CutChar;
		static const DWORD Flgs[];

		HWND HOwn = nullptr;
		
		static std::string TmpType;

	}FDialog;

}

#endif

#endif
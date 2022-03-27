#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"ChWinFileDialog.h"


std::string ChWin::FileDialog::TmpType = "";

const char ChWin::FileDialog::CutChar = '\0';
const DWORD ChWin::FileDialog::Flgs[] =
{
	(OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_CREATEPROMPT | OFN_NONETWORKBUTTON)
	, (OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_CREATEPROMPT | OFN_NONETWORKBUTTON | OFN_OVERWRITEPROMPT)
};

///////////////////////////////////////////////////////////////////////////////////////
//FileDialogÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::FileDialog::Init(const HWND& _HWnd)
{
	SetInitFlg(true);

	HOwn = _HWnd;
	char Tmp[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, Tmp);

	StartDir += &Tmp[0];
	BaseDir = &Tmp[0];
}

void ChWin::FileDialog::Release()
{
	SetInitFlg(false);
	Filters.clear();
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::FileDialog::AddFilter(const Filter& _Fil)
{
	AddFilter(_Fil.Name, _Fil.Type);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::FileDialog::AddFilter(
	const std::string& _Name
	, const std::string& _Type)
{
	if (Filters.find(_Name) != Filters.end())return;
	Filters[_Name] = _Type;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::FileDialog::DelFilter(const std::string& _Name)
{
	if (Filters.empty())return;
	if (Filters.find(_Name) == Filters.end())return;

	Filters.erase(_Name);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::FileDialog::OpenFileDialog()
{
	if (!IsInit())return;

	CreateFilterStr();

	OPENFILENAMEA Tmp;
	char* Tmp2;
	Tmp2 = new char[PathLength];
	ZeroMemory(&Tmp, sizeof(Tmp));
	Tmp.lStructSize = sizeof(Tmp);
	Tmp.hwndOwner = HOwn;
	//Tmp.lpstrFile = &szFile[0];
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not  
	// use the contents of szFile to initialize itself. 
	Tmp.lpstrFile = Tmp2;
	Tmp.lpstrFile[0] = '\0';
	Tmp.nMaxFile = PathLength;
	CreateFilterStr();
	Tmp.lpstrFilter = TmpType.c_str();
	Tmp.nFilterIndex = 1;

	Tmp.lpstrTitle = Title.size() <= 0 ? nullptr : Title.c_str();
	Tmp.lpstrInitialDir = StartDir.size() <= 0 ? nullptr : StartDir.c_str();

	Tmp.Flags = Flgs[ChStd::EnumCast(FlgType::Open)];

	GetOpenFileName(&Tmp);
	if(ChPtr::NotNullCheck(Tmp.lpstrFile))FileName = Tmp.lpstrFile;

	delete[] Tmp2;

	SetCurrentDirectory(BaseDir.c_str());

	OpenFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::FileDialog::SaveFileDialog()
{

	if (!IsInit())return;
	CreateFilterStr();

	OPENFILENAMEA Tmp;
	char* Tmp2;
	Tmp2 = new char[PathLength];
	ZeroMemory(&Tmp, sizeof(Tmp));
	Tmp.lStructSize = sizeof(Tmp);
	Tmp.hwndOwner = HOwn;
	//Tmp.lpstrFile = &szFile[0];
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not  
	// use the contents of szFile to initialize itself. 
	Tmp.lpstrFile = Tmp2;
	Tmp.lpstrFile[0] = '\0';
	Tmp.nMaxFile = PathLength;
	CreateFilterStr();
	Tmp.lpstrFilter = TmpType.c_str();
	Tmp.nFilterIndex = 1;

	Tmp.lpstrTitle = Title.size() <= 0 ? nullptr : Title.c_str();
	Tmp.lpstrInitialDir = StartDir.size() <= 0 ? nullptr : StartDir.c_str();

	Tmp.Flags = Flgs[ChStd::EnumCast(FlgType::Save)];

	GetSaveFileName(&Tmp);
	FileName = Tmp2;

	delete[] Tmp2;

	SetCurrentDirectory(BaseDir.c_str());

	OpenFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::FileDialog::CreateFilterStr()
{
	TmpType.clear();

	for (auto&& Fil : Filters)
	{
		TmpType += Fil.first + "(" + "*" + Fil.second + ")" + CutChar + "*" + Fil.second + CutChar;

	}
	

}


///////////////////////////////////////////////////////////////////////////////////////

std::string ChWin::FileDialog::PathToRerative()
{

	size_t Tmp = FileName.find_last_of("\\",FileName.size());

	std::string BaseStr;

	BaseStr = FileName;

	BaseStr.replace(0, Tmp + 1, "");

	return BaseStr;
}

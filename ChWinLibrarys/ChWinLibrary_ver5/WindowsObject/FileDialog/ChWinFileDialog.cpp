#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"ChWinFileDialog.h"


std::string ChWin::FileDialog::tmpType = "";

const char ChWin::FileDialog::cutChar = '\0';
const DWORD ChWin::FileDialog::flgs[] =
{
	(OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_CREATEPROMPT | OFN_NONETWORKBUTTON)
	, (OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_CREATEPROMPT | OFN_NONETWORKBUTTON | OFN_OVERWRITEPROMPT)
};

///////////////////////////////////////////////////////////////////////////////////////
//FileDialogÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////////

void ChWin::FileDialog::Init(const HWND& _hWnd)
{
	SetInitFlg(true);

	hOwn = _hWnd;
	char tmp[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, tmp);

	startDir += &tmp[0];
	baseDir = &tmp[0];
}

void ChWin::FileDialog::Release()
{
	SetInitFlg(false);
	filters.clear();
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::FileDialog::AddFilter(const Filter& _fil)
{
	AddFilter(_fil.name, _fil.type);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::FileDialog::AddFilter(
	const std::string& _name
	, const std::string& _type)
{
	if (filters.find(_name) != filters.end())return;
	filters[_name] = _type;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::FileDialog::DelFilter(const std::string& _name)
{
	if (filters.empty())return;
	if (filters.find(_name) == filters.end())return;

	filters.erase(_name);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::FileDialog::OpenFileDialog()
{
	if (!IsInit())return;

	CreateFilterStr();

	OPENFILENAMEA tmp;
	char* tmp2;
	tmp2 = new char[pathLength];
	ZeroMemory(&tmp, sizeof(tmp));
	tmp.lStructSize = sizeof(tmp);
	tmp.hwndOwner = hOwn;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not  
	// use the contents of szFile to initialize itself. 
	tmp.lpstrFile = tmp2;
	tmp.lpstrFile[0] = '\0';
	tmp.nMaxFile = pathLength;
	CreateFilterStr();
	tmp.lpstrFilter = tmpType.c_str();
	tmp.nFilterIndex = 1;

	tmp.lpstrTitle = title.size() <= 0 ? nullptr : title.c_str();
	tmp.lpstrInitialDir = startDir.size() <= 0 ? nullptr : startDir.c_str();

	tmp.Flags = flgs[ChStd::EnumCast(FlgType::Open)];

	GetOpenFileName(&tmp);
	if(ChPtr::NotNullCheck(tmp.lpstrFile))fileName = tmp.lpstrFile;

	delete[] tmp2;

	SetCurrentDirectory(baseDir.c_str());

	openFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::FileDialog::SaveFileDialog()
{

	if (!IsInit())return;
	CreateFilterStr();

	OPENFILENAMEA tmp;
	char* tmp2;
	tmp2 = new char[pathLength];
	ZeroMemory(&tmp, sizeof(tmp));
	tmp.lStructSize = sizeof(tmp);
	tmp.hwndOwner = hOwn;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not  
	// use the contents of szFile to initialize itself. 
	tmp.lpstrFile = tmp2;
	tmp.lpstrFile[0] = '\0';
	tmp.nMaxFile = pathLength;
	CreateFilterStr();
	tmp.lpstrFilter = tmpType.c_str();
	tmp.nFilterIndex = 1;

	tmp.lpstrTitle = title.size() <= 0 ? nullptr : title.c_str();
	tmp.lpstrInitialDir = startDir.size() <= 0 ? nullptr : startDir.c_str();

	tmp.Flags = flgs[ChStd::EnumCast(FlgType::Save)];

	GetSaveFileName(&tmp);
	fileName = tmp2;

	delete[] tmp2;

	SetCurrentDirectory(baseDir.c_str());

	openFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChWin::FileDialog::CreateFilterStr()
{
	tmpType.clear();

	for (auto&& fil : filters)
	{
		tmpType += fil.first + "(" + "*" + fil.second + ")" + cutChar + "*" + fil.second + cutChar;

	}
	

}


///////////////////////////////////////////////////////////////////////////////////////

std::string ChWin::FileDialog::PathToRerative()
{

	size_t tmp = fileName.find_last_of("\\",fileName.size());

	std::string baseStr;

	baseStr = fileName;

	baseStr.replace(0, tmp + 1, "");

	return baseStr;
}

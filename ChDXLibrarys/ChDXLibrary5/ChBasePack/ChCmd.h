#ifndef Ch_CPP_Cmd_h
#define Ch_CPP_Cmd_h

//�g�p�s��//
/*
namespace ChCmd
{
#ifdef _WINDEF_

	 ChStd::Bool RawNoLookCmd(const std::string& _Str);

	 //������//
	 //�l�b�g��ɑ��݂���1�f�B���N�g�����_�E�����[�h����//
	static inline ChStd::Bool DLDir
	(
		ChStd::Bool _LookWindFlg
		, const std::string& _DownloadFileName
		, const std::string& _NetPath
		, const std::string& _AtPath = ""
	)
	{
		std::string DownloadPath = _NetPath + _DownloadFileName;


		system("");

	}

	//������//
	//�l�b�g��ɑ��݂���1�t�@�C�����_�E�����[�h����//
	static inline ChStd::Bool DLFile
	(
		ChStd::Bool _LookWindFlg
		, const std::string& _DownloadFileName
		, const std::string& _NetPath
		, const std::string& _AtPath = ""
	)
	{

		std::string DownloadPath = _NetPath + _DownloadFileName;

		std::string Script = "bitsadmin /transfer DownLoad "
			+ _NetPath
			+ _DownloadFileName + " " + _AtPath;

		if (_AtPath.length() < 1)Script += "%CD%";

		Script += _DownloadFileName;

		if (_LookWindFlg)
		{

			system(Script.c_str());
		}

		return RawNoLookCmd(Script);
	}

	//�V�����f�B���N�g�����쐬����//
	static inline ChStd::Bool Make(
		ChStd::Bool _LookWindFlg
		, const std::string& _DirectoryName
	)
	{
		std::string TmpStr = "Make " + _DirectoryName;

		if (_LookWindFlg)
		{

			if (system(TmpStr.c_str()) < 0)return false;

			return true;
		}


		return RawNoLookCmd(TmpStr);
	}

	//������//
	static inline ChStd::Bool RawNoLookCmd(const std::string& _Str)
	{

		std::string TmpStr = _Str;

		std::string TmpPath;
		GetCurrentDirectory(TmpPath.max_size(), &TmpPath[0]);

		STARTUPINFO CmdSetUp;
		PROCESS_INFORMATION ProcessInfo;

		ZeroMemory(&CmdSetUp, sizeof(CmdSetUp));
		ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));
		CmdSetUp.cb = sizeof(CmdSetUp);
		CmdSetUp.dwFlags = STARTF_USESHOWWINDOW;
		CmdSetUp.wShowWindow = SW_HIDE;

		ChStd::Bool TFlg = CreateProcess(0, &TmpStr[0], 0, 0, false, NORMAL_PRIORITY_CLASS
			, 0, &TmpPath[0], &CmdSetUp, &ProcessInfo);
		WaitForSingleObject(ProcessInfo.hProcess, (DWORD)INFINITY);
		CloseHandle(ProcessInfo.hProcess);
		CloseHandle(ProcessInfo.hThread);

		return TFlg;

	}

#endif
}

*/

#endif
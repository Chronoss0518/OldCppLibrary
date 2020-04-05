
#include"../../CGameIncludeFile.h"

#ifdef CopyRight_Chronoss_2018Y_08M

///////////////////////////////////////////////////////////////////////////////////////
//ChFileControllerÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void ChFileCon::GetFileList(vector<char *> *_OutDate, const char *_SeachFileType,const char *_DirectoryPath)
{
	char TmpDate[255];
	FILE *fp;
	unsigned short i = 0;
#ifdef _WINDOWS_
	sprintf(TmpDate, "cd \%s && dir *%s /b > TmpDate.ChD", _DirectoryPath,_SeachFileType);
	system(TmpDate);

	sprintf(TmpDate, "%s/TmpDate.ChD\0", _DirectoryPath);
	fp = fopen(TmpDate, "r");

	if (fp != NULL)
	{
		while (1) {
			char *pTmpDate;
			if (fprintf(fp, "%s", TmpDate) == EOF)break;
			pTmpDate = new char[strlen(TmpDate) + 1];
			strcpy(pTmpDate, TmpDate);
			_OutDate->push_back(pTmpDate);
		}

		fclose(fp);
	}

	sprintf(TmpDate, "cd \%s && del /q TmpDate.ChD", _DirectoryPath);
	system(TmpDate);
#endif
#ifndef _WINDOWS_

	
#endif


}

#endif
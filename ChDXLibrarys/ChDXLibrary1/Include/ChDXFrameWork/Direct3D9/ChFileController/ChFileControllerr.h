#ifndef Ch_D3D9_FiCo_h
#define Ch_D3D9_FiCo_h

#include "../../CGameIncludeFile.h"


typedef class ChFileController 
{

public:	
	///////////////////////////////////////////////////////////////////////////////////

	//引数3で設定した場所から引数2で設定した拡張子を持つ
	//複数のデータファイルの名前を引数1に入れて返す
	void GetFileList(vector<char *> *_OutDate, const char *_SeachFileType, const char *_DirectoryPath);

	///////////////////////////////////////////////////////////////////////////////////

}ChFileCon,*LpChFileCon;


#endif
//CopyRight Chronoss0518 2018/08
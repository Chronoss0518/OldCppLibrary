#ifndef Ch_D3D9_FiCo_h
#define Ch_D3D9_FiCo_h

#include "../../CGameIncludeFile.h"


typedef class ChFileController 
{

public:	
	///////////////////////////////////////////////////////////////////////////////////

	//����3�Őݒ肵���ꏊ�������2�Őݒ肵���g���q������
	//�����̃f�[�^�t�@�C���̖��O������1�ɓ���ĕԂ�
	void GetFileList(vector<char *> *_OutDate, const char *_SeachFileType, const char *_DirectoryPath);

	///////////////////////////////////////////////////////////////////////////////////

}ChFileCon,*LpChFileCon;


#endif
//CopyRight Chronoss0518 2018/08
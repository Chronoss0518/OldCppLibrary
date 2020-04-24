#ifndef Ch_D3D9_Ins_X_h
#define Ch_D3D9_Ins_X_h

#include"../../CGameIncludeFile.h"

typedef class ChSimpleXFile {
private:

public:
	unsigned short ModelNum;
	LPD3DXMESH LpMesh;//���b�V���̌`��
	DWORD NumMaterial;//�}�e���A���̐�
	D3DMATERIAL9 *Mat;//�}�e���A���̓��e
	LPDIRECT3DTEXTURE9 *Tex;//�e�N�X�`���[�̓��e

	///////////////////////////////////////////////////////////////////////////////////

	ChSimpleXFile(LPDIRECT3DDEVICE9 _d, const char *FileName,const unsigned short DateNum);

	///////////////////////////////////////////////////////////////////////////////////

	~ChSimpleXFile();

}ChSmpX,*LpChSmpX;



typedef class ChSimplicityXfileList {
private:

	LPDIRECT3DDEVICE9 Device;

	vector<LpChSmpX>SmpXFilelist;

	///////////////////////////////////////////////////////////////////////////////////

	LpChSmpX CheckSmpXFile(const unsigned short DateNum)
	{
		for (unsigned short i = 0; i < SmpXFilelist.size(); i++) {
			if (DateNum == SmpXFilelist[i]->ModelNum)return SmpXFilelist[i];
		}
		return nullptr;
	}

	///////////////////////////////////////////////////////////////////////////////////

public:

	///////////////////////////////////////////////////////////////////////////////////

	ChSimplicityXfileList(LPDIRECT3DDEVICE9 _d) 
	{Device = _d;}

	///////////////////////////////////////////////////////////////////////////////////

	~ChSimplicityXfileList(void)
	{
		if (SmpXFilelist.empty())return;
		SmpXFilelist.clear();
	}

	///////////////////////////////////////////////////////////////////////////////////

	LpChSmpX GetSmpXFile(const unsigned short DateNum){return SmpXFilelist[DateNum]; }

	///////////////////////////////////////////////////////////////////////////////////

	//XFile�̓o�^(DateName���g����3D���f����I������)
	void SetSmpXFile(const char *_SmpXFileName, const unsigned short DateNum);

	///////////////////////////////////////////////////////////////////////////////////

	//DateName�̃f�[�^�������Ă���
	void DrawSmpXFile(const D3DXMATRIX *_Mat,const unsigned short DateNum);



}ChSmpXlist, *LpChSmpXlist;

#endif
//CopyRight Chronoss0518 2018/08
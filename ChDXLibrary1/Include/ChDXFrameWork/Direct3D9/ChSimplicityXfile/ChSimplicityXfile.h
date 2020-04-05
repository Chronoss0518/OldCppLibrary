#ifndef Ch_D3D9_Ins_X_h
#define Ch_D3D9_Ins_X_h

#include"../../CGameIncludeFile.h"

typedef class ChSimpleXFile {
private:

public:
	unsigned short ModelNum;
	LPD3DXMESH LpMesh;//メッシュの形状
	DWORD NumMaterial;//マテリアルの数
	D3DMATERIAL9 *Mat;//マテリアルの内容
	LPDIRECT3DTEXTURE9 *Tex;//テクスチャーの内容

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

	//XFileの登録(DateNameを使って3Dモデルを選択する)
	void SetSmpXFile(const char *_SmpXFileName, const unsigned short DateNum);

	///////////////////////////////////////////////////////////////////////////////////

	//DateNameのデータを持ってくる
	void DrawSmpXFile(const D3DXMATRIX *_Mat,const unsigned short DateNum);



}ChSmpXlist, *LpChSmpXlist;

#endif
//CopyRight Chronoss0518 2018/08
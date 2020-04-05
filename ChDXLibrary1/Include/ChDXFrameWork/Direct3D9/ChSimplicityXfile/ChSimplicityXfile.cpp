
#include"../../CGameIncludeFile.h"

#ifdef CopyRight_Chronoss_2018Y_08M

///////////////////////////////////////////////////////////////////////////////////////
//ChSimpleXFileメソッド
///////////////////////////////////////////////////////////////////////////////////////

ChSmpX::ChSimpleXFile(LPDIRECT3DDEVICE9 _d,const char *FileName, const unsigned short DateNum)
{

	ModelNum = DateNum;

	LPD3DXBUFFER lpD3DXBuffer;

	D3DXLoadMeshFromX(FileName, D3DXMESH_MANAGED, _d, NULL, &lpD3DXBuffer, NULL, &(NumMaterial), &(LpMesh));

	Mat = new D3DMATERIAL9[NumMaterial];
	Tex = new LPDIRECT3DTEXTURE9[NumMaterial];

	D3DXMATERIAL* D3DXMat = (D3DXMATERIAL*)lpD3DXBuffer->GetBufferPointer();

	DWORD i;
	for (i = 0; i < NumMaterial; i++) {
		Mat[i] = D3DXMat[i].MatD3D;
		Mat[i].Ambient = Mat[i].Diffuse;

		if (FAILED(D3DXCreateTextureFromFile(_d, D3DXMat[i].pTextureFilename, &(Tex[i])))) {
			Tex[i] = NULL;
		}
	}

	lpD3DXBuffer->Release();

}

///////////////////////////////////////////////////////////////////////////////////

ChSmpX::~ChSimpleXFile() {

	if (LpMesh != NULL) {
		DWORD i;

		delete[] Mat;
		for (i = 0; i < NumMaterial; i++) {
			if (Tex[i] != NULL) {
				Tex[i]->Release();
				Tex[i] = NULL;
			}
		}
		delete[] Tex;
		LpMesh->Release();

		LpMesh = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//ChSimplicityXFileメソッド
///////////////////////////////////////////////////////////////////////////////////////

void ChSmpXlist::SetSmpXFile(const char *_SmpXFileName, const unsigned short DateNum)
{
	ChSmpX *TmpX = nullptr;

	if (CheckSmpXFile(DateNum) != nullptr)return;

	TmpX = new ChSmpX(Device,_SmpXFileName, DateNum);

	SmpXFilelist.push_back(TmpX);
}

///////////////////////////////////////////////////////////////////////////////////

void ChSmpXlist::DrawSmpXFile(const D3DXMATRIX *_Mat, const unsigned short DateNum)
{
	ChSmpX *TmpX = nullptr;
	Device->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	TmpX = CheckSmpXFile(DateNum);
	if (TmpX == nullptr)return;
	Device->SetTransform(D3DTS_WORLD, _Mat);
	DWORD i;
	for (i = 0; i < TmpX->NumMaterial; i++) {
		Device->SetMaterial(&TmpX->Mat[i]);
		Device->SetTexture(0, TmpX->Tex[i]);
		TmpX->LpMesh->DrawSubset(i);
	}

	Device->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}

#endif
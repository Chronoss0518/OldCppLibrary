#ifndef Ch_D3D9_Te_h
#define Ch_D3D9_Te_h

#include"../../CGameIncludeFile.h"

typedef class ChTex {
public:

	LPDIRECT3DTEXTURE9 Tex;	//�e�N�X�`���}�b�v���[�p
	float ScalingX;
	float ScalingY;
	unsigned short TexNum;
	unsigned int OWidth;	//�I���W�i���T�C�Y�̉���
	unsigned int OHeight;	//�I���W�i���T�C�Y�̏c��
	unsigned char cola, colr, colg, colb;	//�F�ʊ�{�F

	///////////////////////////////////////////////////////////////////////////////////

	ChTex(
		const unsigned short DateNum
		, const unsigned int _OriginalWidth
		, const unsigned int _OriginalHeight
		);

	///////////////////////////////////////////////////////////////////////////////////

	~ChTex() {
		Tex->Release();
	}

}*LpChTex;



typedef class ChTextureList
{
private:
	vector<LpChTex>TexList;

	LPDIRECT3DDEVICE9 Device;

	///////////////////////////////////////////////////////////////////////////////////

	LpChTex CheckTex(const unsigned short DateNum) {

		for (unsigned short i = 0; i < TexList.size(); i++) {
			if (TexList[i]->TexNum == DateNum)return TexList[i];
		}

		return nullptr;
	}

	///////////////////////////////////////////////////////////////////////////////////

	void LoadTex(LPDIRECT3DTEXTURE9 *lpTex,const char *_TextureName, unsigned int W, unsigned int H,const D3DCOLOR Color)
	{
		if (W == 0)W = D3DX_DEFAULT;
		if (H == 0)H = D3DX_DEFAULT;
		D3DXCreateTextureFromFileEx(Device, _TextureName, W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, lpTex);
	}

	///////////////////////////////////////////////////////////////////////////////////

public:

	///////////////////////////////////////////////////////////////////////////////////

	ChTextureList(LPDIRECT3DDEVICE9 _Dv) { Device = _Dv; }

	///////////////////////////////////////////////////////////////////////////////////

	~ChTextureList() 
	{
		if (TexList.empty())return;
		TexList.clear(); 
	}

	///////////////////////////////////////////////////////////////////////////////////

	void SetTexture(
		const char *_TextureName
		, const unsigned short DateNum
		, const unsigned int _OriginalWidth
		, const unsigned int _OriginalHeight
		, const unsigned int _GameReSizeWidth
		, const unsigned int _GameReSizeHeight
		,const D3DCOLOR ColorKey
	);

	///////////////////////////////////////////////////////////////////////////////////

	LpChTex GetTex(const unsigned short DateNum) { return CheckTex(DateNum); }

	///////////////////////////////////////////////////////////////////////////////////

	//�����F�A��{�F�̐ݒ�
	void SetBlendColor(const unsigned char _a, const unsigned char _r, const unsigned char _g, const unsigned char _b, const unsigned short DateNum);

	///////////////////////////////////////////////////////////////////////////////////

	//�摜�̓������ݒ�
	void SetBlendAlpha(const unsigned char _a, const unsigned short DateNum) { 
		LpChTex TmpTex = CheckTex(DateNum);
		if (TmpTex == nullptr)return;
		TmpTex->cola = _a;
	}

	///////////////////////////////////////////////////////////////////////////////////

}ChTexlist, *LPChTexlist;


#endif
//CopyRight Chronoss0518 2018/08
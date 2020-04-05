
#include"../../CGameIncludeFile.h"

#ifdef CopyRight_Chronoss_2018Y_08M

//=====================================================================================
//ChTexメンバー関数
//=====================================================================================

ChTex::ChTex(
	const unsigned short DateNum
	, const unsigned int _OriginalWidth
	, const unsigned int _OriginalHeight)
{
	TexNum = DateNum;
	cola = 255;
	colr = 255;
	colg = 255;
	colb = 255;
	OWidth = _OriginalWidth;
	OHeight = _OriginalHeight;

}

//=====================================================================================
//ChTextureListメンバー関数
//=====================================================================================

void ChTexlist::SetTexture(
	const char *_TextureName
	, const unsigned short DateNum
	, const unsigned int _OriginalWidth
	, const unsigned int _OriginalHeight
	, const unsigned int _GameReSizeWidth
	, const unsigned int _GameReSizeHeight
	, const D3DCOLOR ColorKey
) {
	if (CheckTex(DateNum) != nullptr)return;
	LpChTex TmpTex = nullptr;
	TmpTex = new ChTex(DateNum, _OriginalWidth, _OriginalHeight);

	LoadTex(&TmpTex->Tex, _TextureName, TmpTex->OWidth, TmpTex->OHeight, ColorKey);
	if (TmpTex->Tex == NULL || TmpTex->Tex == nullptr) 
	{
		delete TmpTex;
		return;
	}
	float tmpX, tmpY;
	tmpX = (float)_GameReSizeWidth / (float)TmpTex->OWidth;
	tmpY = (float)_GameReSizeHeight / (float)TmpTex->OHeight;
	if (_GameReSizeWidth == TmpTex->OWidth)tmpX = 0.0f;
	if (_GameReSizeHeight == TmpTex->OHeight)tmpY = 0.0f;
	TmpTex->ScalingX = tmpX;
	TmpTex->ScalingY = tmpY;
	TexList.push_back(TmpTex);
}

///////////////////////////////////////////////////////////////////////////////////

void ChTexlist::SetBlendColor(const unsigned char _a, const unsigned char _r, const unsigned char _g, const unsigned char _b, const unsigned short DateNum)
{
	LpChTex TmpTex = CheckTex(DateNum);
	if (TmpTex == nullptr)return;
	TmpTex->cola = _a;
	TmpTex->colr = _r;
	TmpTex->colg = _g;
	TmpTex->colb = _b;
}

#endif
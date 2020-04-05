
#include"../../CGameIncludeFile.h"

#ifdef CopyRight_Chronoss_2018Y_08M

//=====================================================================================
//ChSpriteƒƒ“ƒo[ŠÖ”
//=====================================================================================

ChSprite::ChSprite( LPDIRECT3DDEVICE9 _d)
{
	Device = _d;

	D3DXCreateSprite(Device, &Sp);
	Sp->OnResetDevice();


}

///////////////////////////////////////////////////////////////////////////////////

ChSprite::~ChSprite() {
	Sp->Release();
}

///////////////////////////////////////////////////////////////////////////////////

void ChSprite::DrawSprite(LpChTex _tex, const D3DXMATRIX *_Mat)
{

	Sp->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIX tmpMatT,tmpMatS,tmpMat;
	D3DXMatrixTranslation(&tmpMatT, (float)(_tex->OWidth / 2.0f), (float)(_tex->OHeight / 2.0f), 0.0f);
	D3DXMatrixScaling(&tmpMatS, _tex->ScalingX, _tex->ScalingY, 0.0f);
	tmpMat = (*_Mat) * tmpMatT * tmpMatS;

	Device->SetTransform(D3DTS_WORLD, &tmpMat);
	Device->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1));

	RECT TmpRec{ 0,0, _tex->OWidth,_tex->OHeight };
	Sp->Draw(_tex->Tex, &TmpRec, &D3DXVECTOR3((float)(_tex->OWidth / 2.0f), (float)(_tex->OHeight / 2.0f), 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_ARGB(255, 255, 255, 255));
	Sp->End();
}

#endif
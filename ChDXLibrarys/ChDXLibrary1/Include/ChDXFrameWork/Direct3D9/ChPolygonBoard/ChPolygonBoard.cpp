
#include"../../CGameIncludeFile.h"

#ifdef CopyRight_Chronoss_2018Y_08M

//=====================================================================================
//ChSPolygonBordÉÅÉìÉoÅ[ä÷êî
//=====================================================================================

ChPoBo::ChPolygonBoard(LPDIRECT3DDEVICE9 _Dv)
{
	Device = _Dv;
	SetXYPosition(&D3DXVECTOR3(1.0f, 1.0f, 0.0f), 2.0f, 2.0f);
	for (unsigned char i = 0; i < VertexMaxCnt; i++) {
		SetColor(D3DCOLOR_ARGB(255, 255, 255, 255), i);
		//Ver[i].specular = D3DCOLOR_ARGB(255, 255, 255, 255);
	}
	AlphaFlg = FALSE;
	SetTex(D3DXVECTOR2(0.0f, 0.0f), 0);
	SetTex(D3DXVECTOR2(1.0f, 0.0f), 1);
	SetTex(D3DXVECTOR2(1.0f, 1.0f), 2);
	SetTex(D3DXVECTOR2(0.0f, 1.0f), 3);

}

///////////////////////////////////////////////////////////////////////////////////

void ChPoBo::SetXYPosition(const D3DXVECTOR3 *_LeftTopPos, const float _X, const float _Y)
{
	for (char i = 0; i < VertexMaxCnt; i++) {
		Ver[i].pos = *_LeftTopPos;
	}

	Ver[1].pos.x += _X;
	Ver[2].pos.x += _X;
	Ver[2].pos.y -= _Y;
	Ver[3].pos.y -= _Y;
}

///////////////////////////////////////////////////////////////////////////////////

void ChPoBo::SetYZPosition(const D3DXVECTOR3 *_LeftTopPos, const float _Z, const float _Y)
{
	for (char i = 0; i < VertexMaxCnt; i++) {
		Ver[i].pos = *_LeftTopPos;
	}

	Ver[1].pos.z += _Z;
	Ver[2].pos.z += _Z;
	Ver[2].pos.y -= _Y;
	Ver[3].pos.y -= _Y;
}

///////////////////////////////////////////////////////////////////////////////////

void ChPoBo::SetZXPosition(const D3DXVECTOR3 *_LeftTopPos, const float _X, const float _Z)
{
	for (char i = 0; i < VertexMaxCnt; i++) {
		Ver[i].pos = *_LeftTopPos;
	}

	Ver[1].pos.x += _X;
	Ver[2].pos.x += _X;
	Ver[2].pos.z -= _Z;
	Ver[3].pos.z -= _Z;
}

///////////////////////////////////////////////////////////////////////////////////

void ChPoBo::Draw(const LpChTex _Tex, const LPD3DXMATRIX _Mat)
{

	if(AlphaFlg)Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	Device->SetTexture(0, _Tex->Tex);
	Device->SetTransform(D3DTS_WORLD, _Mat);
	//Device->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_SPECULAR | D3DFVF_NORMAL));
	Device->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1));
	/*
		if (UpDateFlg)
		{
			Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, Ver, sizeof(ChVertex));
		}
		else
		{*/
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, Ver, sizeof(ChVertex));
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	/*
}*/

}

#endif
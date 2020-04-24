
#include<Windows.h>
#include"../../ChInclude/ChGameBI.h"
#include"../../ChInclude/ChD3D9I.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"ChPolygonBoard9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////
//ChPolygonBord9ÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::Init(const LPDIRECT3DDEVICE9& _Dv)
{
	Device = _Dv;
	SetXYPosition(ChVec3_9(1.0f, 1.0f, 0.0f), 2.0f, 2.0f);
	for (unsigned char i = 0; i < VertexMaxCnt; i++) {
		SetColor(D3DCOLOR_ARGB(255, 255, 255, 255), i);
		//Ver[i].specular = D3DCOLOR_ARGB(255, 255, 255, 255);
	}
	AlphaFlg = FALSE;
	Ver[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Ver[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Ver[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	Ver[3].tex = D3DXVECTOR2(0.0f, 1.0f);

	InitFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::SetXYPosition(const ChVec3_9& _LeftTopPos, const float _X, const float _Y)
{
	for (char i = 0; i < VertexMaxCnt; i++) {
		Ver[i].pos = _LeftTopPos;
	}

	Ver[1].pos.x += _X;
	Ver[2].pos.x += _X;
	Ver[2].pos.y -= _Y;
	Ver[3].pos.y -= _Y;
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::SetYZPosition(const ChVec3_9& _LeftTopPos, const float _Z, const float _Y)
{
	for (char i = 0; i < VertexMaxCnt; i++) {
		Ver[i].pos = _LeftTopPos;
	}

	Ver[1].pos.z += _Z;
	Ver[2].pos.z += _Z;
	Ver[2].pos.y -= _Y;
	Ver[3].pos.y -= _Y;
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::SetZXPosition(const ChVec3_9& _LeftTopPos, const float _X, const float _Z)
{
	for (char i = 0; i < VertexMaxCnt; i++) {
		Ver[i].pos = _LeftTopPos;
	}

	Ver[1].pos.x += _X;
	Ver[2].pos.x += _X;
	Ver[2].pos.z -= _Z;
	Ver[3].pos.z -= _Z;
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::Draw(
	const ChPtr::Shared<BaseTexture9>& _Tex
	, const LPD3DXMATRIX& _Mat)
{
	if (_Tex == nullptr)return;

	DWORD TmpData;
	Device->GetRenderState(D3DRS_CULLMODE, &TmpData);
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	if (AlphaFlg)Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	Device->SetTexture(0, _Tex->GetTex());

	Device->SetTransform(D3DTS_WORLD, _Mat);

	//Device->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_SPECULAR | D3DFVF_NORMAL));

	Device->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1));

	/*
		if (UpDateFlg)
		{
			Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, Ver, sizeof(ChVertex));
		}
		else
		{
	*/

	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	Device->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

	Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, Ver, sizeof(ChVertex9));
	
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	Device->SetRenderState(D3DRS_NORMALIZENORMALS, ChStd::True);
	Device->SetRenderState(D3DRS_CULLMODE, TmpData);
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::SetPositionVector(const D3DXVECTOR3* _Pos, const char _PosNo)
{
	if (_PosNo > VertexMaxCnt)return;
	if (ChPtr::NullCheck(_Pos))return;
	Ver[_PosNo].pos = *_Pos;
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::SetColor(const D3DCOLOR _Col, const unsigned char _PosNo)
{
	if (_PosNo > VertexMaxCnt)return;
	Ver[_PosNo].col = _Col;
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::SetTex(const D3DXVECTOR2 _Tex, const unsigned char _PosNo)
{
	if (_PosNo > VertexMaxCnt)return;
	Ver[_PosNo].tex = _Tex;
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::SetRectTex(
	const ChPtr::Shared<BaseTexture9> _Tex
	, const RECT& _rect
	, const unsigned char _SPosNo)
{
	if (_Tex == nullptr)return;
	if (_SPosNo > VertexMaxCnt)return;
	D3DXVECTOR2 TmpVec;
	TmpVec = D3DXVECTOR2((float)(_rect.right / _Tex->GetOriginalWidth()), (float)(_rect.top / _Tex->GetOriginalHeight()));
	Ver[(_SPosNo + 0) % VertexMaxCnt].tex = TmpVec;
	TmpVec = D3DXVECTOR2((float)((_rect.right + _rect.left) / _Tex->GetOriginalWidth())
		, (float)(_rect.top / _Tex->GetOriginalHeight()));
	Ver[(_SPosNo + 1) % VertexMaxCnt].tex = TmpVec;
	TmpVec = D3DXVECTOR2((float)((_rect.right + _rect.left) / _Tex->GetOriginalWidth())
		, (float)((_rect.top + _rect.bottom) / _Tex->GetOriginalHeight()));
	Ver[(_SPosNo + 2) % VertexMaxCnt].tex = TmpVec;
	TmpVec = D3DXVECTOR2((float)(_rect.right / _Tex->GetOriginalWidth())
		, (float)((_rect.top + _rect.bottom) / _Tex->GetOriginalHeight()));
	Ver[(_SPosNo + 3) % VertexMaxCnt].tex = TmpVec;
}

///////////////////////////////////////////////////////////////////////////////////
//
//void ChPolygonBoard9::SetNormal(const D3DXVECTOR3 _Normal, const char _PosNo)
//{
//	if (_PosNo > VertexMaxCnt)return;
//	//Ver[_PosNo].normal = _Normal;
//}

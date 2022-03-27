
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"ChPolygonBoard9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////
//ChPolygonBord9ÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::Init(const LPDIRECT3DDEVICE9& _dv)
{
	device = _dv;
	SetXYPosition(ChVec3_9(1.0f, 1.0f, 0.0f), 2.0f, 2.0f);
	for (unsigned char i = 0; i < vertexMaxCnt; i++) {
		SetColor(D3DCOLOR_ARGB(255, 255, 255, 255), i);
		//ver[i].specular = D3DCOLOR_ARGB(255, 255, 255, 255);
	}
	alphaFlg = FALSE;
	ver[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	ver[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	ver[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	ver[3].tex = D3DXVECTOR2(0.0f, 1.0f);

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::SetXYPosition(const ChVec3_9& _leftTopPos, const float _x, const float _y)
{
	for (char i = 0; i < vertexMaxCnt; i++) {
		ver[i].pos = _leftTopPos;
	}

	ver[1].pos.x += _x;
	ver[2].pos.x += _x;
	ver[2].pos.y -= _y;
	ver[3].pos.y -= _y;
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::SetYZPosition(const ChVec3_9& _leftTopPos, const float _z, const float _y)
{
	for (char i = 0; i < vertexMaxCnt; i++) {
		ver[i].pos = _leftTopPos;
	}

	ver[1].pos.z += _z;
	ver[2].pos.z += _z;
	ver[2].pos.y -= _y;
	ver[3].pos.y -= _y;
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::SetZXPosition(const ChVec3_9& _leftTopPos, const float _x, const float _z)
{
	for (char i = 0; i < vertexMaxCnt; i++) {
		ver[i].pos = _leftTopPos;
	}

	ver[1].pos.x += _x;
	ver[2].pos.x += _x;
	ver[2].pos.z -= _z;
	ver[3].pos.z -= _z;
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::Draw(
	const ChPtr::Shared<BaseTexture9>& _tex
	, const LPD3DXMATRIX& _mat)
{
	if (!*this)return;
	if (_tex == nullptr)return;

	DWORD tmpData;
	device->GetRenderState(D3DRS_CULLMODE, &tmpData);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	if (alphaFlg)device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	device->SetTexture(0, _tex->GetTex());

	device->SetTransform(D3DTS_WORLD, _mat);

	//device->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_SPECULAR | D3DFVF_NORMAL));

	device->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1));

	/*
		if (UpDateFlg)
		{
			device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, ver, sizeof(Chvertex));
		}
		else
		{
	*/

	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

	device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, ver, sizeof(ChVertex9));
	
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	device->SetRenderState(D3DRS_CULLMODE, tmpData);
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::SetPositionVector(const D3DXVECTOR3* _pos, const char _posNo)
{
	if (_posNo > vertexMaxCnt)return;
	if (ChPtr::NullCheck(_pos))return;
	ver[_posNo].pos = *_pos;
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::SetColor(const D3DCOLOR _col, const unsigned char _posNo)
{
	if (_posNo > vertexMaxCnt)return;
	ver[_posNo].col = _col;
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::SetTex(const D3DXVECTOR2 _tex, const unsigned char _posNo)
{
	if (_posNo > vertexMaxCnt)return;
	ver[_posNo].tex = _tex;
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard9::SetRectTex(
	const ChPtr::Shared<BaseTexture9> _tex
	, const RECT& _rect
	, const unsigned char _SPosNo)
{
	if (_tex == nullptr)return;
	if (_SPosNo > vertexMaxCnt)return;
	D3DXVECTOR2 tmpVec;
	tmpVec = D3DXVECTOR2((float)(_rect.right / _tex->GetOriginalWidth()), (float)(_rect.top / _tex->GetOriginalHeight()));
	ver[(_SPosNo + 0) % vertexMaxCnt].tex = tmpVec;
	tmpVec = D3DXVECTOR2((float)((_rect.right + _rect.left) / _tex->GetOriginalWidth())
		, (float)(_rect.top / _tex->GetOriginalHeight()));
	ver[(_SPosNo + 1) % vertexMaxCnt].tex = tmpVec;
	tmpVec = D3DXVECTOR2((float)((_rect.right + _rect.left) / _tex->GetOriginalWidth())
		, (float)((_rect.top + _rect.bottom) / _tex->GetOriginalHeight()));
	ver[(_SPosNo + 2) % vertexMaxCnt].tex = tmpVec;
	tmpVec = D3DXVECTOR2((float)(_rect.right / _tex->GetOriginalWidth())
		, (float)((_rect.top + _rect.bottom) / _tex->GetOriginalHeight()));
	ver[(_SPosNo + 3) % vertexMaxCnt].tex = tmpVec;
}

///////////////////////////////////////////////////////////////////////////////////
//
//void ChPolygonBoard9::SetNormal(const D3DXVECTOR3 _Normal, const char _posNo)
//{
//	if (_posNo > vertexMaxCnt)return;
//	//ver[_posNo].normal = _Normal;
//}

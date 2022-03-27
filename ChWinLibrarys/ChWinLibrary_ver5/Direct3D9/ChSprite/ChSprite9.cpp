
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"ChSprite9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////
//ChSprite9ƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////

void Sprite9::Init(const LPDIRECT3DDEVICE9 _d)
{
	device = _d;

	D3DXCreateSprite(device, &sp);
	sp->OnResetDevice();

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite9::Release() {
	if(ChPtr::NotNullCheck(sp))sp->Release();
	sp = nullptr;

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite9::DrawSprite(
	const ChPtr::Shared<Texture9> _tex
	, const ChMat_9 &_mat
	, const ChVec3_9 &_centerPos
	, const RECT &_animationRect)
{
	if (!*this)return;

	if(_tex == nullptr)return;
	if (ChPtr::NullCheck(_tex->GetTex()))
	{
		//ChSystem::ErrerMessage("•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½", "Œx");

	}
	ChVec3_9 tmpVec;

	RECT tmpRec{ 0,0, (long)_tex->GetOriginalWidth(),(long)_tex->GetOriginalHeight() };

	if (_animationRect.top != _animationRect.bottom
		&& _animationRect.left != _animationRect.right)tmpRec = _animationRect;

	ChMat_9 tmpMat;

	if (_tex->GetSclXSize() != 0.0f && _tex->GetSclYSize() != 0.0f)
		tmpMat.Scaling(_tex->GetSclXSize(), _tex->GetSclYSize(), 0.0f);

	tmpMat = (_mat) * tmpMat;

	sp->Begin(D3DXSPRITE_ALPHABLEND);

	device->SetTransform(D3DTS_WORLD, &tmpMat);
	device->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1));

	auto tmp = D3DXVECTOR3((float)(_tex->GetOriginalWidth() / 2.0f), (float)(_tex->GetOriginalHeight() / 2.0f), 0.0f);

	sp->Draw(
		_tex->GetTex()
		, &tmpRec
		, &tmp
		, &tmpVec
		, _tex->GetBaseColD3D());

	sp->End();
}

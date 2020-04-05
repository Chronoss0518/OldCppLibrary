
#include"../../ChGameIncludeFile.h"
#include<d3d9.h>
#include<d3dx9.h>
#include<d3dx9anim.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include"Direct3D9/ChPackDate/ChMatrix_9.h"
#include"Direct3D9/ChPackDate/ChVector3_9.h"
#include"Direct3D9/ChPackDate/ChQuaternion_9.h"
#include"Direct3D9/ChPackDate/ChMaterial9.h"
#include"Direct3D9/ChDirectX9Controller/ChDirectX9Controller.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"ChSprite9.h"

using namespace ChTex;
using namespace ChSystem;

///////////////////////////////////////////////////////////////////////////////////
//ChSprite9メソッド
///////////////////////////////////////////////////////////////////////////////////

void Sprite9::Init(const LPDIRECT3DDEVICE9 _d)
{
	Device = _d;

	D3DXCreateSprite(Device, &Sp);
	Sp->OnResetDevice();


}

///////////////////////////////////////////////////////////////////////////////////

void Sprite9::Release() {
	if(ChPtr::NotNullCheck(Sp))Sp->Release();
	Sp = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite9::DrawSprite(
	const ChPtr::Shared<Texture9> _tex
	, const ChMat_9 &_Mat
	, const ChVec3_9 &_CenterPos
	, const RECT &_AnimationRect)
{
	if(_tex == nullptr)return;
	if (ChPtr::NullCheck(_tex->GetTex()))
	{
		ChSystem::ErrerMessage("描画に失敗しました", "警告");

	}
	ChVec3_9 TmpVec;

	RECT TmpRec{ 0,0, (long)_tex->GetOriginalWidth(),(long)_tex->GetOriginalHeight() };

	if (_AnimationRect.top != _AnimationRect.bottom
		&& _AnimationRect.left != _AnimationRect.right)TmpRec = _AnimationRect;

	ChMat_9 tmpMat;

	if (_tex->GetSclXSize() != 0.0f && _tex->GetSclYSize() != 0.0f)
		tmpMat.Scaling(_tex->GetSclXSize(), _tex->GetSclYSize(), 0.0f);

	tmpMat = (_Mat) * tmpMat;

	Sp->Begin(D3DXSPRITE_ALPHABLEND);

	Device->SetTransform(D3DTS_WORLD, &tmpMat);
	Device->SetFVF((D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1));

	Sp->Draw(
		_tex->GetTex()
		, &TmpRec
		, &D3DXVECTOR3((float)(_tex->GetOriginalWidth() / 2.0f), (float)(_tex->GetOriginalHeight() / 2.0f), 0.0f)
		, &TmpVec
		, _tex->GetBaseColD3D());

	Sp->End();
}

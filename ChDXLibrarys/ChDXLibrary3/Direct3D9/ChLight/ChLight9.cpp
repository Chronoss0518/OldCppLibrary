
#include<d3d9.h>
#include<d3dx9.h>
#include<d3dx9anim.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include"../../ChGameIncludeFile.h"

#include"Direct3D9/ChPackDate/ChMatrix_9.h"
#include"Direct3D9/ChPackDate/ChVector3_9.h"
#include"Direct3D9/ChPackDate/ChQuaternion_9.h"
#include"Direct3D9/ChPackDate/ChMaterial9.h"
#include"Direct3D9/ChDirectX9Controller/ChDirectX9Controller.h"

#include"ChLight9.h"

///////////////////////////////////////////////////////////////////////////////////////
//ChLight9���\�b�h
///////////////////////////////////////////////////////////////////////////////////////

ChLight9::ChLight9(LPDIRECT3DDEVICE9 _Dv) 
{
	Device = _Dv;
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);

	///////////////////////////////////////////////////////////////////////////////////////
	//TypeSet(�����̎��)

	Light.Type = D3DLIGHT_DIRECTIONAL;

	///////////////////////////////////////////////////////////////////////////////////////
	//DirectionSet(���C�g�̊p�x)

	Light.Direction = D3DXVECTOR3(1.0f, -1.0f, 0.0f);

	///////////////////////////////////////////////////////////////////////////////////
	//Position(light�̈ʒu)

	SetPos(&D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	///////////////////////////////////////////////////////////////////////////////////////
	//DiffuserSet(�����F)

	SetLightDif(1.0f, 1.0f, 1.0f, 1.0f);

	///////////////////////////////////////////////////////////////////////////////////////
	//SpecularSet(�������)
	SetLightSpe(FALSE, 1.0f, 1.0f, 1.0f);

	///////////////////////////////////////////////////////////////////////////////////////
	//AmbientSet(��������)

	SetLightAmb(FALSE, 1.0f, 1.0f, 1.0f);

	///////////////////////////////////////////////////////////////////////////////////////
	//RegisterLight

	Device->SetLight(0, &Light);
	Device->LightEnable(0, TRUE);

	///////////////////////////////////////////////////////////////////////////////////////
	//RangeSet(���C�g�͈̔�)

	Light.Range = 25.0f;

	///////////////////////////////////////////////////////////////////////////////////////
	//AttenuatSet(�������֍s�������̃��C�g�̋����v�Z)

	Light.Attenuation0 = 0.0f;
	Light.Attenuation1 = 0.2f;
	Light.Attenuation2 = 0.0f;

	///////////////////////////////////////////////////////////////////////////////////////
	//PositionSet(Point,SpotLight���̃��C�g�̈ʒu)

	Light.Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


}

///////////////////////////////////////////////////////////////////////////////////

	//Light���g�p���邩���Ȃ����̐ݒ�
void ChLight9::SetLight(bool Flg)
{
	Device->LightEnable(0, TRUE);
}

///////////////////////////////////////////////////////////////////////////////////

//Light�̊p�x�̐ݒ�
void ChLight9::SetDir(const ChVec3_9& _Dir)
{
	ChVec3_9 TmpVec = _Dir;
	TmpVec.Normalize();
	Light.Direction = TmpVec;
	RegisterLight();
}

///////////////////////////////////////////////////////////////////////////////////

void ChLight9::SetPos(const D3DXVECTOR3 *_Pos)
{
	Light.Position = *_Pos;
}


///////////////////////////////////////////////////////////////////////////////////

//Light�̌����F�̃Z�b�g
void ChLight9::SetLightDif(const float _a, const float _r, const float _g, const float _b)
{
	Light.Diffuse.a = _a;
	Light.Diffuse.r = _r;
	Light.Diffuse.g = _g;
	Light.Diffuse.b = _b;
	RegisterLight();
}

///////////////////////////////////////////////////////////////////////////////////

//Light�̌�����ʂ̃Z�b�g
void ChLight9::SetLightSpe(bool _SpeFlg, const float _r, const float _g, const float _b)
{
	Device->SetRenderState(D3DRS_SPECULARENABLE, _SpeFlg);
	Light.Specular.r = _r;
	Light.Specular.g = _g;
	Light.Specular.b = _b;
	RegisterLight();
}

///////////////////////////////////////////////////////////////////////////////////

//Light�̌�����ʂ̃Z�b�g
void ChLight9::SetLightAmb(bool _AmbFlg, const float _r, const float _g, const float _b)
{
	Device->SetRenderState(D3DRS_AMBIENT, _AmbFlg);
	Light.Ambient.r = _r;
	Light.Ambient.g = _g;
	Light.Ambient.b = _b;
	RegisterLight();
}

///////////////////////////////////////////////////////////////////////////////////

void ChLight9::RegisterLight()
{
	Device->SetLight(0, &Light);
}
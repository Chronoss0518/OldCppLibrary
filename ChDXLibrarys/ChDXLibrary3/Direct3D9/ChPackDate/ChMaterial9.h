#ifndef Ch_D3D9_Mate9_h
#define Ch_D3D9_Mate9_h

#include"ChMatrix_9.h"


//D3DMATERIAL9をパック化したクラス//
//このままでは利用できないため、いったんD3DMATERIAL9に直す必要がある//
struct ChMaterial_9 :public D3DMATERIAL9
{
	//Material名
	std::string Name = "";
	

	//SubSet描画時に移動させるマテリアルの行列//
	ChMat_9 Mat;

	ChMaterial_9&operator=(const D3DMATERIAL9 _cm)
	{
		if (this == &_cm)return *this;
		D3DMATERIAL9::operator = (_cm);
		return *this;
	}

	D3DMATERIAL9&operator=(const ChMaterial_9 _cm)
	{
		D3DMATERIAL9 TmpMat;
		TmpMat.Ambient = _cm.Ambient;
		TmpMat.Diffuse = _cm.Diffuse;
		TmpMat.Emissive = _cm.Emissive;
		TmpMat.Power = _cm.Power;
		TmpMat.Specular = _cm.Specular;
		return  TmpMat;
	}

	ChMaterial_9(D3DMATERIAL9 &_cm) :D3DMATERIAL9(_cm) {};

	ChMaterial_9(){}
};

#endif
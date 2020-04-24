#ifndef Ch_D3D9_Mate9_h
#define Ch_D3D9_Mate9_h

#include"ChMatrix_9.h"


//D3DMATERIAL9���p�b�N�������N���X//
//���̂܂܂ł͗��p�ł��Ȃ����߁A��������D3DMATERIAL9�ɒ����K�v������//
struct ChMaterial_9 :public D3DMATERIAL9
{
	//Material��
	std::string Name = "";
	

	//SubSet�`�掞�Ɉړ�������}�e���A���̍s��//
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
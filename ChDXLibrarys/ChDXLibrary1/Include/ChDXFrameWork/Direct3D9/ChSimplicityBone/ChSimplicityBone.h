#pragma once


#include"../../CGameIncludeFile.h"
typedef struct ChSimplicityBoneMatrix
{
	unsigned char BoneNum;
	D3DXMATRIX BoneMat;//�ŏIBoneMatrix
	D3DXQUATERNION BoneQua;//Bone�𑀍삷�邽�߂�Quaternion
	D3DXVECTOR3 OffsetPos;//�ЂƂO��Bone�̑��Έʒu
	D3DXMATRIX *OffsetMat;//�ЂƂO��Bone��Matrix
}ChInsBone, *LpChInsBone;

//CopyRight Chronoss0518 2018/08
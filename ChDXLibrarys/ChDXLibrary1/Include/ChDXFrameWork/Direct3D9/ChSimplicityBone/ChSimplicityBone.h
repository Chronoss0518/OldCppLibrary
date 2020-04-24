#pragma once


#include"../../CGameIncludeFile.h"
typedef struct ChSimplicityBoneMatrix
{
	unsigned char BoneNum;
	D3DXMATRIX BoneMat;//最終BoneMatrix
	D3DXQUATERNION BoneQua;//Boneを操作するためのQuaternion
	D3DXVECTOR3 OffsetPos;//ひとつ前のBoneの相対位置
	D3DXMATRIX *OffsetMat;//ひとつ前のBoneのMatrix
}ChInsBone, *LpChInsBone;

//CopyRight Chronoss0518 2018/08
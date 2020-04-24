
#ifndef Ch_D3D9_Com_h
#define Ch_D3D9_Com_h

#include"../../CPP/ChBaseObject/ChBaseObject.h"

typedef class ChTransformComponent9 :public ChCpp::TransformCom
{
public:


	inline void Init()override
	{
		Rotation = ChQua_9();
		Position = ChVec3();
		Scalling = ChVec3(1.0f);
	}

	inline void SetMat(const D3DXMATRIX& _Mat)
	{
		ChMat_9 Mat = _Mat;

		ChVec3_9 TmpVec;
		ChQua_9 TmpQua;

		TmpVec = Mat;
		Position = TmpVec;

		TmpQua = Mat;
		Rotation = TmpQua;

		Scalling = Mat.GetScaleSize();
	}

	inline D3DXMATRIX GetMat()
	{
		ChMat_9 TmpMat;
		TmpMat = Rotation;

		TmpMat = Position;

		TmpMat.Scaling(Scalling);

		return TmpMat;

	}

}ChTransformCom9;

#endif

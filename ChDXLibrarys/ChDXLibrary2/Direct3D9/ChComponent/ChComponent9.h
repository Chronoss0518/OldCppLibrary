
#ifndef Ch_D3D9_Com_h
#define Ch_D3D9_Com_h

#include"../../CPP/ChBaseObject/ChBaseObject.h"

typedef class ChTransformComponent9 :public ChCpp::BaseComponent
{
public:

	ChVec3_9 Position;

	ChQua_9 Rotation;

	ChVec3_9 Scaling = ChVec3_9(1.0f, 1.0f, 1.0f);


	void SetMat(const ChMat_9& _Mat)
	{
		ChMat_9 Mat = _Mat;

		Position = Mat;

		Rotation = Mat;

		Scaling = Mat.GetScaleSize();
	}

	ChMat_9 GetMat()
	{
		ChMat_9 TmpMat;
		TmpMat = Rotation;

		TmpMat = Position;

		TmpMat.Scaling(Scaling);

		return TmpMat;

	}

}ChTransformCom9;

#endif

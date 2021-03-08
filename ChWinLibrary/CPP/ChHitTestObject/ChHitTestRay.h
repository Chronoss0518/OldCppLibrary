#ifndef Ch_CPP_HTR_h
#define Ch_CPP_HTR_h

#include"ChHitTestObject.h"

namespace ChCpp
{

	enum class HitTestRayDirctionAxis
	{
		Top, Down, Front, Back, Right, Left
	};

	class HitTestRay :public HitTestObject
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		ChStd::Bool IsHitPanel(
			const HitTestPanel* _Target)override;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		ChStd::Bool IsHitBox(
			const HitTestBox* _Target)override;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		ChStd::Bool IsHitSphere(
			const HitTestSphere* _Target)override;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		ChStd::Bool IsHitMesh(
			const HitTestMesh* _Target)override;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
		ChStd::Bool IsInnerHitBox(
			const HitTestBox* _Target)override;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
		ChStd::Bool IsInnerHitSphere(
			const HitTestSphere* _Target)override;

	private:

		const static std::map<HitTestRayDirctionAxis, std::function<ChVec3()>>GetRayAxis;

		HitTestRayDirctionAxis RayAxis;

		float MaxLen = FLT_MAX;

	};




}

#endif
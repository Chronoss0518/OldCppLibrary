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

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		ChStd::Bool IsHitPanel(
			const HitTestPanel* _Target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		ChStd::Bool IsHitBox(
			const HitTestBox* _Target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		ChStd::Bool IsHitSphere(
			const HitTestSphere* _Target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		ChStd::Bool IsHitMesh(
			const HitTestMesh* _Target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		ChStd::Bool IsInnerHitBox(
			const HitTestBox* _Target)override;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		ChStd::Bool IsInnerHitSphere(
			const HitTestSphere* _Target)override;

	private:

		const static std::map<HitTestRayDirctionAxis, std::function<ChVec3()>>GetRayAxis;

		HitTestRayDirctionAxis RayAxis;

		float MaxLen = FLT_MAX;

	};




}

#endif
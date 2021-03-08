#ifndef Ch_CPP_HTS_h
#define Ch_CPP_HTS_h

#include"ChHitTestObject.h"

namespace ChCpp
{

	class HitTestSphere :public HitTestObject
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetLen(const float& _Len) { Len = _Len; }

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline float GetLen()const { return Len; }

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

		float Len = 0.0f;


	};




}

#endif
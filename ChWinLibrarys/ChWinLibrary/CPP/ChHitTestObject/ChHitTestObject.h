#ifndef Ch_CPP_HTO_h
#define Ch_CPP_HTO_h

namespace ChCpp
{
	class HitTestRay;
	class HitTestPanel;
	class HitTestBox;
	class HitTestSphere;
	class HitTestMesh;

	class HitTestObject
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPosition(const ChVec3& _Pos) { Mat.SetPosition(_Pos); }

		inline void SetRotation(const ChVec3& _Rot) { Mat.SetRotation(_Rot); }

		inline void SetScalling(const ChVec3& _Scl) { Mat.SetScalling(_Scl); }

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�Փ˂��Ă����ꍇ�ɒ��S���猩�Ăǂ̈ʒu�܂ł߂荞��ł������̐��l//
		inline ChVec3 GetHitVectol() { return HitVector; }

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		virtual ChStd::Bool IsHitPanel(
			const HitTestPanel* _Target) = 0;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		virtual ChStd::Bool IsHitBox(
			const HitTestBox* _Target) = 0;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		virtual ChStd::Bool IsHitSphere(
			const HitTestSphere* _Target) = 0;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g�O����Փ˂��Ă��邩�̔���//
		virtual ChStd::Bool IsHitMesh(
			const HitTestMesh* _Target) = 0;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		virtual ChStd::Bool IsInnerHitBox(
			const HitTestBox* _Target) = 0;

		//�Ώۂ̃I�u�W�F�N�g���I�u�W�F�N�g������Փ˂��Ă��邩�̔���//
		virtual ChStd::Bool IsInnerHitSphere(
			const HitTestSphere* _Target) = 0;

	protected:

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetHitVector(const ChVec3& _Vec) { HitVector = _Vec; }

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline ChVec3 GetPos() const { return Mat.GetPosition(); }

		inline ChVec3 GetRot()const { return Mat.GetRotation(); }

		inline ChVec3 GetScl()const { return Mat.GetScalling(); }

		inline ChLMat GetLMat()const { return Mat; }

		inline ~HitTestObject() {}

	private:

		ChLMat Mat;

		ChVec3 HitVector = 0.0f;

	};

}

#endif
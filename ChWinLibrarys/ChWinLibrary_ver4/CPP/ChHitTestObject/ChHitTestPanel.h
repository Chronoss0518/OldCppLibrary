#ifndef Ch_CPP_HTP_h
#define Ch_CPP_HTP_h

#include"ChHitTestObject.h"

namespace ChCpp
{

	//R=Right,L=Left,T=Top,D=Down//
	enum class HitTestPanelVertexs :unsigned char
	{
		RT, LT, RD, LD, None
	};

	class HitTestPanel :public HitTestObject
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPosition(const HitTestPanelVertexs& _VertexNum, const ChVec3& _Pos)
		{
			VPos[ChStd::EnumCast(_VertexNum)] = _Pos;
		}

		//R=Right,L=Left,T=Top,D=Down//
		inline void SetPosition(
			const ChVec3& _RT,
			const ChVec3& _LT,
			const ChVec3& _RD,
			const ChVec3& _LD)
		{
			VPos[0] = _RT;
			VPos[1] = _LT;
			VPos[2] = _RD;
			VPos[3] = _LD;
		}

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

		ChVec3 VPos[4];


	};




}

#endif
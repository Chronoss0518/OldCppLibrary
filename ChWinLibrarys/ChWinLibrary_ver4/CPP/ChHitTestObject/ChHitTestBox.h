#ifndef Ch_CPP_HTB_h
#define Ch_CPP_HTB_h

#include"ChHitTestObject.h"

namespace ChCpp
{

	//R=Right,L=Left,T=Top,D=Down,F=Front,B=Back//
	enum class HitTestBoxVertexs:unsigned char
	{
		RTF,RTB,LTF,LTB,RDF,RDB,LDF,LDB,None
	};

	class HitTestBox :public HitTestObject
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPosition(const HitTestBoxVertexs& _VertexNum, const ChVec3& _Pos)
		{
			VPos[ChStd::EnumCast(_VertexNum)] = _Pos;
		}

		//R=Right,L=Left,T=Top,D=Down,F=Front,B=Back//
		inline void SetPosition(
			const ChVec3& _RTF,
			const ChVec3& _RTB,
			const ChVec3& _LTF,
			const ChVec3& _LTB,
			const ChVec3& _RDF,
			const ChVec3& _RDB,
			const ChVec3& _LDF,
			const ChVec3& _LDB)
		{
			VPos[0] = _RTF;
			VPos[1] = _RTB;
			VPos[2] = _LTF;
			VPos[3] = _LTB;
			VPos[4] = _RDF;
			VPos[5] = _RDB;
			VPos[6] = _LDF;
			VPos[7] = _LDB;
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

		ChVec3 VPos[8];


	};




}

#endif
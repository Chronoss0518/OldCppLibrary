#ifndef Ch_D3D9_Ob_h
#define Ch_D3D9_Ob_h

#include"../ChVertexData9.h"

namespace ChMesh
{
	typedef class BaseMesh9 Mesh9;

}

namespace ChTex
{
	typedef class BaseTexture9 Texture9;

	class PolygonBoard9;
}

//物体に対しての関数を有するクラス//
//板ポリゴンや3Dモデルに対して機能する//
class ChObjectController9 {
public:


	///////////////////////////////////////////////////////////////////////////////////

	//簡易的XFileのレイ判定//
	ChStd::Bool MeshHitRay(
		DWORD& _Index
		, float& _Len
		, const ChPtr::Shared<ChMesh::BaseMesh9>& _Mesh
		, const ChMat_9& _Obj
		, const ChVec3_9& _Pos
		, const ChVec3_9& _Dir);

	ChStd::Bool MeshHitRay(
		float& _Len
		, const ChPtr::Shared<ChMesh::BaseMesh9>& _Mesh
		, const ChMat_9& _Obj
		, const ChVec3_9& _Pos
		, const ChVec3_9& _Dir);

	ChStd::Bool MeshHitRay(
		const ChPtr::Shared<ChMesh::BaseMesh9>& _Mesh
		, const ChMat_9& _Obj
		, const ChVec3_9& _Pos
		, const ChVec3_9& _Dir);

	///////////////////////////////////////////////////////////////////////////////////

	//板ポリゴンに対しての例判定//
	ChStd::Bool PorygonHitRay(
		float& _Len
		, const ChPtr::Shared<ChTex::PolygonBoard9> _PoBo
		, const ChVec3_9& _Pos
		, const ChVec3_9& _Dir);

	///////////////////////////////////////////////////////////////////////////////////

	//アニメーションリストを保有しなくても//
	//簡単にアニメーションをさせる関数//
	void SimpleAnimetion(
		ChMat_9& _NowMat
		, const ChMat_9& _StartMat
		, const ChMat_9& _EndMat
		, const float& _NowTime);

	///////////////////////////////////////////////////////////////////////////////////

	//板ポリゴン自体がずっとカメラのほうを向くようにするクラス。
	void MatrixBillboard(
		ChMat_9& _OutObj
		, const ChVec3_9& _ObjPos
		, const  ChMat_9& _CamMat);

	///////////////////////////////////////////////////////////////////////////////////

	// _MaskDirectionに'x','y','z'のいずれかを記入すると、//
	//その方向にだけ当たり判定がおんなじ位置になる//
	ChStd::Bool LengthDecision(
		const ChMat_9 &_Mat1
		, const ChMat_9 &_Mat2
		, const float MatLen
		, const char _MaskDirection);

	///////////////////////////////////////////////////////////////////////////////////

	//2D版の当たり判定(改良必)//
	ChStd::Bool Hit2DDecision(
		const ChMat_9& _Obj1Mat
		, const ChMat_9& _Obj2Mat
		, const ChPtr::Shared<ChTex::BaseTexture9>&_Obj1Tex
		, const ChPtr::Shared<ChTex::BaseTexture9>&_Obj2Tex);

	///////////////////////////////////////////////////////////////////////////////////

	//ある点とある面までの距離//
	//処理が重いので回数は少なく//
	float GetLenToPosTri(
		const D3DXVECTOR3& _Pos
		, const D3DXVECTOR3& _FaceVer1
		, const D3DXVECTOR3& _FaceVer2
		, const D3DXVECTOR3& _FaceVer3);

	///////////////////////////////////////////////////////////////////////////////////

	//ある点がある平面に対する垂直な最短距離//
	float GetLenToPosPlane(
		const D3DXVECTOR3& _Pos
		, const D3DXVECTOR3& _FaceVer1
		, const D3DXVECTOR3& _FaceVer2
		, const D3DXVECTOR3& _FaceVer3);

	///////////////////////////////////////////////////////////////////////////////////

	//_ObjectMatに対して_OffsetMatからのCrossVecを生成//
	//_OutVecがNULLまたはnullptrだった場合は失敗する//
	void LookObjectAxis(
		ChVec3_9&_OutVec
		, const ChMat_9&_OffsetMat
		, const ChMat_9& _ObjectMat);

	///////////////////////////////////////////////////////////////////////////////////

	//回転のみの簡易的アニメーション//
	//(改良必)
	void SimpleOffsetAnimation(
		ChMat_9& _NowMat
		, const ChQua_9& _StartQua
		, const ChQua_9& _EndQua
		, const float _EndTime
		, const float _NowTime);

protected:

	ChObjectController9() {}

	~ChObjectController9() {}

public:

	inline static ChObjectController9& GetIns()
	{
		static ChObjectController9 Ins;
		return Ins;
	}

};

static const std::function<ChObjectController9&()>ChObjCon9 = ChObjectController9::GetIns;


#endif // !Ch_D3D9_Ob_h
//CopyRight Chronoss0518 2018/08
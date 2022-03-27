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
class ChObjectController9 
{
public:


	///////////////////////////////////////////////////////////////////////////////////

	//簡易的XFileのレイ判定//
	ChStd::Bool MeshHitRay(
		DWORD& _index
		, float& _len
		, const ChPtr::Shared<ChMesh::BaseMesh9>& _mesh
		, const ChMat_9& _obj
		, const ChVec3_9& _pos
		, const ChVec3_9& _dir);

	ChStd::Bool MeshHitRay(
		float& _len
		, const ChPtr::Shared<ChMesh::BaseMesh9>& _mesh
		, const ChMat_9& _obj
		, const ChVec3_9& _pos
		, const ChVec3_9& _dir);

	ChStd::Bool MeshHitRay(
		const ChPtr::Shared<ChMesh::BaseMesh9>& _mesh
		, const ChMat_9& _obj
		, const ChVec3_9& _pos
		, const ChVec3_9& _dir);

	///////////////////////////////////////////////////////////////////////////////////

	//板ポリゴンに対しての例判定//
	ChStd::Bool PorygonHitRay(
		float& _len
		, const ChPtr::Shared<ChTex::PolygonBoard9> _poBo
		, const ChVec3_9& _pos
		, const ChVec3_9& _dir);

	///////////////////////////////////////////////////////////////////////////////////

	//アニメーションリストを保有しなくても//
	//簡単にアニメーションをさせる関数//
	void SimpleAnimetion(
		ChMat_9& _nowMat
		, const ChMat_9& _startMat
		, const ChMat_9& _endMat
		, const float& _nowTime);

	///////////////////////////////////////////////////////////////////////////////////

	//板ポリゴン自体がずっとカメラのほうを向くようにするクラス。
	void MatrixBillboard(
		ChMat_9& _outObj
		, const ChVec3_9& _objPos
		, const  ChMat_9& _camMat);

	///////////////////////////////////////////////////////////////////////////////////

	// _MaskDirectionに'x','y','z'のいずれかを記入すると、//
	//その方向にだけ当たり判定がおんなじ位置になる//
	ChStd::Bool LengthDecision(
		const ChMat_9 &_mat1
		, const ChMat_9 &_mat2
		, const float matLen
		, const char _maskDirection);

	///////////////////////////////////////////////////////////////////////////////////

	//2D版の当たり判定(改良必)//
	ChStd::Bool Hit2DDecision(
		const ChMat_9& _obj1Mat
		, const ChMat_9& _obj2Mat
		, const ChPtr::Shared<ChTex::BaseTexture9>&_obj1Tex
		, const ChPtr::Shared<ChTex::BaseTexture9>&_obj2Tex);

	///////////////////////////////////////////////////////////////////////////////////

	//ある点とある面までの距離//
	//処理が重いので回数は少なく//
	float GetLenToPosTri(
		const D3DXVECTOR3& _pos
		, const D3DXVECTOR3& _faceVer1
		, const D3DXVECTOR3& _faceVer2
		, const D3DXVECTOR3& _faceVer3);

	///////////////////////////////////////////////////////////////////////////////////

	//ある点がある平面に対する垂直な最短距離//
	float GetLenToPosPlane(
		const D3DXVECTOR3& _pos
		, const D3DXVECTOR3& _faceVer1
		, const D3DXVECTOR3& _faceVer2
		, const D3DXVECTOR3& _faceVer3);

	///////////////////////////////////////////////////////////////////////////////////

	//_ObjectMatに対して_OffsetMatからのCrossVecを生成//
	//_OutVecがNULLまたはnullptrだった場合は失敗する//
	void LookObjectAxis(
		ChVec3_9&_outVec
		, const ChMat_9&_offsetMat
		, const ChMat_9& _objectMat);

	///////////////////////////////////////////////////////////////////////////////////

	//回転のみの簡易的アニメーション//
	//(改良必)
	void SimpleOffsetAnimation(
		ChMat_9& _nowMat
		, const ChQua_9& _startQua
		, const ChQua_9& _endQua
		, const float _endTime
		, const float _nowTime);

protected:

	ChObjectController9() {}

	~ChObjectController9() {}

public:

	inline static ChObjectController9& GetIns()
	{
		static ChObjectController9 ins;
		return ins;
	}

};

static const std::function<ChObjectController9&()>ChObjCon9 = ChObjectController9::GetIns;


#endif // !Ch_D3D9_Ob_h
//CopyRight Chronoss0518 2018/08
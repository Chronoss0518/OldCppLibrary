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

//���̂ɑ΂��Ă̊֐���L����N���X//
//�|���S����3D���f���ɑ΂��ċ@�\����//
class ChObjectController9 {
public:


	///////////////////////////////////////////////////////////////////////////////////

	//�ȈՓIXFile�̃��C����//
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

	//�|���S���ɑ΂��Ă̗ᔻ��//
	ChStd::Bool PorygonHitRay(
		float& _Len
		, const ChPtr::Shared<ChTex::PolygonBoard9> _PoBo
		, const ChVec3_9& _Pos
		, const ChVec3_9& _Dir);

	///////////////////////////////////////////////////////////////////////////////////

	//�A�j���[�V�������X�g��ۗL���Ȃ��Ă�//
	//�ȒP�ɃA�j���[�V������������֐�//
	void SimpleAnimetion(
		ChMat_9& _NowMat
		, const ChMat_9& _StartMat
		, const ChMat_9& _EndMat
		, const float& _NowTime);

	///////////////////////////////////////////////////////////////////////////////////

	//�|���S�����̂������ƃJ�����̂ق��������悤�ɂ���N���X�B
	void MatrixBillboard(
		ChMat_9& _OutObj
		, const ChVec3_9& _ObjPos
		, const  ChMat_9& _CamMat);

	///////////////////////////////////////////////////////////////////////////////////

	// _MaskDirection��'x','y','z'�̂����ꂩ���L������ƁA//
	//���̕����ɂ��������蔻�肪����Ȃ��ʒu�ɂȂ�//
	ChStd::Bool LengthDecision(
		const ChMat_9 &_Mat1
		, const ChMat_9 &_Mat2
		, const float MatLen
		, const char _MaskDirection);

	///////////////////////////////////////////////////////////////////////////////////

	//2D�ł̓����蔻��(���ǕK)//
	ChStd::Bool Hit2DDecision(
		const ChMat_9& _Obj1Mat
		, const ChMat_9& _Obj2Mat
		, const ChPtr::Shared<ChTex::BaseTexture9>&_Obj1Tex
		, const ChPtr::Shared<ChTex::BaseTexture9>&_Obj2Tex);

	///////////////////////////////////////////////////////////////////////////////////

	//����_�Ƃ���ʂ܂ł̋���//
	//�������d���̂ŉ񐔂͏��Ȃ�//
	float GetLenToPosTri(
		const D3DXVECTOR3& _Pos
		, const D3DXVECTOR3& _FaceVer1
		, const D3DXVECTOR3& _FaceVer2
		, const D3DXVECTOR3& _FaceVer3);

	///////////////////////////////////////////////////////////////////////////////////

	//����_�����镽�ʂɑ΂��鐂���ȍŒZ����//
	float GetLenToPosPlane(
		const D3DXVECTOR3& _Pos
		, const D3DXVECTOR3& _FaceVer1
		, const D3DXVECTOR3& _FaceVer2
		, const D3DXVECTOR3& _FaceVer3);

	///////////////////////////////////////////////////////////////////////////////////

	//_ObjectMat�ɑ΂���_OffsetMat�����CrossVec�𐶐�//
	//_OutVec��NULL�܂���nullptr�������ꍇ�͎��s����//
	void LookObjectAxis(
		ChVec3_9&_OutVec
		, const ChMat_9&_OffsetMat
		, const ChMat_9& _ObjectMat);

	///////////////////////////////////////////////////////////////////////////////////

	//��]�݂̂̊ȈՓI�A�j���[�V����//
	//(���ǕK)
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
#ifndef Ch_D3D9_PhyBa_h
#define Ch_D3D9_PhyBa_h

namespace ChMesh
{

typedef class BaseMesh9 Mesh9;
}


//(���ǒ�)//

//�ړ�����ۂɂ�������ɕ����I�ȗ͂������悤�ɂ���N���X//
//�x�[�X�N���X�̂��߁A��{�I�ɂ��ꎩ�̂��g�����Ƃ͂Ȃ�//
class ChPhysicalBase9
{
public:

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	ChPhysicalBase9()
	{
		ObjCon = &ChObjCon9();
	}

	virtual  ~ChPhysicalBase9()
	{
		ObjCon = nullptr;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//InitAndRelease//

	virtual void Init(){}

	virtual void Init(const float _FPS){}

	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	void SetMesh(const ChPtr::Shared<ChMesh::Mesh9> _Mesh);

	//�d�͂̏ꍇ�͏d�̗͂͂�ύX�\(�ʏ펞�͉������ɕb��9.8�̑����ŗ�����)//
	inline virtual void SetData(const float) {}

	inline void SetLen(const float _BaseLen) 
	{
		BaseLen = _BaseLen;
	}

	//�I�u�W�F�N�g�R���g���[���[�̃Z�b�g//
	//�g�������I�u�W�F�N�g�R���g���[���[���Z�b�g�ł���//
	inline void SetObjCon(ChObjectController9* _YouUsedObjCon)
	{
		if (ChPtr::NullCheck(_YouUsedObjCon))return;
		ObjCon = _YouUsedObjCon;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//UpdateFunction//

	virtual ChStd::Bool UpDate(
		ChVec3_9*
		, const ChVec3_9*)
	{
		return ChStd::True;
	};

protected:

	std::vector<ChPtr::Weak<ChMesh::Mesh9>>WpXList;

	float BaseLen = 1.0f;
	ChObjectController9* ObjCon;
	float Pow = 0.0f;
	float FPS = 60.0f;
	ChVec3_9 Vec;

};

//�d�͂𔭐�������N���X//
class ChGravity9 :public ChPhysicalBase9
{
public:


	///////////////////////////////////////////////////////////////////////////////////
	//InitAndRelease//
	
	void Init(const float _FPS)override;

	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	inline void SetData(const float _Data)override
	{
		G = _Data;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//UpdateFunction//

	ChStd::Bool UpDate(
		ChVec3_9* _Pos
		, const ChVec3_9* _MoveDir)override;

private:

	float VirtualHeight = 0.0f;
	float G = 9.8f;
	float TmpSpeed = 0.0f;
};

//���̂ւ̏Փˎ��ɉ����߂��N���X//
class ChPushBack9 :public ChPhysicalBase9
{

public:
	///////////////////////////////////////////////////////////////////////////////////
	//InitAndRelease//

	void Init()override;

	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	inline void SetData(const float _Data)override
	{
		BackLine = _Data;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//UpdateFunction//

	ChStd::Bool UpDate(ChVec3_9*, const ChVec3_9*)override;

private:

	float BackLine = 1.0f;
};

#endif
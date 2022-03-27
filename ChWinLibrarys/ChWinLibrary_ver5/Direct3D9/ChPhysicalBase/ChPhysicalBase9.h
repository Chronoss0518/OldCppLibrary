#ifndef Ch_D3D9_PhyBa_h
#define Ch_D3D9_PhyBa_h

namespace ChMesh
{

typedef class BaseMesh9 Mesh9;
}


//(���ǒ�)//

//�ړ�����ۂɂ�������ɕ����I�ȗ͂������悤�ɂ���N���X//
//�x�[�X�N���X�̂��߁A��{�I�ɂ��ꎩ�̂��g�����Ƃ͂Ȃ�//
class ChPhysicalBase9:public ChCp::Initializer
{
public:

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer//

	ChPhysicalBase9()
	{
		objCon = &ChObjCon9();
	}

	virtual  ~ChPhysicalBase9()
	{
		objCon = nullptr;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//InitAndRelease//

	virtual void Init(){}

	virtual void Init(const float _FPS){}

	///////////////////////////////////////////////////////////////////////////////////
	//SetFunction//

	void SetMesh(const ChPtr::Shared<ChMesh::Mesh9> _mesh);

	//�d�͂̏ꍇ�͏d�̗͂͂�ύX�\(�ʏ펞�͉������ɕb��9.8�̑����ŗ�����)//
	inline virtual void SetData(const float) {}

	inline void SetLen(const float _baseLen) 
	{
		baseLen = _baseLen;
	}

	//�I�u�W�F�N�g�R���g���[���[�̃Z�b�g//
	//�g�������I�u�W�F�N�g�R���g���[���[���Z�b�g�ł���//
	inline void SetObjCon(ChObjectController9* _youUsedObjCon)
	{
		if (ChPtr::NullCheck(_youUsedObjCon))return;
		objCon = _youUsedObjCon;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//UpdateFunction//

	virtual ChStd::Bool UpDate(
		ChVec3_9*
		, const ChVec3_9*)
	{
		return true;
	};

protected:

	std::vector<ChPtr::Weak<ChMesh::Mesh9>>wpXList;

	float baseLen = 1.0f;
	ChObjectController9* objCon = nullptr;
	float pow = 0.0f;
	float FPS = 60.0f;
	ChVec3_9 vec;

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

	inline void SetData(const float _data)override
	{
		g = _data;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//UpdateFunction//

	ChStd::Bool UpDate(
		ChVec3_9* _pos
		, const ChVec3_9* _moveDir)override;

private:

	float virtualHeight = 0.0f;
	float g = 9.8f;
	float tmpSpeed = 0.0f;
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
		backLine = _Data;
	}

	///////////////////////////////////////////////////////////////////////////////////
	//UpdateFunction//

	ChStd::Bool UpDate(ChVec3_9*, const ChVec3_9*)override;

private:

	float backLine = 1.0f;
};

#endif

#ifndef Ch_CPP_OParts_h
#define Ch_CPP_OParts_h

namespace ChCpp
{
	//OP:ObjectParts�̗�//
	//BaseComponent���쐬����ۂɌp�����Ďg�p//
	//�e�I�u�W�F�N�g�Ƀ��\�b�h�����������鎖���o����//
	class OP_Update
	{
	public:

		virtual void UpdateBegin() {};

		virtual void Update() = 0;

		virtual void UpdateEnd() {};

	};

	//OP:ObjectParts�̗�//
	//BaseComponent���쐬����ۂɌp�����Ďg�p//
	//�e�I�u�W�F�N�g�Ƀ��\�b�h�����������鎖���o����//
	class OP_Move
	{
	public:

		virtual void MoveBegin() {};

		virtual void Move() = 0;

		virtual void MoveEnd() {};

	};

	//OP:ObjectParts�̗�//
	//BaseComponent���쐬����ۂɌp�����Ďg�p//
	//�e�I�u�W�F�N�g�Ƀ��\�b�h�����������鎖���o����//
	class OP_Draw
	{
	public:

		virtual void DrawBegin() {}

		virtual void Draw3D() {}

		virtual void Draw2D() {}

		virtual void DrawEnd() {}

	};


}

#endif
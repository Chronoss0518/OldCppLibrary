
#ifndef Ch_CPP_BaCom_h
#define Ch_CPP_BaCom_h

namespace ChCpp
{
	class BaseObject;

	//ChBaseObject�ɑ΂���R���|�[�l���g�V�X�e��//
	//�K�v�ɉ����Ĉȉ��̊֐����I�[�o�[���C�h����//
	//void Init(),void Release(),void Update()//
	//void Move(),void Draw2D(),void Draw3D()//
	class BaseComponent :public  std::enable_shared_from_this<BaseComponent>
	{
	public:

		friend BaseObject;

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//�Z�b�g�����ۂɎ����I�ɌĂ΂��//
		virtual void Init() {};

		//���������ۂɎ����I�ɌĂ΂��//
		virtual void Release() {};

		//���g�����������Ƃ��ɌĂ�//
		void Destroy();

		//���g�̖{�̂��̂Ă������ɑ��点��֐�//
		void ObjectDestroy();

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		virtual void Update() {};

		///////////////////////////////////////////////////////////////////////////////////

		virtual void Move() {}

		///////////////////////////////////////////////////////////////////////////////////

		virtual void Draw3D() {}

		virtual void Draw2D() {}

		///////////////////////////////////////////////////////////////////////////////////
		//LookFunction//

		//���ږ{�̂ɐG�肽���Ƃ��ɌĂԊ֐�//
		ChPtr::Shared<BaseObject> LookObj()
		{
			return Obj;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		virtual ~BaseComponent() { Release(); }

		BaseComponent() {}

		ChStd::Bool UseFlg = true;

	private:

		///////////////////////////////////////////////////////////////////////////////////

		//�Z�b�g�����ۂɌĂ΂��//
		void BaseInit(const ChPtr::Shared<BaseObject> _Obj);

		///////////////////////////////////////////////////////////////////////////////////


		ChPtr::Shared<BaseObject> Obj;

		ChStd::Bool DFlg = false;


	};

}


#endif
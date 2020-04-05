
#ifndef Ch_CPP_BaCom_h
#define Ch_CPP_BaCom_h

#include"../ChBitBool/ChBitBool.h"

#include"ChBaseObjectParts.h"

namespace ChCpp
{
	class BaseObject;

	//ChBaseObject�ɑ΂���R���|�[�l���g�V�X�e��//
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

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetUsing(const ChStd::Bool _Flg) { UseFlg = _Flg; }

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		ChStd::Bool IsDeth() { return DFlg; }

		ChStd::Bool IsUse() { return UseFlg; }

	private:

		ChCpp::BitBool FunctionFlgs = ChCpp::BitBool(2);

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//LookFunction//

		//���ږ{�̂ɐG�肽���Ƃ��ɌĂԊ֐�//
		template<class Class = BaseObject>
		Class& LookObj()
		{
			if (ChPtr::SafeCast<Class>(Obj) == nullptr)
			{
				Class Tmp;
				return Tmp;
			}

			return *ChPtr::SafeCast<Class>(Obj);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		virtual ~BaseComponent() { Release(); }

		BaseComponent() {}

		ChStd::Bool UseFlg = true;

	private:

		///////////////////////////////////////////////////////////////////////////////////

		//�Z�b�g�����ۂɌĂ΂��//
		void BaseInit(const BaseObject* _Obj);

		///////////////////////////////////////////////////////////////////////////////////


		BaseObject* Obj = nullptr;

		ChStd::Bool DFlg = false;


	};

	class TransformComponent :public ChCpp::BaseComponent
	{
	public:

		ChVec3 Position;
		ChQua Rotation;
		ChVec3 Scalling;

	};

	using TransformCom = TransformComponent;

}

#endif
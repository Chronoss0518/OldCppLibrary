
#ifndef Ch_CPP_BaCom_h
#define Ch_CPP_BaCom_h

#include"../ChBitBool/ChBitBool.h"

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

		void SetUsing(const ChStd::Bool _Flg) { useFlg = _Flg; }

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		ChStd::Bool IsDeth() { return dFlg; }

		ChStd::Bool IsUse() { return useFlg; }

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//LookFunction//

		//���ږ{�̂ɐG�肽���Ƃ��ɌĂԊ֐�//
		template<class Class = BaseObject>
		ChStd::Bool LookObj(typename
			std::enable_if<std::is_base_of<BaseObject, Class>::value, ChPtr::Shared<Class>>::type _out)
			
		{
			auto testObj = ChPtr::SharedSafeCast<Class>(obj.lock());

			if (testObj == nullptr)return false;

			_out = testObj;

			return true;

		}

		//���ږ{�̂ɐG�肽���Ƃ��ɌĂԊ֐�//
		template<class Class = BaseObject>
		auto LookObj()->
			typename std::enable_if<std::is_base_of<BaseObject, Class>::value, ChPtr::Shared<Class>>::type

		{
			return ChPtr::SharedSafeCast<Class>(obj.lock());
		}

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		virtual ~BaseComponent() { Release(); }

		BaseComponent() {}

		ChStd::Bool useFlg = true;

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFuncsions//
		virtual void UpdateBegin() {};
		virtual void Update() {};
		virtual void UpdateEnd() {};

		//MoveFuncsions//
		virtual void MoveBegin() {};
		virtual void Move() {};
		virtual void MoveEnd() {};

		//DrawFuncsions//
		virtual void DrawBegin() {}
		virtual void Draw3D() {}
		virtual void Draw2D() {}
		virtual void DrawEnd() {}

	private:

		///////////////////////////////////////////////////////////////////////////////////

		//�Z�b�g�����ۂɌĂ΂��//
		void BaseInit(ChPtr::Shared<BaseObject> _obj);

		///////////////////////////////////////////////////////////////////////////////////


		ChPtr::Weak<BaseObject> obj;

		ChStd::Bool dFlg = false;


	};

}

#endif
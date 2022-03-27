
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
		ChStd::Bool LookObj(typename
			std::enable_if<std::is_base_of<BaseObject, Class>::value, ChPtr::Shared<Class>>::type _Out)
			
		{
			auto This = ChPtr::SharedSafeCast<Class>(shared_from_this());

			if (This == nullptr)return false;

			_Out = This;

			return true;

		}

		//���ږ{�̂ɐG�肽���Ƃ��ɌĂԊ֐�//
		template<class Class = BaseObject>
		auto LookObj()->
			typename std::enable_if<std::is_base_of<BaseObject, Class>::value, ChPtr::Shared<Class>>::type

		{
			return ChPtr::SharedSafeCast<Class>(shared_from_this());


		}

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		virtual ~BaseComponent() { Release(); }

		BaseComponent() {}

		ChStd::Bool UseFlg = true;

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

#ifndef Ch_CPP_BaCom_h
#define Ch_CPP_BaCom_h

#include"../ChBitBool/ChBitBool.h"

namespace ChCpp
{
	class BaseObject;

	//ChBaseObjectに対するコンポーネントシステム//
	 class BaseComponent :public  std::enable_shared_from_this<BaseComponent>
	{
	public:

		friend BaseObject;

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//セットされる際に自動的に呼ばれる//
		virtual void Init() {};

		//消去される際に自動的に呼ばれる//
		virtual void Release() {};

		//自身を消したいときに呼ぶ//
		void Destroy();

		//自身の本体を捨てたい時に走らせる関数//
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

		//直接本体に触りたいときに呼ぶ関数//
		template<class Class = BaseObject>
		ChStd::Bool LookObj(typename
			std::enable_if<std::is_base_of<BaseObject, Class>::value, ChPtr::Shared<Class>>::type _Out)
			
		{
			auto This = ChPtr::SharedSafeCast<Class>(shared_from_this());

			if (This == nullptr)return false;

			_Out = This;

			return true;

		}

		//直接本体に触りたいときに呼ぶ関数//
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

		//セットされる際に呼ばれる//
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
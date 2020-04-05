
#ifndef Ch_CPP_BaCom_h
#define Ch_CPP_BaCom_h

#include"../ChBitBool/ChBitBool.h"

namespace ChCpp
{
	class BaseObject;

	//ChBaseObjectに対するコンポーネントシステム//
	//必要に応じて以下の関数をオーバーライドする//
	//void Init(),void Release(),void Update()//
	//void Move(),void Draw2D(),void Draw3D()//
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

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		virtual void UpdateBegin() {}

		virtual void Update() {}

		virtual void UpdateEnd() {}

		///////////////////////////////////////////////////////////////////////////////////////

		virtual void MoveBegin() {}

		virtual void Move() {}

		virtual void MoveEnd() {}

		///////////////////////////////////////////////////////////////////////////////////////

		virtual void DrawBegin() {}

		virtual void Draw3D() {}

		virtual void Draw2D() {}

		virtual void DrawEnd() {}

	private:

		ChCpp::BitBool FunctionFlgs = ChCpp::BitBool(2);

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//LookFunction//

		//直接本体に触りたいときに呼ぶ関数//
		template<class Class = BaseObject>
		Class& LookObj()
		{
			if (ChPtr::SafeCast<Class>(Obj) == nullptr)
			{
				static Class Tmp;
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

		//セットされる際に呼ばれる//
		void BaseInit(const BaseObject* _Obj);

		///////////////////////////////////////////////////////////////////////////////////


		BaseObject* Obj;

		ChStd::Bool DFlg = false;


	};

	typedef class TransformComponent :public ChCpp::BaseComponent
	{
	public:

		ChVec3 Position;
		ChQua Rotation;
		ChVec3 Scalling;

	}TransformCom;

}


#endif
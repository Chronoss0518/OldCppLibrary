
#ifndef Ch_CPP_BaCom_h
#define Ch_CPP_BaCom_h

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

		//直接本体に触りたいときに呼ぶ関数//
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

		//セットされる際に呼ばれる//
		void BaseInit(const ChPtr::Shared<BaseObject> _Obj);

		///////////////////////////////////////////////////////////////////////////////////


		ChPtr::Shared<BaseObject> Obj;

		ChStd::Bool DFlg = false;


	};

}


#endif

#ifndef Ch_CPP_BaObj_h
#define Ch_CPP_BaObj_h

namespace ChCpp
{
	class BaseComponent;
	class ObjectManager;

	//オブジェクトを生成する場合、このクラスを継承して作成する。//
	//必要に応じて以下の関数をオーバーライドする//
	//void Init(),void Release(),void Update(),void LastUpdate()//
	//void Move(),void Draw2D(),void Draw3D()//
	class BaseObject :public  std::enable_shared_from_this<BaseObject>
	{
	public:

		friend BaseComponent;
		friend ObjectManager;

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//Set時に自動的に走る関数//
		virtual void Init() {}

		//自身を捨てる時に自動的に走る関数//
		virtual void Release() {}

		//自身を捨てたい時に走らせる関数//
		void Destroy();

		void DestroyToChild(const ChPtr::Shared<BaseObject>& _Child);

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//現在のタグを取得//
		std::string GetThisTag() { return Tag; }

		std::string GetMyName() { return MyName; }

		//コンポーネントの取得//
		template<class T = BaseComponent>
		inline auto GetComponent()->typename std::enable_if
			<std::is_base_of<BaseComponent, T>::value, const ChPtr::Shared<T>>::type
		{
			for (auto&& Com : ComList)
			{
				if (ChPtr::SharedSafeCast<T, BaseComponent>(Com) != nullptr)
				{
					if (Com->DFlg)continue;
					if (!Com->UseFlg)continue;
					return ChPtr::SharedSafeCast<T, BaseComponent>(Com);
				}
			}
			return nullptr;
		}

		//コンポーネントの取得※失敗ルート//
		template<typename T = int>
		inline auto GetComponent()->typename std::enable_if
			<!std::is_base_of<BaseComponent, T>::value, const ChPtr::Shared<int>&>::type 
		{

			ChSystem::ErrerMessage("BaseComponentが継承されていないクラスが\n選択されました", "警告");

			return nullptr;
		}

		//コンポーネントリストの取得//
		template<typename T = BaseComponent>
		inline auto GetComponents()->typename std::enable_if
			<std::is_base_of<BaseComponent, T>::value, std::vector<ChPtr::Shared<const T>>&>::type 
		{
			std::vector<ChPtr::Shared<const T>>TmpComList;
			for (auto&& Com : ComList)
			{
				if (ChPtr::SharedSafeCast<T>(Com) == nullptr)continue;
				if (Com->DFlg)continue;
				if (!Com->UseFlg)continue;
				TmpComList.push_back(Com);
			}
			return TmpComList;
		}

		//コンポーネントリストの取得※失敗ルート//
		template<typename T = int>
		inline auto GetComponents()->typename std::enable_if
			<!std::is_base_of<BaseComponent, T>::value, std::vector<ChPtr::Shared<const int>>&>::type 
		{

			std::vector<ChPtr::Shared<const T>>TmpComList;

			ChSystem::ErrerMessage("BaseComponentが継承されていないクラスが\n選択されました", "警告");


			return TmpComList;
		}

		std::vector<ChPtr::Shared<BaseObject>>GetChildlen()
		{
			return ChildList;
		}

		ChPtr::Shared<BaseObject>GetParent()
		{
			return Parent.lock();
		}


		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//コンポーネントのセット//
		template<class T>
		inline auto SetComponent()->typename std::enable_if
			<std::is_base_of<BaseComponent, T>::value, const ChPtr::Shared<T>>::type
		{

			ChPtr::Shared<BaseComponent> TmpCom = ChPtr::Make_S<T>();

			if (TmpCom == nullptr)return nullptr;

			ComList.push_back(TmpCom);

			TmpCom->BaseInit(shared_from_this());

			TmpCom->Init();

			return ChPtr::SharedSafeCast<T>(TmpCom);

		}

		//コンポーネントのセット※失敗ルート//
		template<typename T>
		inline auto SetComponent()->typename std::enable_if
			<!std::is_base_of<BaseComponent, T>::value, const ChPtr::Shared<T>>::type
		{

			ChSystem::System()->ErrerMessage("BaseComponentが継承されていません", "警告");

			return nullptr;
		}

		//子オブジェクトのセット//
		template<class T>
		inline void SetChild(typename std::enable_if
			<std::is_base_of<BaseObject, T>::value, const ChPtr::Shared<T>>::type _ChildObject)
		{
			ChPtr::Shared<BaseObject> Obj = ChPtr::SharedSafeCast<BaseObject>(_ChildObject);
			ChildList.push_back(Obj);
			Obj->Parent = shared_from_this();

		}

		//子オブジェクトのセット※失敗ルート//
		template<class T>
		inline void SetChild(typename std::enable_if
			<!std::is_base_of<BaseObject, T>::value, const ChPtr::Shared<T>>::type _ChildObject)
		{

			ChSystem::System()->ErrerMessage("BaseObjectが継承されていません", "警告");

			return nullptr;
		}

		//自身の名前のセット//
		inline void SetMyName(const std::string& _NewName) { MyName = _NewName; }

		///////////////////////////////////////////////////////////////////////////////////////

		//Tag変更時に走らせる関数//
		void ChengeTag(const std::string& _NewTag);

		protected:

		///////////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		virtual void Update() {}

		virtual void LastUpdate(){}

		///////////////////////////////////////////////////////////////////////////////////////

		virtual void Move() {}

		///////////////////////////////////////////////////////////////////////////////////////

		virtual void Draw3D() {}

		virtual void Draw2D() {}

		public:

		///////////////////////////////////////////////////////////////////////////////////////

		std::vector<ChPtr::Shared<BaseObject>>LookObjectList();

		///////////////////////////////////////////////////////////////////////////////////////

		std::vector<ChPtr::Shared<BaseObject>>LookObjectListForTag(const std::string& _Tag);

		///////////////////////////////////////////////////////////////////////////////////////

		std::vector<ChPtr::Shared<BaseObject>>LookObjectListForName(const std::string& _ObjectName);

		///////////////////////////////////////////////////////////////////////////////////////

		std::vector<ChPtr::Shared<BaseObject>>LookObjectListForTagAndName(const std::string& _ObjectName, const std::string& _Tag);

		protected:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		virtual ~BaseObject() 
		{ 
			Release(); 
			BaseRelease();
		}

		BaseObject() {};


		ChStd::Bool UseFlg = true;

	private:

		//Release時に走る関数//
		void BaseRelease();

		//Set時に走る関数//
		void BaseInit(
			const std::string& _ObjectName
			, const std::string& _Tag
			, const ObjectManager* _ObjMa);

		///////////////////////////////////////////////////////////////////////////////////
		//Component//

		void ReleaseComponent(const std::string& _ComName);

		void ComponentUpdate();

		void ComponentMove();

		void ComponentDraw3D();

		void ComponentDraw2D();

		///////////////////////////////////////////////////////////////////////////////////

		std::vector<ChPtr::Shared<BaseObject>>ChildList;
		ChPtr::Weak<BaseObject>Parent;

		std::vector<ChPtr::Shared<BaseComponent>>ComList;
		std::vector<ChPtr::Shared<BaseComponent>>DeleteList;

		ObjectManager *ObjMa = nullptr;
		std::string MyName;
		std::string Tag;
		ChStd::Bool DFlg = false;

	};


}


#endif
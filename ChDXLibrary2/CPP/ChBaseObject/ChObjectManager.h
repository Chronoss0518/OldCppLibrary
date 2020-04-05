
#ifndef Ch_CPP_ObjMa_h
#define Ch_CPP_ObjMa_h

namespace ChCpp
{

	class BaseObject;

	class ObjectManager
	{
	public:

		friend BaseObject;

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Release();

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//
		
		//オブジェクトを登録する//
		//BaseObjectを継承したオブジェクトのみ登録可能//
		template<class T>
		auto SetObject(const std::string& _ObjectName, const std::string& _Tag) ->typename std::enable_if
			<std::is_base_of<BaseObject, T>::value, ChPtr::Shared<T>>::type
		{

			ChPtr::Shared<T> Object = ChPtr::Make_S<T>();

			ChPtr::Shared<BaseObject> TmpObj
				= ChPtr::SharedSafeCast<BaseObject, T>(Object);

			TmpObj->BaseInit(_ObjectName, _Tag, this);

			TmpObj->Init();

			ObjectList[_Tag].push_back(TmpObj);

			return Object;
		}

		template<class T>
		auto SetObject(const std::string& _ObjectName, const std::string& _Tag)->typename std::enable_if
			<!std::is_base_of<BaseObject, T>::value, ChPtr::Shared<T>>::type
		{
			return nullptr;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		std::vector<ChPtr::Shared<BaseObject>> GetObjectList();

		std::vector<ChPtr::Shared<BaseObject>> GetObjectListForTag(const std::string& _TagName);

		std::vector<ChPtr::Shared<BaseObject>> GetObjectListForName(const std::string& _Name);

		///////////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		//登録されているオブジェクトを更新する//
		void Update();

		///////////////////////////////////////////////////////////////////////////////////////

		//登録されているオブジェクトを移動させる//
		void Move();

		///////////////////////////////////////////////////////////////////////////////////////

		//登録されているオブジェクトを描画する。
		void Draw();

		///////////////////////////////////////////////////////////////////////////////////////

	private:

		std::map<std::string, std::vector<ChPtr::Shared<BaseObject>>>ObjectList;

		std::map<std::string, std::vector<ChPtr::Shared<BaseObject>>>DeleteList;

		///////////////////////////////////////////////////////////////////////////////////////
		//CostructerDestructer//

		ObjectManager() {}

		~ObjectManager()
		{
			Release();
		}

	public:

		static ObjectManager& GetIns()
		{
			static ObjectManager Ins;
			return Ins;
		}

	};

	static const std::function<ObjectManager&()>ObjManager = ObjectManager::GetIns;

}


#endif
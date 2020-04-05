
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
		
		//�I�u�W�F�N�g��o�^����//
		//BaseObject���p�������I�u�W�F�N�g�̂ݓo�^�\//
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

		//�o�^����Ă���I�u�W�F�N�g���X�V����//
		void Update();

		///////////////////////////////////////////////////////////////////////////////////////

		//�o�^����Ă���I�u�W�F�N�g���ړ�������//
		void Move();

		///////////////////////////////////////////////////////////////////////////////////////

		//�o�^����Ă���I�u�W�F�N�g��`�悷��B
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
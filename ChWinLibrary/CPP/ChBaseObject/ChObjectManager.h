
#ifndef Ch_CPP_ObjMa_h
#define Ch_CPP_ObjMa_h

#include"../ChBitBool/ChBitBool.h"

#include"ChBaseObject.h"

namespace ChCpp
{

	

	class ObjectManager:public ChCp::Releaser
	{
	public:

		friend BaseObject;

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Release()override
		{
			if (!ObjectList.empty())ObjectList.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//
		
		//�I�u�W�F�N�g��o�^����//
		//BaseObject���p�������I�u�W�F�N�g�̂ݓo�^�\//
		template<class T>
		auto SetObject(const std::string& _ObjectName, const std::string& _Tag) ->typename std::enable_if
			<std::is_base_of<BaseObject, T>::value, ChPtr::Shared<T>>::type
		{

			ChPtr::Shared<BaseObject> TmpObj = ChPtr::Make_S<T>();

			TmpObj->BaseInit(_ObjectName, _Tag, this);

			TmpObj->Init();

			ObjectList[_Tag].push_back(TmpObj);
			RootObjects.push_back(TmpObj);

			return ChPtr::SharedSafeCast<T>(TmpObj);
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

		//Update���敪����������//
		void ObjectUpdateBegin();

		void ObjectUpdate();

		void ObjectUpdateEnd();

		///////////////////////////////////////////////////////////////////////////////////////

		//�o�^����Ă���I�u�W�F�N�g���ړ�������//
		void Move();

		//Move���敪����������//
		void ObjectMoveBegin();

		void ObjectMove();

		void ObjectMoveEnd();

		///////////////////////////////////////////////////////////////////////////////////////

		//�I�����ꂽ�^�O�̃I�u�W�F�N�g�����ׂď�������//
		void ClearObjectForTag(const std::string& _Tags);

		//�I�����ꂽ���O�̃I�u�W�F�N�g�����ׂď�������//
		void ClearObjectForName(const std::string& _Name);

		//�I�����ꂽ�^�O�Ɗ֘A���閼�O�̃I�u�W�F�N�g�����ׂď�������//
		void ClearObjectForTagAndName(
			const std::string& _Name,
			const std::string& _Tags);

		///////////////////////////////////////////////////////////////////////////////////////

		//�o�^����Ă���I�u�W�F�N�g��`�悷��B
		void Draw();

		//Draw�����킯��������//
		void ObjectDrawBegin();

		void ObjectDraw2D();

		void ObjectDraw3D();

		void ObjectDrawEnd();

		///////////////////////////////////////////////////////////////////////////////////////

	private:

		std::map<std::string, std::vector<ChPtr::Shared<BaseObject>>>ObjectList;

		std::vector<ChPtr::Shared<BaseObject>>RootObjects;


		///////////////////////////////////////////////////////////////////////////////////////
		//CostructerDestructer//

		ObjectManager() {}
		~ObjectManager() {}

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
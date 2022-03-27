
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
		
		//オブジェクトを登録する//
		//BaseObjectを継承したオブジェクトのみ登録可能//
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

		//登録されているオブジェクトを更新する//
		void Update();

		//Updateを区分けしたもの//
		void ObjectUpdateBegin();

		void ObjectUpdate();

		void ObjectUpdateEnd();

		///////////////////////////////////////////////////////////////////////////////////////

		//登録されているオブジェクトを移動させる//
		void Move();

		//Moveを区分けしたもの//
		void ObjectMoveBegin();

		void ObjectMove();

		void ObjectMoveEnd();

		///////////////////////////////////////////////////////////////////////////////////////

		//選択されたタグのオブジェクトをすべて消去する//
		void ClearObjectForTag(const std::string& _Tags);

		//選択された名前のオブジェクトをすべて消去する//
		void ClearObjectForName(const std::string& _Name);

		//選択されたタグと関連する名前のオブジェクトをすべて消去する//
		void ClearObjectForTagAndName(
			const std::string& _Name,
			const std::string& _Tags);

		///////////////////////////////////////////////////////////////////////////////////////

		//登録されているオブジェクトを描画する。
		void Draw();

		//Drawをくわけしたもの//
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
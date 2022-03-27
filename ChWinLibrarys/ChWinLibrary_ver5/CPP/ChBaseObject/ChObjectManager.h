
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
			ClearObject();
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//
		
		//オブジェクトを登録する//
		//BaseObjectを継承したオブジェクトのみ登録可能//
		template<class T>
		auto SetObject(const std::string& _objectName, const std::string& _tag) ->typename std::enable_if
			<std::is_base_of<BaseObject, T>::value, ChPtr::Shared<T>>::type
		{

			ChPtr::Shared<BaseObject> tmpObj = ChPtr::Make_S<T>();

			tmpObj->BaseInit(_objectName, _tag, this);

			tmpObj->Init();

			objectList[_tag].push_back(tmpObj);

			return ChPtr::SharedSafeCast<T>(tmpObj);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		std::vector<ChPtr::Shared<BaseObject>> GetObjectList();

		std::vector<ChPtr::Shared<BaseObject>> GetObjectListForTag(const std::string& _tagName);

		std::vector<ChPtr::Shared<BaseObject>> GetObjectListForName(const std::string& _name);

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

		//登録されているオブジェクトを描画する。
		void Draw();

		//Drawをくわけしたもの//
		void ObjectDrawBegin();

		void ObjectDraw2D();

		void ObjectDraw3D();

		void ObjectDrawEnd();

		///////////////////////////////////////////////////////////////////////////////////////

		//保持しているすべてのオブジェクトを削除する。
		void ClearObject();

		//選択されたタグのオブジェクトをすべて消去する//
		void ClearObjectForTag(const std::string& _tags);

		//選択された名前のオブジェクトをすべて消去する//
		void ClearObjectForName(const std::string& _name);

		//選択されたタグと関連する名前のオブジェクトをすべて消去する//
		void ClearObjectForTagAndName(
			const std::string& _name,
			const std::string& _tags);

		///////////////////////////////////////////////////////////////////////////////////////

	private:

		std::map<std::string, std::vector<ChPtr::Shared<BaseObject>>>objectList;

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
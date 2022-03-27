
#ifndef Ch_CPP_BaObj_h
#define Ch_CPP_BaObj_h

#include"../ChBitBool/ChBitBool.h"

#include"ChBaseComponent.h"
#include"ChOPClass.h"

namespace ChCpp
{
	class ObjectManager;

	//オブジェクトを生成する場合、このクラスを継承して作成する。//
	//このクラスとクラスパーツ(ChCpp::OP)を継承した//
	//オリジナルのクラスを作成して利用する。//
	class BaseObject :public std::enable_shared_from_this<BaseObject>
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

		//自身が持つ子を削除する//
		void DestroyToChild(const ChPtr::Shared<BaseObject>& _child);

		//コンポーネントを指定して削除する//
		void ReleaseComponent(const std::string& _comName);

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//現在のタグを取得//
		std::string GetThisTag() { return tag; }

		std::string GetMyName() { return myName; }

		//コンポーネントの取得//
		template<class T = BaseComponent>
		inline auto GetComponent()->typename std::enable_if
			<std::is_base_of<BaseComponent, T>::value, ChPtr::Shared<T>>::type
		{
			for (auto&& com : comList)
			{
				if (ChPtr::SharedSafeCast<T, BaseComponent>(com) != nullptr)
				{
					if (com->dFlg)continue;
					if (!com->useFlg)continue;
					return ChPtr::SharedSafeCast<T, BaseComponent>(com);
				}
			}
			return nullptr;
		}

		//コンポーネントリストの取得//
		template<typename T = BaseComponent>
		inline auto GetComponents()->typename std::enable_if
			<std::is_base_of<BaseComponent, T>::value, std::vector<ChPtr::Shared<T>>&>::type
		{
			std::vector<ChPtr::Shared<T>>tmpComList;
			for (auto&& com : comList)
			{
				if (ChPtr::SharedSafeCast<T>(com) == nullptr)continue;
				if (com->DFlg)continue;
				if (!com->UseFlg)continue;
				tmpComList.push_back(com);
			}
			return tmpComList;
		}

		//子オブジェクト群の取得//
		std::vector<ChPtr::Shared<BaseObject>>GetChildlen()
		{
			return childList;
		}

		//親の取得//
		ChPtr::Shared<BaseObject>GetParent()
		{
			return parent.lock();
		}


		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//コンポーネントのセット//
		template<class T>
		inline auto SetComponent()->typename std::enable_if
			<std::is_base_of<BaseComponent, T>::value, const ChPtr::Shared<T>>::type
		{

			ChPtr::Shared<BaseComponent> tmpCom = ChPtr::Make_S<T>();

			if (tmpCom == nullptr)return nullptr;

			comList.push_back(tmpCom);

			tmpCom->BaseInit(shared_from_this());

			return ChPtr::SharedSafeCast<T>(tmpCom);

		}

		//子オブジェクトのセット//
		template<class T>
		inline void SetChild(typename std::enable_if
			<std::is_base_of<BaseObject, T>::value, const ChPtr::Shared<T>>::type _childObject)
		{
			ChPtr::Shared<BaseObject> obj = ChPtr::SharedSafeCast<T>(_childObject);
			childList.push_back(obj);

			obj->Parent = shared_from_this();

		}

		//自身の名前のセット//
		inline void SetMyName(const std::string& _newName) { myName = _newName; }

		//使用フラグ//
		inline void SetUseFlg(const ChStd::Bool& _flg) { useFlg = _flg; }

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//使用可否の確認//
		inline ChStd::Bool IsUseFlg() { return useFlg; }

		///////////////////////////////////////////////////////////////////////////////////////

		//Tag変更時に走らせる関数//
		void ChengeTag(const std::string& _newTag);

	public:

		///////////////////////////////////////////////////////////////////////////////////////

		//全体オブジェクトの確認//
		std::vector<ChPtr::Shared<BaseObject>>LookObjectList();

		///////////////////////////////////////////////////////////////////////////////////////

		//選択したタグのオブジェクトの確認//
		std::vector<ChPtr::Shared<BaseObject>>LookObjectListForTag(const std::string& _tag);

		///////////////////////////////////////////////////////////////////////////////////////

		//選択した名前のオブジェクトの確認//
		std::vector<ChPtr::Shared<BaseObject>>LookObjectListForName(const std::string& _objectName);

		///////////////////////////////////////////////////////////////////////////////////////

		//選択したタグ内の選択した名前ののオブジェクトの確認//
		std::vector<ChPtr::Shared<BaseObject>>LookObjectListForTagAndName(const std::string& _objectName, const std::string& _Tag);

		///////////////////////////////////////////////////////////////////////////////////////
		//UsingFunctionToManagers//

		void UpdateBeginFunction();
		void UpdateFunction();
		void UpdateEndFunction();

		void MoveBeginFunction();
		void MoveFunction();
		void MoveEndFunction();

		void DrawBeginFunction();
		void Draw3DFunction();
		void Draw2DFunction();
		void DrawEndFunction();


	protected:

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

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		BaseObject() {};

		ChStd::Bool useFlg = true;

	private:

		//Release時に走る関数//
		void BaseRelease();

		//Set時に走る関数//
		void BaseInit(
			const std::string& _objectName
			, const std::string& _tag
			, const ObjectManager* _objMa);

		///////////////////////////////////////////////////////////////////////////////////
		//Component//

		void IsReleasComponent();

		///////////////////////////////////////////////////////////////////////////////////

		std::vector<ChPtr::Shared<BaseObject>>childList;
		ChPtr::Weak<BaseObject>parent;

		std::vector<ChPtr::Shared<BaseComponent>>comList;

		ObjectManager* objMa = nullptr;
		std::string myName;
		std::string tag;
		ChStd::Bool dFlg = false;

	};


}

#endif
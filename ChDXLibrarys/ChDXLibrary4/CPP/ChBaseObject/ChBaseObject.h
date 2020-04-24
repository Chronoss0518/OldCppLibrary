
#ifndef Ch_CPP_BaObj_h
#define Ch_CPP_BaObj_h

namespace ChCpp
{
	 class BaseComponent;
	 class ObjectManager;
	typedef class TransformComponent TransformCom;

	//�I�u�W�F�N�g�𐶐�����ꍇ�A���̃N���X���p�����č쐬����B//
	//�K�v�ɉ����Ĉȉ��̊֐����I�[�o�[���C�h����//
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

		//Set���Ɏ����I�ɑ���֐�//
		virtual void Init() {}

		//���g���̂Ă鎞�Ɏ����I�ɑ���֐�//
		virtual void Release() {}

		//���g���̂Ă������ɑ��点��֐�//
		void Destroy();

		void DestroyToChild(const ChPtr::Shared<BaseObject>& _Child);

	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//���݂̃^�O���擾//
		std::string GetThisTag() { return Tag; }

		std::string GetMyName() { return MyName; }

		//�R���|�[�l���g�̎擾//
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

		//�R���|�[�l���g���X�g�̎擾//
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

		template<class transform = TransformComponent>
		ChPtr::Shared<transform>GetTransform() 
		{
			if (Transform.lock() == nullptr)
			{
				SetComponent<transform>();
			}

			return ChPtr::SharedSafeCast<transform>(Transform.lock()); 
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

		//�R���|�[�l���g�̃Z�b�g//
		template<class T>
		inline auto SetComponent()->typename std::enable_if
			<std::is_base_of<BaseComponent, T>::value && std::is_base_of<TransformCom, T>::value, const ChPtr::Shared<T>>::type
		{

			if (Transform.lock() != nullptr)
			{
				Transform.lock()->Destroy();
			}

			ChPtr::Shared<BaseComponent> TmpCom = ChPtr::Make_S<T>();


			if (TmpCom == nullptr)return nullptr;

			ComList.push_back(TmpCom);

			TmpCom->BaseInit(this);

			TmpCom->Init();

			Transform = ChPtr::SharedSafeCast<T>(TmpCom);

			return ChPtr::SharedSafeCast<T>(TmpCom);

		}

		//�R���|�[�l���g�̃Z�b�g//
		template<class T>
		inline auto SetComponent()->typename std::enable_if
			<std::is_base_of<BaseComponent, T>::value && !std::is_base_of<TransformCom, T>::value, const ChPtr::Shared<T>>::type
		{

			ChPtr::Shared<BaseComponent> TmpCom = ChPtr::Make_S<T>();

			if (TmpCom == nullptr)return nullptr;

			ComList.push_back(TmpCom);

			TmpCom->BaseInit(this);

			TmpCom->Init();

			return ChPtr::SharedSafeCast<T>(TmpCom);

		}

		//�q�I�u�W�F�N�g�̃Z�b�g//
		template<class T>
		inline void SetChild(typename std::enable_if
			<std::is_base_of<BaseObject, T>::value, const ChPtr::Shared<T>>::type _ChildObject)
		{
			ChPtr::Shared<BaseObject> Obj = ChPtr::SharedSafeCast<BaseObject>(_ChildObject);
			ChildList.push_back(Obj);
			Obj->Parent = shared_from_this();

		}

		//���g�̖��O�̃Z�b�g//
		inline void SetMyName(const std::string& _NewName) { MyName = _NewName; }

		//�g�p�t���O//
		inline void SetUseFlg(const ChStd::Bool& _Flg) { UseFlg = _Flg; }

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		inline ChStd::Bool IsUseFlg() { return UseFlg; }

		///////////////////////////////////////////////////////////////////////////////////////

		//Tag�ύX���ɑ��点��֐�//
		void ChengeTag(const std::string& _NewTag);

		protected:

		///////////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		virtual void UpdateBegin() {}

		virtual void Update() {}

		virtual void UpdateEnd(){}

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

		//Release���ɑ���֐�//
		void BaseRelease();

		//Set���ɑ���֐�//
		void BaseInit(
			const std::string& _ObjectName
			, const std::string& _Tag
			, const ObjectManager* _ObjMa);

		///////////////////////////////////////////////////////////////////////////////////
		//Component//

		void ReleaseComponent(const std::string& _ComName);

		void ComponentUpdateBegin();

		void ComponentUpdate();

		void ComponentUpdateEnd();

		void ComponentMoveBegin();

		void ComponentMove();

		void ComponentMoveEnd();

		void ComponentDrawBegin();

		void ComponentDraw3D();

		void ComponentDraw2D();

		void ComponentDrawEnd();

		///////////////////////////////////////////////////////////////////////////////////

		std::vector<ChPtr::Shared<BaseObject>>ChildList;
		ChPtr::Weak<BaseObject>Parent;

		std::vector<ChPtr::Shared<BaseComponent>>ComList;
		std::vector<ChPtr::Shared<BaseComponent>>DeleteList;

		ObjectManager *ObjMa = nullptr;
		std::string MyName;
		std::string Tag;
		ChStd::Bool DFlg = false;

		ChPtr::Weak<TransformCom> Transform;

	};


}


#endif
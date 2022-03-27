
#ifndef Ch_Game_BaseSystem_h
#define Ch_Game_BaseSystem_h

namespace ChSystem
{
	class SystemManager;

	class BaseSystem : public ChCp::Initializer
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetSystemManager(const SystemManager* _own)
		{
			system = const_cast<SystemManager*>(_own);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Wind�̉����T�C�Y�擾//
		const inline unsigned int GetWindWidth()const { return windSize.w; }

		//Wind�̗����T�C�Y�擾//
		const inline unsigned int GetWindHeight()const { return windSize.h; }

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		virtual ChStd::Bool IsPushKey(const int _key);

		virtual ChStd::Bool IsPushKeyNoHold(const int _key);

		virtual ChStd::Bool IsPause(const int _key);

		virtual ChStd::Bool IsUpdate() { return false; };

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		virtual inline void MouseUpdate() {}

		virtual inline unsigned long GetNowTime() { return 0; }

		///////////////////////////////////////////////////////////////////////////////////

		inline virtual void ErrerMessage(
			const std::string& _mainStr
			, const std::string& _subStr)
		{
			std::cerr << _mainStr;
		};

	protected:

		SystemManager* system = nullptr;

		ChMath::Vector2Base<unsigned long> windSize;

		ChCpp::BitBool buttonList;
		ChCpp::BitBool isNowPush;

		//Pause�p�ϐ�//
		ChStd::Bool nowKey = false;
		ChStd::Bool pauseFlg = false;

	};

	class SystemManager :public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		friend BaseSystem;

		///////////////////////////////////////////////////////////////////////////////////s
		//InitiarizeAndRelease//

		//���������s��(�߂�l�́A�}�l�[�W���[�������V�X�e����Pointer)//
		template<class C>
		auto Init()
			->typename std::enable_if
			<std::is_base_of<BaseSystem,C>::value
			&& !std::is_same<BaseSystem,C>::value, C* const>::type
		{
			if (*this)return nullptr;

			if (ChPtr::NotNullCheck(baseSystems))delete baseSystems;
			baseSystems = nullptr;

			baseSystems = new C();
			baseSystems->SetSystemManager(this);

			SetInitFlg(true);

			return ChPtr::SafeCast<C>(baseSystems);
		}

		inline void Release()override
		{
			if (!*this)return;

			if (ChPtr::NotNullCheck(baseSystems))delete baseSystems;
			baseSystems = nullptr;

			SetInitFlg(false);
		}

		///////////////////////////////////////////////////////////////////////////////////s
		//SetFunction//

		//�S�̂ŗ��p����FPS���Ǘ�//
		inline void SetFPS(const unsigned long _FPS) { FPS = _FPS; }

		inline void SetNowTime(const unsigned long _time) { nowTime = _time; }

		inline void SetUseSystemButtons(const ChStd::Bool _button) { useSystemButton = _button; }

		///////////////////////////////////////////////////////////////////////////////////s
		//GetFunction//

		//FPS�J�E���g�̎擾//
		const inline unsigned long GetFPSCnt() const { return FPS; }

		//�E�B���h�V�X�e��(BaseSystem�p��)���擾����//
		template<class T>
		auto GetSystem()->
			typename std::enable_if
			<std::is_base_of<BaseSystem, T>::value, T* const>::type
		{
			return ChPtr::SafeCast<T>(baseSystems);
		}

		///////////////////////////////////////////////////////////////////////////////////s
		//IsFunction//

		//BaseSystem���ԐړI�Ɋm�F����//
		inline ChStd::Bool IsPushKey(const int _key)
		{
			if (!*this)return false;
			if (baseSystems == nullptr)return false;
			return baseSystems->IsPushKey(_key);
		}

		//BaseSystem���ԐړI�Ɋm�F����//
		inline ChStd::Bool IsPushKeyNoHold(const int _key)
		{
			if (!*this)return false;
			if (baseSystems == nullptr)return false;
			return baseSystems->IsPushKeyNoHold(_key);

		}

		//BaseSystem���ԐړI�Ɋm�F����//
		inline ChStd::Bool IsPause(const int _key)
		{
			if (!*this)return false;
			if (baseSystems == nullptr)return false;
			return baseSystems->IsPause(_key);

		}

		//�V�X�e�����p�����邩//
		ChStd::Bool IsUpdate()
		{
			if (baseSystems == nullptr)return false;
			nowTime = baseSystems->GetNowTime();
			return baseSystems->IsUpdate();
		}

		//�V�X�e���Œ񋟂���Ă���{�^���𗘗p���邩//
		ChStd::Bool IsUseSystemButtons() { return useSystemButton; }

		///////////////////////////////////////////////////////////////////////////////////s

		//FPS����
		inline ChStd::Bool FPSProcess()
		{
			if (!*this)return false;
			if (baseSystems == nullptr)return false;

			nowTime = baseSystems->GetNowTime();

			static unsigned long FPSTime;
			if (nowTime - FPSTime < 1000 / FPS)return false;
			FPSTime = nowTime;
			return true;
		}

	private:

		BaseSystem* baseSystems = nullptr;

		SystemManager() {}
		unsigned long FPS = 60;
		unsigned long nowTime = 0;

		ChStd::Bool useSystemButton = true;

	public:

		static SystemManager& GetIns()
		{

			static SystemManager ins;

			return ins;
		}


	};

	static const std::function<SystemManager & ()>SysManager = SystemManager::GetIns;

}

#endif
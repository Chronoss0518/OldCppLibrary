
#ifndef Ch_Game_BaseSystem_h
#define Ch_Game_BaseSystem_h

#include"../../BaseIncluder/ChBase.h"
#include"../../CPP/ChBitBool/ChBitBool.h"

namespace ChSystem
{
	class SystemManager;

	class BaseSystem : public ChCpp::ChCp::InitPack
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetSystemManager(const SystemManager* _Own)
		{
			System = const_cast<SystemManager*>(_Own);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Wind�̉����T�C�Y�擾//
		const inline unsigned int GetWindWidth()const { return WindWidth; }

		//Wind�̗����T�C�Y�擾//
		const inline unsigned int GetWindHeight()const { return WindHeight; }

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		virtual ChStd::Bool IsPushKey(const int _Key);

		virtual ChStd::Bool IsPushKeyNoHold(const int _Key);

		virtual ChStd::Bool IsPause(const int _Key);

		virtual ChStd::Bool IsUpdate() { return false; };

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		virtual inline void MouseUpdate() {}

		virtual inline unsigned long GetNowTime() { return 0; }

		///////////////////////////////////////////////////////////////////////////////////

		inline virtual void ErrerMessage(
			const std::string& _MainStr
			, const std::string& _SubStr)
		{
			std::cerr << _MainStr;
		};

	protected:

		SystemManager* System;

		unsigned int WindWidth = 0;
		unsigned int WindHeight = 0;

		ChCpp::BitBool ButtonList;
		ChCpp::BitBool IsNowPush;

		//Pause�p�ϐ�//
		ChStd::Bool NowKey = false;
		ChStd::Bool PauseFlg = false;

	};

	class SystemManager :public ChCpp::ChCp::InitializePack
	{
	public:

		friend BaseSystem;

		///////////////////////////////////////////////////////////////////////////////////s
		//InitiarizeAndRelease//

		//���������s��(�߂�l�́A�}�l�[�W���[�������V�X�e����SharedPointer)//
		template<class C>
		auto Init()
			->typename std::enable_if
			<std::is_base_of<BaseSystem,C>::value, ChPtr::Shared<C>>::type
		{
			if (*this)return nullptr;

			BaseSystems = nullptr;

			BaseSystems= ChPtr::Make_S<C>();

			BaseSystems->SetSystemManager(this);

			SetInitFlg(true);

			return ChPtr::SharedSafeCast<C>(BaseSystems);
		}

		void Release()
		{
			if (!*this)return;

			BaseSystems = nullptr;

			SetInitFlg(false);
		}

		///////////////////////////////////////////////////////////////////////////////////s
		//SetFunction//

		//�S�̂ŗ��p����FPS���Ǘ�//
		inline void SetFPS(const unsigned long _FPS) { FPS = _FPS; }

		inline void SetNowTime(const unsigned long _Time) { NowTime = _Time; }

		inline void SetUseSystemButtons(const ChStd::Bool _Button) { UseSystemButton = _Button; }

		///////////////////////////////////////////////////////////////////////////////////s
		//GetFunction//

		//FPS�J�E���g�̎擾//
		const inline unsigned long GetFPSCnt() const { return FPS; }

		//�E�B���h�V�X�e��(BaseSystem�p��)���擾����//
		template<class T>
		auto GetSystem()->
			typename std::enable_if
			<std::is_base_of<BaseSystem, T>::value, ChPtr::Shared<T>>::type
		{
			return ChPtr::SharedSafeCast<T>(BaseSystems);
		}

		///////////////////////////////////////////////////////////////////////////////////s
		//IsFunction//

		//BaseSystem���ԐړI�Ɋm�F����//
		inline ChStd::Bool IsPushKey(const int _Key)
		{
			if (*this)return false;
			if (BaseSystems == nullptr)return false;
			return BaseSystems->IsPause(_Key);
		}

		//BaseSystem���ԐړI�Ɋm�F����//
		inline ChStd::Bool IsPushKeyNoHold(const int _Key)
		{
			if (*this)return false;
			if (BaseSystems == nullptr)return false;
			return BaseSystems->IsPause(_Key);

		}

		//BaseSystem���ԐړI�Ɋm�F����//
		inline ChStd::Bool IsPause(const int _Key)
		{
			if (*this)return false;
			if (BaseSystems == nullptr)return false;
			return BaseSystems->IsPause(_Key);

		}

		//�V�X�e�����p�����邩//
		ChStd::Bool IsUpdate()
		{
			if (!BaseSystems)return false;
			NowTime = BaseSystems->GetNowTime();
			return BaseSystems->IsUpdate();
		}

		//�V�X�e���Œ񋟂���Ă���{�^���𗘗p���邩//
		ChStd::Bool IsUseSystemButtons() { return UseSystemButton; }

		///////////////////////////////////////////////////////////////////////////////////s

		//FPS����
		inline ChStd::Bool FPSProcess()
		{
			static unsigned long FPSTime;
			if (NowTime - FPSTime < 1000 / FPS)return false;
			FPSTime = NowTime;
			return true;
		}

	private:

		ChPtr::Shared<BaseSystem> BaseSystems = nullptr;

		SystemManager() {}

		~SystemManager() {}

		unsigned long FPS = 60;
		unsigned long NowTime = 0;

		ChStd::Bool UseSystemButton = true;

	public:

		static SystemManager& GetIns()
		{

			static SystemManager Ins;

			return Ins;
		}


	};

	static const std::function<SystemManager & ()>SysManager = SystemManager::GetIns;

}

#endif
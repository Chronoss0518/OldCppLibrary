
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

		//Windの横幅サイズ取得//
		const inline unsigned int GetWindWidth()const { return WindWidth; }

		//Windの立幅サイズ取得//
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

		//Pause用変数//
		ChStd::Bool NowKey = false;
		ChStd::Bool PauseFlg = false;

	};

	class SystemManager :public ChCpp::ChCp::InitializePack
	{
	public:

		friend BaseSystem;

		///////////////////////////////////////////////////////////////////////////////////s
		//InitiarizeAndRelease//

		//初期化を行う(戻り値は、マネージャーが扱うシステムのSharedPointer)//
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

		//全体で利用するFPSを管理//
		inline void SetFPS(const unsigned long _FPS) { FPS = _FPS; }

		inline void SetNowTime(const unsigned long _Time) { NowTime = _Time; }

		inline void SetUseSystemButtons(const ChStd::Bool _Button) { UseSystemButton = _Button; }

		///////////////////////////////////////////////////////////////////////////////////s
		//GetFunction//

		//FPSカウントの取得//
		const inline unsigned long GetFPSCnt() const { return FPS; }

		//ウィンドシステム(BaseSystem継承)を取得する//
		template<class T>
		auto GetSystem()->
			typename std::enable_if
			<std::is_base_of<BaseSystem, T>::value, ChPtr::Shared<T>>::type
		{
			return ChPtr::SharedSafeCast<T>(BaseSystems);
		}

		///////////////////////////////////////////////////////////////////////////////////s
		//IsFunction//

		//BaseSystemより間接的に確認する//
		inline ChStd::Bool IsPushKey(const int _Key)
		{
			if (*this)return false;
			if (BaseSystems == nullptr)return false;
			return BaseSystems->IsPause(_Key);
		}

		//BaseSystemより間接的に確認する//
		inline ChStd::Bool IsPushKeyNoHold(const int _Key)
		{
			if (*this)return false;
			if (BaseSystems == nullptr)return false;
			return BaseSystems->IsPause(_Key);

		}

		//BaseSystemより間接的に確認する//
		inline ChStd::Bool IsPause(const int _Key)
		{
			if (*this)return false;
			if (BaseSystems == nullptr)return false;
			return BaseSystems->IsPause(_Key);

		}

		//システムを継続するか//
		ChStd::Bool IsUpdate()
		{
			if (!BaseSystems)return false;
			NowTime = BaseSystems->GetNowTime();
			return BaseSystems->IsUpdate();
		}

		//システムで提供されているボタンを利用するか//
		ChStd::Bool IsUseSystemButtons() { return UseSystemButton; }

		///////////////////////////////////////////////////////////////////////////////////s

		//FPS処理
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
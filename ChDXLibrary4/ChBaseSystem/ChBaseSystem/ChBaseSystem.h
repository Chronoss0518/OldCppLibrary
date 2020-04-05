
#ifndef Ch_Game_BaseSystem_h
#define Ch_Game_BaseSystem_h

#include"../../CPP/ChBitBool/ChBitBool.h"

namespace ChSystem
{
	 class BaseSystem:public ChCpp::ChCp::InitializePack
	{


	public:

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�S�̂ŗ��p����FPS���Ǘ�//
		inline void SetFPS(const unsigned long _FPS)
		{
			FPS = _FPS;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Wind�̉����T�C�Y�擾//
		const inline unsigned int GetWindWidth()const { return WindWidth; }

		//Wind�̗����T�C�Y�擾//
		const inline unsigned int GetWindHeight()const { return WindHeight; }

		//FPS�J�E���g�̎擾//
		const inline unsigned long GetFPSCnt() const{ return FPS; }

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		virtual inline ChStd::Bool IsPushKey(const int _Key)
		{
			return ButtonList.GetBitFlg(_Key);
		}

		virtual inline ChStd::Bool IsPushKeyNoHold(const int _Key)
		{
			return ButtonList.GetBitFlg(_Key);
		}

		virtual inline ChStd::Bool IsPause(const int _Key)
		{
			return false;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		virtual inline void MouseUpdate(){}

		///////////////////////////////////////////////////////////////////////////////////

		inline virtual void ErrerMessage(
			const std::string& _MainStr
			, const std::string& _SubStr)
		{
			std::cerr << _MainStr;
		};

	protected:

		inline virtual ~BaseSystem() {}

		unsigned int WindWidth = 0;
		unsigned int WindHeight = 0;

		unsigned long FPS = 60;

		ChCpp::BitBool ButtonList;
		ChCpp::BitBool IsNowPush;

		ChStd::Bool UseSystemButton = false;

		//Pause�p�ϐ�//
		ChStd::Bool NowKey = false;
		ChStd::Bool PauseFlg = false;



	};

	///////////////////////////////////////////////////////////////////////////////////

	//static const std::function<const BaseSystem*()>System = BaseSystem::GetSystem;


}

#endif
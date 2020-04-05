
#ifndef Ch_Game_BaseSystem_h
#define Ch_Game_BaseSystem_h

namespace ChSystem
{
	class BaseSystem:public ChCpp::ChCp::InitPack
	{


	public:

		struct Mouse
		{

			ChVec2 HweelPos;
			ChVec2 NowPos;
			ChVec2 Move;

			ChStd::Bool LookFlg = true;
			ChStd::Bool StaticFlg = false;
			ChVec2 StartPos;
		};


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
		const inline unsigned int GetWindWidth() { return WindWidth; }

		//Wind�̗����T�C�Y�擾//
		const inline unsigned int GetWindHeight() { return WindHeight; }

		inline const Mouse GetMouseData() const { return Mou; }

		//FPS�J�E���g�̎擾//
		const inline unsigned long GetFPSCnt() { return FPS; }

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

		virtual void ErrerMessage(
			const std::string& _MainStr
			, const std::string& _SubStr)
		{
			std::cerr << _MainStr;
		};

	protected:

		virtual ~BaseSystem() {}

		unsigned int WindWidth = 0;
		unsigned int WindHeight = 0;

		unsigned long FPS = 60;

		Mouse Mou;

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
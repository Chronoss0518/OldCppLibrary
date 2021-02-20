#ifdef _WINDOWS_

#ifndef Ch_Win_Mou_h
#define Ch_Win_Mou_h

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{

	class MouseController :public ChCpp::ChCp::Initializer,public ChCpp::ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(
			const HWND& _hWnd
			, const unsigned long _WindWidth
			, const unsigned long _WindHeight);

		void Init(const ChSystem::Windows& _Win);

		void Release()override;

		inline void SetWindSize(
			const unsigned long _WindWidth
			, const unsigned long _WindHeight)
		{
			if (!*this)return;
			WindWidth = _WindWidth;
			WindHeight = _WindHeight;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetVisibleFlg(const ChStd::Bool _Flg)
		{
			if (!*this)return;
			VisFlg = _Flg; 
		}

		inline void SetCenterFixedFlg(const ChStd::Bool _Flg)
		{
			if (!*this)return;
			VisFlg = _Flg; 
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline POINTS GetWeelMove()
		{
			if (!*this)return { 0,0 };
			return WheelMoveVal; 
		}

		inline POINT GetNowPos() 
		{
			if (!*this)return { 0,0 };
			return NowPos; 
		}

		ChVec2 GetNowPosToChVec2();

		ChVec2 GetNowProPosToChVec2();

		POINT GetMoveValue();

		ChVec2 GetMoveValueToChVec2();

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		void Update();

		void WheelUpdate(const POINTS _UpdateData)
		{
			if (!WheelMoveFlg)return;
			WheelMoveVal = _UpdateData; 
			if(WheelMoveVal.x > 0 || WheelMoveVal.x < 0)WheelMoveVal.x /= WHEEL_DELTA;
			if(WheelMoveVal.y > 0 || WheelMoveVal.y < 0)WheelMoveVal.y /= WHEEL_DELTA;

			WheelMoveFlg = false;
		}
		  
		///////////////////////////////////////////////////////////////////////////////////

		void ReSetWheel()
		{
			WheelMoveVal.x = 0;
			WheelMoveVal.y = 0;
			WheelMoveFlg = true;
		}

		friend ChSystem::Windows;

	protected:

		///////////////////////////////////////////////////////////////////////////////////

	private:
		
		POINTS WheelMoveVal{ 0,0 };
		POINT CenterPos{ 0,0 };
		POINT NowPos{ 0,0 };
		POINT BeforPos{ 0,0 };

		ChStd::Bool WheelMoveFlg = true;
		ChStd::Bool VisFlg = false;
		ChStd::Bool SetCenterPosFlg = false;

		unsigned long WindWidth = 0;
		unsigned long WindHeight = 0;
		HWND hWnd = nullptr;

		MouseController(){}

	public:

		static MouseController& GetIns()
		{
			static MouseController Ins;
			return Ins;
		}

	};

	static const std::function<MouseController&()>Mouse = MouseController::GetIns;

}

#endif

#endif
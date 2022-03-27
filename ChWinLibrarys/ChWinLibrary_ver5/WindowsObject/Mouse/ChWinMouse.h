#ifdef _WINDOWS_

#ifndef Ch_Win_Mou_h
#define Ch_Win_Mou_h

namespace ChSystem
{
	class Windows;
}

namespace ChWin
{

	class MouseController :public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(
			const HWND& _hWnd
			, const unsigned long _windWidth
			, const unsigned long _windHeight);

		void Init(const ChSystem::Windows& _win);

		void Release()override;

		inline void SetWindSize(
			const unsigned long _windWidth
			, const unsigned long _windHeight)
		{
			if (!*this)return;
			windSize.w = _windWidth;
			windSize.h = _windHeight;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetVisibleFlg(const ChStd::Bool _flg)
		{
			if (!*this)return;
			visFlg = _flg; 
		}

		inline void SetCenterFixedFlg(const ChStd::Bool _flg)
		{
			if (!*this)return;
			setCenterPosFlg = _flg;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline POINTS GetWeelMove()
		{
			if (!*this)return { 0,0 };
			return wheelMoveVal; 
		}

		inline POINT GetNowPos() 
		{
			if (!*this)return { 0,0 };
			return nowPos; 
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
			if (!wheelMoveFlg)return;
			wheelMoveVal = _UpdateData; 
			if(wheelMoveVal.x > 0 || wheelMoveVal.x < 0)wheelMoveVal.x /= WHEEL_DELTA;
			if(wheelMoveVal.y > 0 || wheelMoveVal.y < 0)wheelMoveVal.y /= WHEEL_DELTA;

			wheelMoveFlg = false;
		}
		  
		///////////////////////////////////////////////////////////////////////////////////

		void ReSetWheel()
		{
			wheelMoveVal.x = 0;
			wheelMoveVal.y = 0;
			wheelMoveFlg = true;
		}

		friend ChSystem::Windows;

	protected:

		///////////////////////////////////////////////////////////////////////////////////

	private:
		
		POINTS wheelMoveVal{ 0,0 };
		POINT centerPos{ 0,0 };
		POINT nowPos{ 0,0 };
		POINT beforPos{ 0,0 };

		ChStd::Bool wheelMoveFlg = true;
		ChStd::Bool visFlg = false;
		ChStd::Bool setCenterPosFlg = false;

		ChMath::Vector2Base<unsigned long>windSize;

		HWND hWnd = nullptr;

		MouseController(){}

	public:

		static MouseController& GetIns()
		{
			static MouseController ins;
			return ins;
		}

	};

	static const std::function<MouseController&()>Mouse = MouseController::GetIns;

}

#endif

#endif
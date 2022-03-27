#ifndef Ch_CPP_D3DOBJ_XICon_h
#define Ch_CPP_D3DOBJ_XICon_h

namespace ChD3D
{

	class XInputController:public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructorDestructor//

		XInputController();

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init();

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetLMoterSpeed(const unsigned short _Speed)
		{
			vibFlgs.wLeftMotorSpeed = _Speed;
		}

		inline void SetRMoterSpeed(const unsigned short _Speed)
		{
			vibFlgs.wRightMotorSpeed = _Speed;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline unsigned char GetNo()
		{
			return myNo;
		}

		inline unsigned long GetUpdateCounts()
		{
			return state.dwPacketNumber;
		}

		inline ChStd::Bool GetUpFlg() 
		{
			return (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) > 0;
		}

		inline ChStd::Bool GetDownFlg() 
		{
			return (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) > 0;
		}

		inline ChStd::Bool GetLeftFlg() 
		{ 
			return (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) > 0;
		}

		inline ChStd::Bool GetRightFlg()
		{
			return (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) > 0;
		}

		inline ChStd::Bool GetStartFlg() 
		{
			return (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) > 0;
		}

		inline ChStd::Bool GetBackFlg() 
		{
			return (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) > 0;
		}

		inline ChStd::Bool GetAFlg()
		{
			return (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) > 0;
		}

		inline ChStd::Bool GetBFlg() 
		{
			return (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) > 0;
		}

		inline ChStd::Bool GetXFlg() 
		{
			return (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) > 0;
		}

		inline ChStd::Bool GetYFlg() 
		{
			return (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) > 0;
		}

		inline ChStd::Bool GetL1Flg() 
		{
			return (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) > 0;
		}

		inline float GetL2Trigger()
		{
			return RL2DeadZoneTest(state.Gamepad.bLeftTrigger);
		}

		inline ChStd::Bool GetL3Flg()
		{
			return (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) > 0;
		}

		inline ChStd::Bool GetR1Flg()
		{
			return (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) > 0;
		}

		inline float GetR2Trigger() 
		{
			return RL2DeadZoneTest(state.Gamepad.bRightTrigger);
		}

		inline ChStd::Bool GetR3Flg()
		{
			return (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) > 0;
		}

		inline float GetLXStick()
		{
			return LDeadZoneTest(state.Gamepad.sThumbLX);
		}

		inline float GetLYStick()
		{
			return LDeadZoneTest(state.Gamepad.sThumbLY);
		}

		inline float GetRXStick()
		{
			return RDeadZoneTest(state.Gamepad.sThumbRX);
		}

		inline float GetRYStick()
		{
			return RDeadZoneTest(state.Gamepad.sThumbRY);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		void Update();

		///////////////////////////////////////////////////////////////////////////////////

		float RDeadZoneTest(const float _sThumb);

		float LDeadZoneTest(const float _sThumb);

		float RL2DeadZoneTest(const unsigned char _sButton);

		///////////////////////////////////////////////////////////////////////////////////

	private:

		static ChCpp::BitBool controllerFlgs;
		unsigned char myNo = 5;
		XINPUT_STATE state = { 0,{0,0,0,0,0,0,0} };
		XINPUT_VIBRATION vibFlgs = {0,0};
	};

}


#endif

#include<Windows.h>
#include<Xinput.h>

#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"
#include"ChXInputController.h"

#pragma comment(lib,"xinput.lib")

using namespace ChD3D;

ChCpp::BitBool XInputController::ControllerFlgs;

///////////////////////////////////////////////////////////////////////////////////

void XInputController::Init()
{
	unsigned char Tmp = 0;

	for (unsigned char i = 0; i < 4; i++)
	{
		if (ControllerFlgs.GetBitFlg(i))continue;

		MyNo = i;
		ControllerFlgs.SetBitTrue(i);
		break;
	}

	SetInitFlg(true);

}

///////////////////////////////////////////////////////////////////////////////////

void XInputController::Release()
{
	State.Gamepad.bLeftTrigger = 0;
	State.Gamepad.bRightTrigger = 0;
	State.Gamepad.sThumbLX = 0;
	State.Gamepad.sThumbLY = 0;
	State.Gamepad.sThumbRX = 0;
	State.Gamepad.sThumbRY = 0;
	State.Gamepad.wButtons = 0;

	ControllerFlgs.SetBitFalse(MyNo);
	MyNo = 5;

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void XInputController::Update()
{
	if (!*this) return;

	ZeroMemory(&State, sizeof(XINPUT_STATE));

	XInputGetState(MyNo, &State);

	auto LTest = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	auto RTest = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

	State.Gamepad.sThumbLX = State.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? 0 : State.Gamepad.sThumbLX;
	State.Gamepad.sThumbLX = State.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? 0 : State.Gamepad.sThumbLX;

	State.Gamepad.sThumbLY = State.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? 0 : State.Gamepad.sThumbLY;
	State.Gamepad.sThumbLY = State.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? 0 : State.Gamepad.sThumbLY;

	State.Gamepad.sThumbRX = State.Gamepad.sThumbRX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? 0 : State.Gamepad.sThumbRX;
	State.Gamepad.sThumbRX = State.Gamepad.sThumbRX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? 0 : State.Gamepad.sThumbRX;

	State.Gamepad.sThumbRY = State.Gamepad.sThumbRY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? 0 : State.Gamepad.sThumbRY;
	State.Gamepad.sThumbRY = State.Gamepad.sThumbRY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? 0 : State.Gamepad.sThumbRY;

}

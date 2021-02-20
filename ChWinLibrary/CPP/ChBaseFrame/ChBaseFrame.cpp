
#include"../../BaseIncluder/ChBase.h"

#include"ChBaseFrame.h"


using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//BaseFrame9ƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void BaseFrameList::Update()
{
	if (NowFrame == nullptr)return;
	NowFrame->Frame();

	Chenges();
}

///////////////////////////////////////////////////////////////////////////////////

void BaseFrameList::ChengeFrame(const std::string& _FrameName)
{
	if (FrameList.find(_FrameName) == FrameList.end())return;

	NextFrame = FrameList[_FrameName]();


}

///////////////////////////////////////////////////////////////////////////////////

void BaseFrameList::Chenges()
{

	if (NextFrame == nullptr)return;

	if (NowFrame != nullptr)
	{
		NowFrame->Release();
	}

	NowFrame = NextFrame;

	NowFrame->Init();

	NextFrame = nullptr;
}

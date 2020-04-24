
#include"../../ChGameIncludeFile.h"
#include"ChBaseFrame.h"



using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//BaseFrame9ƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void BaseFrameList::Update()
{
	if (NowFrame.lock() == nullptr)return;
	NowFrame.lock()->Frame();

	Chenges();
}

///////////////////////////////////////////////////////////////////////////////////

void BaseFrameList::ChengeFrame(const std::string& _FrameName)
{
	if (FrameList.find(_FrameName) == FrameList.end())return;

	NextFrame = FrameList[_FrameName];


}

///////////////////////////////////////////////////////////////////////////////////

void BaseFrameList::Chenges()
{

	if (NextFrame == nullptr)return;

	if (NowFrame.lock() != nullptr)
	{
		NowFrame.lock()->Release();
	}

	NowFrame = NextFrame;

	NowFrame.lock()->Init();

	NextFrame = nullptr;
}

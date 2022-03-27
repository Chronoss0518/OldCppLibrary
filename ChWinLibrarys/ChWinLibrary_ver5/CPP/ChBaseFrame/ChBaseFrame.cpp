
#include"../../BaseIncluder/ChBase.h"

#include"ChBaseFrame.h"


using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//BaseFrame9ƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void BaseFrameList::Update()
{
	if (nowFrame == nullptr)return;
	nowFrame->Frame();

	Chenges();
}

///////////////////////////////////////////////////////////////////////////////////

void BaseFrameList::ChengeFrame(const std::string& _frameName)
{
	if (frameList.find(_frameName) == frameList.end())return;

	nextFrame = frameList[_frameName]();


}

///////////////////////////////////////////////////////////////////////////////////

void BaseFrameList::Chenges()
{

	if (nextFrame == nullptr)return;

	if (nowFrame != nullptr)
	{
		nowFrame->Release();
	}

	nowFrame = nextFrame;

	nowFrame->Init();

	nextFrame = nullptr;
}

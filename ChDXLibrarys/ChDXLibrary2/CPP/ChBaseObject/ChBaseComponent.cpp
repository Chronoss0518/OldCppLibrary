#include"../../ChGameIncludeFile.h"
#include"ChBaseComponent.h"
#include"ChObjectManager.h"
#include"ChBaseObject.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChBaseComponentÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void BaseComponent::BaseInit(const ChPtr::Shared<BaseObject> _Obj)
{
	Obj = _Obj;
}

void BaseComponent::Destroy()
{
	Obj->DeleteList.push_back(shared_from_this());
	DFlg = true;
}

void BaseComponent::ObjectDestroy()
{
	Obj->Destroy();
}
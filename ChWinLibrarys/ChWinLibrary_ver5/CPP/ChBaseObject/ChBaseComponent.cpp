
#include"../../BaseIncluder/ChBase.h"

#include"ChBaseComponent.h"
#include"ChObjectManager.h"
#include"ChBaseObject.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChBaseComponentÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void BaseComponent::BaseInit(ChPtr::Shared<BaseObject> _obj)
{
	obj = _obj;

	Init();
}

void BaseComponent::Destroy()
{
	dFlg = true;
}

void BaseComponent::ObjectDestroy()
{
	auto tmpObj = obj.lock();
	if (tmpObj == nullptr)return;
	tmpObj->Destroy();
}
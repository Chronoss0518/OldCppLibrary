
#include"../../ChInclude/ChGameBI.h"

#include"ChBaseComponent.h"
#include"ChObjectManager.h"
#include"ChBaseObject.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChBaseComponentÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void BaseComponent::BaseInit(const BaseObject* _Obj)
{
	Obj = const_cast<BaseObject*>(_Obj);
}

void BaseComponent::Destroy()
{
	DFlg = true;
}

void BaseComponent::ObjectDestroy()
{
	Obj->Destroy();
}
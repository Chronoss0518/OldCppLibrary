
#include"../../ChInclude/ChGameBI.h"

#include"ChBaseComponent.h"
#include"ChObjectManager.h"
#include"ChBaseObject.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//BaseObjectƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::Destroy()
{
	ObjMa->DeleteList[Tag].push_back(shared_from_this());
	DFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::DestroyToChild(const ChPtr::Shared<BaseObject>& _Child)
{
	
	ObjMa->DeleteList[_Child->Tag].push_back(_Child);
	DFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::BaseRelease()
{
	if (!ComList.empty())ComList.clear();
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::BaseInit(
	const std::string& _ObjectName
	, const std::string& _Tag
	, const ObjectManager* _ObjMa)
{
	ObjMa = (ObjectManager*)_ObjMa;
	Tag = _Tag;
	MyName = _ObjectName;
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::ReleaseComponent(const std::string& _ComName)
{

	for (auto&& Com : ComList)
	{
		std::string TmpName = typeid((*Com)).name();


		if (TmpName.find(_ComName) == TmpName.npos) {
			continue;
		}

		auto Tmp = std::find(ComList.begin(), ComList.end(), Com);

		ComList.erase(Tmp);
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::ChengeTag(const std::string& _NewTag)
{
	if (DFlg)return;
	auto Tmp = std::find(
		ObjMa->ObjectList[Tag].begin()
		, ObjMa->ObjectList[Tag].end()
		, shared_from_this());

	auto TmpTag = (*Tmp)->Tag;

	ObjMa->ObjectList[_NewTag].push_back((*Tmp));

	ObjMa->ObjectList[TmpTag].erase(Tmp);

	(*Tmp)->Tag = _NewTag;

	if (!ObjMa->ObjectList[TmpTag].empty())return;

	ObjMa->ObjectList.erase(TmpTag);

}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::ComponentMove()
{

	for (auto&& Com : ComList)
	{
		if (Com->DFlg)continue;
		if (!Com->UseFlg)continue;
		Com->Move();
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::ComponentUpdate()
{
	for (auto&& Com : ComList)
	{
		if (Com->DFlg)continue;
		if (!Com->UseFlg)continue;
		Com->Update();
	}

	if (DeleteList.empty())return;

	for (auto&& Com : DeleteList)
	{
		auto Tmp = std::find(
			ComList.begin()
			, ComList.end()
			, Com);
		(*Tmp)->Release();
		ComList.erase(Tmp);
		continue;

	}

	DeleteList.clear();
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::ComponentDraw3D()
{
	for (auto&& Com : ComList)
	{
		if (Com->DFlg)continue;
		if (!Com->UseFlg)continue;
		Com->Draw3D();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::ComponentDraw2D()
{
	for (auto&& Com : ComList)
	{
		if (Com->DFlg)continue;
		if (!Com->UseFlg)continue;
		Com->Draw2D();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<BaseObject>> BaseObject::LookObjectList()
{
	std::vector<ChPtr::Shared<BaseObject>>TmpObjList;

	for (auto&&objlist : ObjMa->ObjectList)
	{
		for (auto&& obj : objlist.second)
		{
			TmpObjList.push_back(obj);
		}
	}

	return TmpObjList;

}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<BaseObject>> BaseObject::LookObjectListForTag
(const std::string& _Tag)
{
	std::vector<ChPtr::Shared<BaseObject>>TmpObjList;

	if (ObjMa->ObjectList.find(_Tag) == ObjMa->ObjectList.end())return TmpObjList;

	auto objlist = ObjMa->ObjectList[_Tag];

	for (auto&& obj : objlist)
	{
		TmpObjList.push_back(obj);
	}

	return TmpObjList;

}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<BaseObject>>
BaseObject::LookObjectListForName(const std::string& _ObjectName)
{

	std::vector<ChPtr::Shared<BaseObject>>TmpObjList;

	for (auto&& Tags : ObjMa->ObjectList)
	{
		for (auto&& Obj : Tags.second)
		{
			if (_ObjectName != Obj->MyName)continue;
			TmpObjList.push_back(Obj);
		}
	}

	return TmpObjList;

}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<BaseObject>>
BaseObject::LookObjectListForTagAndName(
	const std::string& _ObjectName
	,const std::string& _Tag)
{
	std::vector<ChPtr::Shared<BaseObject>>TmpObjList;

	if (ObjMa->ObjectList.find(_Tag) == ObjMa->ObjectList.end())return TmpObjList;

	auto objlist = ObjMa->ObjectList[_Tag];

	for (auto&& obj : objlist)
	{
		if (_ObjectName != obj->MyName)continue;
		TmpObjList.push_back(obj);
	}

	return TmpObjList;


}


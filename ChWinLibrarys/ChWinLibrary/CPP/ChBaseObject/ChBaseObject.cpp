
#include"../../BaseIncluder/ChBase.h"

#include"ChBaseComponent.h"
#include"ChObjectManager.h"
#include"ChBaseObject.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//BaseObject???\?b?h
///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::Destroy()
{
	DFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::DestroyToChild(const ChPtr::Shared<BaseObject>& _Child)
{
	auto It = std::find(ChildList.begin(), ChildList.end(), _Child);

	if (It == ChildList.end())return;
	(*It)->DFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::UpdateBeginFunction()
{
	UpdateBegin();

	for (auto Com : ComList)
	{
		Com->UpdateBegin();
	}

	for (auto&& Childs : ChildList)
	{
		Childs->UpdateBegin();
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::UpdateFunction()
{

	IsReleasComponent();

	Update();

	for (auto Com : ComList)
	{
		Com->Update();
	}

	for (auto&& Childs : ChildList)
	{
		Childs->Update();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::UpdateEndFunction()
{

	UpdateEnd();

	for (auto Com : ComList)
	{
		Com->UpdateEnd();
	}

	for (auto&& Childs : ChildList)
	{
		Childs->UpdateEnd();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::MoveBeginFunction()
{

	MoveBegin();

	for (auto Com : ComList)
	{
		Com->MoveBegin();
	}

	for (auto&& Childs : ChildList)
	{
		Childs->MoveBegin();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::MoveFunction()
{

	Move();

	for (auto Com : ComList)
	{
		Com->Move();
	}

	for (auto&& Childs : ChildList)
	{
		Childs->Move();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::MoveEndFunction()
{

	MoveEnd();

	for (auto Com : ComList)
	{
		Com->MoveEnd();
	}

	for (auto&& Childs : ChildList)
	{
		Childs->MoveEnd();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::DrawBeginFunction()
{

	DrawBegin();

	for (auto Com : ComList)
	{
		Com->DrawBegin();
	}

	for (auto&& Childs : ChildList)
	{
		Childs->DrawBegin();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::Draw3DFunction()
{

	Draw3D();

	for (auto Com : ComList)
	{
		Com->Draw3D();
	}

	for (auto&& Childs : ChildList)
	{
		Childs->Draw3D();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::Draw2DFunction()
{

	Draw2D();

	for (auto Com : ComList)
	{
		Com->Draw2D();
	}

	for (auto&& Childs : ChildList)
	{
		Childs->Draw2D();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::DrawEndFunction()
{

	DrawEnd();

	for (auto Com : ComList)
	{
		Com->DrawEnd();
	}

	for (auto&& Childs : ChildList)
	{
		Childs->DrawEnd();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::BaseRelease()
{
	if (!ComList.empty())ComList.clear();

	for (auto&& Childs : ChildList)
	{
		Childs->BaseRelease();
	}
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

void BaseObject::IsReleasComponent()
{

	auto Com = ComList.begin();
	while (Com != ComList.end())
	{
		if (!(*Com)->DFlg)
		{
			Com++;
			continue;
		}
		ComList.erase(Com);

	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::EraseRootObj(const ChPtr::Shared<BaseObject> _Obj)
{

	{
		auto It = std::find(
			ObjMa->RootObjects.begin()
			, ObjMa->RootObjects.end()
			, _Obj);

		ObjMa->RootObjects.erase(It);
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



#include"../../BaseIncluder/ChBase.h"

#include"ChBaseComponent.h"
#include"ChObjectManager.h"
#include"ChBaseObject.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//BaseObjectÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::Destroy()
{
	dFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::DestroyToChild(const ChPtr::Shared<BaseObject>& _child)
{
	auto It = std::find(childList.begin(), childList.end(), _child);

	if (It == childList.end())return;
	(*It)->dFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::UpdateBeginFunction()
{
	UpdateBegin();

	for (auto com : comList)
	{
		com->UpdateBegin();
	}

	for (auto&& childs : childList)
	{
		childs->UpdateBeginFunction();
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::UpdateFunction()
{

	IsReleasComponent();

	Update();

	for (auto com : comList)
	{
		com->Update();
	}

	for (auto&& childs : childList)
	{
		childs->UpdateFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::UpdateEndFunction()
{

	UpdateEnd();

	for (auto com : comList)
	{
		com->UpdateEnd();
	}

	for (auto&& childs : childList)
	{
		childs->UpdateEnd();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::MoveBeginFunction()
{

	MoveBegin();

	for (auto com : comList)
	{
		com->MoveBegin();
	}

	for (auto&& childs : childList)
	{
		childs->MoveBeginFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::MoveFunction()
{

	Move();

	for (auto com : comList)
	{
		com->Move();
	}

	for (auto&& childs : childList)
	{
		childs->MoveFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::MoveEndFunction()
{

	MoveEnd();

	for (auto com : comList)
	{
		com->MoveEnd();
	}

	for (auto&& childs : childList)
	{
		childs->MoveEndFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::DrawBeginFunction()
{

	DrawBegin();

	for (auto com : comList)
	{
		com->DrawBegin();
	}

	for (auto&& childs : childList)
	{
		childs->DrawBeginFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::Draw3DFunction()
{

	Draw3D();

	for (auto com : comList)
	{
		com->Draw3D();
	}

	for (auto&& childs : childList)
	{
		childs->Draw3DFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::Draw2DFunction()
{

	Draw2D();

	for (auto com : comList)
	{
		com->Draw2D();
	}

	for (auto&& childs : childList)
	{
		childs->Draw2DFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::DrawEndFunction()
{

	DrawEnd();

	for (auto com : comList)
	{
		com->DrawEnd();
	}

	for (auto&& childs : childList)
	{
		childs->DrawEndFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::BaseRelease()
{


	for (auto com : comList)
	{
		com->Release();
	}

	if (!comList.empty())comList.clear();

	for (auto&& childs : childList)
	{
		childs->BaseRelease();
	}

	Release();
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::BaseInit(
	const std::string& _ObjectName
	, const std::string& _tag
	, const ObjectManager* _objMa)
{
	objMa = (ObjectManager*)_objMa;
	tag = _tag;
	myName = _ObjectName;

	Init();
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::ReleaseComponent(const std::string& _comName)
{

	for (auto&& com : comList)
	{
		std::string tmpName = typeid((*com)).name();

		if (tmpName.find(_comName) == tmpName.npos) {
			continue;
		}

		auto tmp = std::find(comList.begin(), comList.end(), com);

		comList.erase(tmp);

		if (comList.empty())break;

	}
}

///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::ChengeTag(const std::string& _newTag)
{
	if (dFlg)return;
	auto tmp = std::find(
		objMa->objectList[tag].begin()
		, objMa->objectList[tag].end()
		, shared_from_this());

	auto tmpTag = (*tmp)->tag;

	objMa->objectList[_newTag].push_back((*tmp));

	objMa->objectList[tmpTag].erase(tmp);

	(*tmp)->tag = _newTag;

	if (!objMa->objectList[tmpTag].empty())return;

	objMa->objectList.erase(tmpTag);

}
///////////////////////////////////////////////////////////////////////////////////////

void BaseObject::IsReleasComponent()
{

	if (comList.empty())return;
	auto com = comList.begin();
	while (com != comList.end())
	{
		if (!(*com)->dFlg)
		{
			com++;
			continue;
		}
		comList.erase(com);

		if (comList.empty())break;

	}
}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<BaseObject>> BaseObject::LookObjectList()
{
	std::vector<ChPtr::Shared<BaseObject>>tmpObjList;

	for (auto&&objlist : objMa->objectList)
	{
		for (auto&& obj : objlist.second)
		{
			tmpObjList.push_back(obj);
		}
	}

	return tmpObjList;

}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<BaseObject>> BaseObject::LookObjectListForTag
(const std::string& _tag)
{
	std::vector<ChPtr::Shared<BaseObject>>tmpObjList;

	if (objMa->objectList.find(_tag) == objMa->objectList.end())return tmpObjList;

	auto objlist = objMa->objectList[_tag];

	for (auto&& obj : objlist)
	{
		tmpObjList.push_back(obj);
	}

	return tmpObjList;

}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<BaseObject>>
BaseObject::LookObjectListForName(const std::string& _ObjectName)
{

	std::vector<ChPtr::Shared<BaseObject>>tmpObjList;

	for (auto&& tags : objMa->objectList)
	{
		for (auto&& Obj : tags.second)
		{
			if (_ObjectName != Obj->myName)continue;
			tmpObjList.push_back(Obj);
		}
	}

	return tmpObjList;

}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<BaseObject>>
BaseObject::LookObjectListForTagAndName(
	const std::string& _ObjectName
	,const std::string& _tag)
{
	std::vector<ChPtr::Shared<BaseObject>>tmpObjList;

	if (objMa->objectList.find(_tag) == objMa->objectList.end())return tmpObjList;

	auto objlist = objMa->objectList[_tag];

	for (auto&& obj : objlist)
	{
		if (_ObjectName != obj->myName)continue;
		tmpObjList.push_back(obj);
	}

	return tmpObjList;


}


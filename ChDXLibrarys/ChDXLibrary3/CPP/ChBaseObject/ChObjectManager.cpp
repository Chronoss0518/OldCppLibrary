
#include"../../ChGameIncludeFile.h"
#include"ChBaseComponent.h"
#include"ChObjectManager.h"
#include"ChBaseObject.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChObjectManagerÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::Release()
{
	if(!ObjectList.empty())ObjectList.clear();

	if (!DeleteList.empty())DeleteList.clear();

}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<BaseObject>> ObjectManager::GetObjectList()
{
	std::vector<ChPtr::Shared<BaseObject>>TmpObjList;

	for (auto&&objlist : ObjectList)
	{
		for (auto&& obj : objlist.second)
		{
			TmpObjList.push_back(obj);
		}
	}

	return TmpObjList;

}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<BaseObject>> ObjectManager::GetObjectListForTag(const std::string& _TagName)
{

	std::vector<ChPtr::Shared<BaseObject>>TmpObjList;

	for (auto&&obj : ObjectList[_TagName])
	{
		TmpObjList.push_back(obj);
	}

	return TmpObjList;

}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<BaseObject>> ObjectManager::GetObjectListForName(const std::string& _Name)
{

	std::vector<ChPtr::Shared<BaseObject>>TmpObjList;

	for (auto&&objlist : ObjectList)
	{
		for (auto&& obj : objlist.second)
		{
			if (obj->GetMyName() != _Name)continue;
			TmpObjList.push_back(obj);
		}
	}

	return TmpObjList;
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::Update()
{


	for (auto&& ObjList : ObjectList)
	{
		for (auto&& Obj : ObjList.second)
		{
			if (Obj->DFlg)continue;
			if (!Obj->UseFlg)continue;
			Obj->Update();
			Obj->ComponentUpdate();
		}
	}

	for (auto&& ObjList : ObjectList)
	{
		for (auto&& Obj : ObjList.second)
		{
			if (Obj->DFlg)continue;
			if (!Obj->UseFlg)continue;
			Obj->LastUpdate();
		}
	}

	if (DeleteList.empty())return;

	for (auto&& ObjList : DeleteList)
	{
		for (auto&& Obj : ObjList.second)
		{

			Obj->Release();
			Obj->BaseRelease();
			auto Tmp = std::find(
				ObjectList[ObjList.first].begin()
				, ObjectList[ObjList.first].end()
				, Obj);
			ObjectList[ObjList.first].erase(Tmp);
		}

	}

	DeleteList.clear();

}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::Move()
{

	for (auto&& ObjList : ObjectList)
	{
		for (auto&& Obj : ObjList.second)
		{
			if (Obj->DFlg)continue;
			if (!Obj->UseFlg)continue;
			Obj->Move();
			Obj->ComponentMove();
		}
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ClearObjectForTag(const std::string& _Tags)
{
	if (ObjectList.find(_Tags) == ObjectList.end())return;

	for (auto&& Obj : ObjectList[_Tags])
	{
		Obj->Destroy();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ClearObjectForName(const std::string& _Name)
{

	for (auto&& ObjList : ObjectList)
	{
		for (auto&& Obj : ObjList.second)
		{
			if (Obj->MyName.find(_Name, 0) == std::string::npos)continue;
			Obj->Destroy();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ClearObjectForTagAndName(
	const std::string& _Name,
	const std::string& _Tags)
{

	if (ObjectList.find(_Tags) == ObjectList.end())return;

	for (auto&& Obj : ObjectList[_Tags])
	{
		if (Obj->MyName.find(_Name, 0) != std::string::npos)continue;

		Obj->Destroy();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::Draw()
{

	for (auto&& ObjList : ObjectList)
	{
		for (auto&& Obj : ObjList.second)
		{
			if (Obj->DFlg)continue;
			if (!Obj->UseFlg)continue;
			Obj->Draw3D();
			Obj->ComponentDraw3D();
		}
	}

	for (auto&& ObjList : ObjectList)
	{
		for (auto&& Obj : ObjList.second)
		{
			if (Obj->DFlg)continue;
			if (!Obj->UseFlg)continue;
			Obj->Draw2D();
			Obj->ComponentDraw2D();
		}
	}
}

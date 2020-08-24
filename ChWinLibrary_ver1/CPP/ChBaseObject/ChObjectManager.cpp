
#include"../../BaseIncluder/ChBase.h"

#include"ChObjectManager.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ChObjectManagerÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::Release()
{
	if (!ObjectList.empty())ObjectList.clear();

}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<BaseObject>> ObjectManager::GetObjectList()
{
	std::vector<ChPtr::Shared<BaseObject>>TmpObjList;

	for (auto&& objlist : ObjectList)
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

	for (auto&& obj : ObjectList[_TagName])
	{
		TmpObjList.push_back(obj);
	}

	return TmpObjList;

}

///////////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<BaseObject>> ObjectManager::GetObjectListForName(const std::string& _Name)
{

	std::vector<ChPtr::Shared<BaseObject>>TmpObjList;

	for (auto&& objlist : ObjectList)
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

	for (auto&& ObjGloap : ObjectList)
	{
		auto Obj = ObjGloap.second.begin();
		while (Obj != ObjGloap.second.end())
		{
			if ((*Obj) != nullptr)
			{

				if (!(*Obj)->DFlg)
				{
					(*Obj)->IsReleasComponent();
					Obj++;
					continue;
				}
			}
			ObjGloap.second.erase(Obj);

		}
	}


	for (auto&& Obj : RootObjects)
	{
		Obj->UpdateBeginFunction();
	}

	for (auto&& Obj : RootObjects)
	{
		Obj->UpdateFunction();
	}

	for (auto&& Obj : RootObjects)
	{
		Obj->UpdateEndFunction();
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectUpdateBegin()
{

	for (auto&& Obj : RootObjects)
	{
		Obj->UpdateBeginFunction();
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectUpdate()
{
	for (auto&& ObjGloap : ObjectList)
	{
		auto Obj = ObjGloap.second.begin();
		while (Obj != ObjGloap.second.end())
		{
			if ((*Obj) != nullptr)
			{

				if (!(*Obj)->DFlg)
				{
					(*Obj)->IsReleasComponent();
					Obj++;
					continue;
				}
			}
			ObjGloap.second.erase(Obj);

		}
	}

	for (auto&& Obj : RootObjects)
	{
		Obj->UpdateFunction();
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectUpdateEnd()
{
	for (auto&& Obj : RootObjects)
	{
		Obj->UpdateEndFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::Move()
{
	for (auto&& Obj : RootObjects)
	{
		Obj->MoveBeginFunction();
	}

	for (auto&& Obj : RootObjects)
	{
		Obj->MoveFunction();
	}

	for (auto&& Obj : RootObjects)
	{
		Obj->MoveEndFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectMoveBegin()
{
	for (auto&& Obj : RootObjects)
	{
		Obj->MoveBeginFunction();
	}

	for (auto&& Obj : RootObjects)
	{
		Obj->MoveFunction();
	}

	for (auto&& Obj : RootObjects)
	{
		Obj->MoveEndFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectMove()
{

	for (auto&& Obj : RootObjects)
	{
		Obj->MoveFunction();
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectMoveEnd()
{

	for (auto&& Obj : RootObjects)
	{
		Obj->MoveEndFunction();
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
	for (auto&& Obj : RootObjects)
	{
		Obj->DrawBeginFunction();
	}

	for (auto&& Obj : RootObjects)
	{
		Obj->Draw3DFunction();
	}

	for (auto&& Obj : RootObjects)
	{
		Obj->Draw2DFunction();
	}

	for (auto&& Obj : RootObjects)
	{
		Obj->DrawEndFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectDrawBegin()
{
	for (auto&& Obj : RootObjects)
	{
		Obj->DrawBeginFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectDraw2D()
{
	for (auto&& Obj : RootObjects)
	{
		Obj->Draw3DFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectDraw3D()
{
	for (auto&& Obj : RootObjects)
	{
		Obj->Draw2DFunction();
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ObjectManager::ObjectDrawEnd()
{
	for (auto&& Obj : RootObjects)
	{
		Obj->DrawEndFunction();
	}
}

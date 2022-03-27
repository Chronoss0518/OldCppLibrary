
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"
#include"../../CPP/ChBaseObject/ChBaseObject.h"
#include"../../CPP/ChBaseObject/ChBaseComponent.h"
#include"../../CPP/ChBaseObject/ChObjectManager.h"


#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChShader/ChShader9.h"
#include"../ChAnimationObject/ChAnimationObject9.h"
#include"../ChMesh/ChBaseMesh9.h"
#include"../ChMesh/ChSkinMesh9.h"
#include"../ChMeshManager/ChMeshManager9.h"
#include"ChComponent9.h"
#include"ChModelComponents9.h"


///////////////////////////////////////////////////////////////////////////////////////
//ChModelComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void ChModelCom9::SetModel(const std::string& _modelName)
{
	model = nullptr;

	std::string mName = _modelName;
	std::string path = "./";

	DIvidePathToName(path, mName, _modelName);

	model = ChMesh::BaseMesh9::MeshType(mName);

	model->CreateMesh(mName, path, ChD3D9::D3D9API().GetDevice());

	if (ChPtr::NullCheck(model->GetMesh()))model = nullptr;


}

///////////////////////////////////////////////////////////////////////////////////

void ChModelCom9::Draw3D()
{
	if (model == nullptr)return;
	if (model->GetMesh() == nullptr)return;

	ChMat_9 tmpMat;
	{

		//auto Trans = LookObj()->GetTransform<ChTransformCom9>();

		//if (nullptr != Trans)
		//{
		//	tmpMat = Trans->GetMat();
		//}

	}

	ChD3D9::Shader().DrawMesh(model, tmpMat);

}

///////////////////////////////////////////////////////////////////////////////////

void ChModelCom9::DIvidePathToName(
	std::string& _path
	, std::string& _name
	, const std::string& _fullPathName)
{

	{

		size_t sPos = 0;
		
		ChStd::Bool tmpFlg = false;

		size_t slashSize = 1;
		std::string slash[2]
		{
			"/","\\"
		};

		for (auto&& sla : slash)
		{
			if ((sPos = _fullPathName.rfind(sla.c_str(), _fullPathName.size()))
				== std::string::npos)continue;

			size_t tmpSize = _fullPathName.size() - sPos;
			slashSize = sla.length();
			tmpFlg = true;
			break;
		}


		if (!tmpFlg)return;

		size_t tmpSize = _fullPathName.size() - sPos;

		_path = _fullPathName.substr(0, sPos);
		_name = _fullPathName.substr(sPos + slashSize, tmpSize);

	}

}

///////////////////////////////////////////////////////////////////////////////////////
//ChMModelComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void ChMModelCom9::SetModel(const std::string& _modelName)
{
	std::string mName = _modelName;
	std::string path = "./";

	model = nullptr;

	DIvidePathToName(path, mName, _modelName);

	auto tmpMesh = ChMesh::MeManager9().GetMesh(mName);

	if (tmpMesh != nullptr)
	{
		model = tmpMesh;

		return;

	}

	if (!ChMesh::MeManager9().IsPath(path))
	{
		ChMesh::MeManager9().SetDirectoryPath(path, path);
	}

	ChMesh::MeManager9().SetMesh(mName, mName, path);

	model = ChMesh::MeManager9().GetMesh(mName);

}

///////////////////////////////////////////////////////////////////////////////////////
//ChSkinMeshModelComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void ChSkModelCom9::SetModel(const std::string& _modelName)
{
	model = nullptr;

	std::string mName = _modelName;
	std::string path = "./";

	DIvidePathToName(path, mName, _modelName);


	model = ChMesh::BaseMesh9::SkinMeshType(mName);

	model->CreateMesh(mName, path, ChD3D9::D3D9API().GetDevice());

	if (ChPtr::NullCheck(model->GetMesh()))model = nullptr;


}

///////////////////////////////////////////////////////////////////////////////////

void ChSkModelCom9::Update()
{
	if (model == nullptr)return;

	auto tmpModel = ChPtr::SharedSafeCast<ChMesh::SkinMesh9>(model);

	if (tmpModel == nullptr)return;

	tmpModel->SetSkin();

}

///////////////////////////////////////////////////////////////////////////////////////
//ChMSkinMeshModelComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void ChMSkModelCom9::SetModel(const std::string& _modelName)
{
	std::string mName = _modelName;
	std::string path = "./";

	model = nullptr;

	DIvidePathToName(path, mName, _modelName);


	auto tmpMesh = ChPtr::SharedSafeCast
		<ChMesh::SkinMesh9>(ChMesh::MeManager9().GetMesh(mName));

	if (tmpMesh != nullptr)
	{
		model = tmpMesh;

		return;

	}

	if (ChMesh::MeManager9().IsMesh(mName))return;

	if (!ChMesh::MeManager9().IsPath(path))
	{
		ChMesh::MeManager9().SetDirectoryPath(path, path);
	}

	ChMesh::MeManager9().SetSkinMesh(mName, mName, path);

	model = ChMesh::MeManager9().GetMesh(mName);

}


#include<d3d9.h>
#include<d3dx9.h>
#include<d3dx9anim.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include"../../ChGameIncludeFile.h"

#include"Direct3D9/ChPackDate/ChMatrix_9.h"
#include"Direct3D9/ChPackDate/ChVector3_9.h"
#include"Direct3D9/ChPackDate/ChQuaternion_9.h"
#include"Direct3D9/ChPackDate/ChMaterial9.h"
#include"Direct3D9/ChDirectX9Controller/ChDirectX9Controller.h"

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

void ChModelCom9::SetModel(const std::string& _ModelName)
{
	Model = nullptr;

	std::string MName = _ModelName;
	std::string Path = "./";

	DIvidePathToName(Path, MName, _ModelName);

	Model = ChMesh::BaseMesh9::MeshType(MName);

	Model->CreateMesh(MName, Path, ChD3D9::D3D9API().GetDevice());

	if (ChPtr::NullCheck(Model->GetMesh()))Model = nullptr;


}

///////////////////////////////////////////////////////////////////////////////////

void ChModelCom9::Draw3D()
{
	if (Model == nullptr)return;
	if (Model->GetMesh() == nullptr)return;

	ChMat_9 TmpMat;
	{

		auto Trans = LookObj()->GetComponent<ChTransformCom9>();

		if (nullptr != Trans)
		{

			TmpMat = Trans->GetMat();
		}
	}

	ChD3D9::Shader().DrawMesh(Model, TmpMat);

}

///////////////////////////////////////////////////////////////////////////////////

void ChModelCom9::DIvidePathToName(
	std::string& _Path
	, std::string& _Name
	, const std::string& _FullPathName)
{

	{

		size_t SPos = 0;
		
		ChStd::Bool TmpFlg = false;

		size_t SlashSize = 1;
		std::string Slash[2]
		{
			"/","\\"
		};

		for (auto&& sla : Slash)
		{
			if ((SPos = _FullPathName.rfind(sla.c_str(), _FullPathName.size()))
				== std::string::npos)continue;

			size_t TmpSize = _FullPathName.size() - SPos;
			SlashSize = sla.length();
			TmpFlg = true;
			break;
		}


		if (!TmpFlg)return;

		size_t TmpSize = _FullPathName.size() - SPos;

		_Path = _FullPathName.substr(0, SPos);
		_Name = _FullPathName.substr(SPos + SlashSize, TmpSize);

	}

}

///////////////////////////////////////////////////////////////////////////////////////
//ChMModelComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void ChMModelCom9::SetModel(const std::string& _ModelName)
{
	std::string MName = _ModelName;
	std::string Path = "./";

	Model = nullptr;

	DIvidePathToName(Path, MName, _ModelName);

	auto TmpMesh = ChMesh::MeManager9().GetMesh(MName);

	if (TmpMesh != nullptr)
	{
		Model = TmpMesh;

		return;

	}

	if (!ChMesh::MeManager9().IsPath(Path))
	{
		ChMesh::MeManager9().SetDirectoryPath(Path, Path);
	}

	ChMesh::MeManager9().SetMesh(MName, MName, Path);

	Model = ChMesh::MeManager9().GetMesh(MName);

}

///////////////////////////////////////////////////////////////////////////////////////
//ChSkinMeshModelComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void ChSkModelCom9::SetModel(const std::string& _ModelName)
{
	Model = nullptr;

	std::string MName = _ModelName;
	std::string Path = "./";

	DIvidePathToName(Path, MName, _ModelName);


	Model = ChMesh::BaseMesh9::SkinMeshType(MName);

	Model->CreateMesh(MName, Path, ChD3D9::D3D9API().GetDevice());

	if (ChPtr::NullCheck(Model->GetMesh()))Model = nullptr;


}

///////////////////////////////////////////////////////////////////////////////////

void ChSkModelCom9::Update()
{
	if (Model == nullptr)return;

	auto TmpModel = ChPtr::SharedSafeCast<ChMesh::SkinMesh9>(Model);

	if (TmpModel == nullptr)return;

	TmpModel->SetSkin();

}

///////////////////////////////////////////////////////////////////////////////////////
//ChMSkinMeshModelComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void ChMSkModelCom9::SetModel(const std::string& _ModelName)
{
	std::string MName = _ModelName;
	std::string Path = "./";

	Model = nullptr;

	DIvidePathToName(Path, MName, _ModelName);


	auto TmpMesh = ChPtr::SharedSafeCast
		<ChMesh::SkinMesh9>(ChMesh::MeManager9().GetMesh(MName));

	if (TmpMesh != nullptr)
	{
		Model = TmpMesh;

		return;

	}

	if (ChMesh::MeManager9().IsMesh(MName))return;

	if (!ChMesh::MeManager9().IsPath(Path))
	{
		ChMesh::MeManager9().SetDirectoryPath(Path, Path);
	}

	ChMesh::MeManager9().SetSkinMesh(MName, MName, Path);

	Model = ChMesh::MeManager9().GetMesh(MName);

}

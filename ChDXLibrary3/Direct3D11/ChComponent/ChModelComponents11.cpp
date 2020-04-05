
#include"../../ChGameIncludeFile.h"
#include<d3d9.h>
#include<d3dx9.h>
#include<d3dx9anim.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

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

	{

		size_t SPos = 0;

		if ((SPos = MName.rfind("/", MName.size()))
			!= std::string::npos)
		{

			size_t TmpSize = MName.size() - SPos;

			Path = MName.substr(0, SPos);
			MName = _ModelName.substr(SPos + 1, TmpSize);
		}
	}

	Model = ChMesh::BaseMesh9::MeshType(MName);

	Model->CreateMesh(MName, Path, ChD3D9::D3D9API().GetDevice());

	if (ChPtr::NullCheck(Model->GetMesh()))Model = nullptr;


}

///////////////////////////////////////////////////////////////////////////////////

void ChModelCom9::Draw3D()
{
	if (Model == nullptr)return;

	if (!ChD3D9::D3D9API().IsDraw())return;

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

///////////////////////////////////////////////////////////////////////////////////////
//ChMModelComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void ChMModelCom9::SetModel(const std::string& _ModelName)
{
	std::string MName = _ModelName;
	std::string Path = "./";

	Model = nullptr;

	{

		size_t SPos = 0;

		if ((SPos = MName.rfind("/", MName.size()))
			!= std::string::npos)
		{

			size_t TmpSize = MName.size() - SPos;

			Path = MName.substr(0, SPos);
			MName = _ModelName.substr(SPos + 1, TmpSize);
		}
	}

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

	{

		size_t SPos = 0;

		if ((SPos = MName.rfind("/", MName.size()))
			!= std::string::npos)
		{

			size_t TmpSize = MName.size() - SPos;

			Path = MName.substr(0, SPos);
			MName = _ModelName.substr(SPos + 1, TmpSize);
		}
	}

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

	{

		size_t SPos = 0;

		if ((SPos = MName.rfind("/", MName.size()))
			!= std::string::npos)
		{

			size_t TmpSize = MName.size() - SPos;

			Path = MName.substr(0, SPos);
			MName = _ModelName.substr(SPos + 1, TmpSize);
		}
	}

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

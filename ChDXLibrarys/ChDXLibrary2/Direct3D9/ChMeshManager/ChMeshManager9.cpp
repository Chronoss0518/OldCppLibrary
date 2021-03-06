
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

#include"../ChAnimationObject/ChAnimationObject9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"../ChMesh/ChBaseMesh9.h"
#include"../ChMesh/ChSkinMesh9.h"
#include"ChMeshManager9.h"

using namespace ChMesh;

MeshFace9 MeshManager9::NFace;

std::vector<ChPtr::Shared<ChMaterial_9>> MeshManager9::NMaterial;

///////////////////////////////////////////////////////////////////////////////////////
//MeshManager9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void MeshManager9::Init(const LPDIRECT3DDEVICE9 _Dev)
{
	Device = _Dev;
	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::Release()
{
	if (!MeshList.empty())MeshList.clear();
	if (!PathList.empty())PathList.clear();
	if (MeshList.empty())return;
	MeshList.clear();
	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::SetMesh(
	const std::string& _MeshName
	, const std::string& _DataName
	, const std::string& _UsePashName)
{

	if (MeshList.find(_DataName) != MeshList.end())return;

	if (_MeshName.length() <= 0)return;

	std::string TmpString;
	std::string TmpPathName = "./";
	if (PathList.find(_UsePashName) != PathList.end())
	{
		TmpPathName = *PathList[_UsePashName] + '/';
	}

	auto TmpMesh = Mesh9::MeshType(_MeshName);

	TmpMesh->CreateMesh(_MeshName, TmpPathName, Device);

	if (TmpMesh->InsMesh() == nullptr)
	{
		//ChSystem::ErrerMessage("メッシュが読み込まれませんでした","警告");

		TmpMesh = nullptr;
		return;
	}

	MeshList[_DataName] = TmpMesh;

}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::SetSkinMesh(const std::string& _MeshName
	, const std::string& _DataName
	, const std::string& _UsePashName)
{

	if (MeshList.find(_DataName) != MeshList.end())return;

	if (_MeshName.length() <= 0)return;

	std::string TmpString;
	std::string TmpPathName = "./";
	if (PathList.find(_UsePashName) != PathList.end())
	{
		TmpPathName = *PathList[_UsePashName] + '/';
	}

	auto TmpMesh = Mesh9::SkinMeshType(_MeshName);

	TmpMesh->CreateMesh(_MeshName, TmpPathName, Device);

	if (TmpMesh->InsMesh() == nullptr)
	{
		//ChSystem::ErrerMessage("メッシュが読み込まれませんでした", "警告");

		return;
	}

	{
		auto TmpSkinMesh = ChPtr::SharedSafeCast<ChMesh::SkinMesh9>(TmpMesh);

		if (TmpSkinMesh->BoneList.size() <= 0)
		{
			//ChSystem::ErrerMessage("スキンメッシュではありません", "警告");

			TmpMesh->Release();
			return;
		}
	}


	MeshList[_DataName] = TmpMesh;

}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::SetDirectoryPath(const std::string& _DirectoryPath
	, const std::string& _UseDirectoryPashName)
{
	if (PathList.find(_UseDirectoryPashName) != PathList.end())return;
	if (_DirectoryPath.length() <= 0)return;

	PathList.insert(std::pair<std::string, ChPtr::Shared<std::string>>(_UseDirectoryPashName, ChPtr::Make_S<std::string>()));
	*PathList[_UseDirectoryPashName] = _DirectoryPath;
}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::SetTexture(
	const std::string& _DataName
	, const unsigned long _TexNum
	, const ChPtr::Shared<ChTex::Texture9> _Tex)
{
	if (_Tex == nullptr)return;
	if (MeshList.find(_DataName) == MeshList.end())return;

	if (MeshList[_DataName]->InsTex().size() <= _TexNum)return;

	MeshList[_DataName]->InsTex()[_TexNum] = nullptr;

	MeshList[_DataName]->InsTex()[_TexNum] = _Tex;

}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::SetAnimation(
	const std::string& _MeshName
	, const std::string& _AniamtionName
	, const std::string& _XFileName)
{
	if (MeshList.find(_MeshName) == MeshList.end())
	{
		//ChSystem::ErrerMessage("登録されていない数値です", "警告");

		return;
	}

	auto SkinMesh = ChPtr::SharedSafeCast<SkinMesh9>(MeshList[_MeshName]);

	if (SkinMesh == nullptr)
	{
		//ChSystem::ErrerMessage("スキンメッシュではありません", "警告");

		return;
	}

	SkinMesh->SetAnimation(_AniamtionName, _XFileName);

}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::SetAnimation(
	const std::string& _MeshName
	, const std::string& _AniamtionName
	, const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _Animes)
{

	if (MeshList.find(_MeshName) == MeshList.end())
	{
		//ChSystem::ErrerMessage("登録されていない数値です", "警告");

		return;
	}

	auto SkinMesh = ChPtr::SharedSafeCast<SkinMesh9>(MeshList[_MeshName]);

	if (SkinMesh == nullptr)
	{
		//ChSystem::ErrerMessage("スキンメッシュではありません", "警告");

		return;
	}

	SkinMesh->SetAnimation(_AniamtionName, _Animes);

}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::SetAnimationTime(
	const std::string& _MeshName
	, const std::string& _AniamtionName
	, const float _PlayAniTime)
{

	if (_PlayAniTime <= 0.0f)
	{
		//ChSystem::ErrerMessage("最低でも0より大きい数値が必要です", "警告");

		return;
	}

	if (MeshList.find(_MeshName) == MeshList.end())
	{
		//ChSystem::ErrerMessage("登録されていない数値です", "警告");

		return;
	}

	auto SkinMesh = ChPtr::SharedSafeCast<SkinMesh9>(MeshList[_MeshName]);

	if (SkinMesh == nullptr)
	{
		//ChSystem::ErrerMessage("スキンメッシュではありません", "警告");

		return;
	}

	SkinMesh->SetAniTime(_AniamtionName, _PlayAniTime);
}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::ClearData(const std::string& _DataName)
{
	if (MeshList.empty())return;

	if (MeshList.find(_DataName) == MeshList.end()) return;

	MeshList.erase(_DataName);

	return;

}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::DrawMesh(
	const ChMat_9& _Mat
	, const std::string& _DataName
	, const long _SubNum)
{

	if (MeshList.find(_DataName) == MeshList.end())return;
	MeshList[_DataName]->SetSkin();
	MeshList[_DataName]->Draw(_Mat, Device, _SubNum);

}

///////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<ChMaterial_9>>& MeshManager9::GetMeshMaterials(
	const std::string& _DataName)
{

	if (MeshList.empty())return NMaterial;
	if (MeshList.find(_DataName) == MeshList.end())return NMaterial;
	return MeshList[_DataName]->InsMaterials();
}

///////////////////////////////////////////////////////////////////////////////////

MeshFace9 MeshManager9::GetEasyFace(
	const std::string& _DataName
	, const unsigned long _FaseNum)
{
	MeshFace9 Face;

	if (MeshList.find(_DataName) == MeshList.end())return NFace;
	if (MeshList[_DataName]->InsFace().size() <= _FaseNum)return NFace;
	Face = *MeshList[_DataName]->InsFace()[_FaseNum];
	return Face;
}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::CreateEasyFace(
	const std::string& _DataName
	, const unsigned short _BaseMatNum)
{

	if (MeshList.find(_DataName) == MeshList.end())return;

	MeshList[_DataName]->CreateEasyFaceList();
}


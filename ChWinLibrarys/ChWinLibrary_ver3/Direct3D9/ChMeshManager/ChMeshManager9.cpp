
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"

#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChAnimationObject/ChAnimationObject9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"../ChMesh/ChBaseMesh9.h"
#include"../ChMesh/ChSkinMesh9.h"
#include"ChMeshManager9.h"

using namespace ChMesh;

MeshFace9 MeshManager9::NFace;

std::vector<ChPtr::Shared<ChMaterial_9>> MeshManager9::NMaterial;

///////////////////////////////////////////////////////////////////////////////////////
//MeshManager9ÉÅÉ\ÉbÉh
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
		//ChSystem::ErrerMessage("ÉÅÉbÉVÉÖÇ™ì«Ç›çûÇ‹ÇÍÇ‹ÇπÇÒÇ≈ÇµÇΩ","åxçê");

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
		//ChSystem::ErrerMessage("ÉÅÉbÉVÉÖÇ™ì«Ç›çûÇ‹ÇÍÇ‹ÇπÇÒÇ≈ÇµÇΩ", "åxçê");

		return;
	}

	{
		auto TmpSkinMesh = ChPtr::SharedSafeCast<ChMesh::SkinMesh9>(TmpMesh);

		if (TmpSkinMesh->BoneList.size() <= 0)
		{
			//ChSystem::ErrerMessage("ÉXÉLÉìÉÅÉbÉVÉÖÇ≈ÇÕÇ†ÇËÇ‹ÇπÇÒ", "åxçê");

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
		//ChSystem::ErrerMessage("ìoò^Ç≥ÇÍÇƒÇ¢Ç»Ç¢êîílÇ≈Ç∑", "åxçê");

		return;
	}

	auto SkinMesh = ChPtr::SharedSafeCast<SkinMesh9>(MeshList[_MeshName]);

	if (SkinMesh == nullptr)
	{
		//ChSystem::ErrerMessage("ÉXÉLÉìÉÅÉbÉVÉÖÇ≈ÇÕÇ†ÇËÇ‹ÇπÇÒ", "åxçê");

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
		//ChSystem::ErrerMessage("ìoò^Ç≥ÇÍÇƒÇ¢Ç»Ç¢êîílÇ≈Ç∑", "åxçê");

		return;
	}

	auto SkinMesh = ChPtr::SharedSafeCast<SkinMesh9>(MeshList[_MeshName]);

	if (SkinMesh == nullptr)
	{
		//ChSystem::ErrerMessage("ÉXÉLÉìÉÅÉbÉVÉÖÇ≈ÇÕÇ†ÇËÇ‹ÇπÇÒ", "åxçê");

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
		//ChSystem::ErrerMessage("ç≈í·Ç≈Ç‡0ÇÊÇËëÂÇ´Ç¢êîílÇ™ïKóvÇ≈Ç∑", "åxçê");

		return;
	}

	if (MeshList.find(_MeshName) == MeshList.end())
	{
		//ChSystem::ErrerMessage("ìoò^Ç≥ÇÍÇƒÇ¢Ç»Ç¢êîílÇ≈Ç∑", "åxçê");

		return;
	}

	auto SkinMesh = ChPtr::SharedSafeCast<SkinMesh9>(MeshList[_MeshName]);

	if (SkinMesh == nullptr)
	{
		//ChSystem::ErrerMessage("ÉXÉLÉìÉÅÉbÉVÉÖÇ≈ÇÕÇ†ÇËÇ‹ÇπÇÒ", "åxçê");

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


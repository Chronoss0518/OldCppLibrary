
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

MeshFace9 MeshManager9::nFace;

std::vector<ChPtr::Shared<ChMaterial_9>> MeshManager9::nMaterial;

///////////////////////////////////////////////////////////////////////////////////////
//MeshManager9ÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void MeshManager9::Init(const LPDIRECT3DDEVICE9 _dev)
{
	device = _dev;
	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::Release()
{
	if (!meshList.empty())meshList.clear();
	if (!pathList.empty())pathList.clear();
	if (meshList.empty())return;
	meshList.clear();
	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::SetMesh(
	const std::string& _MeshName
	, const std::string& _DataName
	, const std::string& _UsePashName)
{

	if (meshList.find(_DataName) != meshList.end())return;

	if (_MeshName.length() <= 0)return;

	std::string tmpString;
	std::string tmpPathName = "./";
	if (pathList.find(_UsePashName) != pathList.end())
	{
		tmpPathName = *pathList[_UsePashName] + '/';
	}

	auto tmpMesh = Mesh9::MeshType(_MeshName);

	tmpMesh->CreateMesh(_MeshName, tmpPathName, device);

	if (tmpMesh->InsMesh() == nullptr)
	{
		//ChSystem::ErrerMessage("ÉÅÉbÉVÉÖÇ™ì«Ç›çûÇ‹ÇÍÇ‹ÇπÇÒÇ≈ÇµÇΩ","åxçê");

		tmpMesh = nullptr;
		return;
	}

	meshList[_DataName] = tmpMesh;

}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::SetSkinMesh(const std::string& _MeshName
	, const std::string& _DataName
	, const std::string& _UsePashName)
{

	if (meshList.find(_DataName) != meshList.end())return;

	if (_MeshName.length() <= 0)return;

	std::string tmpString;
	std::string tmpPathName = "./";
	if (pathList.find(_UsePashName) != pathList.end())
	{
		tmpPathName = *pathList[_UsePashName] + '/';
	}

	auto tmpMesh = Mesh9::SkinMeshType(_MeshName);

	tmpMesh->CreateMesh(_MeshName, tmpPathName, device);

	if (tmpMesh->InsMesh() == nullptr)
	{
		//ChSystem::ErrerMessage("ÉÅÉbÉVÉÖÇ™ì«Ç›çûÇ‹ÇÍÇ‹ÇπÇÒÇ≈ÇµÇΩ", "åxçê");

		return;
	}

	{
		auto tmpSkinMesh = ChPtr::SharedSafeCast<ChMesh::SkinMesh9>(tmpMesh);

		if (tmpSkinMesh->boneList.size() <= 0)
		{
			//ChSystem::ErrerMessage("ÉXÉLÉìÉÅÉbÉVÉÖÇ≈ÇÕÇ†ÇËÇ‹ÇπÇÒ", "åxçê");

			tmpMesh->Release();
			return;
		}
	}


	meshList[_DataName] = tmpMesh;

}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::SetDirectoryPath(const std::string& _DirectoryPath
	, const std::string& _UseDirectoryPashName)
{
	if (pathList.find(_UseDirectoryPashName) != pathList.end())return;
	if (_DirectoryPath.length() <= 0)return;

	pathList.insert(std::pair<std::string, ChPtr::Shared<std::string>>(_UseDirectoryPashName, ChPtr::Make_S<std::string>()));
	*pathList[_UseDirectoryPashName] = _DirectoryPath;
}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::SetTexture(
	const std::string& _DataName
	, const unsigned long _TexNum
	, const ChPtr::Shared<ChTex::Texture9> _Tex)
{
	if (_Tex == nullptr)return;
	if (meshList.find(_DataName) == meshList.end())return;

	if (meshList[_DataName]->InsTex().size() <= _TexNum)return;

	meshList[_DataName]->InsTex()[_TexNum] = nullptr;

	meshList[_DataName]->InsTex()[_TexNum] = _Tex;

}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::SetAnimation(
	const std::string& _MeshName
	, const std::string& _AniamtionName
	, const std::string& _XFileName)
{
	if (meshList.find(_MeshName) == meshList.end())
	{
		//ChSystem::ErrerMessage("ìoò^Ç≥ÇÍÇƒÇ¢Ç»Ç¢êîílÇ≈Ç∑", "åxçê");

		return;
	}

	auto SkinMesh = ChPtr::SharedSafeCast<SkinMesh9>(meshList[_MeshName]);

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

	if (meshList.find(_MeshName) == meshList.end())
	{
		//ChSystem::ErrerMessage("ìoò^Ç≥ÇÍÇƒÇ¢Ç»Ç¢êîílÇ≈Ç∑", "åxçê");

		return;
	}

	auto SkinMesh = ChPtr::SharedSafeCast<SkinMesh9>(meshList[_MeshName]);

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

	if (meshList.find(_MeshName) == meshList.end())
	{
		//ChSystem::ErrerMessage("ìoò^Ç≥ÇÍÇƒÇ¢Ç»Ç¢êîílÇ≈Ç∑", "åxçê");

		return;
	}

	auto SkinMesh = ChPtr::SharedSafeCast<SkinMesh9>(meshList[_MeshName]);

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
	if (meshList.empty())return;

	if (meshList.find(_DataName) == meshList.end()) return;

	meshList.erase(_DataName);

	return;

}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::DrawMesh(
	const ChMat_9& _Mat
	, const std::string& _DataName
	, const long _SubNum)
{

	if (meshList.find(_DataName) == meshList.end())return;
	meshList[_DataName]->SetSkin();
	meshList[_DataName]->Draw(_Mat, device, _SubNum);

}

///////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<ChMaterial_9>>& MeshManager9::GetMeshMaterials(
	const std::string& _DataName)
{

	if (meshList.empty())return nMaterial;
	if (meshList.find(_DataName) == meshList.end())return nMaterial;
	return meshList[_DataName]->InsMaterials();
}

///////////////////////////////////////////////////////////////////////////////////

MeshFace9 MeshManager9::GetEasyFace(
	const std::string& _DataName
	, const unsigned long _FaseNum)
{
	MeshFace9 face;

	if (meshList.find(_DataName) == meshList.end())return nFace;
	if (meshList[_DataName]->InsFace().size() <= _FaseNum)return nFace;
	face = *meshList[_DataName]->InsFace()[_FaseNum];
	return face;
}

///////////////////////////////////////////////////////////////////////////////////

void MeshManager9::CreateEasyFace(
	const std::string& _DataName
	, const unsigned short _BaseMatNum)
{

	if (meshList.find(_DataName) == meshList.end())return;

	meshList[_DataName]->CreateEasyFaceList();
}



#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"

#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChAnimationObject/ChAnimationObject9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"../ChMesh/ChBaseMesh9.h"
#include"../ChMesh/ChSkinMesh9.h"
#include"ChMeshList9.h"

using namespace ChMesh;

MeshFace9 MeshList9::nFace;

std::vector<ChPtr::Shared<ChMaterial_9>> MeshList9::nMaterial;

///////////////////////////////////////////////////////////////////////////////////////
//ChMeshListメソッド
///////////////////////////////////////////////////////////////////////////////////////

MeshList9::~MeshList9()
{
	Release();
}

///////////////////////////////////////////////////////////////////////////////////

void MeshList9::SetMesh(
	const std::string& _meshName
	, const ChStd::DataNo _dataNum)
{
	if (meshList.find(_dataNum) != meshList.end())return;

	if (_meshName.length() <= 0)return;

	std::string tmpString = _meshName;
	std::string tmpPathName = "./";
	if (directoryPath.length() > 0)
	{
		tmpPathName = directoryPath + '/';
	}

	auto tmpMesh = Mesh9::MeshType(_meshName);

	tmpMesh->CreateMesh(_meshName, tmpPathName, device);

	if (tmpMesh->mesh == nullptr)
	{

			//ChSystem::ErrerMessage("メッシュが読み込まれませんでした", "警告");

		return;
	}


	meshList[_dataNum] = tmpMesh;

}

///////////////////////////////////////////////////////////////////////////////////

void MeshList9::SetSkinMesh(
	const std::string& _meshName
	, const ChStd::DataNo _dataNum)
{

	if (meshList.find(_dataNum) != meshList.end())return;

	if (_meshName.length() <= 0)return;

	std::string tmpString = _meshName;
	std::string tmpPathName = "./";
	if (directoryPath.length() > 0)
	{
		tmpPathName = directoryPath + '/';
	}

	auto tmpMesh = Mesh9::SkinMeshType(_meshName);

	tmpMesh->CreateMesh(_meshName, tmpPathName, device);

	if (tmpMesh->InsMesh() == nullptr)
	{

			//ChSystem::ErrerMessage("メッシュが読み込まれませんでした", "警告");

		return;
	}

	{
		auto tmpSkinMesh = ChPtr::SharedSafeCast<ChMesh::SkinMesh9>(tmpMesh);

		if (tmpSkinMesh->boneList.size() <= 0)
		{
			//ChSystem::ErrerMessage("スキンメッシュではありません", "警告");

			tmpMesh->Release();
			return;
		}
	}
	meshList[_dataNum] = tmpMesh;

}

///////////////////////////////////////////////////////////////////////////////////

void ChMeshList9::SetTexture(
	const ChStd::DataNo _dataNum
	, const unsigned long _texNum
	, const ChPtr::Shared<ChTex::Texture9> _tex)
{
	if (_tex == nullptr)return;
	if (meshList.size() <= _dataNum)return;

	if (meshList[_dataNum]->InsTex().size() <= _texNum)return;

	meshList[_dataNum]->InsTex()[_texNum] = nullptr;

	meshList[_dataNum]->InsTex()[_texNum] = _tex;

}

///////////////////////////////////////////////////////////////////////////////////

void ChMeshList9::SetAnimation(
	const ChStd::DataNo _dataNum
	, const std::string& _aniamtionName
	, const std::string& _xFileName)
{
	if (_dataNum >= meshList.size())
	{
		//ChSystem::ErrerMessage("登録されていない数値です", "警告");

		return;
	}

	auto skinMesh = ChPtr::SharedSafeCast<SkinMesh9>(meshList[_dataNum]);

	if (skinMesh == nullptr)
	{
		//ChSystem::ErrerMessage("スキンメッシュではありません", "警告");

		return;
	}

	skinMesh->SetAnimation(_aniamtionName, _xFileName);

}

///////////////////////////////////////////////////////////////////////////////////

void ChMeshList9::SetAnimation(
	const ChStd::DataNo _dataNum
	, const std::string& _aniamtionName
	, const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _animes)
{

	if (_dataNum >= meshList.size())
	{
		//ChSystem::ErrerMessage("登録されていない数値です", "警告");

		return;
	}

	auto skinMesh = ChPtr::SharedSafeCast<SkinMesh9>(meshList[_dataNum]);

	if (skinMesh == nullptr)
	{
		//ChSystem::ErrerMessage("スキンメッシュではありません", "警告");

		return;
	}

	skinMesh->SetAnimation(_aniamtionName, _animes);

}

///////////////////////////////////////////////////////////////////////////////////

void ChMeshList9::DrawMesh(
	const ChMat_9&_Mat
	, const ChStd::DataNo _dataNum
	, const long _subNum)
{

	if (meshList.size() <= _dataNum) return;

	meshList[_dataNum]->Draw(_Mat, device, _subNum);


}

///////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<ChMaterial_9>>& ChMeshList9::GetMeshMaterials(
	const ChStd::DataNo _dataNum)
{
	static std::vector<ChPtr::Shared<ChMaterial_9>> tmpMateList;

	if (meshList.empty())return nMaterial;
	if (meshList.size() <= _dataNum)return nMaterial;
	return meshList[_dataNum]->InsMaterials();
}

///////////////////////////////////////////////////////////////////////////////////

MeshFace9 ChMeshList9::GetEasyFace(
	const ChStd::DataNo _dataNum
	, const unsigned long _faceNum)
{
	MeshFace9 face;

	if (meshList.size() <= _dataNum)return nFace;

	if (meshList[_dataNum]->InsFace().size() <= _faceNum)return nFace;

	face = *meshList[_dataNum]->InsFace()[_faceNum];

	return face;

}

///////////////////////////////////////////////////////////////////////////////////

void ChMeshList9::CreateEasyFace(
	const ChStd::DataNo _dataNum
	, const unsigned short _BaseMatNum)
{

	if (meshList.size() <= _dataNum)return;

	meshList[_dataNum]->CreateEasyFaceList();
}

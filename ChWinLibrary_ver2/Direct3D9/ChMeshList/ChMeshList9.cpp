
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

MeshFace9 MeshList9::NFase;

std::vector<ChPtr::Shared<ChMaterial_9>> MeshList9::NMaterial;

///////////////////////////////////////////////////////////////////////////////////////
//ChMeshListメソッド
///////////////////////////////////////////////////////////////////////////////////////

MeshList9::~MeshList9()
{
	Release();
}

///////////////////////////////////////////////////////////////////////////////////

void MeshList9::SetMesh(
	const std::string& _MeshName
	, const ChStd::DataNo _DataNum)
{
	if (MeshList.find(_DataNum) != MeshList.end())return;

	if (_MeshName.length() <= 0)return;

	std::string TmpString = _MeshName;
	std::string TmpPathName = "./";
	if (DirectoryPath.length() > 0)
	{
		TmpPathName = DirectoryPath + '/';
	}

	auto TmpMesh = Mesh9::MeshType(_MeshName);

	TmpMesh->CreateMesh(_MeshName, TmpPathName, Device);

	if (TmpMesh->Mesh == nullptr)
	{

			//ChSystem::ErrerMessage("メッシュが読み込まれませんでした", "警告");

		return;
	}


	MeshList[_DataNum] = TmpMesh;

}

///////////////////////////////////////////////////////////////////////////////////

void MeshList9::SetSkinMesh(
	const std::string& _MeshName
	, const ChStd::DataNo _DataNum)
{

	if (MeshList.find(_DataNum) != MeshList.end())return;

	if (_MeshName.length() <= 0)return;

	std::string TmpString = _MeshName;
	std::string TmpPathName = "./";
	if (DirectoryPath.length() > 0)
	{
		TmpPathName = DirectoryPath + '/';
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
	MeshList[_DataNum] = TmpMesh;

}

///////////////////////////////////////////////////////////////////////////////////

void ChMeshList9::SetTexture(
	const ChStd::DataNo _DataNum
	, const unsigned long _TexNum
	, const ChPtr::Shared<ChTex::Texture9> _Tex)
{
	if (_Tex == nullptr)return;
	if (MeshList.size() <= _DataNum)return;

	if (MeshList[_DataNum]->InsTex().size() <= _TexNum)return;

	MeshList[_DataNum]->InsTex()[_TexNum] = nullptr;

	MeshList[_DataNum]->InsTex()[_TexNum] = _Tex;

}

///////////////////////////////////////////////////////////////////////////////////

void ChMeshList9::SetAnimation(
	const ChStd::DataNo _DataNum
	, const std::string& _AniamtionName
	, const std::string& _XFileName)
{
	if (_DataNum >= MeshList.size())
	{
		//ChSystem::ErrerMessage("登録されていない数値です", "警告");

		return;
	}

	auto SkinMesh = ChPtr::SharedSafeCast<SkinMesh9>(MeshList[_DataNum]);

	if (SkinMesh == nullptr)
	{
		//ChSystem::ErrerMessage("スキンメッシュではありません", "警告");

		return;
	}

	SkinMesh->SetAnimation(_AniamtionName, _XFileName);

}

///////////////////////////////////////////////////////////////////////////////////

void ChMeshList9::SetAnimation(
	const ChStd::DataNo _DataNum
	, const std::string& _AniamtionName
	, const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _Animes)
{

	if (_DataNum >= MeshList.size())
	{
		//ChSystem::ErrerMessage("登録されていない数値です", "警告");

		return;
	}

	auto SkinMesh = ChPtr::SharedSafeCast<SkinMesh9>(MeshList[_DataNum]);

	if (SkinMesh == nullptr)
	{
		//ChSystem::ErrerMessage("スキンメッシュではありません", "警告");

		return;
	}

	SkinMesh->SetAnimation(_AniamtionName, _Animes);

}

///////////////////////////////////////////////////////////////////////////////////

void ChMeshList9::DrawMesh(
	const ChMat_9&_Mat
	, const ChStd::DataNo _DataNum
	, const long _SubNum)
{

	if (MeshList.size() <= _DataNum) return;

	MeshList[_DataNum]->Draw(_Mat, Device, _SubNum);


}

///////////////////////////////////////////////////////////////////////////////////

std::vector<ChPtr::Shared<ChMaterial_9>>& ChMeshList9::GetMeshMaterials(
	const ChStd::DataNo _DataNum)
{
	static std::vector<ChPtr::Shared<ChMaterial_9>> TmpMateList;

	if (MeshList.empty())return NMaterial;
	if (MeshList.size() <= _DataNum)return NMaterial;
	return MeshList[_DataNum]->InsMaterials();
}

///////////////////////////////////////////////////////////////////////////////////

MeshFace9 ChMeshList9::GetEasyFace(
	const ChStd::DataNo _DataNum
	, const unsigned long _FaseNum)
{
	MeshFace9 Face;

	if (MeshList.size() <= _DataNum)return NFase;

	if (MeshList[_DataNum]->InsFace().size() <= _FaseNum)return NFase;

	Face = *MeshList[_DataNum]->InsFace()[_FaseNum];

	return Face;

}

///////////////////////////////////////////////////////////////////////////////////

void ChMeshList9::CreateEasyFace(
	const ChStd::DataNo _DataNum
	, const unsigned short _BaseMatNum)
{

	if (MeshList.size() <= _DataNum)return;

	MeshList[_DataNum]->CreateEasyFaceList();
}

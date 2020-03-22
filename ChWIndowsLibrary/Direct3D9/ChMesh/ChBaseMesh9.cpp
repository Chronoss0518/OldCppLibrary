
#include<Windows.h>
#include"../../ChInclude/ChGameBI.h"

#include"../../CPP/ChBitBool/ChBitBool.h"

#include"../../ChInclude/ChD3D9I.h"

#include"../ChAnimationObject/ChAnimationObject9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"ChBaseMesh9.h"
#include"MeshIncluder9.h"
#include"../ChFont/ChFont9.h"

using namespace ChTex;
using namespace ChMesh;

///////////////////////////////////////////////////////////////////////////////////////
//ChBaseMesh9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void BaseMesh9::Release() {

	if (ChPtr::NullCheck(Mesh))return;

	if (!Material.empty())Material.clear();

	if (!TexList.empty())TexList.clear();
	if (!NormalTex.empty())NormalTex.clear();
	if (!EasyFaceList.empty())EasyFaceList.clear();

	Mesh->Release();

	Mesh = nullptr;

}

///////////////////////////////////////////////////////////////////////////////////

void BaseMesh9::CreateEasyFaceList()
{

	MeshVertex9* MeshData;

	WORD *p;

	Mesh->LockIndexBuffer(0, (LPVOID*)&p);
	Mesh->LockVertexBuffer(0, (LPVOID*)&MeshData);

	for (unsigned long FaseNum = 0
		; FaseNum < Mesh->GetNumFaces()
		; FaseNum++)
	{

		auto MeshFace = ChPtr::Make_S<MeshFace9>();

		for (unsigned char i = 0; i < 3; i++)
		{
			MeshFace->VertexNum[i] = (*(p + FaseNum * 3 + i));
		}

		MeshFace->Normal = (MeshData + MeshFace->VertexNum[0])->Normal;
		for (unsigned char i = 1; i < 3; i++)
		{
			MeshFace->Normal += (MeshData + MeshFace->VertexNum[i])->Normal;
		}

		MeshFace->Normal.Normalize();

		MeshFace->CenterPos = *OffsetVertexList[MeshFace->VertexNum[0]];

		for (unsigned char i = 1; i < 3; i++)
		{
			MeshFace->CenterPos += *OffsetVertexList[MeshFace->VertexNum[i]];

		}

		MeshFace->CenterPos /= 3.0f;

		EasyFaceList.push_back(MeshFace);

	}

	Mesh->UnlockIndexBuffer();
	Mesh->UnlockVertexBuffer();

}

///////////////////////////////////////////////////////////////////////////////////

void BaseMesh9::SetMaterialName(const std::string& _FileName)
{

	ChFIO::File File;
	File.FileOpen(_FileName);

	std::string TmpStr = File.FileRead();

	std::string TmpMateName = "Material ";

	size_t Size = 0;

	unsigned int i = 0;
	while ((Size = TmpStr.find(TmpMateName, Size)) != std::string::npos)
	{
		Size += TmpMateName.length();
		size_t TmpNum = TmpStr.find("{", Size);
		if (TmpNum == std::string::npos)break;
		TmpNum -= (Size + 1);
		Material[i]->Name = TmpStr.substr(Size, TmpNum);
		Size += TmpNum;
		i++;

	}

}

///////////////////////////////////////////////////////////////////////////////////

void BaseMesh9::CreateMesh(
	const std::string& _FileName
	, const std::string& _PathName
	, const LPDIRECT3DDEVICE9& _Dev)
{
	OpenFile(_FileName, _PathName, _Dev);

	SetOffsetVertex();

}

///////////////////////////////////////////////////////////////////////////////////

void BaseMesh9::Draw(
	const ChMat_9& _Mat
	, const LPDIRECT3DDEVICE9& _Dev
	, const long _SubNum)
{

	D3DMATERIAL9 TmpMate;
	ChMat_9 TmpMat;

	if (_SubNum < 0 || _SubNum >= (long)Material.size())
	{

		for (unsigned short i = 0; i < Material.size(); i++) {
			TmpMate = *Material[i];

			//頂点情報の整理//
			_Dev->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
			_Dev->SetMaterial(&TmpMate);
			_Dev->SetTexture(0, TexList[i]->GetTex());

			TmpMat = Material[i]->Mat * _Mat;
			_Dev->SetTransform(D3DTS_WORLD, &TmpMat);
			_Dev->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

			Mesh->DrawSubset(i);
		}
		return;
	}

	TmpMate = *Material[_SubNum];

	_Dev->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	_Dev->SetMaterial(&TmpMate);
	_Dev->SetTexture(0, TexList[_SubNum]->GetTex());

	TmpMat = Material[_SubNum]->Mat * _Mat;
	_Dev->SetTransform(D3DTS_WORLD, &TmpMat);
	_Dev->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	Mesh->DrawSubset(_SubNum);

}

///////////////////////////////////////////////////////////////////////////////////

void BaseMesh9::SetOffsetVertex()
{
	if (ChPtr::NullCheck(Mesh))return;

	MeshVertex9 *TmpVer = nullptr;
	Mesh->LockVertexBuffer(NULL, (LPVOID*)&TmpVer);

	if (ChPtr::NullCheck(TmpVer))return;

	for (unsigned long Ver = 0; Ver < Mesh->GetNumVertices(); Ver++)
	{
		auto TmpPos = ChPtr::Make_S<ChVec3_9>();

		*TmpPos = (TmpVer + Ver)->Pos;

OffsetVertexList.push_back(TmpPos);
	}


	Mesh->UnlockVertexBuffer();
	return;
}

///////////////////////////////////////////////////////////////////////////////////

ChPtr::Shared<BaseMesh9> BaseMesh9::MeshType(
	const std::string& _FileName)
{
	std::string TmpStr;
	{
		size_t TmpNum = _FileName.rfind(".");
		if (TmpNum == _FileName.npos)return ChPtr::Make_S<BaseMesh9>();
		TmpStr = &_FileName[TmpNum];
	}

	if (TmpStr.find(".x") != TmpStr.npos)
	{
		return ChPtr::Make_S<XFileMesh9>();
	}

	return ChPtr::Make_S<BaseMesh9>();

}

///////////////////////////////////////////////////////////////////////////////////

ChPtr::Shared<BaseMesh9> BaseMesh9::SkinMeshType(
	const std::string& _FileName)
{

	std::string TmpStr;
	{
		size_t TmpNum = _FileName.rfind(".");
		if (TmpNum == _FileName.npos)return ChPtr::Make_S<SkinMesh9>();
		TmpStr = &_FileName[TmpNum];
	}

	if (TmpStr.find(".x") != TmpStr.npos)
	{
		return ChPtr::Make_S<SXFileMesh9>();
	}

	return ChPtr::Make_S<SkinMesh9>();

}

///////////////////////////////////////////////////////////////////////////////////////
//ChXFileMesh9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void XFileMesh9::OpenFile(
	const std::string& _FileName
	, const std::string& _PathName
	, const LPDIRECT3DDEVICE9& _Dev)
{

	if (_FileName.rfind(".x") == std::string::npos)return;

	std::string TmpStr;
	TmpStr = _PathName + "/" + _FileName;

	if (_PathName.length() <= 0)TmpStr = "." + TmpStr;


	{

		LPD3DXBUFFER TmpBuffer;

		DWORD NumMaterial;

		D3DXLoadMeshFromX(
			TmpStr.c_str()
			, D3DXMESH_MANAGED
			, _Dev
			, NULL
			, &TmpBuffer
			, NULL
			, &(NumMaterial)
			, &(Mesh));

		if (ChPtr::NullCheck(Mesh))return;

		D3DXMATERIAL* D3DXMat = (D3DXMATERIAL*)TmpBuffer->GetBufferPointer();
		std::string TmpString;

		for (DWORD i = 0; i < NumMaterial; i++) {


			auto TmpMat = ChPtr::Make_S<ChMaterial_9>();
			*TmpMat = (D3DXMat + i)->MatD3D;

			TmpMat->Specular = TmpMat->Diffuse;

			TmpString = "";

			if (ChPtr::NotNullCheck((D3DXMat + i)->pTextureFilename))
			{
				TmpString = &(D3DXMat + i)->pTextureFilename[0];
				TmpString = _PathName + "/" + TmpString;
				if (_PathName.length() <= 0)TmpString = "." + TmpString;

			}
			Material.push_back(TmpMat);

			auto TmpTex = BaseTexture9::TextureType(TmpString.c_str());

			TmpTex->CreateTexture(TmpString.c_str(), _Dev);

			if (ChPtr::NullCheck(TmpTex->GetTex())) {

				TmpTex->CreateColTexture(_Dev);

			}

			TexList.push_back(TmpTex);

		}

		TmpBuffer->Release();
	}

	{

		LPD3DXMESH TmpMesh = nullptr;
		HRESULT Res;
		Res = Mesh->CloneMeshFVF(
			D3DXMESH_MANAGED |
			D3DXMESH_NPATCHES,
			D3DFVF_XYZ |//座標
			D3DFVF_NORMAL |//法線
			D3DFVF_TEX1//テクスチャ座標
			, _Dev, &TmpMesh//クローン先
		);

		Mesh->Release();

		Mesh = TmpMesh;
	}

	SetMaterialName(TmpStr);

}

///////////////////////////////////////////////////////////////////////////////////////
//ChSkinMesh9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void SkinMesh9::SetAnimation(
	const std::string& _AniamtionName
	, const std::string& _XFileName)
{
	BoneAnimation TmpAni;


	TmpAni = ChANiSupport().CreateKeyFrame(_XFileName);

	size_t AniNum = 0;
	for (auto&& Bones : BoneList)
	{
		if (TmpAni.find(Bones.first) == TmpAni.end())continue;
		AniNum = TmpAni[Bones.first]->GetAniCnt();
		break;
	}

	for (auto&& Bones : BoneList)
	{
		if (TmpAni.find(Bones.first) != TmpAni.end())continue;
		auto Ani = ChPtr::Make_S<ChAnimationObject9>();

		for (size_t i = 0; i < AniNum; i++)
		{
			Ani->SetAniObject(ChMat_9());
		}
		TmpAni[Bones.first] = Ani;

	}


	if (TmpAni.size() < BoneList.size())return;

	Animations[_AniamtionName] = TmpAni;

	if (StartPlayAniCheck)return;
	StartPlayAniCheck = true;
	NowPlayAniName = _AniamtionName;

	for (auto&& Ani : Animations[NowPlayAniName])
	{
		Ani.second->Play();
	}


}

///////////////////////////////////////////////////////////////////////////////////////

void SkinMesh9::SetSkin()
{
	if (ChPtr::NullCheck(Mesh))return;
	if (Animations.size() <= 0)return;
	if (BoneList.size() <= 0)return;

	MeshVertex9 *TmpVer = nullptr;
	Mesh->LockVertexBuffer(NULL, (LPVOID*)&TmpVer);

	if (ChPtr::NullCheck(TmpVer))return;

	//BoneUpdate//
	for (auto&& BoneName : BoneNameList)
	{
		ChMat_9 TmpMat = BoneList[BoneName]->OffMat;

		BoneList[BoneName]->UpdateMat = Animations[NowPlayAniName][BoneName]->Update();


	}

	//LastUpdateBone//

	for (unsigned long i = BoneNameList.size() - 1; i + 1 > 0; i--)
	{

		ChMat_9 TmpMat = BoneList[BoneNameList[i]]->OffMat;

		if (BoneList[BoneNameList[i]]->OffsetBone == nullptr)
		{

			BoneList[BoneNameList[i]]->UpdateMat
				= TmpMat * BoneList[BoneNameList[i]]->UpdateMat;

			continue;
		}

		BoneList[BoneNameList[i]]->UpdateMat
			= TmpMat
			* BoneList[BoneNameList[i]]->UpdateMat
			* BoneList[BoneNameList[i]]->OffsetBone->UpdateMat;

	}

	//UpdateVertex//
	for (unsigned long Ver = 0; Ver < Mesh->GetNumVertices(); Ver++)
	{
		ChMat_9 TmpMat;
		TmpMat.Clear0();
		ChVec3_9 TmpVec;

		TmpVec = *OffsetVertexList[Ver];

		for (auto&& Bones : BoneVertexList[Ver]->UpdateMat)
		{

			if (Bones->WaitPow <= 0.0f)continue;

			ChMat_9 Tmp;
			Tmp = (*Bones->UpdateMat
				* Bones->WaitPow);

			TmpMat += Tmp;

		}



		TmpVec.MatPos(TmpMat, TmpVec);

		(TmpVer + Ver)->Pos = TmpVec;
	}



	Mesh->UnlockVertexBuffer();

}

///////////////////////////////////////////////////////////////////////////////////////
//ChSXFileMesh9メソッド
///////////////////////////////////////////////////////////////////////////////////////

const std::string SXFileMesh9::FreamMat = "FrameTransformMatrix {";

const std::string SXFileMesh9::SkinWaights = "SkinWeights {";

void SXFileMesh9::OpenFile(
	const std::string& _FileName
	, const std::string& _PathName
	, const LPDIRECT3DDEVICE9& _Dev)
{

	if (_FileName.rfind(".x") == std::string::npos)return;

	std::string TmpStr;
	TmpStr = _PathName + "/" + _FileName;

	if (_PathName.length() <= 0)TmpStr = "." + TmpStr;



	{

		LPD3DXBUFFER TmpBuffer;

		DWORD NumMaterial;

		D3DXLoadMeshFromX(
			TmpStr.c_str()
			, D3DXMESH_MANAGED
			, _Dev
			, NULL
			, &TmpBuffer
			, NULL
			, &(NumMaterial)
			, &(Mesh));

		if (ChPtr::NullCheck(Mesh))return;

		D3DXMATERIAL* D3DXMat = (D3DXMATERIAL*)TmpBuffer->GetBufferPointer();
		std::string TmpString;

		for (DWORD i = 0; i < NumMaterial; i++) {


			auto TmpMat = ChPtr::Make_S<ChMaterial_9>();
			*TmpMat = (D3DXMat + i)->MatD3D;

			TmpMat->Specular = TmpMat->Diffuse;

			TmpString = "";
			if (ChPtr::NotNullCheck((D3DXMat + i)->pTextureFilename))
			{
				TmpString = &(D3DXMat + i)->pTextureFilename[0];
				TmpString = _PathName + TmpString;
			}
			Material.push_back(TmpMat);

			auto TmpTex = BaseTexture9::TextureType(TmpString.c_str());

			TmpTex->CreateTexture(TmpString.c_str(), _Dev);

			if (ChPtr::NullCheck(TmpTex->GetTex())) {

				TmpTex->CreateColTexture(_Dev);

			}

			TexList.push_back(TmpTex);

		}

		TmpBuffer->Release();
	}

	{

		LPD3DXMESH TmpMesh = nullptr;

		HRESULT Res;
		Res = Mesh->CloneMeshFVF(
			D3DXMESH_MANAGED |
			D3DXMESH_NPATCHES,
			D3DFVF_XYZ |//座標
			D3DFVF_NORMAL |//法線
			D3DFVF_TEX1//テクスチャ座標
			, _Dev, &TmpMesh//クローン先
		);


		Mesh->Release();

		Mesh = TmpMesh;
	}

	if (ChPtr::NullCheck(Mesh))return;

	SetMaterialName(TmpStr);

	SetOffsetVertex();

	{

		std::string FStr;
		{

			ChFIO::File File;
			File.FileOpen(_PathName + _FileName);
			FStr = File.FileRead();
			File.FileClose();

		}
		SetBone(FStr);

		if (TestName.size() <= 0)return;
	}
	TestName.clear();

}

///////////////////////////////////////////////////////////////////////////////////

void SXFileMesh9::SetBone(const std::string& _FStr)
{

	{

		if (_FStr.find("Frame ") == std::string::npos)return;

		size_t FPos = _FStr.find("Frame ");

		CreateBoneTree(_FStr, FPos);

	}

	SetBoneVertex(_FStr);

	for (auto&& BoneName : BoneNameList)
	{
/*
		ChMat_9 TmpMat;

		TmpMat = BoneList[BoneName]->BaseMat;

		BoneList[BoneName]->BaseMat
			= TmpMat * BoneList[BoneName]->OffsetBone->BaseMat;
*/
		


		if (BoneList[BoneName]->OffsetBone == nullptr)continue;

/*
		ChMat_9 TmpMat;

		TmpMat = BoneList[BoneName]->OffMat;

		TmpMat.Inverse();

		BoneList[BoneName]->OffMat
			=  TmpMat * BoneList[BoneName]->OffsetBone->OffMat;
*/
	}


}

///////////////////////////////////////////////////////////////////////////////////

void SXFileMesh9::SetBoneVertex(const std::string& _FStr)
{
	std::string End = ";";
	size_t FPos = 0;
	if (_FStr.find("template SkinWeights {", FPos) != std::string::npos)
	{
		FPos = _FStr.find("template SkinWeights {", FPos);
		FPos += std::strlen("template SkinWeights {");
	}

	{

		std::string BoneName;

		while (_FStr.find(SkinWaights, FPos) != std::string::npos)
		{

			FPos = _FStr.find(SkinWaights, FPos);
			FPos = _FStr.find("\"", FPos);
			BoneName = _FStr.substr(FPos + 1, _FStr.find("\";", FPos) - FPos - 1);

			if (TestName == BoneName)break;
			if(TestName.size() <= 0)TestName = BoneName;
			

			FPos = _FStr.find("\";", FPos);
			FPos += 2;
			FPos = _FStr.find(";", FPos);
			FPos += 2;

			std::vector<unsigned long> TmpNum;

			while (1)
			{
				std::string Num = _FStr.substr(FPos, _FStr.find(",", FPos + 1) - FPos);
				auto Ver = ChPtr::Make_S<BoneVertex::BonePow>();
				auto VertexNo = std::atol(Num.c_str());
				TmpNum.push_back(VertexNo);
				Ver->UpdateMat = &BoneList[BoneName]->UpdateMat;
				Ver->OffMat = &BoneList[BoneName]->OffMat;
				BoneVertexList[VertexNo]->UpdateMat.push_back(Ver);
				if (_FStr.find(End, FPos) <= _FStr.find(",", FPos))break;
				FPos = _FStr.find(",", FPos + 1);
				FPos += 2;


			}
			FPos = _FStr.find(End, FPos);
			FPos += 2;


			for (auto&& VerNum : TmpNum)
			{
				std::string Num = _FStr.substr(FPos, _FStr.find(",", FPos + 1) - FPos);
				
				BoneVertexList[VerNum]->
					UpdateMat[BoneVertexList[VerNum]->
					UpdateMat.size() - 1]->
					WaitPow = (float)std::atof(Num.c_str());

				if (_FStr.find(End, FPos) <= _FStr.find(",", FPos))break;
				FPos = _FStr.find(",", FPos + 1);
				FPos += 2;


			}

			FPos = _FStr.find(End, FPos);
			FPos += 2;
			{
				ChMatrix TmpMat;
				TmpMat.Deserialize(_FStr, FPos);

				BoneList[BoneName]->OffMat = TmpMat;
			}

		}
	}



}

///////////////////////////////////////////////////////////////////////////////////

void SXFileMesh9::CreateBoneTree(
	const std::string& _FStr
	, size_t& _FPos
	, const ChPtr::Shared<Bone>& _Bone)
{
	_FPos += 6;
	size_t TmpPos = _FStr.find(" {", _FPos);

	if (BoneList.find(_FStr.substr(_FPos, TmpPos - _FPos)) != BoneList.end())return;

	auto TmpBone = ChPtr::Make_S<Bone>();
	TmpBone->OffsetBone = _Bone;

	std::string Test = _FStr.substr(_FPos, TmpPos - _FPos);
	BoneList[Test] = TmpBone;
	TmpBone->MyName = Test;
	BoneNameList.push_back(Test);

	_FPos = _FStr.find(FreamMat, _FPos);

	_FPos += FreamMat.length();

	{
		ChMatrix TmpMat;
		TmpMat.Deserialize(_FStr, _FPos);
		TmpBone->BaseMat = TmpMat;
	}

	_FPos = _FStr.find("}", _FPos);
	_FPos += 1;

	////メッシュ取得//
	//if (_FStr.find("Mesh {", _FPos) <= _FStr.find("}", _FPos))
	//{
	//	size_t Tmp = VertexNum;
	//	_FPos = _FStr.find("Mesh {", _FPos);
	//	_FPos = _FStr.find("\n", _FPos);
	//	_FPos += 1;
	//	std::string Num = _FStr.substr(_FPos, _FStr.find(";", _FPos) - _FPos);
	//	VertexNum += std::atol(Num.c_str());
	//}

	while (_FStr.find("}", _FPos) >= _FStr.find("Frame ", _FPos))
	{
		_FPos = _FStr.find("Frame ", _FPos);
		if (_FPos == std::string::npos)break;
		CreateBoneTree(_FStr, _FPos, TmpBone);

	}

	_FPos = _FStr.find("}", _FPos);
	_FPos += 1;
}

///////////////////////////////////////////////////////////////////////////////////

void SkinMesh9::SetOffsetVertex()
{
	if (ChPtr::NullCheck(Mesh))return;

	MeshVertex9 *TmpVer = nullptr;
	Mesh->LockVertexBuffer(NULL, (LPVOID*)&TmpVer);

	if (ChPtr::NullCheck(TmpVer))return;

	for (unsigned long Ver = 0; Ver < Mesh->GetNumVertices(); Ver++)
	{
		auto TmpPos = ChPtr::Make_S<ChVec3_9>();
		auto TmpVertex = ChPtr::Make_S<BoneVertex>();

		*TmpPos = (TmpVer + Ver)->Pos;

		TmpVertex->Pos = (TmpVer + Ver)->Pos;

		OffsetVertexList.push_back(TmpPos);

		BoneVertexList.push_back(TmpVertex);
	}


	Mesh->UnlockVertexBuffer();
	return;
}

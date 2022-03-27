
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"

#include"../../CPP/ChFile/ChFile.h"

#include"../../BaseIncluder/ChD3D9I.h"

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

	if (ChPtr::NullCheck(mesh))return;

	if (!material.empty())material.clear();

	if (!texList.empty())texList.clear();
	if (!normalTex.empty())normalTex.clear();
	if (!easyFaceList.empty())easyFaceList.clear();

	mesh->Release();

	mesh = nullptr;

}

///////////////////////////////////////////////////////////////////////////////////

void BaseMesh9::CreateEasyFaceList()
{

	MeshVertex9* meshData;

	WORD *p;

	mesh->LockIndexBuffer(0, (LPVOID*)&p);
	mesh->LockVertexBuffer(0, (LPVOID*)&meshData);

	for (unsigned long faceNum = 0
		; faceNum < mesh->GetNumFaces()
		; faceNum++)
	{

		auto meshFace = ChPtr::Make_S<MeshFace9>();

		for (unsigned char i = 0; i < 3; i++)
		{
			meshFace->vertexNum[i] = (*(p + faceNum * 3 + i));
		}

		meshFace->normal = (meshData + meshFace->vertexNum[0])->normal;
		for (unsigned char i = 1; i < 3; i++)
		{
			meshFace->normal += (meshData + meshFace->vertexNum[i])->normal;
		}

		meshFace->normal.Normalize();

		meshFace->centerPos = *offsetVertexList[meshFace->vertexNum[0]];

		for (unsigned char i = 1; i < 3; i++)
		{
			meshFace->centerPos += *offsetVertexList[meshFace->vertexNum[i]];

		}

		meshFace->centerPos /= 3.0f;

		easyFaceList.push_back(meshFace);

	}

	mesh->UnlockIndexBuffer();
	mesh->UnlockVertexBuffer();

}

///////////////////////////////////////////////////////////////////////////////////

void BaseMesh9::SetMaterialName(const std::string& _fileName)
{

	ChCpp::File<> file;
	file.FileOpen(_fileName);

	std::string tmpStr;
	tmpStr = file.FileReadText();

	std::string tmpMateName = "Material ";

	size_t size = 0;

	unsigned int i = 0;
	while ((size = tmpStr.find(tmpMateName, size)) != std::string::npos)
	{
		size += tmpMateName.length();
		size_t tmpNum = tmpStr.find("{", size);
		if (tmpNum == std::string::npos)break;
		tmpNum -= (size + 1);
		material[i]->name = tmpStr.substr(size, tmpNum);
		size += tmpNum;
		i++;

	}

}

///////////////////////////////////////////////////////////////////////////////////

void BaseMesh9::CreateMesh(
	const std::string& _fileName
	, const std::string& _pathName
	, const LPDIRECT3DDEVICE9& _dev)
{
	OpenFile(_fileName, _pathName, _dev);

	SetOffsetVertex();

}

///////////////////////////////////////////////////////////////////////////////////

void BaseMesh9::Draw(
	const ChMat_9& _mat
	, const LPDIRECT3DDEVICE9& _dev
	, const long _subNum)
{

	D3DMATERIAL9 tmpMate;
	ChMat_9 tmpMat;

	if (_subNum < 0 || _subNum >= (long)material.size())
	{

		for (unsigned short i = 0; i < material.size(); i++) {
			tmpMate = *material[i];

			//頂点情報の整理//
			_dev->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
			_dev->SetMaterial(&tmpMate);
			_dev->SetTexture(0, texList[i]->GetTex());

			tmpMat = material[i]->mat * _mat;
			_dev->SetTransform(D3DTS_WORLD, &tmpMat);
			_dev->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

			mesh->DrawSubset(i);
		}
		return;
	}

	tmpMate = *material[_subNum];

	_dev->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	_dev->SetMaterial(&tmpMate);
	_dev->SetTexture(0, texList[_subNum]->GetTex());

	tmpMat = material[_subNum]->mat * _mat;
	_dev->SetTransform(D3DTS_WORLD, &tmpMat);
	_dev->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	mesh->DrawSubset(_subNum);

}

///////////////////////////////////////////////////////////////////////////////////

void BaseMesh9::SetOffsetVertex()
{
	if (ChPtr::NullCheck(mesh))return;

	MeshVertex9 *tmpVer = nullptr;
	mesh->LockVertexBuffer(NULL, (LPVOID*)&tmpVer);

	if (ChPtr::NullCheck(tmpVer))return;

	for (unsigned long ver = 0; ver < mesh->GetNumVertices(); ver++)
	{
		auto tmpPos = ChPtr::Make_S<ChVec3_9>();

		*tmpPos = (tmpVer + ver)->pos;

offsetVertexList.push_back(tmpPos);
	}


	mesh->UnlockVertexBuffer();
	return;
}

///////////////////////////////////////////////////////////////////////////////////

ChPtr::Shared<BaseMesh9> BaseMesh9::MeshType(
	const std::string& _fileName)
{
	std::string tmpStr;
	{
		size_t tmpNum = _fileName.rfind(".");
		if (tmpNum == _fileName.npos)return ChPtr::Make_S<BaseMesh9>();
		tmpStr = &_fileName[tmpNum];
	}

	if (tmpStr.find(".x") != tmpStr.npos)
	{
		return ChPtr::Make_S<XFileMesh9>();
	}

	return ChPtr::Make_S<BaseMesh9>();

}

///////////////////////////////////////////////////////////////////////////////////

ChPtr::Shared<BaseMesh9> BaseMesh9::SkinMeshType(
	const std::string& _fileName)
{

	std::string tmpStr;
	{
		size_t tmpNum = _fileName.rfind(".");
		if (tmpNum == _fileName.npos)return ChPtr::Make_S<SkinMesh9>();
		tmpStr = &_fileName[tmpNum];
	}

	if (tmpStr.find(".x") != tmpStr.npos)
	{
		return ChPtr::Make_S<SXFileMesh9>();
	}

	return ChPtr::Make_S<SkinMesh9>();

}

///////////////////////////////////////////////////////////////////////////////////////
//ChXFileMesh9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void XFileMesh9::OpenFile(
	const std::string& _fileName
	, const std::string& _pathName
	, const LPDIRECT3DDEVICE9& _dev)
{

	if (_fileName.rfind(".x") == std::string::npos)return;

	std::string tmpStr;
	tmpStr = _pathName + "/" + _fileName;

	if (_pathName.length() <= 0)tmpStr = "." + tmpStr;


	{

		LPD3DXBUFFER tmpBuffer;

		DWORD numMaterial;

		D3DXLoadMeshFromX(
			tmpStr.c_str()
			, D3DXMESH_MANAGED
			, _dev
			, NULL
			, &tmpBuffer
			, NULL
			, &(numMaterial)
			, &(mesh));

		if (ChPtr::NullCheck(mesh))return;

		D3DXMATERIAL* D3DXMat = (D3DXMATERIAL*)tmpBuffer->GetBufferPointer();
		std::string tmpString;

		for (DWORD i = 0; i < numMaterial; i++) {


			auto tmpMat = ChPtr::Make_S<ChMaterial_9>();
			*tmpMat = (D3DXMat + i)->MatD3D;

			tmpMat->Specular = tmpMat->Diffuse;

			tmpString = "";

			if (ChPtr::NotNullCheck((D3DXMat + i)->pTextureFilename))
			{
				tmpString = &(D3DXMat + i)->pTextureFilename[0];
				tmpString = _pathName + "/" + tmpString;
				if (_pathName.length() <= 0)tmpString = "." + tmpString;

			}
			material.push_back(tmpMat);

			auto tmpTex = BaseTexture9::TextureType(tmpString.c_str());

			tmpTex->CreateTexture(tmpString.c_str(), _dev);

			if (ChPtr::NullCheck(tmpTex->GetTex())) {

				tmpTex->CreateColTexture(_dev);

			}

			texList.push_back(tmpTex);

		}

		tmpBuffer->Release();
	}

	{

		LPD3DXMESH tmpMesh = nullptr;
		HRESULT res;
		res = mesh->CloneMeshFVF(
			D3DXMESH_MANAGED |
			D3DXMESH_NPATCHES,
			D3DFVF_XYZ |//座標
			D3DFVF_NORMAL |//法線
			D3DFVF_TEX1//テクスチャ座標
			, _dev, &tmpMesh//クローン先
		);

		mesh->Release();

		mesh = tmpMesh;
	}

	SetMaterialName(tmpStr);

}

///////////////////////////////////////////////////////////////////////////////////////
//ChSkinMesh9メソッド
///////////////////////////////////////////////////////////////////////////////////////

void SkinMesh9::SetAnimation(
	const std::string& _animationName
	, const std::string& _XFileName)
{
	BoneAnimation tmpAni;


	tmpAni = ChANiSupport().CreateKeyFrame(_XFileName);

	size_t AniNum = 0;
	for (auto&& bones : boneList)
	{
		if (tmpAni.find(bones.first) == tmpAni.end())continue;
		AniNum = tmpAni[bones.first]->GetAniCnt();
		break;
	}

	for (auto&& bones : boneList)
	{
		if (tmpAni.find(bones.first) != tmpAni.end())continue;
		auto Ani = ChPtr::Make_S<ChAnimationObject9>();

		for (size_t i = 0; i < AniNum; i++)
		{
			Ani->SetAniObject(ChMat_9());
		}
		tmpAni[bones.first] = Ani;

	}


	if (tmpAni.size() < boneList.size())return;

	animations[_animationName] = tmpAni;

	if (startPlayAniCheck)return;
	startPlayAniCheck = true;
	nowPlayAniName = _animationName;

	for (auto&& Ani : animations[nowPlayAniName])
	{
		Ani.second->Play();
	}


}

///////////////////////////////////////////////////////////////////////////////////////

void SkinMesh9::SetSkin()
{
	if (ChPtr::NullCheck(mesh))return;
	if (animations.size() <= 0)return;
	if (boneList.size() <= 0)return;

	MeshVertex9 *tmpVer = nullptr;
	mesh->LockVertexBuffer(NULL, (LPVOID*)&tmpVer);

	if (ChPtr::NullCheck(tmpVer))return;

	//BoneUpdate//
	for (auto&& boneName : boneNameList)
	{
		ChMat_9 tmpMat = boneList[boneName]->offMat;

		boneList[boneName]->updateMat = animations[nowPlayAniName][boneName]->Update();


	}

	//LastUpdateBone//

	for (unsigned long i = boneNameList.size() - 1; i + 1 > 0; i--)
	{

		ChMat_9 tmpMat = boneList[boneNameList[i]]->offMat;

		if (boneList[boneNameList[i]]->offsetBone == nullptr)
		{

			boneList[boneNameList[i]]->updateMat
				= tmpMat * boneList[boneNameList[i]]->updateMat;

			continue;
		}

		boneList[boneNameList[i]]->updateMat
			= tmpMat
			* boneList[boneNameList[i]]->updateMat
			* boneList[boneNameList[i]]->offsetBone->updateMat;

	}

	//UpdateVertex//
	for (unsigned long ver = 0; ver < mesh->GetNumVertices(); ver++)
	{
		ChMat_9 tmpMat;
		tmpMat.Clear0();
		ChVec3_9 tmpVec;

		tmpVec = *offsetVertexList[ver];

		for (auto&& bones : boneVertexList[ver]->updateMat)
		{

			if (bones->waitPow <= 0.0f)continue;

			ChMat_9 tmp;
			tmp = (*bones->updateMat
				* bones->waitPow);

			tmpMat += tmp;

		}



		tmpVec.MatPos(tmpMat, tmpVec);

		(tmpVer + ver)->pos = tmpVec;
	}



	mesh->UnlockVertexBuffer();

}

///////////////////////////////////////////////////////////////////////////////////////
//ChSXFileMesh9メソッド
///////////////////////////////////////////////////////////////////////////////////////

const std::string SXFileMesh9::frameMat = "FrameTransformMatrix {";

const std::string SXFileMesh9::skinWaights = "SkinWeights {";

void SXFileMesh9::OpenFile(
	const std::string& _fileName
	, const std::string& _pathName
	, const LPDIRECT3DDEVICE9& _dev)
{

	if (_fileName.rfind(".x") == std::string::npos)return;

	std::string tmpStr;
	tmpStr = _pathName + "/" + _fileName;

	if (_pathName.length() <= 0)tmpStr = "." + tmpStr;



	{

		LPD3DXBUFFER tmpBuffer;

		DWORD numMaterial;

		D3DXLoadMeshFromX(
			tmpStr.c_str()
			, D3DXMESH_MANAGED
			, _dev
			, NULL
			, &tmpBuffer
			, NULL
			, &(numMaterial)
			, &(mesh));

		if (ChPtr::NullCheck(mesh))return;

		D3DXMATERIAL* D3DXMat = (D3DXMATERIAL*)tmpBuffer->GetBufferPointer();
		std::string tmpString;

		for (DWORD i = 0; i < numMaterial; i++) {


			auto tmpMat = ChPtr::Make_S<ChMaterial_9>();
			*tmpMat = (D3DXMat + i)->MatD3D;

			tmpMat->Specular = tmpMat->Diffuse;

			tmpString = "";
			if (ChPtr::NotNullCheck((D3DXMat + i)->pTextureFilename))
			{
				tmpString = &(D3DXMat + i)->pTextureFilename[0];
				tmpString = _pathName + tmpString;
			}
			material.push_back(tmpMat);

			auto tmpTex = BaseTexture9::TextureType(tmpString.c_str());

			tmpTex->CreateTexture(tmpString.c_str(), _dev);

			if (ChPtr::NullCheck(tmpTex->GetTex())) {

				tmpTex->CreateColTexture(_dev);

			}

			texList.push_back(tmpTex);

		}

		tmpBuffer->Release();
	}

	{

		LPD3DXMESH tmpMesh = nullptr;

		HRESULT res;
		res = mesh->CloneMeshFVF(
			D3DXMESH_MANAGED |
			D3DXMESH_NPATCHES,
			D3DFVF_XYZ |//座標
			D3DFVF_NORMAL |//法線
			D3DFVF_TEX1//テクスチャ座標
			, _dev, &tmpMesh//クローン先
		);


		mesh->Release();

		mesh = tmpMesh;
	}

	if (ChPtr::NullCheck(mesh))return;

	SetMaterialName(tmpStr);

	SetOffsetVertex();

	{

		std::string fStr;
		{

			ChCpp::File<> file;
			file.FileOpen(_pathName + _fileName);
			fStr = file.FileReadText();
			file.FileClose();

		}
		SetBone(fStr);

		if (testName.size() <= 0)return;
	}
	testName.clear();

}

///////////////////////////////////////////////////////////////////////////////////

void SXFileMesh9::SetBone(const std::string& _fStr)
{

	{

		if (_fStr.find("Frame ") == std::string::npos)return;

		size_t fPos = _fStr.find("Frame ");

		CreateBoneTree(_fStr, fPos);

	}

	SetBoneVertex(_fStr);

	for (auto&& boneName : boneNameList)
	{
/*
		ChMat_9 tmpMat;

		tmpMat = boneList[boneName]->baseMat;

		boneList[boneName]->baseMat
			= tmpMat * boneList[boneName]->offsetbone->baseMat;
*/
		


		if (boneList[boneName]->offsetBone == nullptr)continue;

/*
		ChMat_9 tmpMat;

		tmpMat = boneList[boneName]->offMat;

		tmpMat.Inverse();

		boneList[boneName]->offMat
			=  tmpMat * boneList[boneName]->offsetBone->offMat;
*/
	}


}

///////////////////////////////////////////////////////////////////////////////////

void SXFileMesh9::SetBoneVertex(const std::string& _fStr)
{
	std::string End = ";";
	size_t fPos = 0;
	if (_fStr.find("template SkinWeights {", fPos) != std::string::npos)
	{
		fPos = _fStr.find("template SkinWeights {", fPos);
		fPos += std::strlen("template SkinWeights {");
	}

	{

		std::string boneName;

		while (_fStr.find(skinWaights, fPos) != std::string::npos)
		{

			fPos = _fStr.find(skinWaights, fPos);
			fPos = _fStr.find("\"", fPos);
			boneName = _fStr.substr(fPos + 1, _fStr.find("\";", fPos) - fPos - 1);

			if (testName == boneName)break;
			if(testName.size() <= 0)testName = boneName;
			

			fPos = _fStr.find("\";", fPos);
			fPos += 2;
			fPos = _fStr.find(";", fPos);
			fPos += 2;

			std::vector<unsigned long> tmpNum;

			while (1)
			{
				std::string num = _fStr.substr(fPos, _fStr.find(",", fPos + 1) - fPos);
				auto ver = ChPtr::Make_S<BoneVertex::BonePow>();
				auto VertexNo = std::atol(num.c_str());
				tmpNum.push_back(VertexNo);
				ver->updateMat = &boneList[boneName]->updateMat;
				ver->offMat = &boneList[boneName]->offMat;
				boneVertexList[VertexNo]->updateMat.push_back(ver);
				if (_fStr.find(End, fPos) <= _fStr.find(",", fPos))break;
				fPos = _fStr.find(",", fPos + 1);
				fPos += 2;


			}
			fPos = _fStr.find(End, fPos);
			fPos += 2;


			for (auto&& VerNum : tmpNum)
			{
				std::string num = _fStr.substr(fPos, _fStr.find(",", fPos + 1) - fPos);
				
				boneVertexList[VerNum]->
					updateMat[boneVertexList[VerNum]->
					updateMat.size() - 1]->
					waitPow = (float)std::atof(num.c_str());

				if (_fStr.find(End, fPos) <= _fStr.find(",", fPos))break;
				fPos = _fStr.find(",", fPos + 1);
				fPos += 2;


			}

			fPos = _fStr.find(End, fPos);
			fPos += 2;
			{
				ChLMatrix tmpMat;
				tmpMat.Deserialize(_fStr, fPos);

				boneList[boneName]->offMat = tmpMat;
			}

		}
	}



}

///////////////////////////////////////////////////////////////////////////////////

void SXFileMesh9::CreateBoneTree(
	const std::string& _fStr
	, size_t& _fPos
	, const ChPtr::Shared<Bone>& _bone)
{
	_fPos += 6;
	size_t tmpPos = _fStr.find(" {", _fPos);

	if (boneList.find(_fStr.substr(_fPos, tmpPos - _fPos)) != boneList.end())return;

	auto tmpBone = ChPtr::Make_S<Bone>();
	tmpBone->offsetBone = _bone;

	std::string test = _fStr.substr(_fPos, tmpPos - _fPos);
	boneList[test] = tmpBone;
	tmpBone->myName = test;
	boneNameList.push_back(test);

	_fPos = _fStr.find(frameMat, _fPos);

	_fPos += frameMat.length();

	{
		ChLMatrix tmpMat;
		tmpMat.Deserialize(_fStr, _fPos);
		tmpBone->baseMat = tmpMat;
	}

	_fPos = _fStr.find("}", _fPos);
	_fPos += 1;

	////メッシュ取得//
	//if (_fStr.find("mesh {", _fPos) <= _fStr.find("}", _fPos))
	//{
	//	size_t tmp = vertexNum;
	//	_fPos = _fStr.find("mesh {", _fPos);
	//	_fPos = _fStr.find("\n", _fPos);
	//	_fPos += 1;
	//	std::string num = _fStr.substr(_fPos, _fStr.find(";", _fPos) - _fPos);
	//	vertexNum += std::atol(num.c_str());
	//}

	while (_fStr.find("}", _fPos) >= _fStr.find("Frame ", _fPos))
	{
		_fPos = _fStr.find("Frame ", _fPos);
		if (_fPos == std::string::npos)break;
		CreateBoneTree(_fStr, _fPos, tmpBone);

	}

	_fPos = _fStr.find("}", _fPos);
	_fPos += 1;
}

///////////////////////////////////////////////////////////////////////////////////

void SkinMesh9::SetOffsetVertex()
{
	if (ChPtr::NullCheck(mesh))return;

	MeshVertex9 *tmpVer = nullptr;
	mesh->LockVertexBuffer(NULL, (LPVOID*)&tmpVer);

	if (ChPtr::NullCheck(tmpVer))return;

	for (unsigned long ver = 0; ver < mesh->GetNumVertices(); ver++)
	{
		auto tmpPos = ChPtr::Make_S<ChVec3_9>();
		auto tmpVertex = ChPtr::Make_S<BoneVertex>();

		*tmpPos = (tmpVer + ver)->pos;

		tmpVertex->pos = (tmpVer + ver)->pos;

		offsetVertexList.push_back(tmpPos);

		boneVertexList.push_back(tmpVertex);
	}


	mesh->UnlockVertexBuffer();
	return;
}

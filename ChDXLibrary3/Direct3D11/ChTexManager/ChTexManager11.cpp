
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

#include"../ChTexture/ChBaseTexture9.h"
#include"ChTexManager9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////////
//ChTextureManager9ÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void TextureManager9::Init(LPDIRECT3DDEVICE9 _Dv)
{
	Device = _Dv;
}

///////////////////////////////////////////////////////////////////////////////////

void TextureManager9::Release()
{

	if (!TexList.empty()) {
		TexList.clear();
	}
	if (!PathList.empty())
	{
		PathList.clear();
	}

}

///////////////////////////////////////////////////////////////////////////////////

TextureManager9::~TextureManager9()
{
	Release();
}

///////////////////////////////////////////////////////////////////////////////////

void TextureManager9::SetTexture(
	const std::string& _TextureName
	, const std::string& _DataName
	, const std::string& _UsePathName
	, const unsigned int _GameReSizeWidth
	, const unsigned int _GameReSizeHeight
	, const D3DCOLOR& _ColorKey)
{
	if (TexList.find(_DataName) != TexList.end())return;
	if (_TextureName.length() <= 0)return;

	std::string TmpPath = "./";


	if (PathList.find(_UsePathName) != PathList.end())
	{
		TmpPath = *PathList[_UsePathName];
		TmpPath += "/";

	}

	std::string TmpString = _TextureName;

	TmpString = TmpPath + TmpString;

	auto TmpTex = ChTex::Texture9::TextureType(TmpString);

	TmpTex->CreateTexture(TmpString, Device, _ColorKey);

	if (ChPtr::NullCheck(TmpTex->GetTex()))
	{
		ChSystem::ErrerMessage("âÊëúÇ™ì«Ç›çûÇ‹ÇÍÇ‹ÇπÇÒÇ≈ÇµÇΩ", "åxçê");


		TmpTex = nullptr;
		return;
	}


	if (ChPtr::NullCheck(TmpTex->GetTex())) return;

	TmpTex->InsSclXSize() = 0.0f;
	TmpTex->InsSclYSize() = 0.0f;
	if (_GameReSizeWidth != NULL && _GameReSizeHeight != NULL) {
		float tmpX, tmpY;
		tmpX = (float)_GameReSizeWidth / (float)TmpTex->GetOriginalWidth();
		tmpY = (float)_GameReSizeHeight / (float)TmpTex->GetOriginalHeight();
		if (_GameReSizeWidth == TmpTex->GetOriginalWidth())tmpX = 0.0f;
		if (_GameReSizeHeight == TmpTex->GetOriginalHeight())tmpY = 0.0f;
		TmpTex->InsSclXSize() = tmpX;
		TmpTex->InsSclYSize() = tmpY;
	}

	TexList[_DataName] = TmpTex;

}

///////////////////////////////////////////////////////////////////////////////////

void TextureManager9::SetColorTex(
	const unsigned long& _Color
	, const std::string& _DataName
	, const unsigned int _GameReSizeWidth
	, const unsigned int _GameReSizeHeight
	, const unsigned long _Type)
{
	if (TexList.find(_DataName) != TexList.end())return;

	auto TmpTex = ChPtr::Make_S<Texture9>();

	TmpTex->CreateColTexture(Device, _Color);

	TmpTex->InsSclXSize() = 1.0f;
	TmpTex->InsSclYSize() = 1.0f;

	if (_GameReSizeWidth != 0 && _GameReSizeHeight != 0)
	{
		TmpTex->InsSclXSize() = (float)_GameReSizeWidth;
		TmpTex->InsSclYSize() = (float)_GameReSizeHeight;
	}

	TexList[_DataName] = TmpTex;

	return;
}

///////////////////////////////////////////////////////////////////////////////////

void TextureManager9::SetBlendColor(
	const ChStd::COLOR255& _Color
	, const std::string _DataName)
{

	if (TexList.find(_DataName) == TexList.end())return;
	TexList[_DataName]->SetBaseColor(_Color);
}

///////////////////////////////////////////////////////////////////////////////////

void TextureManager9::SetBlendAlpha(
	const unsigned char _a
	, std::string _DataName)
{
	if (TexList.find(_DataName) == TexList.end())return;
	TexList[_DataName]->InsBaseColor().a = _a;
}

///////////////////////////////////////////////////////////////////////////////////

void TextureManager9::SetDirectoryPath(std::string _DirectoryPath
	, const std::string _UseDirectoryPashName)
{
	if (PathList.find(_UseDirectoryPashName) != PathList.end())return;
	if (_DirectoryPath.length() <= 0)return;

	PathList.insert(std::pair<std::string, ChPtr::Shared<std::string>>(_UseDirectoryPashName, ChPtr::Make_S<std::string>()));
	*PathList[_UseDirectoryPashName] = _DirectoryPath;
}

///////////////////////////////////////////////////////////////////////////////////

void TextureManager9::ClearData(const std::string _DataName)
{
	if (TexList.empty())return;

	if (TexList.find(_DataName) == TexList.end()) return;

	TexList.erase(_DataName);

	return;

}

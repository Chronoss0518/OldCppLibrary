
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"ChTexManager9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////////
//ChTextureManager9ÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void TextureManager9::Init(LPDIRECT3DDEVICE9 _dv)
{
	device = _dv;

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void TextureManager9::Release()
{

	if (!texList.empty()) {
		texList.clear();
	}
	if (!pathList.empty())
	{
		pathList.clear();
	}

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

TextureManager9::~TextureManager9()
{
	Release();
}

///////////////////////////////////////////////////////////////////////////////////

void TextureManager9::SetTexture(
	const std::string& _textureName
	, const std::string& _dataName
	, const std::string& _usePathName
	, const unsigned int _gameReSizeWidth
	, const unsigned int _gameReSizeHeight
	, const D3DCOLOR& _colorKey)
{
	if (texList.find(_dataName) != texList.end())return;
	if (_textureName.length() <= 0)return;

	std::string tmpPath = "./";


	if (pathList.find(_usePathName) != pathList.end())
	{
		tmpPath = *pathList[_usePathName];
		tmpPath += "/";

	}

	std::string tmpString = _textureName;

	tmpString = tmpPath + tmpString;

	auto tmpTex = ChTex::Texture9::TextureType(tmpString);

	tmpTex->CreateTexture(tmpString, device, _colorKey);

	if (ChPtr::NullCheck(tmpTex->GetTex()))
	{
		//ChSystem::ErrerMessage("âÊëúÇ™ì«Ç›çûÇ‹ÇÍÇ‹ÇπÇÒÇ≈ÇµÇΩ", "åxçê");


		tmpTex = nullptr;
		return;
	}


	if (ChPtr::NullCheck(tmpTex->GetTex())) return;

	tmpTex->InsSclXSize() = 0.0f;
	tmpTex->InsSclYSize() = 0.0f;
	if (_gameReSizeWidth != NULL && _gameReSizeHeight != NULL) {
		float tmpX, tmpY;
		tmpX = (float)_gameReSizeWidth / (float)tmpTex->GetOriginalWidth();
		tmpY = (float)_gameReSizeHeight / (float)tmpTex->GetOriginalHeight();
		if (_gameReSizeWidth == tmpTex->GetOriginalWidth())tmpX = 0.0f;
		if (_gameReSizeHeight == tmpTex->GetOriginalHeight())tmpY = 0.0f;
		tmpTex->InsSclXSize() = tmpX;
		tmpTex->InsSclYSize() = tmpY;
	}

	texList[_dataName] = tmpTex;

}

///////////////////////////////////////////////////////////////////////////////////

void TextureManager9::SetColorTex(
	const unsigned long& _color
	, const std::string& _dataName
	, const unsigned int _gameReSizeWidth
	, const unsigned int _gameReSizeHeight
	, const unsigned long _type)
{
	if (texList.find(_dataName) != texList.end())return;

	auto tmpTex = ChPtr::Make_S<Texture9>();

	tmpTex->CreateColTexture(device, _color);

	tmpTex->InsSclXSize() = 1.0f;
	tmpTex->InsSclYSize() = 1.0f;

	if (_gameReSizeWidth != 0 && _gameReSizeHeight != 0)
	{
		tmpTex->InsSclXSize() = (float)_gameReSizeWidth;
		tmpTex->InsSclYSize() = (float)_gameReSizeHeight;
	}

	texList[_dataName] = tmpTex;

	return;
}

///////////////////////////////////////////////////////////////////////////////////

void TextureManager9::SetBlendColor(
	const ChVec4& _color
	, const std::string _dataName)
{

	if (texList.find(_dataName) == texList.end())return;
	texList[_dataName]->SetBaseColor(_color);
}

///////////////////////////////////////////////////////////////////////////////////

void TextureManager9::SetBlendAlpha(
	const unsigned char _a
	, std::string _dataName)
{
	if (texList.find(_dataName) == texList.end())return;
	texList[_dataName]->InsBaseColor().a = _a;
}

///////////////////////////////////////////////////////////////////////////////////

void TextureManager9::SetDirectoryPath(std::string _directoryPath
	, const std::string _useDirectoryPashName)
{
	if (pathList.find(_useDirectoryPashName) != pathList.end())return;
	if (_directoryPath.length() <= 0)return;

	pathList.insert(std::pair<std::string, ChPtr::Shared<std::string>>(_useDirectoryPashName, ChPtr::Make_S<std::string>()));
	*pathList[_useDirectoryPashName] = _directoryPath;
}

///////////////////////////////////////////////////////////////////////////////////

void TextureManager9::ClearData(const std::string _dataName)
{
	if (texList.empty())return;

	if (texList.find(_dataName) == texList.end()) return;

	texList.erase(_dataName);

	return;

}

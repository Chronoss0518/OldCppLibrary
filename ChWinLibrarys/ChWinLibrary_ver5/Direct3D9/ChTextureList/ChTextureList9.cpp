
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChTexture/ChBaseTexture9.h"
#include"ChTextureList9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////////
//ChTextureList9ÉÅÉ\ÉbÉh
///////////////////////////////////////////////////////////////////////////////////////

void ChTexList9::SetTexture(
	const std::string& _textureName
	, const ChStd::DataNo _dataNum
	, const unsigned int _gameReSizeWidth
	, const unsigned int _gameReSizeHeight
	, const D3DCOLOR ColorKey)
{
	if (texList.find(_dataNum) != texList.end())return;

	if (_textureName.length() <= 0)return;

	std::string tmpPath = "./";

	if (directoryPath.length() > 0)
	{
		tmpPath = directoryPath;
		tmpPath += "/";
	}

	std::string tmpString = _textureName;

	tmpString = tmpPath + tmpString;

	auto tmpTex = ChTex::Texture9::TextureType(tmpString);

	tmpTex->CreateTexture(tmpString,device, ColorKey);

	if (ChPtr::NullCheck(tmpTex->GetTex()))
	{
		//ChSystem::ErrerMessage("âÊëúÇ™ì«Ç›çûÇ‹ÇÍÇ‹ÇπÇÒÇ≈ÇµÇΩ", "åxçê");

		tmpTex = nullptr;
		return;
	}

	tmpTex->InsSclXSize() = 1.0f;
	tmpTex->InsSclYSize() = 1.0f;
	
	{
		float tmpX, tmpY;
		tmpX = _gameReSizeWidth > 1.0f ? (float)_gameReSizeWidth / (float)tmpTex->GetOriginalWidth() : 1.0f;
		tmpY = _gameReSizeHeight > 1.0f ? (float)_gameReSizeHeight / (float)tmpTex->GetOriginalHeight() : 1.0f;
		
		tmpTex->InsSclXSize() = tmpX;
		tmpTex->InsSclYSize() = tmpY;
	}

	texList[_dataNum] = tmpTex;



}

///////////////////////////////////////////////////////////////////////////////////

void TextureList9::SetColorTex(
	const unsigned long& _color
	, const ChStd::DataNo _dataNum
	, const unsigned int _gameReSizeWidth
	, const unsigned int _gameReSizeHeight
	, const unsigned long _type)
{
	if (texList.find(_dataNum) != texList.end())return;

	auto tmpTex = ChPtr::Make_S<Texture9>();

	tmpTex->CreateColTexture(device, _color);

	tmpTex->InsSclXSize() = 1.0f;
	tmpTex->InsSclYSize() = 1.0f;

	if (_gameReSizeWidth > 0 && _gameReSizeHeight > 0)
	{
		tmpTex->InsSclXSize() = (float)_gameReSizeWidth;
		tmpTex->InsSclYSize() = (float)_gameReSizeHeight;
	}

	texList[_dataNum] = tmpTex;

	return;
}

///////////////////////////////////////////////////////////////////////////////////

void TextureList9::SetBlendColor(
	const ChVec4& _color
	, const ChStd::DataNo _dataNum)
{
	if (texList.find(_dataNum) == texList.end())return;

	texList[_dataNum]->SetBaseColor(_color);
}

///////////////////////////////////////////////////////////////////////////////////

void TextureList9::SetBlendAlpha(const unsigned char _a, const ChStd::DataNo _dataNum) {

	if (texList.find(_dataNum) == texList.end())return;

	texList[_dataNum]->InsBaseColor().a = _a;
}


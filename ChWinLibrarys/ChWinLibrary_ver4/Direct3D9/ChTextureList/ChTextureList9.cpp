
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
	const std::string& _TextureName
	, const ChStd::DataNo DataNum
	, const unsigned int _GameReSizeWidth
	, const unsigned int _GameReSizeHeight
	, const D3DCOLOR ColorKey)
{
	if (TexList.find(DataNum) != TexList.end())return;

	if (_TextureName.length() <= 0)return;

	std::string TmpPath = "./";

	if (DirectoryPath.length() > 0)
	{
		TmpPath = DirectoryPath;
		TmpPath += "/";
	}

	std::string TmpString = _TextureName;

	TmpString = TmpPath + TmpString;

	auto TmpTex = ChTex::Texture9::TextureType(TmpString);

	TmpTex->CreateTexture(TmpString,Device, ColorKey);

	if (ChPtr::NullCheck(TmpTex->GetTex()))
	{
		//ChSystem::ErrerMessage("âÊëúÇ™ì«Ç›çûÇ‹ÇÍÇ‹ÇπÇÒÇ≈ÇµÇΩ", "åxçê");

		TmpTex = nullptr;
		return;
	}

	TmpTex->InsSclXSize() = 1.0f;
	TmpTex->InsSclYSize() = 1.0f;
	
	{
		float tmpX, tmpY;
		tmpX = _GameReSizeWidth > 1.0f ? (float)_GameReSizeWidth / (float)TmpTex->GetOriginalWidth() : 1.0f;
		tmpY = _GameReSizeHeight > 1.0f ? (float)_GameReSizeHeight / (float)TmpTex->GetOriginalHeight() : 1.0f;
		
		TmpTex->InsSclXSize() = tmpX;
		TmpTex->InsSclYSize() = tmpY;
	}

	TexList[DataNum] = TmpTex;



}

///////////////////////////////////////////////////////////////////////////////////

void TextureList9::SetColorTex(
	const unsigned long& _Color
	, const ChStd::DataNo _DataNum
	, const unsigned int _GameReSizeWidth
	, const unsigned int _GameReSizeHeight
	, const unsigned long _Type)
{
	if (TexList.find(_DataNum) != TexList.end())return;

	auto TmpTex = ChPtr::Make_S<Texture9>();

	TmpTex->CreateColTexture(Device, _Color);

	TmpTex->InsSclXSize() = 1.0f;
	TmpTex->InsSclYSize() = 1.0f;

	if (_GameReSizeWidth > 0 && _GameReSizeHeight > 0)
	{
		TmpTex->InsSclXSize() = (float)_GameReSizeWidth;
		TmpTex->InsSclYSize() = (float)_GameReSizeHeight;
	}

	TexList[_DataNum] = TmpTex;

	return;
}

///////////////////////////////////////////////////////////////////////////////////

void TextureList9::SetBlendColor(
	const ChVec4& _Color
	, const ChStd::DataNo DataNum)
{
	if (TexList.find(DataNum) == TexList.end())return;

	TexList[DataNum]->SetBaseColor(_Color);
}

///////////////////////////////////////////////////////////////////////////////////

void TextureList9::SetBlendAlpha(const unsigned char _a, const ChStd::DataNo DataNum) {

	if (TexList.find(DataNum) == TexList.end())return;

	TexList[DataNum]->InsBaseColor().a = _a;
}


#include<Windows.h>

#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"ChBaseTexture9.h"
#include"TexIncluder9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////
//BaseTexture9メソッド
///////////////////////////////////////////////////////////////////////////////////

void BaseTexture9::Release()
{
	if (ChPtr::NotNullCheck(Tex))Tex->Release();
	Tex = nullptr;

	if (ChPtr::NotNullCheck(Sur))Sur->Release();
	Sur = nullptr;

	if (ChPtr::NotNullCheck(ZBu))ZBu->Release();
	ZBu = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////

template<class T>
T BaseTexture9::GetColor(
	const unsigned int _Width
	, const unsigned int _Height)
{

	T TmpCol;

	ZeroMemory(&TmpCol, sizeof(TmpCol));

	if (_Width >= OWidth || _Height >= OHeight)return TmpCol;

	D3DLOCKED_RECT LockRect;

	if (Tex->LockRect(0, &LockRect, nullptr, 0) != D3D_OK)
	{
		return TmpCol;
	}
	T* pPitch = (T*)LockRect.pBits;

	DWORD Pitch = LockRect.Pitch / sizeof(T);
	pPitch += (Pitch * _Height);
	TmpCol = *(pPitch + _Width);

	Tex->UnlockRect(0);

	return TmpCol;
}
template D3DCOLOR BaseTexture9::GetColor(
	const unsigned int _Width
	, const unsigned int _Height);

///////////////////////////////////////////////////////////////////////////////////

ChVec4 BaseTexture9::D3DColorToColor255(const D3DCOLOR& _Col)
{

	D3DCOLOR TmpCol = _Col;
	ChVec4 TmpCol2;
	TmpCol2.a = static_cast<unsigned char>((TmpCol >> 24) & 0xff) / 255.0f;
	TmpCol2.r = static_cast<unsigned char>((TmpCol >> 16) & 0xff) / 255.0f;
	TmpCol2.g = static_cast<unsigned char>((TmpCol >> 8) & 0xff) / 255.0f;
	TmpCol2.b = static_cast<unsigned char>((TmpCol) & 0xff) / 255.0f;
	return TmpCol2;
}

///////////////////////////////////////////////////////////////////////////////////

void BaseTexture9::CreateTexture(
	const std::string& _FileName
	, const LPDIRECT3DDEVICE9& _Dev
	, const D3DCOLOR& _ColKey)
{
	if (ChPtr::NotNullCheck(Tex))return;

	OpenFile(_FileName);
	if (OWidth <= 0 || OHeight <= 0)return;

	D3DXCreateTextureFromFileEx(
		_Dev
		, _FileName.c_str()
		, OWidth, OHeight
		, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE, D3DX_DEFAULT
		, _ColKey, NULL, NULL, &Tex);
}

///////////////////////////////////////////////////////////////////////////////////

void BaseTexture9::CreateColTexture(
	const LPDIRECT3DDEVICE9& _Dev
	, const D3DCOLOR& _Col
	, const unsigned long _W
	, const unsigned long _H)
{
	D3DXCreateTexture(
		_Dev, _W, _H, 1, 0
		, D3DFMT_A8R8G8B8
		, D3DPOOL_MANAGED, &Tex);

	if (Tex == nullptr)return;

	OWidth = _W;
	OHeight = _H;

	SetTexColor(_Col);

}

///////////////////////////////////////////////////////////////////////////////////

template<typename T>
void BaseTexture9::CreateMinuColTexture(
	const LPDIRECT3DDEVICE9& _Dev
	, const T& _Col
	, const unsigned long _W
	, const unsigned long _H
	, const _D3DFORMAT _FMT
	, const unsigned long _Usage
	, const _D3DPOOL _Pool)
{

	D3DXCreateTexture(
		_Dev, _W, _H, 1, _Usage
		, _FMT, _Pool, &Tex);

	if (Tex == nullptr)return;

	OWidth = _W;
	OHeight = _H;

	if(_Usage != 0)return;

	SetTexColor(_Col);

}
template void BaseTexture9::CreateMinuColTexture(
	const LPDIRECT3DDEVICE9& _Dev
	, const D3DCOLOR& _Col
	, const unsigned long _W
	, const unsigned long _H
	, const _D3DFORMAT _FMT
	, const DWORD _Usage
	, const _D3DPOOL _Pool);

///////////////////////////////////////////////////////////////////////////////////

void BaseTexture9::CreateZBuffer(
	const LPDIRECT3DDEVICE9& _Dev
	, const _D3DFORMAT _FMT
	, const _D3DMULTISAMPLE_TYPE _MSample
	, const unsigned long _MQuality)
{

	if (ChPtr::NullCheck(Tex))return;

	_Dev->CreateDepthStencilSurface(
		OWidth
		, OHeight
		, _FMT
		, _MSample
		, _MQuality
		, false
		, &ZBu
		, nullptr);
}

///////////////////////////////////////////////////////////////////////////////////

ChPtr::Shared<BaseTexture9> BaseTexture9::TextureType(
	const std::string _FileName)
{
	std::string TmpStr;

	{
		size_t TmpNum = _FileName.rfind(".");
		if (TmpNum == _FileName.npos)return ChPtr::Make_S<BaseTexture9>();
		TmpStr = &_FileName[TmpNum];
	}

	if (TmpStr.find("png") != TmpStr.npos)
	{
		return ChPtr::Make_S<PngTex9>();
	}

	if (TmpStr.find("jpeg") != TmpStr.npos
		|| TmpStr.find("jpg") != TmpStr.npos)
	{
		return ChPtr::Make_S<JpegTex>();
	}

	return ChPtr::Make_S<BaseTexture9>();
	
}

///////////////////////////////////////////////////////////////////////////////////

template<typename T>
void BaseTexture9::SetTexColor(const T& _Color)
{

	D3DLOCKED_RECT LockRect;
	if (Tex->LockRect(0, &LockRect, nullptr, 0) != D3D_OK)
	{
		Release();
		return;
	}
	T* pPitch = (T*)LockRect.pBits;

	UINT Pitch = LockRect.Pitch / sizeof(T);
	for (unsigned int h = 0; h < OHeight; h++)
	{
		for (unsigned int w = 0; w < OWidth; w++)
		{
			pPitch[w] = _Color;
		}
		pPitch += Pitch;
	}

	Tex->UnlockRect(0);
}
template void BaseTexture9::SetTexColor(const D3DCOLOR& _Color);

///////////////////////////////////////////////////////////////////////////////////
//ChPngTex9メソッド
///////////////////////////////////////////////////////////////////////////////////

void PngTex9::OpenFile(const std::string& _FileName)
{

	ChFIO::File File;

	File.FileOpen(_FileName, std::ios::binary | std::ios::in | std::ios::out);

	std::string TmpStr;

	File.FileRead(TmpStr);

	File.FileClose();

	auto Chank = SetChank(TmpStr);

	if (Chank.CHData <= 0 || Chank.CWData <= 0)return;

	OWidth = Chank.CWData;
	OHeight = Chank.CHData;

}

///////////////////////////////////////////////////////////////////////////////////

PngTex9::CIHDR PngTex9::SetChank(const std::string& _Str)
{
	CIHDR Chank;
	if (_Str == "")return Chank;

	size_t FPos;

	{
		std::string Tmp = (char*)Chank.CType;
		FPos = _Str.find(Tmp, 1);
	}


	if (FPos == std::string::npos)return Chank;
	FPos -= 4;

	SetBynaryForStr(Chank.Length, _Str, FPos);

	FPos += 4;

	SetBynaryForStr(Chank.CWData, _Str, FPos);

	SetBynaryForStr(Chank.CHData, _Str, FPos);

	SetBynaryForStr(Chank.BD, _Str, FPos);

	SetBynaryForStr(Chank.ColType, _Str, FPos);

	SetBynaryForStr(Chank.Zips, _Str, FPos);

	SetBynaryForStr(Chank.Fillter, _Str, FPos);

	SetBynaryForStr(Chank.Interlase, _Str, FPos);

	SetBynaryForStr(Chank.CRC, _Str, FPos);

	return Chank;
}

///////////////////////////////////////////////////////////////////////////////////
//ChPngTex9メソッド
///////////////////////////////////////////////////////////////////////////////////

void JpegTex::OpenFile(const std::string& _FileName)
{

	ChFIO::File File;
	File.FileOpen(_FileName , std::ios::binary | std::ios::in | std::ios::out);

	std::string TmpStr;
	File.FileRead(TmpStr);

	File.FileClose();

	auto Data = SetSegment(TmpStr);

	if (Data.TexWidht <= 0 || Data.TexHeight <= 0)return;

	OWidth = Data.TexWidht;
	OHeight = Data.TexHeight;
}

///////////////////////////////////////////////////////////////////////////////////

JpegTex::S_SOF JpegTex::SetSegment(const std::string& _Str)
{
	S_SOF Seg;


	if (_Str == "")return Seg;

	size_t FPos;

	{
		std::string Tmp = (char*)Seg.MType;
		FPos = _Str.find(Tmp, 1);
	}


	if (FPos == std::string::npos)return Seg;
	FPos += 2;

	SetBynaryForStr(Seg.S_Len, _Str, FPos);

	SetBynaryForStr(Seg.Sample, _Str, FPos);

	SetBynaryForStr(Seg.TexHeight, _Str, FPos);

	SetBynaryForStr(Seg.TexWidht, _Str, FPos);

	SetBynaryForStr(Seg.TypeCnt, _Str, FPos);

	return Seg;
}

///////////////////////////////////////////////////////////////////////////////////
//ChBmpTex9メソッド
///////////////////////////////////////////////////////////////////////////////////

#include<Windows.h>

#include"../../BaseIncluder/ChBase.h"
#include"../../CPP/ChFile/ChFile.h"

#include"../../BaseIncluder/ChD3D9I.h"

#include"ChBaseTexture9.h"
#include"TexIncluder9.h"

using namespace ChTex;

///////////////////////////////////////////////////////////////////////////////////
//BaseTexture9メソッド
///////////////////////////////////////////////////////////////////////////////////

void BaseTexture9::Release()
{
	if (ChPtr::NotNullCheck(tex))tex->Release();
	tex = nullptr;

	if (ChPtr::NotNullCheck(sur))sur->Release();
	sur = nullptr;

	if (ChPtr::NotNullCheck(zBu))zBu->Release();
	zBu = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////

template<class T>
T BaseTexture9::GetColor(
	const unsigned int _width
	, const unsigned int _height)
{

	T tmpCol;

	ZeroMemory(&tmpCol, sizeof(tmpCol));

	if (_width >= original.w || _height >= original.h)return tmpCol;

	D3DLOCKED_RECT lockRect;

	if (tex->LockRect(0, &lockRect, nullptr, 0) != D3D_OK)
	{
		return tmpCol;
	}
	T* pPitch = (T*)lockRect.pBits;

	DWORD pitch = lockRect.Pitch / sizeof(T);
	pPitch += (pitch * _height);
	tmpCol = *(pPitch + _width);

	tex->UnlockRect(0);

	return tmpCol;
}
template D3DCOLOR BaseTexture9::GetColor(
	const unsigned int _Width
	, const unsigned int _Height);

///////////////////////////////////////////////////////////////////////////////////

ChVec4 BaseTexture9::D3DColorToColor255(const D3DCOLOR& _col)
{

	D3DCOLOR tmpCol = _col;
	ChVec4 tmpCol2;
	tmpCol2.a = static_cast<unsigned char>((tmpCol >> 24) & 0xff) / 255.0f;
	tmpCol2.r = static_cast<unsigned char>((tmpCol >> 16) & 0xff) / 255.0f;
	tmpCol2.g = static_cast<unsigned char>((tmpCol >> 8) & 0xff) / 255.0f;
	tmpCol2.b = static_cast<unsigned char>((tmpCol) & 0xff) / 255.0f;
	return tmpCol2;
}

///////////////////////////////////////////////////////////////////////////////////

void BaseTexture9::CreateTexture(
	const std::string& _fileName
	, const LPDIRECT3DDEVICE9& _dev
	, const D3DCOLOR& _colKey)
{
	if (ChPtr::NotNullCheck(tex))return;

	OpenFile(_fileName);
	if (original.w <= 0 || original.h <= 0)return;

	D3DXCreateTextureFromFileEx(
		_dev
		, _fileName.c_str()
		, original.w, original.h
		, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE, D3DX_DEFAULT
		, _colKey, NULL, NULL, &tex);
}

///////////////////////////////////////////////////////////////////////////////////

void BaseTexture9::CreateColTexture(
	const LPDIRECT3DDEVICE9& _dev
	, const D3DCOLOR& _col
	, const unsigned long _w
	, const unsigned long _h)
{
	D3DXCreateTexture(
		_dev, _w, _h, 1, 0
		, D3DFMT_A8R8G8B8
		, D3DPOOL_MANAGED, &tex);

	if (tex == nullptr)return;

	original.w = _w;
	original.h = _h;

	SetTexColor(_col);

}

///////////////////////////////////////////////////////////////////////////////////

template<typename T>
void BaseTexture9::CreateMinuColTexture(
	const LPDIRECT3DDEVICE9& _dev
	, const T& _col
	, const unsigned long _w
	, const unsigned long _h
	, const _D3DFORMAT _format
	, const unsigned long _usage
	, const _D3DPOOL _pool)
{

	D3DXCreateTexture(
		_dev, _w, _h, 1, _usage
		, _format, _pool, &tex);

	if (tex == nullptr)return;

	original.w = _w;
	original.h = _h;

	if(_usage != 0)return;

	SetTexColor(_col);

}
template void BaseTexture9::CreateMinuColTexture(
	const LPDIRECT3DDEVICE9& _dev
	, const D3DCOLOR& _col
	, const unsigned long _w
	, const unsigned long _h
	, const _D3DFORMAT _format
	, const DWORD _usage
	, const _D3DPOOL _pool);

///////////////////////////////////////////////////////////////////////////////////

void BaseTexture9::CreateZBuffer(
	const LPDIRECT3DDEVICE9& _dev
	, const _D3DFORMAT _format
	, const _D3DMULTISAMPLE_TYPE _mSample
	, const unsigned long _mQuality)
{

	if (ChPtr::NullCheck(tex))return;

	_dev->CreateDepthStencilSurface(
		original.w
		, original.h
		, _format
		, _mSample
		, _mQuality
		, false
		, &zBu
		, nullptr);
}

///////////////////////////////////////////////////////////////////////////////////

ChPtr::Shared<BaseTexture9> BaseTexture9::TextureType(
	const std::string _fileName)
{
	std::string tmpStr;

	{
		size_t tmpNum = _fileName.rfind(".");
		if (tmpNum == _fileName.npos)return ChPtr::Make_S<BaseTexture9>();
		tmpStr = &_fileName[tmpNum];
	}

	if (tmpStr.find("png") != tmpStr.npos)
	{
		return ChPtr::Make_S<PngTex9>();
	}

	if (tmpStr.find("jpeg") != tmpStr.npos
		|| tmpStr.find("jpg") != tmpStr.npos)
	{
		return ChPtr::Make_S<JpegTex>();
	}

	return ChPtr::Make_S<BaseTexture9>();
	
}

///////////////////////////////////////////////////////////////////////////////////

template<typename T>
void BaseTexture9::SetTexColor(const T& _color)
{

	D3DLOCKED_RECT lockRect;
	if (tex->LockRect(0, &lockRect, nullptr, 0) != D3D_OK)
	{
		Release();
		return;
	}
	T* pPitch = (T*)lockRect.pBits;

	UINT pitch = lockRect.Pitch / sizeof(T);
	for (unsigned int h = 0; h < original.h; h++)
	{
		for (unsigned int w = 0; w < original.w; w++)
		{
			pPitch[w] = _color;
		}
		pPitch += pitch;
	}

	tex->UnlockRect(0);
}
template void BaseTexture9::SetTexColor(const D3DCOLOR& _color);

///////////////////////////////////////////////////////////////////////////////////
//ChPngTex9メソッド
///////////////////////////////////////////////////////////////////////////////////

void PngTex9::OpenFile(const std::string& _fileName)
{

	ChCpp::File<> file;

	file.FileOpen(_fileName, std::ios::binary | std::ios::in | std::ios::out);

	std::string tmpStr;

	{

		std::vector<char> tmp;

		file.FileReadBinary(tmp);

		tmpStr = &tmp[0];

	}

	file.FileClose();

	auto chank = SetChank(tmpStr);

	if (chank.CHData <= 0 || chank.CWData <= 0)return;

	original.w = chank.CWData;
	original.h = chank.CHData;

}

///////////////////////////////////////////////////////////////////////////////////

PngTex9::CIHDR PngTex9::SetChank(const std::string& _str)
{
	CIHDR chank;
	if (_str == "")return chank;

	size_t fPos;

	{
		std::string tmp = (char*)chank.CType;
		fPos = _str.find(tmp, 1);
	}


	if (fPos == std::string::npos)return chank;
	fPos -= 4;

	SetBynaryForStr(chank.Length, _str, fPos);

	fPos += 4;

	SetBynaryForStr(chank.CWData, _str, fPos);

	SetBynaryForStr(chank.CHData, _str, fPos);

	SetBynaryForStr(chank.BD, _str, fPos);

	SetBynaryForStr(chank.ColType, _str, fPos);

	SetBynaryForStr(chank.Zips, _str, fPos);

	SetBynaryForStr(chank.Fillter, _str, fPos);

	SetBynaryForStr(chank.Interlase, _str, fPos);

	SetBynaryForStr(chank.CRC, _str, fPos);

	return chank;
}

///////////////////////////////////////////////////////////////////////////////////
//ChPngTex9メソッド
///////////////////////////////////////////////////////////////////////////////////

void JpegTex::OpenFile(const std::string& _fileName)
{

	ChCpp::File<> File;
	File.FileOpen(_fileName , std::ios::binary | std::ios::in | std::ios::out);

	std::string tmpStr;

	{

		std::vector<char> tmp;

		tmp.resize(File.GetLength());

		File.FileReadBinary(tmp);

		tmpStr = &tmp[0];

	}

	File.FileClose();

	auto data = SetSegment(tmpStr);

	if (data.TexWidht <= 0 || data.TexHeight <= 0)return;

	original.w = data.TexWidht;
	original.h = data.TexHeight;
}

///////////////////////////////////////////////////////////////////////////////////

JpegTex::S_SOF JpegTex::SetSegment(const std::string& _str)
{
	S_SOF seg;


	if (_str == "")return seg;

	size_t fPos;

	{
		std::string tmp = (char*)seg.MType;
		fPos = _str.find(tmp, 1);
	}


	if (fPos == std::string::npos)return seg;
	fPos += 2;

	SetBynaryForStr(seg.S_Len, _str, fPos);
					
	SetBynaryForStr(seg.Sample, _str, fPos);
					
	SetBynaryForStr(seg.TexHeight, _str, fPos);
					
	SetBynaryForStr(seg.TexWidht, _str, fPos);
					
	SetBynaryForStr(seg.TypeCnt, _str, fPos);

	return seg;
}

///////////////////////////////////////////////////////////////////////////////////
//ChBmpTex9メソッド
///////////////////////////////////////////////////////////////////////////////////

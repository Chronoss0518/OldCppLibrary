
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include<DirectXTex.h>
#include<WICTextureLoader11.h>


#include"../ChDirectX11Controller/ChDirectX11Controller.h"
//#include"../ChTexture/ChBaseTexture11.h"
//#include"../ChMesh/ChBaseMesh11.h"
//#include"../ChLight/ChLight11.h"
#include"ChTexture11.h"

namespace ChD3D11
{

	void Texture11::CreateTexture(const std::string& _TexPath)
	{
		if (!D3D11API().IsInit())return;

		ID3D11Device* TmpDevice = const_cast<ID3D11Device*>(D3D11Device());

		CreateTexture(_TexPath, TmpDevice);
	}


	void Texture11::CreateTexture(const std::string& _TexPath, ID3D11Device* _Device)
	{



		if (FAILED(DirectX::CreateWICTextureFromFile(
			_Device
			, ChStd::ToWString(_TexPath).c_str()
			,&BaseTex
			,&TexView)))
		{
			TexView = nullptr;
			BaseTex = nullptr;
		}
	}

	void Texture11::CreateTexture(const std::wstring& _TexPath)
	{

		if (!D3D11API().IsInit())return;

		ID3D11Device* TmpDevice = const_cast<ID3D11Device*>(D3D11Device());

		CreateTexture(_TexPath, TmpDevice);
	}

	void Texture11::CreateTexture(const std::wstring& _TexPath, ID3D11Device* _Device)
	{

		if (FAILED(DirectX::CreateWICTextureFromFile(
			_Device
			, _TexPath.c_str()
			, &BaseTex
			, &TexView)))
		{
			TexView = nullptr;
			BaseTex = nullptr;
		}
	}


}

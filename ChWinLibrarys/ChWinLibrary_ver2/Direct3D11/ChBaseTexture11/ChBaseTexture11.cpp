
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

//#include"../ChTexture/ChBaseTexture11.h"
//#include"../ChMesh/ChBaseMesh11.h"
//#include"../ChLight/ChLight11.h"
#include"ChBaseTexture11.h"

namespace ChTex
{

	void ChBaseTexture11::Init(const std::string& _TexPath, ID3D11Device* _Device)
	{
		if (FAILED(D3DX11CreateShaderResourceViewFromFile(Device
			, _TexPath.c_str()
			, nullptr
			, nullptr
			, &BaseTex
			, NULL)))BaseTex = nullptr;

	}

}

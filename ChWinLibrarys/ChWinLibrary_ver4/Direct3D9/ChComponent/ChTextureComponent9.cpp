
#include<Windows.h>
#include"../../BaseIncluder/CHBase.h"

#include"../../CPP/ChBitBool/ChBitBool.h"
#include"../../CPP/ChBaseObject/ChBaseObject.h"
#include"../../CPP/ChBaseObject/ChBaseComponent.h"
#include"../../CPP/ChBaseObject/ChObjectManager.h"

#include"../../BaseIncluder/ChD3D9I.h"

#include"../ChShader/ChShader9.h"
#include"../ChTexture/ChBaseTexture9.h"
#include"../ChSprite/ChSprite9.h"
#include"../ChPolygonBoard/ChPolygonBoard9.h"
#include"ChComponent9.h"
#include"ChTextureComponent9.h"

///////////////////////////////////////////////////////////////////////////////////
//ChTextureComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////

void ChTextureComponent9::SetTexture(const std::string& _TextureName)
{
	Texture = ChTex::BaseTexture9::TextureType(_TextureName);
	Texture->CreateTexture(_TextureName, ChD3D9::D3D9Device());
}

///////////////////////////////////////////////////////////////////////////////////
//ChSpriteTextureComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////

void ChSpriteTextureComponent9::Draw2D()
{
	if (Texture == nullptr)return;

	for (unsigned char i = 0; i < 4; i++)
	{
		Ver.SpData[i].Pos.z = 0.0f;
	}

	ChMat_9 TmpMat;

	//{

	//	auto Trans = LookObj()->GetTransform<ChTransformCom9>();

	//	if (nullptr != Trans)
	//	{

	//		TmpMat = Trans->GetMat();
	//	}

	//}

	ChD3D9::Shader().DrawSprite(Texture, TmpMat,Ver);

}

///////////////////////////////////////////////////////////////////////////////////
//ChPolygonTextureComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////

void ChPolygonTextureComponent9::Draw3D()
{
	if (Texture == nullptr)return;

	ChMat_9 TmpMat;

	{

		//auto Trans = LookObj()->GetTransform<ChTransformCom9>();

		//if (nullptr != Trans)
		//{

		//	TmpMat = Trans->GetMat();
		//}

	}

	ChD3D9::Shader().DrawPolygonBoard(Texture, Ver, TmpMat);


}

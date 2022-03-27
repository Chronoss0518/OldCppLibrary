
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

void ChTextureComponent9::SetTexture(const std::string& _textureName)
{
	texture = ChTex::BaseTexture9::TextureType(_textureName);
	texture->CreateTexture(_textureName, ChD3D9::D3D9Device());
}

///////////////////////////////////////////////////////////////////////////////////
//ChSpriteTextureComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////

void ChSpriteTextureComponent9::Draw2D()
{
	if (texture == nullptr)return;

	for (unsigned char i = 0; i < 4; i++)
	{
		ver.spData[i].pos.z = 0.0f;
	}

	ChMat_9 TmpMat;

	//{

	//	auto Trans = LookObj()->GetTransform<ChTransformCom9>();

	//	if (nullptr != Trans)
	//	{

	//		TmpMat = Trans->GetMat();
	//	}

	//}

	ChD3D9::Shader().DrawSprite(texture, TmpMat,ver);

}

///////////////////////////////////////////////////////////////////////////////////
//ChPolygonTextureComponent9メソッド
///////////////////////////////////////////////////////////////////////////////////

void ChPolygonTextureComponent9::Draw3D()
{
	if (texture == nullptr)return;

	ChMat_9 TmpMat;

	{

		//auto Trans = LookObj()->GetTransform<ChTransformCom9>();

		//if (nullptr != Trans)
		//{

		//	TmpMat = Trans->GetMat();
		//}

	}

	ChD3D9::Shader().DrawPolygonBoard(texture, ver, TmpMat);


}

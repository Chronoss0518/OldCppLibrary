#ifndef Ch_D3D9_TexCom_h
#define Ch_D3D9_TexCom_h

#include"../ChVertexData9.h"

#include"../../CPP/ChBaseObject/ChBaseComponent.h"

namespace ChTex
{
	class BaseTexture9;
}

typedef class ChTextureComponent9 :public ChCpp::BaseComponent
{
public:

	//�p�X���L�q//
	//�R���|�[�l���g�ɉ摜�f�[�^���쐬����//
	void SetTexture(const std::string& _TextureName);

	///////////////////////////////////////////////////////////////////////////////////
	//InsFunction//

	//�摜�f�[�^���擾//
	inline ChPtr::Shared<ChTex::BaseTexture9> InsTex() { return Texture; }

	///////////////////////////////////////////////////////////////////////////////////

protected:

	ChPtr::Shared<ChTex::BaseTexture9>Texture = nullptr;

}ChTexCom9;


///////////////////////////////////////////////////////////////////////////////////

typedef class ChSpriteTextureComponent9 :public ChTexCom9
{
public:

	void Draw2D()override;

	///////////////////////////////////////////////////////////////////////////////////

	//�X�v���C�g�z�u�f�[�^//
	ChD3D9::SpriteData& SpriteData() { return Ver; }

protected:

	ChD3D9::SpriteData Ver;

}ChSpTexCom9;

///////////////////////////////////////////////////////////////////////////////////

typedef class ChPolygonTextureComponent9 :public ChTexCom9
{
public:

	///////////////////////////////////////////////////////////////////////////////////

	void Draw3D()override;

	///////////////////////////////////////////////////////////////////////////////////

	//�|���S���z�u�f�[�^//
	ChD3D9::VertexData& PolygonData() { return Ver; }

protected:

	ChD3D9::VertexData Ver;

}ChPoTexCom9;



#endif
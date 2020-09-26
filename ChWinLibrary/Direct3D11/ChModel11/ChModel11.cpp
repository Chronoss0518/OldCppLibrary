
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChDirectX11Controller/ChDirectX11Controller.h"
#include"../ChTexture11/ChTexture11.h"
#include"ChModel11.h"

namespace ChD3D11
{
	void Model11::SetTextures()
	{
		if (!D3D11API().IsInit())return;
		if (Model->ModelData == nullptr)return;

			SetTextures(Model->ModelData, D3D11Device());

	}

	void Model11::SetTextures(const ID3D11Device* _Device)
	{
		if (ChPtr::NullCheck(_Device))return;
		if (Model->ModelData == nullptr)return;

		SetTextures(Model->ModelData, _Device);

	}


	void Model11::SetTextures(
		ChPtr::Shared<ChCpp::BaseModel::Frame> _Frames
		, const ID3D11Device* _Device)
	{

		if (_Frames == nullptr)return;

		for (auto&& Frame : _Frames->ChildFrames)
		{

			SetTextures(Frame, _Device);
		}

		if (_Frames->Meshs == nullptr)return;


		for (auto&& Mate : _Frames->Meshs->MaterialList)
		{

			for (auto&& TexName : Mate->TextureNames)
			{
				auto Tex = ChPtr::Make_S<Texture11>();
				Tex->CreateTexture(TexName, const_cast<ID3D11Device*>(_Device));

				if (Tex->IsTex())continue;

				MaterialNames[_Frames->MyName][Mate->MaterialName] = Tex;

			}

		}


	}




}
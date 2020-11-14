
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChDirectX11Controller/ChDirectX11Controller.h"
#include"../ChTexture/ChTexture11.h"
#include"ChMesh11.h"

namespace ChD3D11
{
	///////////////////////////////////////////////////////////////////////////////////////
	//ChMesh11 Method
	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::Init(
		const ID3D11Device* _Device)
	{
		Release();

		SetDevice(const_cast<ID3D11Device*>(_Device));

	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::Init()
	{
		if (!D3D11API().IsInit())return;

		Release();

		SetDevice(D3D11Device());

	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::Release()
	{
		FrameList.clear();
		ModelData = nullptr;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::Create(const ChCpp::ModelFrame& _BaseModels)
	{
		if (_BaseModels.ModelData == nullptr)return;

		CreateFrames(ModelData,*_BaseModels.ModelData);

		ModelData->FrameName = _BaseModels.ModelData->MyName;

	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::CreateFrames(
		ChPtr::Shared<FrameData11>& _Frames
		, const ChCpp::ModelFrame::Frame& _BaseModels)
	{

		_Frames = ChPtr::Make_S<FrameData11>();
		
		CreatePrimitiveData(_Frames, _BaseModels);

		for (auto&& Models : _BaseModels.ChildFrames)
		{
			ChPtr::Shared<FrameData11> Tmp;
			CreateFrames(Tmp, *Models);
			_Frames->ChildFrame.push_back(Tmp);
			Tmp->ParentFrame = _Frames;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::CreatePrimitiveData(
		ChPtr::Shared<FrameData11>& _Frames
		, const ChCpp::ModelFrame::Frame& _BaseModels)
	{

		if (_BaseModels.Meshs == nullptr)return;

		auto SurfaceList = CreateSurfaceList(_BaseModels);

		unsigned long MateNum = _BaseModels.Meshs->MaterialList.size();

		if (MateNum <= 0)
		{
			auto Mate = ChPtr::Shared<ChCpp::ModelFrame::Material>();

			_BaseModels.Meshs->MaterialList.push_back(Mate);

			Mate->Diffuse = ChVec4(1.0f);
			Mate->MaterialName = "Material1";
			Mate->Specular = ChVec4(0.0f);
			Mate->SpePow = (0.0f);
			Mate->AmbientPow = (0.0f);

			MateNum = _BaseModels.Meshs->MaterialList.size();
		}

		auto& MateList = _BaseModels.Meshs->MaterialList;

		auto& VerList = _BaseModels.Meshs->VertexList;

		_Frames->PrimitiveCount = MateNum;

		//PrimitiveCount//
		for (unsigned long i = 0; i< MateNum;i++)
		{

			auto& Faces = SurfaceList[i];
			
			auto Prim = ChPtr::Make_S<PrimitiveData11<PrimitiveVertex11>>();

			Prim->VertexArray = new PrimitiveVertex11[Faces.size() * 3];

			Prim->IndexArray = new unsigned long[Faces.size() * 3];

			Prim->VertexNum = Faces.size() * 3;
			Prim->IndexNum = Faces.size() * 3;


			unsigned long NowCount = 0;

			//FaceCount//
			for (unsigned long FCount = 0; FCount < Faces.size(); FCount++)
			{

				ChVec3_11 FaceNormal = 0.0f;
				FaceNormal += VerList[Faces[FCount]->VertexData[0].VertexNo]->Normal;
				FaceNormal += VerList[Faces[FCount]->VertexData[1].VertexNo]->Normal;
				FaceNormal += VerList[Faces[FCount]->VertexData[2].VertexNo]->Normal;

				FaceNormal.Normalize();

				//VertexCount//
				for (unsigned long j = 0; j < 3; j++)
				{

					auto& Vertexs = (Prim->VertexArray[NowCount]);

					Vertexs.Pos = VerList[Faces[FCount]->VertexData[j].VertexNo]->Pos;
					Vertexs.Normal = VerList[Faces[FCount]->VertexData[j].VertexNo]->Normal;
					Vertexs.FaceNormal = FaceNormal;
					Vertexs.BlendPow = VerList[Faces[FCount]->VertexData[j].VertexNo]->BlendPow;
					Vertexs.BlendIndex = VerList[Faces[FCount]->VertexData[j].VertexNo]->BoneNo;

					Vertexs.UVPos = Faces[FCount]->VertexData[j].UVPos;

					Prim->IndexArray[NowCount] = NowCount;

					NowCount++;

				}


			}

			CreateVertexBuffer(*Prim);
			CreateIndexBuffer(*Prim);

			Prim->Mate = ChPtr::Make_S<Material11>();

			Prim->Mate->Ambient = ChVec4(MateList[i]->AmbientPow);
			Prim->Mate->Diffuse = MateList[i]->Diffuse;
			Prim->Mate->Specular = MateList[i]->Specular;
			Prim->Mate->Specular.a = MateList[i]->SpePow;
			Prim->Mate->MaterialName = MateList[i]->MaterialName;
			
			for (auto TexName : MateList[i]->TextureNames)
			{
				auto Tex = ChPtr::Make_S<Texture11>();

				Tex->CreateTexture(TexName);

				Prim->Mate->TextureList.push_back(Tex);

			}

			_Frames->PrimitiveDatas[MateList[i]->MaterialName] = Prim;

		}

		FrameList.push_back(_Frames);



	}
	
	///////////////////////////////////////////////////////////////////////////////////////

	std::vector<std::vector<ChPtr::Shared<ChCpp::ModelFrame::SurFace>>>
		Mesh11::CreateSurfaceList(
			const ChCpp::ModelFrame::Frame& _BaseModels)
	{

		std::vector<std::vector<ChPtr::Shared<ChCpp::ModelFrame::SurFace>>>SurfaceList;

		unsigned long MateNum = _BaseModels.Meshs->MaterialList.size();


		if (MateNum < 2)
		{
			SurfaceList.push_back(_BaseModels.Meshs->FaceList);
			return SurfaceList;
		}

		unsigned long VerCount = _BaseModels.Meshs->FaceList.size();

		for (unsigned long i = 0; i < MateNum; i++)
		{
			std::vector<ChPtr::Shared<ChCpp::ModelFrame::SurFace>> Tmp;

			for (unsigned long j = 0; j < VerCount; j++)
			{
				if (_BaseModels.Meshs->FaceList[j]->Materials != i)continue;

				auto TmpFace = _BaseModels.Meshs->FaceList[j];

				Tmp.push_back(TmpFace);
			}
			SurfaceList.push_back(Tmp);
		}

		return SurfaceList;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::SetDrawData(ID3D11DeviceContext* _DC)
	{


		if (ModelData == nullptr)return;

		unsigned int Strides = sizeof(PrimitiveVertex11);
		unsigned int Offsets = 0;

		for (auto&& Frame : FrameList)
		{
			for (auto&& Prim : Frame->PrimitiveDatas)
			{

				_DC->IASetVertexBuffers(0, 1, &Prim.second->Vertexs, &Strides, &Offsets);
				_DC->IASetIndexBuffer(Prim.second->Indexs, DXGI_FORMAT_R32_UINT, 0);


				_DC->DrawIndexed(Prim.second->IndexNum, 0, 0);

			}
		}

	}

	///////////////////////////////////////////////////////////////////////////////////////

	void Mesh11::SetDrawData(ID3D11DeviceContext* _CD,const std::string& _FrameName)
	{
		if (ModelData == nullptr)return;

		for (auto&& Frame : FrameList)
		{
			for (auto&& Prim : Frame->PrimitiveDatas)
			{

			}
		}

	}


}
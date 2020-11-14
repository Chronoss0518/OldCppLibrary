
//SStruct = ShaderStructure//
#ifndef Ch_D3D11_SStruct_h
#define Ch_D3D11_SStruct_h

namespace ChD3D11
{
	class Texture11;

	struct ShaderUseMaterial11
	{
		ChVec4 Diffuse = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ChVec4 Specular = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ChVec4 Ambient = ChVec4(0.3f, 0.3f, 0.3f, 1.0f);
	};

	struct Material11 :public ShaderUseMaterial11
	{
		inline operator ShaderUseMaterial11()
		{
			Material11 Tmp;
			Tmp.Diffuse = Diffuse;
			Tmp.Specular = Specular;
			return Tmp;
		}

		std::string MaterialName;
		std::vector<ChPtr::Shared<Texture11>>TextureList;
	};


	struct Vertex11
	{
		ChVec3 Pos;
		ChVec2 UVPos;
		ChVec4 Color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	struct MeshVertex11: public Vertex11
	{
		ChVec3 Normal = ChVec3(0.0f, 0.0f, -1.0f);
	};

	struct PrimitiveVertex11 : public MeshVertex11
	{
		ChVec3 FaceNormal = ChVec3(0.0f,0.0f,-1.0f);
		ChUIMat BlendIndex;
		ChLMat BlendPow;
		unsigned long BlendNum = 0;
	};

	//struct MeshVertex11: public Vertex11
	//{
	//	ChVec3 Normal;
	//	float Temperature;//ëŒè€ÉÅÉbÉVÉÖÇÃîMó 
	//	UINT4 Blend;
	//	ChVec4 BlendPow;
	//};

	template<class Vertex = Vertex11>
	struct PrimitiveData11
	{
		IndexBuffer Indexs = nullptr;
		VertexBuffer Vertexs = nullptr;


		typename std::enable_if<std::is_base_of<Vertex11, Vertex>::value, Vertex*>::type VertexArray = nullptr;
		unsigned long* IndexArray = nullptr;

		unsigned long VertexNum = 0;
		unsigned long IndexNum = 0;

		ChPtr::Shared<Material11> Mate;

		inline void Release()
		{

			if (ChPtr::NotNullCheck(Indexs))
			{
				Indexs->Release();
				Indexs = nullptr;
			}

			if (ChPtr::NotNullCheck(Vertexs))
			{
				Vertexs->Release();
				Vertexs = nullptr;
			}

			if (ChPtr::NotNullCheck(VertexArray))
			{
				delete[] VertexArray;
				VertexArray = nullptr;
			}

			if (ChPtr::NotNullCheck(IndexArray))
			{
				delete[] IndexArray;
				IndexArray = nullptr;
			}

		}

		inline ~PrimitiveData11()
		{
			Release();
		}
	};

	template<class Vertex = Vertex11>
	class ShaderObject
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		~ShaderObject(){ Release(); }

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		virtual void Release() {};

		///////////////////////////////////////////////////////////////////////////////////////

		virtual void SetDrawData(ID3D11DeviceContext* _CD) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		auto CreateVertexBuffer(PrimitiveData11<Vertex>& _Prim)
			->typename std::enable_if<std::is_base_of<Vertex11, Vertex>::value, void>::type
		{

			D3D11_BUFFER_DESC Desc;

			Desc.ByteWidth = sizeof(Vertex) * _Prim.VertexNum;
			Desc.Usage = D3D11_USAGE_DEFAULT;
			Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			Desc.CPUAccessFlags = 0;
			Desc.MiscFlags = 0;
			Desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA Data;
			Data.pSysMem = _Prim.VertexArray;
			Data.SysMemPitch = 0;
			Data.SysMemSlicePitch = 0;

			Device->CreateBuffer(&Desc, &Data, &_Prim.Vertexs);

		}

		///////////////////////////////////////////////////////////////////////////////////

		auto CreateIndexBuffer(PrimitiveData11<Vertex>& _Prim)
			->typename std::enable_if<std::is_base_of<Vertex11, Vertex>::value, void>::type
		{

			D3D11_BUFFER_DESC Desc;
			Desc.ByteWidth = sizeof(unsigned long) * _Prim.IndexNum;
			Desc.Usage = D3D11_USAGE_DEFAULT;
			Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			Desc.CPUAccessFlags = 0;
			Desc.MiscFlags = 0;
			Desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA Data;
			Data.pSysMem = _Prim.IndexArray;
			Data.SysMemPitch = 0;
			Data.SysMemSlicePitch = 0;

			Device->CreateBuffer(&Desc, &Data, &_Prim.Indexs);

		}


	protected:

		ID3D11Device* GetDevice() { return Device; }

		void SetDevice(ID3D11Device* _Device) { Device = _Device; }

	private:


		ID3D11Device* Device = nullptr;



	};

}

#endif
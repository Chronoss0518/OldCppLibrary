
//SStruct = ShaderStructure//
#ifndef Ch_D3D11_SStruct_h
#define Ch_D3D11_SStruct_h

namespace ChD3D11
{
	class Texture11;

	struct ShaderUseMaterial11
	{
		ChVec4 diffuse = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ChVec4 specular = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ChVec4 ambient = ChVec4(0.3f, 0.3f, 0.3f, 1.0f);
		ChMat_11 frameMatrix;
	};

	struct Material11
	{
		ShaderUseMaterial11 material;


		ConstantBuffer mBuffer = nullptr;
		std::string materialName;
		std::vector<ChPtr::Shared<Texture11>>textureList;
	};

	struct Vertex11
	{
		ChVec3 pos;
		ChVec2 uvPos;
		ChVec4 color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	struct MeshVertex11: public Vertex11
	{
		ChVec3 normal = ChVec3(0.0f, 0.0f, -1.0f);
	};

	struct PrimitiveVertex11 : public MeshVertex11
	{
		ChVec3 faceNormal = ChVec3(0.0f,0.0f,-1.0f);
		ChUIMat blendIndex;
		ChLMat blendPow;
		unsigned long blendNum = 0;
	};

	template<class Vertex = Vertex11>
	struct PrimitiveData11
	{
		IndexBuffer indexs = nullptr;
		VertexBuffer vertexs = nullptr;


		typename std::enable_if<std::is_base_of<Vertex11, Vertex>::value, Vertex*>::type vertexArray = nullptr;
		unsigned long* indexArray = nullptr;

		unsigned long vertexNum = 0;
		unsigned long indexNum = 0;

		ChPtr::Shared<Material11> mate;

		inline void Release()
		{

			if (ChPtr::NotNullCheck(indexs))
			{
				indexs->Release();
				indexs = nullptr;
			}

			if (ChPtr::NotNullCheck(vertexs))
			{
				vertexs->Release();
				vertexs = nullptr;
			}

			if (ChPtr::NotNullCheck(vertexArray))
			{
				delete[] vertexArray;
				vertexArray = nullptr;
			}

			if (ChPtr::NotNullCheck(indexArray))
			{
				delete[] indexArray;
				indexArray = nullptr;
			}

			if (mate != nullptr)
			{

				if (ChPtr::NotNullCheck(mate->mBuffer))
				{
					mate->mBuffer->Release();
					mate->mBuffer = nullptr;
				}
			}

		}

		inline ~PrimitiveData11()
		{
			Release();
		}
	};

	template<class Vertex = Vertex11>
	class ShaderObject:public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		virtual void Release()override {};

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		virtual void SetDrawData(ID3D11DeviceContext* _cd) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		auto CreateVertexBuffer(PrimitiveData11<Vertex>& _prim)
			->typename std::enable_if<std::is_base_of<Vertex11, Vertex>::value, void>::type
		{

			D3D11_BUFFER_DESC desc;

			desc.ByteWidth = sizeof(Vertex) * _prim.vertexNum;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA data;
			data.pSysMem = _prim.vertexArray;
			data.SysMemPitch = 0;
			data.SysMemSlicePitch = 0;

			device->CreateBuffer(&desc, &data, &_prim.vertexs);

		}

		///////////////////////////////////////////////////////////////////////////////////

		auto CreateIndexBuffer(PrimitiveData11<Vertex>& _prim)
			->typename std::enable_if<std::is_base_of<Vertex11, Vertex>::value, void>::type
		{

			D3D11_BUFFER_DESC desc;
			desc.ByteWidth = sizeof(unsigned long) * _prim.indexNum;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA data;
			data.pSysMem = _prim.indexArray;
			data.SysMemPitch = 0;
			data.SysMemSlicePitch = 0;

			device->CreateBuffer(&desc, &data, &_prim.indexs);

		}

		template<class T>
		void CreateContentBuffer(ConstantBuffer* _buffer)
		{

			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

			desc.ByteWidth = sizeof(T);
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;

			device->CreateBuffer(&desc, nullptr, _buffer);
		}

	protected:

		///////////////////////////////////////////////////////////////////////////////////

		ID3D11Device* GetDevice() { return device; }

		///////////////////////////////////////////////////////////////////////////////////

		void SetDevice(ID3D11Device* _device) { device = _device; }

		///////////////////////////////////////////////////////////////////////////////////

	private:


		ID3D11Device* device = nullptr;



	};

}

#endif
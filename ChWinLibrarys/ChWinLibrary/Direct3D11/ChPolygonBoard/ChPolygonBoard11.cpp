
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"ChPolygonBoard11.h"



using namespace ChD3D11;


void PolygonBoard11::Init()
{
	if (!D3D11API().IsInit())return;

	Init(D3D11Device());

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::Init(ID3D11Device* _Device)
{
	Release();

	SetDevice((_Device));

	Primitives.VertexNum = 4;

	Primitives.VertexArray = new MeshVertex11[Primitives.VertexNum];
	
	{
		auto& Vertex = (Primitives.VertexArray[0]);
		Vertex.Pos = ChVec3(-0.5f, 0.5f, 0.0f);
		Vertex.UVPos = ChVec2(0.0f, 0.0f);
		Vertex.Color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	{
		auto& Vertex = (Primitives.VertexArray[1]);
		Vertex.Pos = ChVec3(0.5f, 0.5f, 0.0f);
		Vertex.UVPos = ChVec2(1.0f, 0.0f);
		Vertex.Color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	{
		auto& Vertex = (Primitives.VertexArray[2]);
		Vertex.Pos = ChVec3(0.5f, -0.5f, 0.0f);
		Vertex.UVPos = ChVec2(1.0f, 1.0f);
		Vertex.Color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	{
		auto& Vertex = (Primitives.VertexArray[3]);
		Vertex.Pos = ChVec3(-0.5f, -0.5f, 0.0f);
		Vertex.UVPos = ChVec2(0.0f, 1.0f);
		Vertex.Color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}


	Primitives.IndexNum = 6;

	Primitives.IndexArray = new unsigned long[Primitives.IndexNum];

	Primitives.IndexArray[0] = (0);
	Primitives.IndexArray[1] = (1);
	Primitives.IndexArray[2] = (2);
	Primitives.IndexArray[3] = (0);
	Primitives.IndexArray[4] = (2);
	Primitives.IndexArray[5] = (3);


	for (unsigned char i = 0; i < 4; i++)
	{

		auto Vertex = reinterpret_cast<MeshVertex11*>(&Primitives.VertexArray[i]);

		int Tmp;
		Tmp = 0;
	}


	UpdateVertex();

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::Release()
{
	ShaderObject<MeshVertex11>::Release();
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetPos(const unsigned char  _PosNames, const  ChVec3& _PosData)
{

	if (_PosNames >= 4)return;

	ChVec3 TmpVec;

	TmpVec = _PosData - Primitives.VertexArray[_PosNames].Pos;

	if(TmpVec.Len() > 0.0f)UpdateFlg = true;

	Primitives.VertexArray[_PosNames].Pos = _PosData;

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetUVPos(const unsigned char _PosNames, const ChVec2& _PosData)
{
	if (_PosNames >= 4)return;

	ChVec2 TmpVec;

	TmpVec = _PosData - Primitives.VertexArray[_PosNames].UVPos;

	if (TmpVec.Len() > 0.0f)UpdateFlg = true;

	Primitives.VertexArray[_PosNames].UVPos = _PosData;

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::UpdateVertex()
{

	if (!UpdateFlg)return;

	CreateVertexBuffer(Primitives);

	CreateIndexBuffer(Primitives);

	UpdateFlg = false;


}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetDrawData(ID3D11DeviceContext* _DC)
{
	UpdateVertex();

	unsigned int Strides = sizeof(MeshVertex11);
	unsigned int Offsets = 0;

	_DC->IASetVertexBuffers(0, 1, &Primitives.Vertexs, &Strides, &Offsets);
	_DC->IASetIndexBuffer(Primitives.Indexs, DXGI_FORMAT_R32_UINT, 0);


	_DC->DrawIndexed(Primitives.IndexNum, 0, 0);
}

///////////////////////////////////////////////////////////////////////////////////


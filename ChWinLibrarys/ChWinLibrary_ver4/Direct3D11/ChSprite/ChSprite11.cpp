
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"ChSprite11.h"

using namespace ChD3D11;

void Sprite11::Init()
{
	if (!D3D11API().IsInit())return;

	Init(D3D11Device());
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::Init(const ID3D11Device* _Device)
{
	Release();

	SetDevice(const_cast<ID3D11Device*>(_Device));

	Primitives.VertexNum = 4;

	Primitives.VertexArray = new Vertex11[Primitives.VertexNum];

	Primitives.IndexNum = 6;

	Primitives.IndexArray = new unsigned long[Primitives.IndexNum];

	Primitives.IndexArray[0] = (0);
	Primitives.IndexArray[1] = (1);
	Primitives.IndexArray[2] = (2);
	Primitives.IndexArray[3] = (0);
	Primitives.IndexArray[4] = (2);
	Primitives.IndexArray[5] = (3);

	UpdateVertex();
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::Release()
{
	ShaderObject<Vertex11>::Release();
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetPos(const unsigned char _PosNames, const  ChVec2& _PosData)
{

	if (_PosNames >= 4)return;

	Position[_PosNames] = _PosData;

	UpdateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetUVPos(const unsigned char _PosNames, const ChVec2& _PosData)
{
	if (_PosNames >= 4)return;

	UVPoss[_PosNames] = _PosData;

	UpdateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::Move(const float _x, const float _y)
{
	for (unsigned char i = 0; i < 4; i++)
	{
		Position[i].x += _x;
		Position[i].y += _y;
	}

	UpdateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::UpdateVertex()
{

	if (!UpdateFlg)return;

	for (unsigned char i = 0; i < Primitives.VertexNum; i++)
	{

		Primitives.VertexArray[i].Pos = Position[i];
		Primitives.VertexArray[i].UVPos = UVPoss[i];
	}

	CreateVertexBuffer(Primitives);

	CreateIndexBuffer(Primitives);

	UpdateFlg = false;

}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetDrawData(ID3D11DeviceContext* _DC)
{
	UpdateVertex();

	unsigned int Strides = sizeof(Vertex11);
	unsigned int Offsets = 0;

	_DC->IASetVertexBuffers(0, 1, &Primitives.Vertexs, &Strides, &Offsets);
	_DC->IASetIndexBuffer(Primitives.Indexs, DXGI_FORMAT_R32_UINT, 0);


	_DC->DrawIndexed(Primitives.IndexNum, 0, 0);
}

///////////////////////////////////////////////////////////////////////////////////


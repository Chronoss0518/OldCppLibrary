
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

void Sprite11::Init(const ID3D11Device* _device)
{
	Release();

	SetDevice(const_cast<ID3D11Device*>(_device));

	primitives.vertexNum = 4;

	primitives.vertexArray = new Vertex11[primitives.vertexNum];

	primitives.indexNum = 6;

	primitives.indexArray = new unsigned long[primitives.indexNum];

	primitives.indexArray[0] = (0);
	primitives.indexArray[1] = (1);
	primitives.indexArray[2] = (2);
	primitives.indexArray[3] = (0);
	primitives.indexArray[4] = (2);
	primitives.indexArray[5] = (3);

	UpdateVertex();
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::Release()
{
	ShaderObject<Vertex11>::Release();
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetPos(const unsigned char _posNames, const  ChVec2& _posData)
{

	if (_posNames >= 4)return;

	poss[_posNames] = _posData;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetUVPos(const unsigned char _posNames, const ChVec2& _posData)
{
	if (_posNames >= 4)return;

	uvPoss[_posNames] = _posData;

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::Move(const float _x, const float _y)
{
	for (unsigned char i = 0; i < 4; i++)
	{
		poss[i].x += _x;
		poss[i].y += _y;
	}

	updateFlg = true;
}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::UpdateVertex()
{

	if (!updateFlg)return;

	for (unsigned char i = 0; i < primitives.vertexNum; i++)
	{

		primitives.vertexArray[i].pos = poss[i];
		primitives.vertexArray[i].uvPos = uvPoss[i];
	}

	CreateVertexBuffer(primitives);

	CreateIndexBuffer(primitives);

	updateFlg = false;

}

///////////////////////////////////////////////////////////////////////////////////

void Sprite11::SetDrawData(ID3D11DeviceContext* _dc)
{
	UpdateVertex();

	unsigned int Strides = sizeof(Vertex11);
	unsigned int Offsets = 0;

	_dc->IASetVertexBuffers(0, 1, &primitives.vertexs, &Strides, &Offsets);
	_dc->IASetIndexBuffer(primitives.indexs, DXGI_FORMAT_R32_UINT, 0);


	_dc->DrawIndexed(primitives.indexNum, 0, 0);
}

///////////////////////////////////////////////////////////////////////////////////


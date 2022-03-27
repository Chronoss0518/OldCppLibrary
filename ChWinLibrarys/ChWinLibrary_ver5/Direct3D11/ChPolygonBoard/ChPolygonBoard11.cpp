
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

	primitives.vertexNum = 4;

	primitives.vertexArray = new MeshVertex11[primitives.vertexNum];
	
	{
		auto& vertex = (primitives.vertexArray[0]);
		vertex.pos = ChVec3(-0.5f, 0.5f, 0.0f);
		vertex.uvPos = ChVec2(0.0f, 0.0f);
		vertex.color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	{
		auto& vertex = (primitives.vertexArray[1]);
		vertex.pos = ChVec3(0.5f, 0.5f, 0.0f);
		vertex.uvPos = ChVec2(1.0f, 0.0f);
		vertex.color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	{
		auto& vertex = (primitives.vertexArray[2]);
		vertex.pos = ChVec3(0.5f, -0.5f, 0.0f);
		vertex.uvPos = ChVec2(1.0f, 1.0f);
		vertex.color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	{
		auto& vertex = (primitives.vertexArray[3]);
		vertex.pos = ChVec3(-0.5f, -0.5f, 0.0f);
		vertex.uvPos = ChVec2(0.0f, 1.0f);
		vertex.color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}


	primitives.indexNum = 6;

	primitives.indexArray = new unsigned long[primitives.indexNum];

	primitives.indexArray[0] = (0);
	primitives.indexArray[1] = (1);
	primitives.indexArray[2] = (2);
	primitives.indexArray[3] = (0);
	primitives.indexArray[4] = (2);
	primitives.indexArray[5] = (3);


	for (unsigned char i = 0; i < 4; i++)
	{

		auto vertex = reinterpret_cast<MeshVertex11*>(&primitives.vertexArray[i]);

		int tmp;
		tmp = 0;
	}


	UpdateVertex();

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::Release()
{
	ShaderObject<MeshVertex11>::Release();
}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetPos(const unsigned char  _posNames, const  ChVec3& _posData)
{

	if (_posNames >= 4)return;

	ChVec3 tmpVec;

	tmpVec = _posData - primitives.vertexArray[_posNames].pos;

	if(tmpVec.Len() > 0.0f)updateFlg = true;

	primitives.vertexArray[_posNames].pos = _posData;

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetUVPos(const unsigned char _posNames, const ChVec2& _posData)
{
	if (_posNames >= 4)return;

	ChVec2 tmpVec;

	tmpVec = _posData - primitives.vertexArray[_posNames].uvPos;

	if (tmpVec.Len() > 0.0f)updateFlg = true;

	primitives.vertexArray[_posNames].uvPos = _posData;

}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::UpdateVertex()
{

	if (!updateFlg)return;

	CreateVertexBuffer(primitives);

	CreateIndexBuffer(primitives);

	updateFlg = false;


}

///////////////////////////////////////////////////////////////////////////////////

void PolygonBoard11::SetDrawData(ID3D11DeviceContext* _dc)
{
	UpdateVertex();

	unsigned int Strides = sizeof(MeshVertex11);
	unsigned int Offsets = 0;

	_dc->IASetVertexBuffers(0, 1, &primitives.vertexs, &Strides, &Offsets);
	_dc->IASetIndexBuffer(primitives.indexs, DXGI_FORMAT_R32_UINT, 0);


	_dc->DrawIndexed(primitives.indexNum, 0, 0);
}

///////////////////////////////////////////////////////////////////////////////////


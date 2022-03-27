
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"ChShaderObject11.h"

using namespace ChD3D11;

void ShaderObject11::Init(
	ID3D11Device* _Device)
{
	if (ChPtr::NullCheck(_Device))return;

	Device = _Device;

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::Release()
{

	if (ChPtr::NotNullCheck(Shader))
	{
		Shader->Release();
		Shader = nullptr;
	}

	if (ChPtr::NotNullCheck(LInput))
	{
		LInput->Release();
		LInput = nullptr;
	}

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::CreateVertexShader(
	const D3D11_INPUT_ELEMENT_DESC* _Desc
	, const unsigned long _DescNum
	, const void* _Binary
	, const unsigned long _BinarySize
)
{
	if (!*this)return;

	if (ChPtr::NullCheck(_Binary))return;

	Release();

	ID3D11VertexShader* Tmp;

	Device->CreateVertexShader(_Binary, _BinarySize, nullptr, &Tmp);

	Shader = Tmp;

	Type = ShaderType::Vertex;

	Device->CreateInputLayout(_Desc, _DescNum, _Binary, _BinarySize, &LInput);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::CreatePixelShader(
	const void* _Binary
	, const unsigned long _BinarySize
)
{

	if (!*this)return;

	if (ChPtr::NullCheck(_Binary))return;

	Release();

	ID3D11PixelShader* Tmp;

	Device->CreatePixelShader(_Binary, _BinarySize, nullptr, &Tmp);

	Shader = Tmp;

	Type = ShaderType::Pixel;

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::CreateGeometryShader(
	const void* _Binary
	, const unsigned long _BinarySize
)
{
	if (!*this)return;

	if (ChPtr::NullCheck(_Binary))return;

	Release();

	ID3D11GeometryShader* Tmp;

	Device->CreateGeometryShader(_Binary, _BinarySize, nullptr, &Tmp);

	Shader = Tmp;

	Type = ShaderType::Geometry;

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::CreateComputeShader(
	const void* _Binary
	, const unsigned long _BinarySize
)
{
	if (!*this)return;

	if (ChPtr::NullCheck(_Binary))return;

	Release();

	ID3D11ComputeShader* Tmp;

	Device->CreateComputeShader(_Binary, _BinarySize, nullptr, &Tmp);

	Shader = Tmp;

	Type = ShaderType::Compute;

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::CreateDomainShader(
	const void* _Binary
	, const unsigned long _BinarySize
)
{
	if (!*this)return;

	if (ChPtr::NullCheck(_Binary))return;

	Release();

	ID3D11DomainShader* Tmp;

	Device->CreateDomainShader(_Binary, _BinarySize, nullptr, &Tmp);

	Shader = Tmp;

	Type = ShaderType::Domain;

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::SetShader(
	ID3D11DeviceContext* _DC
)
{
	if (!*this)return;

	if (ChPtr::NullCheck(Shader))return;


	GetShaderSetter()[Type](_DC);
}


#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"ChShaderObject11.h"

using namespace ChD3D11;

///////////////////////////////////////////////////////////////////////////////////////
//ChShaderObject11メソッド
///////////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::Release()
{

	if (!*this)return;

	if (ChPtr::NotNullCheck(Shader))
	{
		Shader->Release();
		Shader = nullptr;
	}

	SetInitFlg(false);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::CreateVertexShader(
	ID3D11Device* _Device
	, ID3D11InputLayout** _LInput
	, const D3D11_INPUT_ELEMENT_DESC* _Desc
	, const unsigned long _DescNum
	, const void* _Binary
	, const unsigned long _BinarySize
)
{
	if (ChPtr::NullCheck(_Device))return;
	if (ChPtr::NullCheck(_Binary))return;

	Release();

	ID3D11VertexShader* Tmp;

	_Device->CreateVertexShader(_Binary, _BinarySize, nullptr, &Tmp);

	Shader = Tmp;

	_Device->CreateInputLayout(_Desc, _DescNum, _Binary, _BinarySize, _LInput);

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::CreatePixelShader(
	ID3D11Device* _Device
	, const void* _Binary
	, const unsigned long _BinarySize
)
{
	if (ChPtr::NullCheck(_Device))return;
	if (ChPtr::NullCheck(_Binary))return;

	Release();

	ID3D11PixelShader* Tmp;

	_Device->CreatePixelShader(_Binary, _BinarySize, nullptr, &Tmp);

	Shader = Tmp;

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::CreateGeometryShader(
	ID3D11Device* _Device
	, const void* _Binary
	, const unsigned long _BinarySize
)
{
	if (ChPtr::NullCheck(_Device))return;
	if (ChPtr::NullCheck(_Binary))return;

	Release();

	ID3D11GeometryShader* Tmp;

	_Device->CreateGeometryShader(_Binary, _BinarySize, nullptr, &Tmp);

	Shader = Tmp;

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::CreateComputeShader(
	ID3D11Device* _Device
	, const void* _Binary
	, const unsigned long _BinarySize
)
{
	if (ChPtr::NullCheck(_Device))return;
	if (ChPtr::NullCheck(_Binary))return;

	Release();

	ID3D11ComputeShader* Tmp;

	_Device->CreateComputeShader(_Binary, _BinarySize, nullptr, &Tmp);

	Shader = Tmp;

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::CreateDomainShader(
	ID3D11Device* _Device
	, const void* _Binary
	, const unsigned long _BinarySize
)
{

	if (ChPtr::NullCheck(_Device))return;
	if (ChPtr::NullCheck(_Binary))return;

	Release();

	ID3D11DomainShader* Tmp;

	_Device->CreateDomainShader(_Binary, _BinarySize, nullptr, &Tmp);

	Shader = Tmp;

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::SetVertexShader(
	ID3D11DeviceContext* _DC
	, ID3D11InputLayout* _LInput)
{
	if (!*this)return;

	auto Tmp = static_cast<ID3D11VertexShader*>(Shader);

	_DC->VSSetShader(Tmp, nullptr, 0);

	_DC->IASetInputLayout(_LInput);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::SetPixelShader(
	ID3D11DeviceContext* _DC)
{
	if (!*this)return;

	auto Tmp = static_cast<ID3D11PixelShader*>(Shader);

	_DC->PSSetShader(Tmp, nullptr, 0);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::SetGeometryShader(
	ID3D11DeviceContext* _DC)
{
	if (!*this)return;

	auto Tmp = static_cast<ID3D11GeometryShader*>(Shader);

	_DC->GSSetShader(Tmp, nullptr, 0);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::SetComputeShader(
	ID3D11DeviceContext* _DC)
{
	if (!*this)return;

	auto Tmp = static_cast<ID3D11ComputeShader*>(Shader);

	_DC->CSSetShader(Tmp, nullptr, 0);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::SetDomainShader(
	ID3D11DeviceContext* _DC)
{
	if (!*this)return;

	auto Tmp = static_cast<ID3D11DomainShader*>(Shader);

	_DC->DSSetShader(Tmp, nullptr, 0);
}

///////////////////////////////////////////////////////////////////////////////////////
//ChVertexShader11メソッド
///////////////////////////////////////////////////////////////////////////////////////

void VertexShader11::Init(
	ID3D11Device* _Device
	, const D3D11_INPUT_ELEMENT_DESC* _Desc
	, const unsigned long _DescNum
	, const void* _Binary
	, const unsigned long _BinarySize)
{

	CreateVertexShader(_Device, &LInput, _Desc, _DescNum, _Binary, _BinarySize);
}

///////////////////////////////////////////////////////////////////////////////////

void VertexShader11::Release()
{
	ShaderObject11::Release();

	if (ChPtr::NotNullCheck(LInput))
	{
		LInput->Release();
		LInput = nullptr;
	}

}

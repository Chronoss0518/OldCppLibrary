
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

	if (ChPtr::NotNullCheck(shader))
	{
		shader->Release();
		shader = nullptr;
	}

	SetInitFlg(false);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::CreateVertexShader(
	ID3D11Device* _device
	, ID3D11InputLayout** _lInput
	, const D3D11_INPUT_ELEMENT_DESC* _desc
	, const unsigned long _descNum
	, const void* _binary
	, const unsigned long _binarySize
)
{
	if (ChPtr::NullCheck(_device))return;
	if (ChPtr::NullCheck(_binary))return;

	Release();

	ID3D11VertexShader* tmp;

	_device->CreateVertexShader(_binary, _binarySize, nullptr, &tmp);

	shader = tmp;

	_device->CreateInputLayout(_desc, _descNum, _binary, _binarySize, _lInput);

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::CreatePixelShader(
	ID3D11Device* _device
	, const void* _binary
	, const unsigned long _binarySize
)
{
	if (ChPtr::NullCheck(_device))return;
	if (ChPtr::NullCheck(_binary))return;

	Release();

	ID3D11PixelShader* tmp;

	_device->CreatePixelShader(_binary, _binarySize, nullptr, &tmp);

	shader = tmp;

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::CreateGeometryShader(
	ID3D11Device* _device
	, const void* _binary
	, const unsigned long _binarySize
)
{
	if (ChPtr::NullCheck(_device))return;
	if (ChPtr::NullCheck(_binary))return;

	Release();

	ID3D11GeometryShader* tmp;

	_device->CreateGeometryShader(_binary, _binarySize, nullptr, &tmp);

	shader = tmp;

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::CreateComputeShader(
	ID3D11Device* _device
	, const void* _binary
	, const unsigned long _binarySize
)
{
	if (ChPtr::NullCheck(_device))return;
	if (ChPtr::NullCheck(_binary))return;

	Release();

	ID3D11ComputeShader* tmp;

	_device->CreateComputeShader(_binary, _binarySize, nullptr, &tmp);

	shader = tmp;

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::CreateDomainShader(
	ID3D11Device* _device
	, const void* _binary
	, const unsigned long _binarySize
)
{

	if (ChPtr::NullCheck(_device))return;
	if (ChPtr::NullCheck(_binary))return;

	Release();

	ID3D11DomainShader* tmp;

	_device->CreateDomainShader(_binary, _binarySize, nullptr, &tmp);

	shader = tmp;

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::SetVertexShader(
	ID3D11DeviceContext* _DC
	, ID3D11InputLayout* _lInput)
{
	if (!*this)return;

	auto tmp = static_cast<ID3D11VertexShader*>(shader);

	_DC->VSSetShader(tmp, nullptr, 0);

	_DC->IASetInputLayout(_lInput);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::SetPixelShader(
	ID3D11DeviceContext* _DC)
{
	if (!*this)return;

	auto tmp = static_cast<ID3D11PixelShader*>(shader);

	_DC->PSSetShader(tmp, nullptr, 0);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::SetGeometryShader(
	ID3D11DeviceContext* _DC)
{
	if (!*this)return;

	auto tmp = static_cast<ID3D11GeometryShader*>(shader);

	_DC->GSSetShader(tmp, nullptr, 0);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::SetComputeShader(
	ID3D11DeviceContext* _DC)
{
	if (!*this)return;

	auto tmp = static_cast<ID3D11ComputeShader*>(shader);

	_DC->CSSetShader(tmp, nullptr, 0);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderObject11::SetDomainShader(
	ID3D11DeviceContext* _DC)
{
	if (!*this)return;

	auto tmp = static_cast<ID3D11DomainShader*>(shader);

	_DC->DSSetShader(tmp, nullptr, 0);
}

///////////////////////////////////////////////////////////////////////////////////////
//ChVertexShader11メソッド
///////////////////////////////////////////////////////////////////////////////////////

void VertexShader11::Init(
	ID3D11Device* _device
	, const D3D11_INPUT_ELEMENT_DESC* _desc
	, const unsigned long _descNum
	, const void* _binary
	, const unsigned long _binarySize)
{

	CreateVertexShader(_device, &lInput, _desc, _descNum, _binary, _binarySize);
}

///////////////////////////////////////////////////////////////////////////////////

void VertexShader11::Release()
{
	ShaderObject11::Release();

	if (ChPtr::NotNullCheck(lInput))
	{
		lInput->Release();
		lInput = nullptr;
	}

}

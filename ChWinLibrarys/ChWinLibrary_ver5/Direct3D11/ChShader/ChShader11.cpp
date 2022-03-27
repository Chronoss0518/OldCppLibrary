
#include<windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"


#include"../ChTexture/ChTexture11.h"
#include"../ChMesh/ChMesh11.h"
#include"../ChPolygonBoard/ChPolygonBoard11.h"
#include"../ChSprite/ChSprite11.h"
#include"ChShader11.h"

using namespace ChD3D11;

//ChStd::FPOINT ShaderController11::windSize = ChStd::FPOINT(1280.0f, 720.0f);

///////////////////////////////////////////////////////////////////////////////////////
//ChShaderController11メソッド
///////////////////////////////////////////////////////////////////////////////////////

void ShaderController11::InitShader()
{

	{
#include"MBVShader.inc"

		D3D11_INPUT_ELEMENT_DESC Decl[14];

		Decl[0] = { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[1] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[2] = { "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[3] = { "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[4] = { "NORMAL",  1, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[5] = { "BLENDINDEX",  0, DXGI_FORMAT_R32G32B32A32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[6] = { "BLENDINDEX",  1, DXGI_FORMAT_R32G32B32A32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[7] = { "BLENDINDEX",  2, DXGI_FORMAT_R32G32B32A32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[8] = { "BLENDINDEX",  3, DXGI_FORMAT_R32G32B32A32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[9] = { "BLENDWEIGHT",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[10] = { "BLENDWEIGHT",  1, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[11] = { "BLENDWEIGHT",  2, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[12] = { "BLENDWEIGHT",  3, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[13] = { "BLENDINDEX",  4, DXGI_FORMAT_R32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

		bvModel.Init(device,Decl, 14, main, sizeof(main));

		//VSInputElements Elements;

		//Elements.Add(Semantics::Position, DXGI_FORMAT_R32G32B32_FLOAT);
		//Elements.Add(Semantics::Normal, DXGI_FORMAT_R32G32B32_FLOAT);
		//Elements.Add(Semantics::Normal, DXGI_FORMAT_R32G32B32_FLOAT);
		//Elements.Add(Semantics::Color, DXGI_FORMAT_R32G32B32A32_FLOAT);
		//Elements.Add(Semantics::TexCoord, DXGI_FORMAT_R32G32_FLOAT);
		//Elements.Add(Semantics::TexCoord, DXGI_FORMAT_R32_FLOAT);
		//Elements.Add(Semantics::BlendIndex, DXGI_FORMAT_R32G32B32A32_UINT);
		//Elements.Add(Semantics::BlendIndex, DXGI_FORMAT_R32G32B32A32_UINT);
		//Elements.Add(Semantics::BlendIndex, DXGI_FORMAT_R32G32B32A32_UINT);
		//Elements.Add(Semantics::BlendIndex, DXGI_FORMAT_R32G32B32A32_UINT);
		//Elements.Add(Semantics::BlendWeight, DXGI_FORMAT_R32G32B32A32_FLOAT);
		//Elements.Add(Semantics::BlendWeight, DXGI_FORMAT_R32G32B32A32_FLOAT);
		//Elements.Add(Semantics::BlendWeight, DXGI_FORMAT_R32G32B32A32_FLOAT);
		//Elements.Add(Semantics::BlendWeight, DXGI_FORMAT_R32G32B32A32_FLOAT);
		//Elements.Add(Semantics::BlendIndex, DXGI_FORMAT_R32_UINT);

		//bvModel.CreateVertexShader(Elements.GetDesc(), Elements.GetCount(), main, sizeof(main));

	}

	{
#include"PTVShader.inc"

		D3D11_INPUT_ELEMENT_DESC Decl[4];


		Decl[0] = { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[1] = { "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[3] = { "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };


		pvTex.Init(device,Decl, 4, main, sizeof(main));

	}

	{
#include"MBPShader.inc"


		bpModel.Init(device,main, sizeof(main));

	}


	{
#include"STVShader.inc"

		D3D11_INPUT_ELEMENT_DESC Decl[3];

		//device->CreateVertexShader(&main, sizeof(main), nullptr, &spvTex);

		Decl[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };


		spvTex.Init(device,Decl, 3, main, sizeof(main));

		//device->CreateInputLayout(SpDecl, ARRAYSIZE(SpDecl), &main, sizeof(main), &SpILayout);

	}

	{
#include"TPShader.inc"
		
		bpTex.Init(device,&main, sizeof(main));

		//device->CreatePixelShader(&main, sizeof(main), nullptr, &bpTex);
	}

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Init(
	DirectX3D11& _chDevice
	, const ChVec2& _windSize)
{
	if (!_chDevice.IsInit())return;

	Init(_chDevice.GetDevice(), _chDevice.GetDC(), _chDevice.GetSC(), _windSize.w, _windSize.h);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Init(
	DirectX3D11& _chDevice
	, const float& _windWitdh
	, const float& _windHeight)
{
	if (!_chDevice.IsInit())return;

	Init(_chDevice.GetDevice(), _chDevice.GetDC(), _chDevice.GetSC(), _windWitdh, _windHeight);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Init(
	ID3D11Device* _device
	, ID3D11DeviceContext* _dc
	, IDXGISwapChain* _SC
	, const ChVec2& _windSize) 
{
	Init(_device, _dc, _SC, _windSize.w, _windSize.h);

}


///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Init(
	ID3D11Device* _device
	, ID3D11DeviceContext* _dc
	, IDXGISwapChain* _SC
	, const float& _width
	, const float& _height)
{

	if (ChPtr::NullCheck(_device))return;
	if (ChPtr::NullCheck(_dc))return;
	if (ChPtr::NullCheck(_SC))return;

	device = (_device);
	dc = (_dc);
	
	InitShader();

	whiteTex.CreateColorTexture(device, ChVec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 1);

	normalTex.CreateColorTexture(device, ChVec4(0.5f, 1.0f, 0.5f, 1.0f), 1, 1);

	bdObject.projMat.CreateProjectionMat(
		ChMath::ToRadian(60.0f)
		, _width
		, _height
		, 1.0f
		, 1000.0f);

	bdObject.viewMat.CreateViewMat(
		ChVec3(0.0f, 0.0f, -1.0f)
		, ChVec3(0.0f, 0.0f, 1.0f)
		, ChVec3(0.0f, 1.0f, 0.0f));

	bdObject.windSize = ChVec4(_width, _height, 0.0f, 0.0f);

	BaseDataUpdate();

	dsBuffer.CreateDepthBuffer(_device, _width, _height);


	//描画方法//
	D3D11_RASTERIZER_DESC rasteriserDesc
	{
		fill
		,cull
		,true
		,0
		,0.0f
		,0.0f
		,false
		,false
		,false
		,false
	};

	device->CreateRasterizerState(&rasteriserDesc, &rasteriser);

	dc->RSSetState(rasteriser);

	out3D.CreateRenderTarget(
		_device,
		static_cast<unsigned long>(_width),
		static_cast<unsigned long>(_height));

	out2D.CreateRenderTarget(
		_device,
		static_cast<unsigned long>(_width),
		static_cast<unsigned long>(_height));

	outSprite.Init(device);

	window.Init(_device, _SC);

	window.SetSwapEffect(DXGI_SWAP_EFFECT_DISCARD);

	view.SetDrawDepth(0.0f, 1.0f);
	view.SetWindPos(ChVec2(0.0f, 0.0f));
	view.SetWindSize(ChVec2(_width, _height));

	lightDatas.Init(_device);



	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Release()
{
	whiteTex.Release();
	normalTex.Release();

	lightDatas.Release();
	window.Release();

	if (ChPtr::NotNullCheck(baseData))
	{
		baseData->Release();
		baseData = nullptr;
	}

	if (ChPtr::NotNullCheck(charaData))
	{
		charaData->Release();
		charaData = nullptr;
	}

	if (ChPtr::NotNullCheck(polygonData))
	{
		polygonData->Release();
		polygonData = nullptr;
	}

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::SetRenderTarget(Texture11& _tex)
{
	if (!*this)return;
	if (drawFlg)return;


	renderTargets.push_back(const_cast<ID3D11RenderTargetView*>(_tex.GetRTView()));

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::SetDrawDatas()
{

	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (rasteriserUpdate)
	{
		rasteriser->Release();

		//描画方法//
		D3D11_RASTERIZER_DESC RasteriserDesc
		{
			fill
			,cull
			,true
			,0
			,0.0f
			,0.0f
			,false
			,false
			,false
			,false
		};


		device->CreateRasterizerState(&RasteriserDesc, &rasteriser);

		dc->RSSetState(rasteriser);

		rasteriserUpdate = false;

	}


	dc->RSSetState(rasteriser);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::DrawStart()
{

	if (!*this)return;
	if (drawFlg)return;


	if (!renderTargets.empty())
	{
		tmpView = &renderTargets[0];
		dc->OMSetRenderTargets(renderTargets.size(), tmpView, nullptr);
		dc->ClearRenderTargetView(renderTargets[0], backColor.val.GetVal());
		rtDrawFlg = true;
	}
	else
	{
		//window.SetDrawData(dc, dsBuffer.GetDSView());

		window.ClearView(dc, backColor);

		dsBuffer.ClearDepthBuffer(dc);

		ChVec4 tmpCol = ChVec4(0.0f, 0.0f, 0.0f,0.0f);

		dc->ClearRenderTargetView(out3D.GetRTView(), backColor.val.GetVal());
		dc->ClearRenderTargetView(out2D.GetRTView(), tmpCol.val.GetVal());

		out3D.SetDrawData(dc, 12);

		rtDrawFlg = false;
	}

	view.SetDrawData(dc);

	lightDatas.SetPSDrawData(dc);

	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	SetDrawDatas();

	//bdObject.projMat = bdObject.projMat.Transpose();
	//bdObject.viewMat = bdObject.viewMat.Transpose();

	if (bdUpdateFlg)
	{

		dc->UpdateSubresource(baseData, 0, nullptr, &bdObject, 0, 0);

		bdUpdateFlg = false;
	}

	dc->VSSetConstantBuffers(0, 1, &baseData);

	dc->PSSetConstantBuffers(0, 1, &baseData);

	drawFlg = true;


}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::DrawEnd()
{

	if (!*this)return;
	if (!drawFlg)return;

	if (ChPtr::NullCheck(device))return;

	drawFlg = false;

	if (rtDrawFlg)return;
	

	window.SetDrawData(dc, nullptr);


	spvTex.SetShader(dc);

	bpTex.SetShader(dc);


	dc->UpdateSubresource(polygonData, 0, nullptr, &pdObject, 0, 0);

	dc->VSSetConstantBuffers(1, 1, &polygonData);
	dc->PSSetConstantBuffers(1, 1, &polygonData);

	out3D.SetDrawData(dc, 0);

	outSprite.SetDrawData(dc);

	spvTex.SetShader(dc);

	bpTex.SetShader(dc);

	dc->UpdateSubresource(polygonData, 0, nullptr, &pdObject, 0, 0);

	dc->VSSetConstantBuffers(1, 1, &polygonData);
	dc->PSSetConstantBuffers(1, 1, &polygonData);

	out2D.SetDrawData(dc, 0);

	outSprite.SetDrawData(dc);

	// バックバッファをプライマリバッファにコピー
	window.Draw();

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Draw(
	Mesh11& _Mesh
	, const ChMat_11& _mat)
{

	if (!*this)return;
	if (!drawFlg)return;
	if (!_Mesh.IsMesh())return;


	cdObject.modelMat = _mat.Transpose();

	cdObject.modelMat = _mat;

	bvModel.SetShader(dc);

	bpModel.SetShader(dc);

	dc->UpdateSubresource(charaData, 0, nullptr, &cdObject, 0, 0);

	dc->VSSetConstantBuffers(1, 1, &charaData);
	dc->PSSetConstantBuffers(1, 1, &charaData);

	if (!rtDrawFlg)
	{
		ID3D11RenderTargetView* tmp = out3D.GetRTView();
		dc->OMSetRenderTargets(1, &tmp, dsBuffer.GetDSView());

	}

	_Mesh.SetDrawData(dc);

}

///////////////////////////////////////////////////////////////////////////////////

//Mesh描画用関数//
void ShaderController11::DrawOutLine(
	Mesh11& _Mesh
	, const ChVec4& _Color
	, const ChMat_11& _mat
	, const float _Size)
{
	if (!*this)return;
	if (_Size < 0.0f)return;
	if (!drawFlg)return;
	if (_Mesh.IsMesh())return;


	if (!rtDrawFlg)
	{
		ID3D11RenderTargetView* tmp = out3D.GetRTView();
		dc->OMSetRenderTargets(1, &tmp, dsBuffer.GetDSView());

	}

	D3D11_CULL_MODE tmpCull = GetCullMode();
	SetCullMode(D3D11_CULL_MODE::D3D11_CULL_FRONT);

	bvModel.SetShader(dc);

	bpModel.SetShader(dc);

	SetCullMode(tmpCull);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Draw(
	ChD3D11::Texture11& _tex
	, PolygonBoard11& _porygon
	, const ChMat_11& _mat)
{
	if (!*this)return;
	if (!drawFlg)return;

	if (!rtDrawFlg)
	{
		ID3D11RenderTargetView* tmp = out3D.GetRTView();
		dc->OMSetRenderTargets(1, &tmp, dsBuffer.GetDSView());

	}

	//cdObject.modelMat = _mat.Transpose();
	cdObject.modelMat = _mat;

	ChD3D11::Texture11* drawTex = &_tex;

	if (!drawTex->IsTex())drawTex = &whiteTex;

	pvTex.SetShader(dc);

	bpModel.SetShader(dc);

	dc->UpdateSubresource(charaData, 0, nullptr, &cdObject, 0, 0);

	dc->VSSetConstantBuffers(1, 1, &charaData);
	dc->PSSetConstantBuffers(1, 1, &charaData);

	drawTex->SetDrawData(dc, 0);

	_porygon.SetDrawData(dc);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Draw(
	ChD3D11::Texture11& _tex
	, Sprite11& _sprite
	, const ChMat_11& _mat)
{

	if (!*this)return;
	if (!drawFlg)return;

	if (!rtDrawFlg)
	{
		ID3D11RenderTargetView* tmp = out2D.GetRTView();
		dc->OMSetRenderTargets(1, &tmp, nullptr);

		out3D.SetDrawData(dc, 12);
	}

	//pdObject.modelMat = _mat.Transpose();
	pdObject.modelMat = _mat;

	ChD3D11::Texture11* drawTex = &_tex;

	if (!drawTex->IsTex())drawTex = &whiteTex;

	spvTex.SetShader(dc);

	bpTex.SetShader(dc);

	dc->UpdateSubresource(polygonData, 0, nullptr, &pdObject, 0, 0);

	dc->VSSetConstantBuffers(1, 1, &polygonData);
	dc->PSSetConstantBuffers(1, 1, &polygonData);

	drawTex->SetDrawData(dc, 0);

	_sprite.SetDrawData(dc);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::BaseDataUpdate()
{



	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	desc.ByteWidth = sizeof(BaseDatas);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	device->CreateBuffer(&desc, nullptr, &baseData);

	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	desc.ByteWidth = sizeof(CharaDatas);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	device->CreateBuffer(&desc, nullptr, &charaData);

	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	desc.ByteWidth = sizeof(PolygonDatas);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	device->CreateBuffer(&desc, nullptr, &polygonData);
}

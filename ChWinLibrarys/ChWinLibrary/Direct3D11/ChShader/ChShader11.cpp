
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"
//
//#include"../ChTexture/ChBaseTexture11.h"
//#include"../ChMesh/ChBaseMesh11.h"
//#include"../ChLight/ChLight11.h"
#include"../ChTexture/ChTexture11.h"
#include"../ChMesh/ChMesh11.h"
#include"../ChPolygonBoard/ChPolygonBoard11.h"
#include"../ChSprite/ChSprite11.h"
#include"ChShader11.h"

using namespace ChD3D11;

//ChStd::FPOINT ShaderController11::WindSize = ChStd::FPOINT(1280.0f, 720.0f);

///////////////////////////////////////////////////////////////////////////////////////
//ChShaderController11メソッド
///////////////////////////////////////////////////////////////////////////////////////

void ShaderController11::InitShader()
{

	{
#include"MBVShader.inc"

		D3D11_INPUT_ELEMENT_DESC Decl[15];

		Decl[0] = { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[1] = { "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[2] = { "NORMAL",  1, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[3] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[4] = { "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[5] = { "TEXCOORD",  1, DXGI_FORMAT_R32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[6] = { "BLENDINDEX",  0, DXGI_FORMAT_R32G32B32A32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[7] = { "BLENDINDEX",  1, DXGI_FORMAT_R32G32B32A32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[8] = { "BLENDINDEX",  2, DXGI_FORMAT_R32G32B32A32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[9] = { "BLENDINDEX",  3, DXGI_FORMAT_R32G32B32A32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[10] = { "BLENDWEIGHT",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[11] = { "BLENDWEIGHT",  1, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[12] = { "BLENDWEIGHT",  2, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[13] = { "BLENDWEIGHT",  3, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[14] = { "BLENDINDEX",  4, DXGI_FORMAT_R32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

		BVModel.CreateVertexShader(Decl, 15, main, sizeof(main));

	}

	{
#include"PTVShader.inc"

		D3D11_INPUT_ELEMENT_DESC Decl[4];


		Decl[0] = { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[1] = { "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[3] = { "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };


		PoVTex.CreateVertexShader(Decl, 4, main, sizeof(main));

	}

	{
#include"MBPShader.inc"


		BPModel.CreatePixelShader(main, sizeof(main));

	}


	{
#include"STVShader.inc"

		D3D11_INPUT_ELEMENT_DESC Decl[3];

		//Device->CreateVertexShader(&main, sizeof(main), nullptr, &SpVTex);

		Decl[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };


		SpVTex.CreateVertexShader(Decl, 3, main, sizeof(main));

		//Device->CreateInputLayout(SpDecl, ARRAYSIZE(SpDecl), &main, sizeof(main), &SpILayout);

	}

	{
#include"TPShader.inc"
		
		BPTex.CreatePixelShader(&main, sizeof(main));

		//Device->CreatePixelShader(&main, sizeof(main), nullptr, &BPTex);
	}

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Init(
	ID3D11Device* _Device
	, ID3D11DeviceContext* _DC
	, IDXGISwapChain* _SC
	, const float& _WindWidth
	, const float& _WindHeight) {

	if (ChPtr::NullCheck(_Device))return;
	if (ChPtr::NullCheck(_DC))return;
	if (ChPtr::NullCheck(_SC))return;

	Device = (_Device);
	DC = (_DC);
	Window = (_SC);

	SpVTex.Init(_Device);
	BPTex.Init(_Device);

	BVModel.Init(_Device);
	BPModel.Init(_Device);
	PoVTex.Init(_Device);
	//CVModel.Init(_Device);
	//CPModel.Init(_Device);

	InitShader();

	ViewPort.MaxDepth = 1.0f;
	ViewPort.MinDepth = 0.0f;
	ViewPort.TopLeftX = 0.0f;
	ViewPort.TopLeftY = 0.0f;
	ViewPort.Width = _WindWidth;
	ViewPort.Height = _WindHeight;

	WhiteTex.CreateColorTexture(Device,ChVec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 1);

	NormalTex.CreateColorTexture(Device, ChVec4(0.5f, 1.0f, 0.5f, 1.0f), 1, 1);

	BDObject.ProjMat.CreateProjectionMat(
		ChMath::ToRadian(60.0f)
		, _WindWidth
		, _WindHeight
		, 1.0f
		, 1000.0f);

	BDObject.ViewMat.CreateViewMat(
		ChVec3(0.0f, 0.0f, -1.0f)
		, ChVec3(0.0f, 0.0f, 1.0f)
		, ChVec3(0.0f, 1.0f, 0.0f));

	BDObject.WindSize = ChVec4(_WindWidth, _WindHeight, 0.0f, 0.0f);

	BaseDataUpdate();

	{
		ChVec4 TmpCol[256];

		for (unsigned long i = 0; i < 256; i++)
		{
			TmpCol[i] = ChVec4(i / 256.0f, i / 256.0f, i / 256.0f, 1.0f);
		}

		LightEffectTex.CreateColorTexture(Device, TmpCol, 256, 1);

	}

	{

		ID3D11Texture2D* pBackBuffer;

		_SC->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		_Device->CreateRenderTargetView(pBackBuffer, nullptr, &BBTargetView);

		pBackBuffer->Release();

	}

	DSBuffer.CreateDepthBuffer(Device, _WindWidth, _WindHeight);

	//描画方法//
	D3D11_RASTERIZER_DESC RasteriserDesc
	{
		Fill
		,Cull
		,true
		,0
		,0.0f
		,0.0f
		,false
		,false
		,false
		,false
	};

	Device->CreateRasterizerState(&RasteriserDesc, &Rasteriser);

	DC->RSSetState(Rasteriser);

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Release()
{
	WhiteTex.Release();
	NormalTex.Release();
	LightEffectTex.Release();

	if (ChPtr::NotNullCheck(BBTargetView))
	{
		BBTargetView->Release();
		BBTargetView = nullptr;
	}

	if (ChPtr::NotNullCheck(BaseData))
	{
		BaseData->Release();
		BaseData = nullptr;
	}

	if (ChPtr::NotNullCheck(CharaData))
	{
		CharaData->Release();
		CharaData = nullptr;
	}

	if (ChPtr::NotNullCheck(PolygonData))
	{
		PolygonData->Release();
		PolygonData = nullptr;
	}

	MyLightTex.Release();

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::SetRenderTarget(ChPtr::Shared<Texture11> _Tex)
{
	if (!*this)return;
	if (DrawFlg)return;

	if (_Tex == nullptr)return;

	RenderTargets.push_back(const_cast<ID3D11RenderTargetView*>(_Tex->GetRTView()));

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::SetDrawDatas()
{

	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (RasteriserUpdate)
	{
		Rasteriser->Release();

		//描画方法//
		D3D11_RASTERIZER_DESC RasteriserDesc
		{
			Fill
			,Cull
			,true
			,0
			,0.0f
			,0.0f
			,false
			,false
			,false
			,false
		};


		Device->CreateRasterizerState(&RasteriserDesc, &Rasteriser);

		DC->RSSetState(Rasteriser);

		RasteriserUpdate = false;

	}


	DC->RSSetState(Rasteriser);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::IsLight(const ChStd::Bool _Flg)
{
	LightUseFlg = _Flg;

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::DrawStart()
{

	if (!*this)return;
	if (DrawFlg)return;


	if (!RenderTargets.empty())
	{
		TmpView = &RenderTargets[0];
		DC->OMSetRenderTargets(RenderTargets.size(), TmpView, nullptr);
		DC->ClearRenderTargetView(RenderTargets[0], BackColor.Val.GetVal());
		RTDrawFlg = true;
	}
	else
	{

		DC->OMSetRenderTargets(1, &BBTargetView, DSBuffer.GetDSView());
		DC->ClearRenderTargetView(BBTargetView, BackColor.Val.GetVal());
		DSBuffer.ClearDepthBuffer(DC);

		RTDrawFlg = false;
	}

	DC->RSSetViewports(1, &ViewPort);

	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Device->BeginScene();

	SetDrawDatas();

	//BDObject.ProjMat = BDObject.ProjMat.Transpose();
	//BDObject.ViewMat = BDObject.ViewMat.Transpose();

	if (BDUpdateFlg)
	{

		DC->UpdateSubresource(BaseData, 0, nullptr, &BDObject, 0, 0);

		BDUpdateFlg = false;


	}

	DC->VSSetConstantBuffers(0, 1, &BaseData);

	DC->PSSetConstantBuffers(0, 1, &BaseData);

	DrawFlg = true;


}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::DrawEnd()
{

	if (!*this)return;
	if (!DrawFlg)return;

	if (ChPtr::NullCheck(Device))return;


	//Device->EndScene();

	DrawFlg = false;


	if (RTDrawFlg)return;

	// バックバッファをプライマリバッファにコピー
	Window->Present(BufferDatas, 0);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Draw(
	Mesh11& _Mesh
	, const ChMat_11& _Mat)
{

	if (!*this)return;
	if (!DrawFlg)return;
	if (!_Mesh.IsMesh())return;

	//CDObject.ModelMat = _Mat.Transpose();
	CDObject.ModelMat = _Mat;

	BVModel.SetShader(DC);

	BPModel.SetShader(DC);

	DC->UpdateSubresource(CharaData, 0, nullptr, &CDObject, 0, 0);

	DC->VSSetConstantBuffers(1, 1, &CharaData);
	DC->PSSetConstantBuffers(1, 1, &CharaData);

	_Mesh.SetDrawData(DC);

}

///////////////////////////////////////////////////////////////////////////////////

//Mesh描画用関数//
void ShaderController11::DrawToons(
	Mesh11& _Mesh
	, const ChVec4& _Color
	, const ChMat_11& _Mat
	, const float _Size)
{
	if (!*this)return;
	if (_Size < 0.0f)return;
	if (!DrawFlg)return;
	if (_Mesh.IsMesh())return;


	D3D11_CULL_MODE TmpCull = GetCullMode();
	SetCullMode(D3D11_CULL_MODE::D3D11_CULL_FRONT);

	BVModel.SetShader(DC);

	BPModel.SetShader(DC);

	SetCullMode(TmpCull);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Draw(
	ChD3D11::Texture11& _Tex
	, PolygonBoard11& _Polygon
	, const ChMat_11& _Mat)
{
	if (!*this)return;
	if (!DrawFlg)return;

	//CDObject.ModelMat = _Mat.Transpose();
	CDObject.ModelMat = _Mat;

	ChD3D11::Texture11* DrawTex = &_Tex;

	if (!DrawTex->IsTex())DrawTex = &WhiteTex;

	PoVTex.SetShader(DC);

	BPModel.SetShader(DC);

	DC->UpdateSubresource(CharaData, 0, nullptr, &CDObject, 0, 0);

	DC->VSSetConstantBuffers(1, 1, &CharaData);
	DC->PSSetConstantBuffers(1, 1, &CharaData);

	DrawTex->SetDrawData(DC, 0);

	_Polygon.SetDrawData(DC);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Draw(
	ChD3D11::Texture11& _Tex
	, Sprite11& _Sprite
	, const ChMat_11& _Mat)
{

	if (!*this)return;
	if (!DrawFlg)return;

	//PDObject.ModelMat = _Mat.Transpose();
	PDObject.ModelMat = _Mat;

	ChD3D11::Texture11* DrawTex = &_Tex;

	if (!DrawTex->IsTex())DrawTex = &WhiteTex;

	SpVTex.SetShader(DC);

	BPTex.SetShader(DC);


	DC->UpdateSubresource(PolygonData, 0, nullptr, &PDObject, 0, 0);

	DC->VSSetConstantBuffers(1, 1, &PolygonData);
	DC->PSSetConstantBuffers(1, 1, &PolygonData);

	DrawTex->SetDrawData(DC, 0);

	_Sprite.SetDrawData(DC);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::CreateLightPowTex(const std::string& _LightPowTexName)
{

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::SetLightFunction()
{

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::BaseDataUpdate()
{



	D3D11_BUFFER_DESC Desc;
	ZeroMemory(&Desc, sizeof(D3D11_BUFFER_DESC));

	Desc.ByteWidth = sizeof(BaseDatas);
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.CPUAccessFlags = 0;
	Desc.MiscFlags = 0;
	Desc.StructureByteStride = 0;

	Device->CreateBuffer(&Desc, nullptr, &BaseData);

	ZeroMemory(&Desc, sizeof(D3D11_BUFFER_DESC));

	Desc.ByteWidth = sizeof(CharaDatas);
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.CPUAccessFlags = 0;
	Desc.MiscFlags = 0;
	Desc.StructureByteStride = 0;

	Device->CreateBuffer(&Desc, nullptr, &CharaData);

	ZeroMemory(&Desc, sizeof(D3D11_BUFFER_DESC));

	Desc.ByteWidth = sizeof(PolygonDatas);
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.CPUAccessFlags = 0;
	Desc.MiscFlags = 0;
	Desc.StructureByteStride = 0;

	Device->CreateBuffer(&Desc, nullptr, &PolygonData);
}

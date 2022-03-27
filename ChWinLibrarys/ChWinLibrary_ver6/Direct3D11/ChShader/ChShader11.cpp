
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"


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

		BVModel.Init(Device,Decl, 14, main, sizeof(main));

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

		//BVModel.CreateVertexShader(Elements.GetDesc(), Elements.GetCount(), main, sizeof(main));

	}

	{
#include"PTVShader.inc"

		D3D11_INPUT_ELEMENT_DESC Decl[4];


		Decl[0] = { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[1] = { "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[3] = { "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };


		PoVTex.Init(Device,Decl, 4, main, sizeof(main));

	}

	{
#include"MBPShader.inc"


		BPModel.Init(Device,main, sizeof(main));

	}


	{
#include"STVShader.inc"

		D3D11_INPUT_ELEMENT_DESC Decl[3];

		//Device->CreateVertexShader(&main, sizeof(main), nullptr, &SpVTex);

		Decl[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
		Decl[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };


		SpVTex.Init(Device,Decl, 3, main, sizeof(main));

		//Device->CreateInputLayout(SpDecl, ARRAYSIZE(SpDecl), &main, sizeof(main), &SpILayout);

	}

	{
#include"TPShader.inc"
		
		BPTex.Init(Device,&main, sizeof(main));

		//Device->CreatePixelShader(&main, sizeof(main), nullptr, &BPTex);
	}

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Init(
	DirectX3D11& _ChDevice
	, const ChVec2& _WindSize)
{
	if (!_ChDevice.IsInit())return;

	Init(_ChDevice.GetDevice(), _ChDevice.GetDC(), _ChDevice.GetSC(), _WindSize.w, _WindSize.h);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Init(
	DirectX3D11& _ChDevice
	, const float& _WindWitdh
	, const float& _WindHeight)
{
	if (!_ChDevice.IsInit())return;

	Init(_ChDevice.GetDevice(), _ChDevice.GetDC(), _ChDevice.GetSC(), _WindWitdh, _WindHeight);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Init(
	ID3D11Device* _Device
	, ID3D11DeviceContext* _DC
	, IDXGISwapChain* _SC
	, const ChVec2& _WindSize) 
{
	Init(_Device, _DC, _SC, _WindSize.w, _WindSize.h);

}


///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Init(
	ID3D11Device* _Device
	, ID3D11DeviceContext* _DC
	, IDXGISwapChain* _SC
	, const float& _Witdh
	, const float& _Height)
{

	if (ChPtr::NullCheck(_Device))return;
	if (ChPtr::NullCheck(_DC))return;
	if (ChPtr::NullCheck(_SC))return;

	Device = (_Device);
	DC = (_DC);
	
	InitShader();

	WhiteTex.CreateColorTexture(Device, ChVec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 1);

	NormalTex.CreateColorTexture(Device, ChVec4(0.5f, 1.0f, 0.5f, 1.0f), 1, 1);

	BDObject.ProjMat.CreateProjectionMat(
		ChMath::ToRadian(60.0f)
		, _Witdh
		, _Height
		, 1.0f
		, 1000.0f);

	BDObject.ViewMat.CreateViewMat(
		ChVec3(0.0f, 0.0f, -1.0f)
		, ChVec3(0.0f, 0.0f, 1.0f)
		, ChVec3(0.0f, 1.0f, 0.0f));

	BDObject.WindSize = ChVec4(_Witdh, _Height, 0.0f, 0.0f);

	BaseDataUpdate();

	{
		ChVec4 TmpCol[256];

		for (unsigned long i = 0; i < 256; i++)
		{
			TmpCol[i] = ChVec4(i / 256.0f, i / 256.0f, i / 256.0f, 1.0f);
		}

		LightEffectTex.CreateColorTexture(Device, TmpCol, 256, 1);

	}

	DSBuffer.CreateDepthBuffer(_Device, _Witdh, _Height);


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

	//Out3D.CreateRenderTarget(
	//	_Device,
	//	_SC,
	//	static_cast<unsigned long>(_Witdh),
	//	static_cast<unsigned long>(_Height));

	//Out2D.CreateRenderTarget(
	//	_Device,
	//	_SC,
	//	static_cast<unsigned long>(_Witdh),
	//	static_cast<unsigned long>(_Height));

	Window.Init(_Device, _SC);

	Window.SetSwapEffect(DXGI_SWAP_EFFECT_DISCARD);

	View.SetDrawDepth(0.0f, 1.0f);
	View.SetWindPos(ChVec2(0.0f, 0.0f));
	View.SetWindSize(ChVec2(_Witdh, _Height));

	SetInitFlg(true);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Release()
{
	WhiteTex.Release();
	NormalTex.Release();
	LightEffectTex.Release();


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

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::SetRenderTarget(Texture11& _Tex)
{
	if (!*this)return;
	if (DrawFlg)return;


	RenderTargets.push_back(const_cast<ID3D11RenderTargetView*>(_Tex.GetRTView()));

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
		Window.SetDrawData(DC, DSBuffer.GetDSView());

		Window.ClearView(DC, BackColor);

		DSBuffer.ClearDepthBuffer(DC);

		//ChVec4 TmpCol = ChVec4(0.0f, 0.0f, 0.0f,0.0f);

		//DC->ClearRenderTargetView(Out3D.GetRTView(), BackColor.Val.GetVal());
		//DC->ClearRenderTargetView(Out2D.GetRTView(), TmpCol.Val.GetVal());

		RTDrawFlg = false;
	}

	View.SetDrawData(DC);

	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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

	DrawFlg = false;

	if (RTDrawFlg)return;

	// バックバッファをプライマリバッファにコピー
	Window.Draw();

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController11::Draw(
	Mesh11& _Mesh
	, const ChMat_11& _Mat)
{

	if (!*this)return;
	if (!DrawFlg)return;
	if (!_Mesh.IsMesh())return;

	//if (!RTDrawFlg)
	//{
	//	ID3D11RenderTargetView* Tmp = Out3D.GetRTView();
	//	DC->OMSetRenderTargets(1, &Tmp, DSBuffer.GetDSView());
	//}

	CDObject.ModelMat = _Mat.Transpose();

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
void ShaderController11::DrawOutLine(
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

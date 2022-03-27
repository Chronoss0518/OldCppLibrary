
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"
//
//#include"../ChTexture/ChBaseTexture11.h"
//#include"../ChMesh/ChBaseMesh11.h"
//#include"../ChLight/ChLight11.h"
#include"ChShader11.h"



using namespace ChD3D11;

ChStd::FPOINT ShaderController::WindSize = ChStd::FPOINT(1280.0f, 720.0f);

///////////////////////////////////////////////////////////////////////////////////////
//ChShaderControllerメソッド
///////////////////////////////////////////////////////////////////////////////////////

void ShaderController::Init(const ID3D11Device* _d
	, const float& _WindWidth
	, const float& _WindHeight) {

	if (ChPtr::NullCheck(_d))return;

	Device = _d;
	Param = _Param;

	InitShader();

	Device->GetVertexDeclaration(&BaseDec);

	{

		D3DVERTEXELEMENT9 decl[] = {
			{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,     0},
			{0, sizeof(D3DXVECTOR3), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,  0},
			{0, sizeof(D3DXVECTOR3) + sizeof(D3DCOLORVALUE), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
			D3DDECL_END()
		};


		Device->CreateVertexDeclaration(decl, &TVerDec);

	}

	{

		D3DVERTEXELEMENT9 decl[] = {
			{0,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,     0},
			{0, sizeof(D3DXVECTOR4), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,  0},
			{0, sizeof(D3DXVECTOR4) + sizeof(D3DXVECTOR3), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
			D3DDECL_END()
		};


		Device->CreateVertexDeclaration(decl, &MVerDec);

	}

	MakeWhiteTexture();

	MakeNormalMapTexture();

	MakeLightingPowTexture();

	BeforeTex = ChPtr::Make_S<ChTex::Texture9>();

	BeforeTex->CreateMinuColTexture<D3DCOLOR>(Device, D3DCOLOR_ARGB(255, 255, 255, 255));

	SetInitFlg(true);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController::Release()
{
	if (ChPtr::NotNullCheck(BVModel))
	{
		BVModel->Release();
		BVModel = nullptr;
	}
	if (ChPtr::NotNullCheck(BPModel))
	{
		BPModel->Release();
		BPModel = nullptr;
	}

	if (ChPtr::NotNullCheck(CVModel))
	{
		CVModel->Release();
		CVModel = nullptr;
	}
	if (ChPtr::NotNullCheck(CPModel))
	{
		CPModel->Release();
		CPModel = nullptr;
	}

	if (ChPtr::NotNullCheck(SpVTex))
	{
		SpVTex->Release();
		SpVTex = nullptr;
	}
	if (ChPtr::NotNullCheck(PoVTex))
	{
		PoVTex->Release();
		PoVTex = nullptr;
	}
	if (ChPtr::NotNullCheck(BPTex))
	{
		BPTex->Release();
		BPTex = nullptr;
	}

	WhiteTex = nullptr;
	NormalTex = nullptr;
	LightEffectTex = nullptr;

	if (ChPtr::NotNullCheck(BaseDec))
	{
		BaseDec->Release();
		BaseDec = nullptr;
	}
	if (ChPtr::NotNullCheck(TVerDec))
	{
		TVerDec->Release();
		TVerDec = nullptr;
	}
	if (ChPtr::NotNullCheck(MVerDec))
	{
		MVerDec->Release();
		MVerDec = nullptr;
	}

	MyLightTex = nullptr;

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController::SetDrawDatas(const D3DCOLOR&
	_BackColor)
{

	// バックバッファと Z バッファをクリア
	Device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, _BackColor, 1.0f, 0);

	if (ChPtr::NullCheck(Device))return;

	struct MatData
	{
		ChMat_9 ViewMat;
		ChMat_9 ProMat;
	};

	MatData Tmp;



	Device->GetTransform(D3DTS_VIEW, &Tmp.ViewMat);
	Device->GetTransform(D3DTS_PROJECTION, &Tmp.ProMat);

	//ビュー・射影行列セット//
	Device->SetVertexShader(PoVTex);

	Device->SetVertexShaderConstantF(0, (const float*)&Tmp, 8);

	Device->SetVertexShader(CVModel);

	Device->SetVertexShaderConstantF(0, (const float*)&Tmp, 8);

	Device->SetVertexShader(BVModel);

	Device->SetVertexShaderConstantF(0, (const float*)&Tmp, 8);

	ChVec4 TmpPos;

	TmpPos = CamPos;

	TmpPos.w = 0.0f;

	Device->SetPixelShader(BPModel);

	Device->SetPixelShaderConstantF(0, (const float*)&TmpPos, 1);


}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController::IsLight(const ChStd::Bool _Flg)
{
	LightUseFlg = _Flg;

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController::DrawStart(const D3DCOLOR&
	_BackColor)
{
	if (!*this)return;
	if (RTDrawFlg)return;
	if (DrawFlg)return;

	SetDrawDatas(_BackColor);

	Device->BeginScene();

	DrawFlg = true;

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController::DrawEnd()
{
	if (!*this)return;
	if (RTDrawFlg)return;
	if (!DrawFlg)return;

	if (ChPtr::NullCheck(Device))return;


	Device->EndScene();

	DrawFlg = false;

	// バックバッファをプライマリバッファにコピー
	if (FAILED(Device->Present(NULL, NULL, NULL, NULL)))
	{
		Device->Reset(&Param);
	}

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController::DrawMesh(
	const ChPtr::Shared<ChMesh::Mesh9> _Mesh
	, const ChMat_9& _Mat)
{

	if (!*this)return;
	if (!DrawFlg && !RTDrawFlg)return;
	if (_Mesh == nullptr)return;
	if (ChPtr::NullCheck(_Mesh->GetMesh()))return;

	Device->SetVertexShader(BVModel);
	Device->SetPixelShader(BPModel);

	SetLightFunction();


	ChMat_9 TmpMat;


	Device->SetVertexDeclaration(MVerDec);

	for (unsigned long i = 0; i < _Mesh->GetMaterials().size(); i++) {

		TmpMat = _Mesh->GetMaterials()[i]->Mat * _Mat;

		Device->SetVertexShaderConstantF(8, (const float*)&_Mat, 4);

		auto TmpMate = SetMateData(*_Mesh->GetMaterials()[i]);

		Device->SetPixelShaderConstantF(1, (const float*)&TmpMate, 2);


		{

			auto TmpTex = _Mesh->GetTex()[i]->GetTex();

			if (ChPtr::NullCheck(TmpTex))TmpTex = WhiteTex->GetTex();

			Device->SetTexture(0, TmpTex);

		}

		if (!_Mesh->GetNormalTex().empty())
		{
			auto pNormal = _Mesh->GetNormalTex()[i]->GetTex();

			if (ChPtr::NullCheck(pNormal))pNormal = NormalTex->GetTex();

			Device->SetTexture(2, pNormal);

		}
		else
		{
			Device->SetTexture(2, NormalTex->GetTex());
		}

		_Mesh->GetMesh()->DrawSubset(i);
	}

	Device->SetVertexDeclaration(BaseDec);

}

///////////////////////////////////////////////////////////////////////////////////

//Mesh描画用関数//
void ShaderController::DrawMeshContour(
	const ChPtr::Shared<ChMesh::Mesh9> _Mesh
	, const ChStd::COLOR1f& _Color
	, const ChMat_9& _Mat
	, const float _Size)
{
	if (!*this)return;
	if (_Size < 0.0f)return;
	if (!DrawFlg && !RTDrawFlg)return;
	if (_Mesh == nullptr)return;
	if (ChPtr::NullCheck(_Mesh->GetMesh()))return;

	CULL TmpCull = GetCullMode();
	SetCullMode(ChD3D9::CULL::CW);

	Device->SetVertexShader(CVModel);
	Device->SetPixelShader(CPModel);

	ChMat_9 TmpMat;

	Device->SetVertexDeclaration(MVerDec);

	for (unsigned long i = 0; i < _Mesh->GetMaterials().size(); i++) {

		TmpMat = _Mesh->GetMaterials()[i]->Mat * _Mat;

		Device->SetVertexShaderConstantF(8, (const float*)&_Mat, 4);

		ChVec4 TmpVec = ChVec4(_Size, 0.0f, 0.0f, 0.0f);

		Device->SetVertexShaderConstantF(12, (const float*)&_Size, 1);

		Device->SetPixelShaderConstantF(0, (const float*)&_Color, 1);

		_Mesh->GetMesh()->DrawSubset(i);
	}

	Device->SetVertexDeclaration(BaseDec);

	SetCullMode(TmpCull);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController::DrawPolygonBoard(
	const ChPtr::Shared<ChTex::Texture9>& _Tex
	, const VertexData& _Vertex
	, const ChMat_9& _Mat
	, const unsigned int _TriangleCount
)
{

	if (!*this)return;
	if (!DrawFlg && !RTDrawFlg)return;
	if (_Tex == nullptr)return;
	if (_Tex->GetBaseColor().a <= 0.1f)return;

	Device->SetVertexShader(PoVTex);
	Device->SetPixelShader(BPTex);

	//キャラクター移動行列セット//
	Device->SetVertexShaderConstantF(8, (const float*)&_Mat, 4);

	{

		D3DXVECTOR4 TmpVec;
		TmpVec.x = (_Tex->GetBaseColor().r / 255.0f);
		TmpVec.y = (_Tex->GetBaseColor().g / 255.0f);
		TmpVec.z = (_Tex->GetBaseColor().b / 255.0f);
		TmpVec.w = (_Tex->GetBaseColor().a / 255.0f);
		Device->SetPixelShaderConstantF(0, (const float*)&TmpVec, 1);
	}

	//画像セット//
	auto Tex = _Tex->GetTex();

	if (ChPtr::NullCheck(Tex)) Tex = WhiteTex->GetTex();

	Device->SetTexture(0, Tex);

	Device->SetVertexDeclaration(TVerDec);

	Device->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN, _TriangleCount
		, _Vertex.Ver, sizeof(VertexData::Vertex));

	Device->SetVertexDeclaration(BaseDec);

}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController::DrawSprite(
	const ChPtr::Shared<ChTex::Texture9>& _Tex
	, const ChMat_9& _Mat
	, const SpriteData& _SpData)
{

	if (!*this)return;
	if (!DrawFlg && !RTDrawFlg)return;
	if (_Tex == nullptr)return;
	if (_Tex->GetBaseColor().a <= 0.1f)return;

	Device->SetVertexShader(SpVTex);
	Device->SetPixelShader(BPTex);

	//キャラクター移動行列セット//
	Device->SetVertexShaderConstantF(0, (const float*)&_Mat, 4);

	{

		D3DXVECTOR4 TmpVec = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

		TmpVec.x = WindSize.w;
		TmpVec.y = WindSize.h;

		//WindSizeSet//
		Device->SetVertexShaderConstantF(4, (const float*)&TmpVec, 1);

	}


	{

		ChStd::COLOR1f TmpVec;
		TmpVec = _Tex->GetBaseColor();

		Device->SetPixelShaderConstantF(0, (const float*)&TmpVec, 1);
	}

	{

		//画像セット//
		auto Tex = _Tex->GetTex();

		if (ChPtr::NullCheck(Tex)) Tex = WhiteTex->GetTex();

		Device->SetTexture(0, Tex);

	}

	SpriteData TmpSprite = _SpData;

	for (unsigned char i = 0; i < 4; i++)
	{
		TmpSprite.SpData[i].Pos.z = 0.0f;
	}



	Device->SetVertexDeclaration(TVerDec);

	Device->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN, 2
		, TmpSprite.SpData.Ver, sizeof(VertexData::Vertex));

	Device->SetVertexDeclaration(BaseDec);


}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController::CreateLightPowTex(const std::string& _LightPowTexName)
{
	if (_LightPowTexName.length())
	{
		//ChSystem::ErrerMessage("使用する画像のファイル名を入力してください", "警告");

		return;
	}

	MyLightTex = ChTex::BaseTexture9::TextureType(_LightPowTexName.c_str());

	MyLightTex->CreateTexture(_LightPowTexName.c_str(), Device);

	if (MyLightTex->GetTex() == nullptr)
	{

		//ChSystem::ErrerMessage("画像の作成に失敗しました", "警告");

		MyLightTex = nullptr;

		return;
	}


}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController::MakeWhiteTexture()
{
	WhiteTex = ChPtr::Make_S<ChTex::BaseTexture9>();

	WhiteTex->CreateColTexture(Device, D3DCOLOR_ARGB(255, 255, 255, 255));
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController::MakeLightingPowTexture()
{

	LightEffectTex = ChPtr::Make_S<ChTex::BaseTexture9>();

	LightEffectTex->CreateColTexture(Device, D3DCOLOR_ARGB(255, 255, 255, 255), 255, 1);

	unsigned char Col = 0;

	D3DLOCKED_RECT LockRect;
	if (LightEffectTex->InsTex()->LockRect(0, &LockRect, nullptr, 0) != D3D_OK)
	{
		LightEffectTex = nullptr;
		return;
	}
	UINT* pPitch = (UINT*)LockRect.pBits;

	UINT Pitch = LockRect.Pitch / sizeof(UINT);
	for (unsigned int h = 0; h < LightEffectTex->GetOriginalHeight(); h++)
	{
		for (unsigned int w = 0; w < LightEffectTex->GetOriginalWidth(); w++)
		{
			*(pPitch + w) = D3DCOLOR_ARGB(Col, Col, Col, Col);
			Col++;
		}
		pPitch += Pitch;
	}

	LightEffectTex->InsTex()->UnlockRect(0);
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController::MakeNormalMapTexture()
{
	NormalTex = ChPtr::Make_S<ChTex::BaseTexture9>();

	NormalTex->CreateColTexture(Device, D3DCOLOR_ARGB(255, 128, 128, 128));

}

///////////////////////////////////////////////////////////////////////////////////

ShaderController::Material ShaderController::SetMateData(D3DMATERIAL9& _Mate)
{
	Material Tmp;
	Tmp.Dif.a = _Mate.Diffuse.a;
	Tmp.Dif.r = _Mate.Diffuse.r;
	Tmp.Dif.g = _Mate.Diffuse.g;
	Tmp.Dif.b = _Mate.Diffuse.b;

	Tmp.SpeCol.r = _Mate.Specular.r;
	Tmp.SpeCol.g = _Mate.Specular.g;
	Tmp.SpeCol.b = _Mate.Specular.b;

	Tmp.SpePow = _Mate.Power;

	return Tmp;
}

///////////////////////////////////////////////////////////////////////////////////

void ShaderController::SetLightFunction()
{


	Device->SetVertexShader(BVModel);
	Device->SetPixelShader(BPModel);

	{
		auto LightTex = LightEffectTex->GetTex();

		if (ChPtr::NullCheck(LightTex))LightTex = WhiteTex->GetTex();

		if (UseMyLightTex)LightTex = MyLightTex->GetTex();

		Device->SetTexture(1, LightTex);

	}

	{

		Light.Dir.Normalize();

		TmpPLight PLight[7];
		float PLFlg[8];
		for (unsigned char i = 0; i < 7; i++)
		{
			PLFlg[i] = PosLight[i].Flg;
			if (!PosLight[i].Flg)continue;
			if (PosLight[i].Len <= 0.0f)PosLight[i].Flg = false;

			PLFlg[i] = PosLight[i].Flg ? 1.0f : -1.0f;
			PLight[i].Dif = PosLight[i].Dif;
			PLight[i].Len = PosLight[i].Len;
			PLight[i].Pos = PosLight[i].Pos;
		}
		PLFlg[7] = LightUseFlg ? 1.0f : -1.0f;

		Device->SetPixelShaderConstantF(3, (const float*)&Light, 2);

		float TmpFlg[8] =
		{
			PLFlg[0],PLFlg[1],PLFlg[2],PLFlg[3],
			PLFlg[4],PLFlg[5],PLFlg[6],PLFlg[7]
		};

		Device->SetPixelShaderConstantF(5, TmpFlg, 2);
		Device->SetPixelShaderConstantF(7, (const float*)&PLFlg, 14);
	}

}

///////////////////////////////////////////////////////////////////////////////////////
//行列、CameraDataセット//

float4x4 ProjectMat;
float4x4 ViewMat;
float4x4 WorldMat;

float3 CamPos;

///////////////////////////////////////////////////////////////////////////////////////
//SpriteData//

float3 SpPos[4] =
{float3(-1.0f,1.0f,0.0f)
,float3(1.0f,1.0f,0.0f)
,float3(1.0f,-1.0f,0.0f)
,float3(-1.0f,-1.0f,0.0f)};

///////////////////////////////////////////////////////////////////////////////////////
//Material//

struct BaseMaterial
{
	//自己発光
	float4 Deffuse;

	//反射光
	float4 Specula;
	float SpePow;

	//環境光
	float4 Emissive;
};

BaseMaterial Mate =
{
	float4(1.0f,1.0f,1.0f,1.0f)
	,float4(1.0f,1.0f,1.0f,1.0f)
	,1.0f
	,float4(1.0f,1.0f,1.0f,1.0f)
};

///////////////////////////////////////////////////////////////////////////////////////
//TextureAndSumpler//

//使用するテクスチャ
texture TexMap;

sampler S_TexMap = sampler_state
{
	Texture = <TexMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

//使用する法線マップ
texture NormalMap;

sampler S_NormalMap = sampler_state
{
	Texture = <NormalMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

///////////////////////////////////////////////////////////////////////////////////////
//ContourShader(輪郭シェーダ)//

struct Contour
{
	float4 Col;
	float Size;
};

Contour Con = { float4(1.0f,0.0f,0.0f,0.0f),0.0f };

///////////////////////////////////////////////////////////////////////////////////////
//Fog//

struct FogData
{
	int Flg;
	float Density;
	float4 Col;
};

FogData Fog =
{
	0
	, 1.0f
	,float4(1.0f,1.0f,1.0f,1.0f)
};

///////////////////////////////////////////////////////////////////////////////////////
//BaseData//

struct BaseData
{
	float4 Pos:POSITION;//画面上の位置//
	float3 WPos:TEXCOORD1;//3D空間上での位置//
	float2 UVPos:TEXCOORD2;//UV座標
	float3 Normal:TEXCOORD3;
};

struct ConData
{
	float4 Pos:POSITION;//画面上の位置//
	float2 UVPos:TEXCOORD1;//UV座標
};

///////////////////////////////////////////////////////////////////////////////////////
//ProtoTypefunction//

BaseData SetNormalMap(BaseData _BD);

float4 LightCol(BaseData _BD);

float4 PLightCol(BaseData _BD);

///////////////////////////////////////////////////////////////////////////////////////
//BaseVertexShader//

BaseData BVS(
	float4 Pos:POSITION
	, float3 Normal : NORMAL
	, float2 UV : TEXCOORD0
)
{
	BaseData BD;

	BD.Pos = mul(Pos, WorldMat);
	BD.WPos = BD.Pos.xyz;

	BD.Pos = mul(BD.Pos, ViewMat);
	BD.Pos = mul(BD.Pos, ProjectMat);



	//UV座標セット(法線間ピングの位置としても利用)
	BD.UVPos = UV;

	BD.Normal = Normal;


	return BD;
}

///////////////////////////////////////////////////////////////////////////////////////
//BasePixelShader//

float4 BPS(BaseData BD) :COLOR0
{
	BD = SetNormalMap(BD);

	float4 BaseCol;

	BaseCol = tex2D(S_TexMap, BD.UVPos) * Mate.Deffuse;
	//if (BaseCol.a < 0.1f)discard;
	clip(BaseCol.a < 0.1f ? -1.0f : 1.0f);

	BaseCol += PLightCol(BD);


	BaseCol += LightCol(BD);



	return BaseCol;
}

//TechniqueData//
technique BaseTec
{
	pass P0
	{
		vertexshader = compile vs_3_0 BVS();
		pixelshader = compile ps_3_0 BPS();
	}
};

technique CullTec
{
	pass P0
	{
		vertexshader = compile vs_3_0 BVS();
		pixelshader = compile ps_3_0 BPS();
		CullMode = CCW;
	}
};

///////////////////////////////////////////////////////////////////////////////////////
//ContourVertexShader//
ConData CVS(
	float4 Pos:POSITION
	, float3 Normal : NORMAL
	, float2 UV : TEXCOORD0
)
{
	ConData CD;
	Pos.xyz += Normal * Con.Size;
	CD.Pos = mul(Pos, WorldMat);

	CD.Pos = mul(CD.Pos, ViewMat);
	CD.Pos = mul(CD.Pos, ProjectMat);

	//UV座標セット(法線間ピングの位置としても利用)
	CD.UVPos = UV;


	return CD;
}

//ContourPixelShader//
float4 CPS(ConData CD) :float40
{


	float4 BaseCol;

	BaseCol = tex2D(S_TexMap, CD.UVPos) * Mate.Deffuse;


	if (BaseCol.a < 0.1f)discard;



	return Con.Col;
}


///////////////////////////////////////////////////////////////////////////////////////
//ContourTechnique//

technique ConTec
{
	pass P0
	{
		vertexshader = compile vs_3_0 BVS();
		pixelshader = compile ps_3_0 BPS();
		CullMode = CW;
	}
};

///////////////////////////////////////////////////////////////////////////////////////
//function//

BaseData SetNormalMap(BaseData _BD)
{

	//法線マッピング用//
	float3 Y_Normal;
	float3 WNormal;//3D空間上での法線//
	float3 WTanjent;//3D空間上での接線(Tanjent)//
	float3 WBiNormal;//3D空間上での従法線(BiNormal)//



	WNormal = normalize(mul(_BD.Normal, (float3x3)WorldMat).xyz);

	Y_Normal = abs(dot(WNormal, float3(0.0f, 1.0f, 0.0f))) <= 0.999999
		? float3(0.0f, 1.0f, 0.0f) : float3(0.0f, 0.0f, -1.0f);

	WTanjent = normalize(cross(Y_Normal, WNormal));
	WBiNormal = normalize(cross(WTanjent, WNormal));

	_BD.Normal = normalize(tex2D(S_NormalMap, _BD.UVPos).xyz);

	float3x3 mTBN =
	{
		(WTanjent)
		, (WBiNormal)
		, (WNormal)
	};

	_BD.Normal = normalize(mul(_BD.Normal, mTBN));


	return _BD;
}

///////////////////////////////////////////////////////////////////////////////////////
//Light//

struct BaseLight
{
	float3 Dir;
	float4 Diffuse;
	int Flg;
};

BaseLight BLight = {
	float3(0.0f,-1.0f,0.0f)
	,float4(1.0f,1.0f,1.0f,1.0f)
	,0 };

struct PointLight
{
	float3 Pos;
	float Len;
	float4 Diffuse;
	int Flg;
};

PointLight PLight[10]
=
{
	{float3(0.0f,0.0f,0.0f),0.0f,float4(1.0f,1.0f,1.0f,1.0f),0}
	,{float3(0.0f,0.0f,0.0f),0.0f,float4(1.0f,1.0f,1.0f,1.0f),0}
	,{float3(0.0f,0.0f,0.0f),0.0f,float4(1.0f,1.0f,1.0f,1.0f),0}
	,{float3(0.0f,0.0f,0.0f),0.0f,float4(1.0f,1.0f,1.0f,1.0f),0}
	,{float3(0.0f,0.0f,0.0f),0.0f,float4(1.0f,1.0f,1.0f,1.0f),0}
	,{float3(0.0f,0.0f,0.0f),0.0f,float4(1.0f,1.0f,1.0f,1.0f),0}
	,{float3(0.0f,0.0f,0.0f),0.0f,float4(1.0f,1.0f,1.0f,1.0f),0}
	,{float3(0.0f,0.0f,0.0f),0.0f,float4(1.0f,1.0f,1.0f,1.0f),0}
	,{float3(0.0f,0.0f,0.0f),0.0f,float4(1.0f,1.0f,1.0f,1.0f),0}
	,{float3(0.0f,0.0f,0.0f),0.0f,float4(1.0f,1.0f,1.0f,1.0f),0}
};

texture LightPowMap;

sampler S_LPMap = sampler_state
{
	Texture = <LightPowMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

//平行光//
float4 LLamCol(BaseData _BD, float3 _Dir,float4 _LCol)
{

	float4 BaseCol = _LCol;

	float LPow;//角度によるライトの強さ//
	
	LPow = dot(-_Dir, _BD.Normal);

	LPow = saturate(LPow);

/*
	saturate(x) : max(0,min(1,x))と同意義
	もっと深く踏み込めば、
	add_sat x,y,z : x = saturate(y + z)と書くことも可能
*/

	BaseCol = BaseCol * tex2D(S_LPMap, float2(LPow, 0.5f));

	return BaseCol;
}

//反射光//
float4 LSpeCol(BaseData _BD, float3 _Dir, float4 _LCol)
{
	float4 BaseCol = _LCol;

	float3 LCNormal = normalize(-_Dir + CamPos);

	float4 SpeCol = dot(LCNormal, _BD.Normal);

	SpeCol = saturate(SpeCol);

	

	return BaseCol;
}

//環境光//
float4 LEmiCol(BaseData _BD)
{

	return float4(0.0f, 0.0f, 0.0f, 0.0f);
}

float4 LightCol(BaseData _BD)
{
	float4 BaseCol = float4(0.0f, 0.0f, 0.0f, 0.0f);

	if (BLight.Flg < 1)return BaseCol;

	BaseCol += LLamCol(_BD, BLight.Dir, BLight.Diffuse);

	BaseCol += LSpeCol(_BD, BLight.Dir, BLight.Diffuse);

	BaseCol += LEmiCol(_BD);

	return BaseCol;

}

float4 PLightCol(BaseData _BD)
{

	float4 BaseCol = float4(0.0f, 0.0f, 0.0f, 0.0f);

	for (int i = 0; i < 10; i++)
	{
		if (PLight[i].Flg <= 0)continue;

		float TmpLen;

		TmpLen = length(PLight[i].Pos.xyz - _BD.Pos.xyz);

		if (TmpLen < PLight[i].Len)continue;

	}

	return BaseCol;

}

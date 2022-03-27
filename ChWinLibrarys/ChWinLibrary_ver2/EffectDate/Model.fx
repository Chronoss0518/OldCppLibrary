
float4x4 g_mW;//キャラクタローカル変換行列
float4x4 g_mV;//ビュー行列
float4x4 g_mP;//射影変換行列

//マテリアルデータ=====================================================================

struct Material
{
	float4 Diffuse;

	//反射光===========================================================================
	float4 Specular;
	float SpePower;

	//自己照明=========================================================================
	float Emissive;
	float3 Pos;

	//輪郭=============================================================================
	float InkSize;
	float4 InkCol;
};

struct Light
{
	//平行光
	float LPow;
	int g_LightEnable;//ライトの有無
	float3 g_LightDir;//ライトの方向
	float4 g_LightColor;//ライト色

	//環境光
	float4 g_LightAmbient;

	//反射光
	float SpcPow;
};

struct Fog
{
	float4 Col;

};




float4 g_MateDiffuse = float4(1, 1, 1, 1);

float4 g_MateSpecular = float4(0,1,1,1);//反射色

float g_MateSpePower = 50;//反射色の鋭さ

float4 g_MateEmissive;//自己照明

float g_InkSize = 0.01f;	//輪郭の太さ

float4 g_InkColor = float4(0.0f, 0.0f, 0.0f, 1.0f);//輪郭の色



float4 g_FogCol = float4(1.0f, 1.0f, 1.0f, 0.0f);

//テクスチャ===========================================================================
texture g_MateDiffuseTex;//マテリアルのテクスチャ
texture g_ToonTex;
texture g_MateNormalTex;

//環境マップ用グローバル===============================================================

texture g_EnvTex;//キューブ環境マップ
float g_ReflectionPower = 0.5;//映り込み率


samplerCUBE g_EnvSmp = sampler_state {
	Texture = <g_EnvTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

//テクスチャ用サンプラ
sampler g_MateDiffuseSmp = sampler_state {
	TexTure = <g_MateDiffuseTex>;//使用するテクスチャ
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

sampler g_ToonSmp = sampler_state {
	TexTure = <g_ToonTex>;//使用するテクスチャ
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

//NormalTexture
sampler g_MateNormalSmp = sampler_state
{
	Texture = <g_MateNormalTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};


//カメラ関係===========================================================================

float3 g_CamPos;

//////ライト関係=======================================================================

//平行光
float LPow = 1;
int g_LightEnable = 1;//ライトの有無
float3 g_LightDir = float3(1.0f, -1.0f, 0.0f);//ライトの方向
float4 g_LightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);//ライト色

//環境光
float4 g_LightAmbient = float4(1.0f, 0.2f, 0.2f, 0.2f);

//反射光
float SpcPow;




//反射光(スペキュラ============================================================

float3 LSpecular(float3 _Normal, float3 _CamLook)
{
	float3 SpeCol = 0;

	float3 SpeDir = normalize(-g_LightDir + _CamLook);
	float SpePow = dot(SpeDir, _Normal);
	//PhonegShading

	//float3 vRef = reflect(g_LightDir, w_normal);//反射角
	//float SpePow = dot(vRef, vCam);

	//BlinnPhongShading:計算量が軽くなる。(現実味を帯びやすくなる)

	SpePow = saturate(SpePow);

	SpePow = pow(SpePow, g_MateSpePower);

	SpeCol += g_LightColor.rgb * SpePow;

	return SpeCol;
}

//--------------------------
//頂点シェダ===========================================================================
//--------------------------


//出力用構造体
struct VS_OUT {
	float4 Pos	: POSITION;
	float3 wN	: TEXCOORD0;//ワールド法線
	float3 wPos : TEXCOORD1;//ワールド座標
	float2 UV	: TEXCOORD2;//UV座標
	float3 wT	: TEXCOORD3;//ワールド接線		Tanjgent
	float3 wB	: TEXCOORD4;//ワールド従法線()	BiNormal
};

//頂点シェダ
VS_OUT VS(
	float4 pos : POSITION,
	float3 normal : NORMAL,
	float2 uv : TEXCOORD0
){
	VS_OUT Out;

	//座標を2Dへ
	Out.Pos = mul(pos, g_mW);
	Out.wPos = Out.Pos.xyz;//float4.xyzを行うとfloat3のxyzを使用することができる。

	Out.Pos = mul(Out.Pos, g_mV);
	Out.Pos = mul(Out.Pos, g_mP);
	Out.UV = uv;

	Out.wN = normalize(mul(normal, (float3x3)g_mW));

	float3 vUp = abs(dot(Out.wN, float3(0, 1, 0))) <= 0.999999 ? float3(0, 1, 0) : float3(0, 0, -1);

	Out.wT = normalize(cross(vUp, Out.wN));
	Out.wB = normalize(cross(Out.wN, Out.wT));


	//出力
	return Out;
}

//--------------------------
//ピクセルシェダ関連
//--------------------------
//出力構造体
struct PS_OUT {
	float4 Color : COLOR0;
};
//ピクセルシェダ
PS_OUT PS(VS_OUT In)
{
	//カメラへの方向
	float3 vCam = normalize(g_CamPos - In.wPos);//ピクセルからのカメラ方向

	//法線を正規化
	float3 TmpVec = tex2D(g_MateNormalSmp, In.UV).xyz;
	float3 w_normal = normalize(TmpVec);

	float3x3 mTBN =
	{
		normalize(In.wT),
		normalize(In.wB),
		normalize(In.wN)
	};

	w_normal = mul(w_normal, mTBN);
	w_normal = normalize(w_normal);


	//モデルカラー=====================================================================

	float4 texCol = tex2D(g_MateDiffuseSmp, In.UV);//サンプラの持っている色を取得

	float4 modelCol = g_MateDiffuse * texCol;
	if (modelCol.a < 0.1f)discard;//アルファテスト

	return texCol;

	//環境マッピング
	float3 vRef = reflect(-vCam, w_normal);
	float4 envCol = texCUBE(g_EnvSmp, vRef);

	modelCol.rgb = lerp(modelCol.rgb, envCol.rgb, g_ReflectionPower);
	//modelCol.a = g_MateDiffuse.a;

	//ライトカラー=====================================================================
	
	float3 lightCol = 0;//全ライトの合計拡散色

	float3 lightSpe = 0;//全ライトの合計反射色

	if (g_LightEnable) {

		//平行光=======================================================================
		//拡散光(ランバート)

		float LPow = dot(-g_LightDir, w_normal);

		LPow = saturate(LPow);//入れた数値の1以上の値をすべて1へ、0以下のものを0へ代入する。
		
		float4 ToonCol = tex2D(g_ToonSmp, float2(LPow, 0.5f));

		lightCol += g_LightColor.rgb * ToonCol.rgb;

		//環境光(アンビエント)=========================================================

		lightCol += g_LightAmbient.rgb;

		//スペキュラ===================================================================
		lightSpe += LSpecular(w_normal, vCam);
	}
	else {
		lightCol = 2.0f;
		lightSpe = 0.0f;
	}
	//拡散色===========================================================================

	float4 diffuseCol = modelCol;

	diffuseCol.rgb *= lightCol;//拡散色の場合は合成(掛け算)を行う。
	//反射色

	float4 SpeCol;

	SpeCol.rgb = g_MateSpecular.rgb * lightSpe;

	SpeCol.a = 0;

	//出力=============================================================================

	PS_OUT Out;
	Out.Color = diffuseCol + SpeCol;
	Out.Color.rgb += g_MateEmissive.rgb;
	//法線の描画

	//Out.Color.a = 0.0f;

	//Out.Color.rgb = w_normal;
	return Out;
}

//--------------------------
//Fogピクセルシェダ
//--------------------------
//ピクセルシェダ
PS_OUT FogPS(VS_OUT In)
{
	//カメラへの方向
	float3 vCam = normalize(g_CamPos - In.wPos);//ピクセルからのカメラ方向

	//法線を正規化
	float3 TmpVec = tex2D(g_MateNormalSmp, In.UV).xyz;
	float3 w_normal = normalize(TmpVec);

	float3x3 mTBN =
	{
		normalize(In.wT),
		normalize(In.wB),
		normalize(In.wN)
	};

	w_normal = mul(w_normal, mTBN);
	w_normal = normalize(w_normal);


	//モデルカラー=====================================================================

	float4 texCol = tex2D(g_MateDiffuseSmp, In.UV);//サンプラの持っている色を取得

	if (texCol.a < 0.1f)discard;//アルファテスト

	float4 modelCol = g_MateDiffuse * texCol;

	//環境マッピング
	float3 vRef = reflect(-vCam, w_normal);
	float4 envCol = texCUBE(g_EnvSmp, vRef);

	modelCol.rgb = lerp(modelCol.rgb, envCol.rgb, g_ReflectionPower);

	//ライトカラー=====================================================================

	float3 lightCol = 0;//全ライトの合計拡散色

	float3 lightSpe = 0;//全ライトの合計反射色

	if (g_LightEnable) {

		//平行光=======================================================================
		//拡散光(ランバート)

		float LPow = dot(-g_LightDir, w_normal);

		LPow = saturate(LPow);//入れた数値の1以上の値をすべて1へ、0以下のものを0へ代入する。

		float4 ToonCol = tex2D(g_ToonSmp, float2(LPow, 0.5f));

		lightCol += g_LightColor.rgb * ToonCol.rgb;

		//環境光(アンビエント)=========================================================

		lightCol += g_LightAmbient.rgb;

		//反射光(スペキュラ============================================================
		//PhonegShading

		//float3 vRef = reflect(g_LightDir, w_normal);//反射角
		//float SpePow = dot(vRef, vCam);

		//BlinnPhongShading:計算量が軽くなる。(現実味を帯びやすくなる)

		float3 vH = normalize(-g_LightDir + vCam);

		float SpePow = dot(vH, w_normal);

		SpePow = saturate(SpePow);

		SpePow = pow(SpePow, g_MateSpePower);

		lightSpe += g_LightColor.rgb * SpePow;
	}
	else {
		lightCol = 1;
	}
	
	//拡散色===========================================================================

	float4 diffuseCol = modelCol; 
	//diffuseCol = lerp(modelCol, g_FogCol, length(In.wPos - g_CamPos) * 5);
	diffuseCol.rgb *= lightCol;//拡散色の場合は合成(掛け算)を行う。
	//反射色

	float4 SpeCol;

	SpeCol.rgb = g_MateSpecular.rgb * lightSpe;

	SpeCol.a = 0;

	//出力=============================================================================
	float4 FogCol = g_FogCol;

	FogCol.rgb = g_FogCol.rgb * abs(length(In.wPos - g_CamPos)) * (0.001f);

	PS_OUT Out;
 	Out.Color = diffuseCol + SpeCol;
	Out.Color += FogCol;
	//Out.Color = lerp(Out.Color, g_FogCol, length(In.wPos - g_CamPos) * 5);
	Out.Color.rgb += g_MateEmissive.rgb;
	//法線の描画

	//Out.Color.rgb = w_normal;
	return Out;
}

//--------------------------
//テクニック
//--------------------------
technique Tech{
	pass P0 {
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
		CullMode = CCW;
	}
}

technique NCTech {
	pass P0 {
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}

technique FogTech
{
	pass P0 {
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 FogPS();
		CullMode = CCW;
	}
};

//--------------------------
//輪郭シェーダ
//--------------------------

struct InkVS_OUT {
	float4 Pos : POSITION;//射影座標
	float2 UV : TEXCOORD0;//UV
};

InkVS_OUT InkVS(
	float4 pos : POSITION,
	float3 normal : NORMAL,
	float2 uv : TEXCOORD0
) {
	InkVS_OUT Out;

	//座標を法線方向にずらす
	pos.xyz += normal * g_InkSize;


	Out.Pos = mul(pos, g_mW);
	Out.Pos = mul(Out.Pos, g_mV);
	Out.Pos = mul(Out.Pos, g_mP);

	Out.UV = uv;

	return Out;
}

struct InkPS_OUT {
	float4 Color:COLOR;
};

InkPS_OUT InkPS(
	InkVS_OUT In
) {
	InkPS_OUT Out;

	float4 texCol = tex2D(g_MateDiffuseSmp, In.UV);//サンプラの持っている色を取得
	if (texCol.a < 0.1f)discard;//アルファテスト
	Out.Color = g_InkColor;
	return Out;
}

technique InkTech {
	pass P0{
		VertexShader = compile vs_3_0 InkVS();
		PixelShader = compile ps_3_0 InkPS();

		CullMode = CW;//表面カリングモード
	}
};

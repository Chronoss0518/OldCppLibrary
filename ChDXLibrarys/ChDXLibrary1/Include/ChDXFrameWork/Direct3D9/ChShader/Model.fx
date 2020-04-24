
//--------------------------
//グロバル定数
//--------------------------
float4x4 g_mW;//キャラクタローカル変換行列
float4x4 g_mV;//ビュー行列
float4x4 g_mP;//射影変換行列


//マテリアルデータ=====================================================================

float4 g_MateDiffuse = float4(1, 1, 1, 1);

float4 g_MateSpecular = float4(1,1,1,1);//反射色

float g_MateSpePower = 50;//反射色の鋭さ

float4 g_MateEmissive;//自己照明

float g_InkSize = 0.01f;	//輪郭の太さ

float4 g_InkColor = float4(0.0f, 0.0f, 0.0f, 1.0f);//輪郭の色

//テクスチャ===========================================================================
texture g_MateDiffuseTex;//マテリアルのテクスチャ
texture g_ToonTex;

//環境マップ用グローバル===========================================================

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


//float3 g_LightDir;
float3 normal;

//カメラ関係===========================================================================

float3 g_CamPos;//カメラの位置


//////ライト関係=======================================================================
//平行光

float LPow;
int g_LightEnable = 1;//ライトの有無
float3 g_LightDir = float3(0.0f, -1.0f, 0.0f);//ライトの方向
float4 g_LightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);//ライト色

//環境光
float4 g_LightAmbient = float4(0.2f, 0.2f, 0.2f, 0.2f);

//反射光
float SpcPow;

//--------------------------
//頂点シェダ===========================================================================
//--------------------------

//出力用構造体
struct VS_OUT {
	float4 Pos	: POSITION;
	float3 wN	: TEXCOORD0;//ワールド法線
	float3 wPos : TEXCOORD1;//ワールド座標
	float2 UV	: TEXCOORD2;//UV座標
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

	float3 w_normal = normalize(In.wN);

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

	diffuseCol.rgb *= lightCol;//拡散色の場合は合成(掛け算)を行う。
	//反射色

	float4 SpeCol;

	SpeCol.rgb = g_MateSpecular.rgb * lightSpe;

	SpeCol.a = 0;

	//出力=============================================================================

	PS_OUT Out;
	Out.Color = diffuseCol + SpeCol;
	Out.Color.rgb += g_MateEmissive.rgb;
	
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

//--------------------------
//環境マッピング
//--------------------------


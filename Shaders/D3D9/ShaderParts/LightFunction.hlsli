

//--------------------------
//ライトデータ
//--------------------------


struct Light
{
	float4 Dif;
	float4 Dir;
};

Light light : register(c3);

struct PLight
{
	float4 Dif;
	float4 Pos;
};

int PLightCnt = 7;


struct LightFlg
{
	float4 LF1;
	float4 LF2;
};

LightFlg LFlg : register(c5);

PLight pLight[7] :register(c7);

float4 CamPos:register(c0);

//未実装
texture LightPowMap :register(t1);

//画像から1ピクセルの色を取得するための物//
sampler LightSmp = sampler_state {
	Texture = <LightPowMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

float3 LamLightCol(
	float3 _Dif
	, float _Pow)
{

	float3 TmpLightCol = _Dif;

	TmpLightCol *= _Pow;

	return TmpLightCol;
}

float3 SpeLightCol(
	float3 _Dir
	, float3 _ModelPos
	, float3 _Normal
	, float4 M_SpeCol)
{
	float3 TmpLightCol = { 0.0f,0.0f,0.0f };

	if (M_SpeCol.a < 0)return TmpLightCol;

	float3 TmpVec = normalize(CamPos.xyz - _ModelPos);//ピクセルからのカメラ方向

	TmpVec = normalize(-_Dir + TmpVec);

	float LCDot = dot(TmpVec, _Normal);

	float Pow = saturate(LCDot);

	TmpLightCol = M_SpeCol.rgb * pow(Pow, M_SpeCol.a);

	return TmpLightCol;
}

float3 AmbLightCol()
{

	float3 TmpLightCol = light.Dif.rgb;

	TmpLightCol *= light.Dir.w;

	return TmpLightCol;

}

float4 LightCol(
	float3 _Pos
	, float3 _Normal
	, float4 _Color
	,float4 M_SpeCol)
{

	float4 Col = _Color;

	if (LFlg.LF2.w <= 0.0f)return Col;

	float Dot;

	Dot = dot(_Normal, -light.Dir.xyz);

	Dot = saturate(Dot);

	float TmpPow = tex2D(LightSmp, float2(Dot, 0.5f)).r;

	Col.rgb *= (LamLightCol(light.Dif.rgb, TmpPow) + AmbLightCol());

	Col.rgb += SpeLightCol(
		light.Dir.xyz
		, _Pos.xyz
		, _Normal
		, M_SpeCol);

	//Col.rgb += AmbLightCol();

	return Col;
}

float4 PLightCol(
	PLight plight
	, float3 _Pos
	, float3 _Normal
	, float4 _Color
	, float4 M_SpeCol)
{

	float4 Col = _Color;

	bool TmpFlg = false;

	float3 TmpVec = _Pos.xyz;

	TmpVec = TmpVec - plight.Pos.xyz;

	float Len;

	Len = length(TmpVec);

	TmpFlg = Len > plight.Pos.w ? true : false;

	if (TmpFlg)return Col;

	TmpVec = normalize(TmpVec);

	float Par = Len / plight.Pos.w;

	float Dot;

	Dot = dot(_Normal, -TmpVec);

	Dot = saturate(Dot);

	Col.rgb *= LamLightCol(plight.Dif.rgb, Dot) * Par;

	Col.rgb += SpeLightCol(
		TmpVec
		, _Pos.xyz
		, _Normal
		, M_SpeCol) * Par;

	return Col;
}

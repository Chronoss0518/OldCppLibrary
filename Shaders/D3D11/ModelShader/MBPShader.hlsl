//--------------------------
//外部行列
//--------------------------


//--------------------------
//共通データ
//--------------------------

#include"MShader.hlsli"

//--------------------------
//ライトデータ
//--------------------------

#include"../ShaderParts/Light.hlsli"

//--------------------------
//BaseShader
//--------------------------

float4 LightCol(VS_OUT _Base, float4 _Color);

float4 PLightCol(PLight plight, VS_OUT _Base, float4 _Color);

struct RenderDatas
{
	float4 Main : SV_Target0;
	float4 Temperature :SV_Target1;
	float4 NightVision :SV_Target2;
};


//ピクセルシェダ(PixelShader)//
//通常描画//
float4 main(VS_OUT In) :SV_Target0
{
	//カメラの前方にあるかの判定//

	float X = In.ProPos.x / In.ProPos.w;
	float Y = In.ProPos.y / In.ProPos.w;
	float Z = In.ProPos.z / In.ProPos.w;
	//float X = In.Pos.x;
	//float Y = In.Pos.y;
	//float Z = In.Pos.z;

	clip(X >= -1.0f && X <= 1.0f ? 1.0f : -1.0f);
	clip(Y >= -1.0f && Y <= 1.0f ? 1.0f : -1.0f);
	clip(Z >= 0.0f && Z <= 1.0f ? 1.0f : -1.0f);

//RenderDatas RDColor;

	float4 Color = In.Color;

	Color = Dif * ModelTex.Sample(ModelSmp, In.UV) * Color;

	//Color = Dif;
	//Color = ModelTex.Sample(ModelSmp, In.UV);

	clip(Color.a < 0.001f ? -1 : 1);

	//Color = LightCol(In, Color);

	//for (int i = 0; i < 10; i++)
	//{
	//	if (!LightUseFlg)break;

	//	Color = PLightCol(pLight[i], In , Color);

	//}

	//float4 Temperature = float4(0.0f, 0.0f, 0.0f, 0.0f);
	//
	//RDColor.Main = Color;
	//RDColor.Temperature = Temperature;

	//float4 NightVision = float4(0.5f, 0.5f, 1.0f, 1.0f) * (length(Color) * 1.5f);

	//NightVision.a = 1.0f;

	//RDColor.NightVision = NightVision;


	return Color;

}


float4 LightCol(VS_OUT _Base, float4 _Color)
{

	float4 Col = _Color;

	if(!LightUseFlg)return Col;

	float Dot;

	Dot = dot(_Base.Normal, -light.Dir);

	Dot = saturate(Dot);

	float TmpPow = LightPowMap.Sample(LightSmp, float2(Dot, 0.5f)).r;

	Col.rgb *= (LamLightCol(light.Dif.rgb, TmpPow) + AmbLightCol());

	Col.rgb += SpeLightCol(light.Dir, _Base.UsePos.xyz, _Base.Normal,SpeCol);

	//Col.rgb += AmbLightCol();

	return Col;
}

float4 PLightCol(PLight plight, VS_OUT _Base, float4 _Color)
{

	float4 Col = _Color;

	if (!LightUseFlg)return Col;
	if (!plight.Flg)return Col;

	bool TmpFlg = false;

	float3 TmpVec = _Base.UsePos.xyz;

	TmpVec = TmpVec - plight.Pos;

	float Len;

	Len = length(TmpVec);

	TmpFlg = Len > plight.Len ? true : false;

	if (TmpFlg)return Col;

	TmpVec = normalize(TmpVec);

	float Par = Len / plight.Len;

	float Dot;

	Dot = dot(_Base.Normal, -TmpVec);

	Dot = saturate(Dot);

	Col.rgb *= LamLightCol(plight.Dif.rgb, Dot) * Par;

	Col.rgb += SpeLightCol(TmpVec, _Base.UsePos.xyz, _Base.Normal,SpeCol) * Par;

	return Col;
}

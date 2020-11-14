
struct Light
{
	float4 Dif;
	float3 Dir;
	float AmbPow;
};

struct PLight
{
	float3 Pos;
	float4 Dif;
	float Len;
	bool Flg;
};

cbuffer LightData :register(b7)
{
	float3 CamPos = float3(0.0f, 0.0f, 0.0f);

	bool LightUseFlg = false;

	Light light = {
		float4(1.0f,1.0f,1.0f,1.0f)
		,float3(0.0f,-1.0f,0.0f)
		,0.3f
	};

	int PlightCnt = 10;

	PLight pLight[10];

};


//未実装
texture2D LightPowMap :register(t2);

//画像から1ピクセルの色を取得するための物//
sampler LightSmp = sampler_state {
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};


float3 LamLightCol(float3 _Dif, float _Pow);

float3 SpeLightCol(float3 _Dir, float3 _ModelPos, float3 _Normal,float4 _Speculer);

float3 AmbLightCol();


float3 LamLightCol(float3 _Dif, float _Pow)
{

	float3 TmpLightCol = _Dif;

	TmpLightCol *= _Pow;

	return TmpLightCol;
}

float3 SpeLightCol(float3 _Dir, float3 _ModelPos, float3 _Normal, float4 _Speculer)
{

	float3 TmpVec = normalize(CamPos - _ModelPos);//ピクセルからのカメラ方向

	TmpVec = normalize(-_Dir + TmpVec);

	float LCDot = dot(TmpVec, _Normal);

	float Pow = saturate(LCDot);

	float3 TmpLightCol = _Speculer.rgb * pow(Pow, _Speculer.a);

	return TmpLightCol;
}

float3 AmbLightCol()
{

	float3 TmpLightCol = light.Dif.rgb;

	TmpLightCol *= light.AmbPow;

	return TmpLightCol;

}


//--------------------------
//共通データ
//--------------------------

#include"MCShader.hlsli"

//--------------------------
//モデルデータ
//--------------------------

float4 BaseColor = float4(1.0f, 0.0f, 0.0f, 0.0f);

//ピクセルシェダ(PixelShader)//
//通常描画//
float4 main(VS_OUT In) :COLOR0
{
	//カメラの前方にあるかの判定//

clip(In.ProPos.x > 1.0f && In.ProPos.x < -1.0f ? -1.0f : 1.0f);
clip(In.ProPos.y > 1.0f && In.ProPos.y < -1.0f ? -1.0f : 1.0f);
clip(In.ProPos.z > 1.0f && In.ProPos.z < 0.0f ? -1.0f : 1.0f);

	float4 Color = BaseColor;

	clip(Color.a < 1.0f ? -1 : 1);

	return Color;

}

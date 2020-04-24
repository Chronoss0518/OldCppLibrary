#include"../../CGameIncludeFile.h"

#ifdef CopyRight_Chronoss_2018Y_08M

///////////////////////////////////////////////////////////////////////////////////////
//ChShaderメソッド
///////////////////////////////////////////////////////////////////////////////////////

void ChEffect::SmpXfileDraw(const LpChSmpX _x,const D3DXMATRIX *_Mat, ChEffectType _Type)
{
	
	SetVPMatrix();

	//射影行列とビュー行列のセット
	Effect->SetMatrix("g_mW", _Mat);

	Effect->SetTechnique("Tech");//テクニックセレクト

	Effect->Begin(0, 0);//テクニックスタート

	Effect->BeginPass(0);//パススタート




	for (int i = 0; i < _x->NumMaterial; i++) {

		D3DMATERIAL9* mate = ((_x->Mat) + i);
		//diffuseをセット
		Effect->SetVector("g_MateDiffuse", (D3DXVECTOR4*)&mate->Diffuse);

		//specuraのセット
		Effect->SetVector("g_MateSpecular", (D3DXVECTOR4 *)&mate->Specular);
		Effect->SetFloat("g_MateSpePower", mate->Power);

		//自己照明(エミッシブ)
		Effect->SetVector("g_MateEmissive", (D3DXVECTOR4*)&mate->Emissive);

		LPDIRECT3DTEXTURE9 pTex = nullptr;

		pTex = *_x->Tex;

		if (pTex == nullptr)pTex = WhiteTexture;//Textureを取得できなかったときに白色のテクスチャをセットする。

		Effect->SetTexture("g_MateDiffuseTex", *_x->Tex);

		Effect->SetTexture("g_ToonTex",LightEffectTex[_Type]);
		//データのセットを待つ
		Effect->CommitChanges();
		_x->LpMesh->DrawSubset(i);
	}


	Effect->EndPass();

	Effect->End();


}

#endif
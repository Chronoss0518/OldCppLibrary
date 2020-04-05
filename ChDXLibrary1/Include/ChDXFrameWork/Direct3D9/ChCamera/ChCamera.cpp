
#include"../../CGameIncludeFile.h"

#ifdef CopyRight_Chronoss_2018Y_08M

///////////////////////////////////////////////////////////////////////////////////////
//ChCameraメソッド
///////////////////////////////////////////////////////////////////////////////////////

void ChCamera::SetView(void)
{
	D3DXMATRIX mView, mProj;
	D3DXVECTOR3 TmpCamP;

	if (CamMat != nullptr && CamMat != NULL) {
		D3DXVec3TransformCoord(&TmpCamP, &CamP, CamMat);
		D3DXVec3TransformNormal(&CamH, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), CamMat);
	}
	else
	{
		CamH.x = 0.0f;
		CamH.y = 1.0f;
		CamH.z = 0.0f;
	}
	D3DXVec3Normalize(&CamH, &CamH);
	// 視点行列の設定
	D3DXMatrixLookAtLH(&mView,
		&TmpCamP,	// カメラの位置
		&CamL,	// カメラの視点
		&CamH	// カメラの頭の方向
	);

	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)WW / (float)WH, 1.0f, 1000.0f);

	//行列設定
	Device->SetTransform(D3DTS_VIEW, &mView);
	Device->SetTransform(D3DTS_PROJECTION, &mProj);

}

#endif
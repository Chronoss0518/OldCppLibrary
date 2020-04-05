
#include"../../CGameIncludeFile.h"

#ifdef CopyRight_Chronoss_2018Y_08M

///////////////////////////////////////////////////////////////////////////////////////
//ChCamera���\�b�h
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
	// ���_�s��̐ݒ�
	D3DXMatrixLookAtLH(&mView,
		&TmpCamP,	// �J�����̈ʒu
		&CamL,	// �J�����̎��_
		&CamH	// �J�����̓��̕���
	);

	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)WW / (float)WH, 1.0f, 1000.0f);

	//�s��ݒ�
	Device->SetTransform(D3DTS_VIEW, &mView);
	Device->SetTransform(D3DTS_PROJECTION, &mProj);

}

#endif
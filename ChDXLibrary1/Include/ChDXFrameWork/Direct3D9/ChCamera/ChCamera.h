#ifndef Ch_D3D9_Cam_h
#define Ch_D3D9_Cam_h

#include"../../CGameIncludeFile.h"

class ChCamera 
{
private:
	LPDIRECT3DDEVICE9 Device = nullptr;
	D3DXMATRIX *CamMat = nullptr;


public:
	D3DXVECTOR3 CamP, CamL, CamH;

	///////////////////////////////////////////////////////////////////////////////////

	//Matrix�𗘗p���Ȃ��ꍇ��NULL�܂���nullptr
	//Matrix�𗘗p����ꍇ��CamP�͊�ƂȂ�}�g���b�N�X����̈ʒu�Ƃ��Ĉ���
	ChCamera(const LPDIRECT3DDEVICE9 _Dv,D3DXMATRIX *_CamMat) 
	{
		CamP = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		CamL = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Device = _Dv;
		CamMat = _CamMat;
	}

	///////////////////////////////////////////////////////////////////////////////////

	LPD3DXVECTOR3 GetCamPos(void) { return &CamP; }

	///////////////////////////////////////////////////////////////////////////////////

	LPD3DXVECTOR3 GetCamLook(void) { return &CamL; }

	///////////////////////////////////////////////////////////////////////////////////

	//CameraMatrix����̋������Z�b�g
	void SetCamPos(const D3DXVECTOR3 *_Pos) { CamP = *_Pos; }

	///////////////////////////////////////////////////////////////////////////////////

	void SetView(void);

	///////////////////////////////////////////////////////////////////////////////////

	void SetCamLook(const D3DXVECTOR3 *_Look) { CamL = *_Look; }

};

#endif
//CopyRight Chronoss0518 2018/08
#ifndef Ch_D3D9_Mou_h
#define Ch_D3D9_Mou_h

#include"../../CGameIncludeFile.h"

typedef class ChMouseController {
private:
	POINT MouSPos;
	POINT MouNPos;
	bool MouseCamLFlg;
public:

	///////////////////////////////////////////////////////////////////////////////////

	ChMouseController(bool _MouseCamSetFlg);

	///////////////////////////////////////////////////////////////////////////////////

	void SetCamlookMouse(void);




}ChMouCon,*LpMouCon;

#endif
//CopyRight Chronoss0518 2018/08
#ifndef Ch_D3D9_Ob_h
#define Ch_D3D9_Ob_h

#include"../../CGameIncludeFile.h"

struct ChFRECT
{
	float x;
	float y;
	float w;
	float h;
};

typedef class ChObjectController {
public:

	///////////////////////////////////////////////////////////////////////////////////

	bool SmpXFileHitRay(
		const ChSmpX *_XFile
		, const D3DXMATRIX *_Obj
		, const D3DXVECTOR3 * _Pos
		, const D3DXVECTOR3 *_Dir
		, float *_Len);

	///////////////////////////////////////////////////////////////////////////////////

	bool PorygonHitRay(
		const ChPoBo *_PoBo
		, const D3DXVECTOR3 *_Pos
		, D3DXVECTOR3 *_Dir
		, float *_Len);

	///////////////////////////////////////////////////////////////////////////////////

	bool SimpleAnimetion(
		const D3DXMATRIX *_StartMat
		,const D3DXMATRIX *_EndMat
		, const float _EndTime
		, float *_NowTime
		, D3DXMATRIX *_NowMat
		, float _FrameSpeed);

	///////////////////////////////////////////////////////////////////////////////////

	void MatrixBillboard
	(D3DXMATRIX *_OutObj
		,const D3DXVECTOR3 *_ObjPos
		,const D3DXMATRIX *_CamMat);

	///////////////////////////////////////////////////////////////////////////////////

	// _MaskDirectionÇ…'x','y','z'ÇÃÇ¢Ç∏ÇÍÇ©ÇãLì¸Ç∑ÇÈÇ∆ÅA
	//ÇªÇÃï˚å¸Ç…ÇæÇØìñÇΩÇËîªíËÇ™Ç®ÇÒÇ»Ç∂à íuÇ…Ç»ÇÈ
	bool LengthDecision(
		const D3DXMATRIX *_Mat1
		, const D3DXMATRIX *_Mat2
		, const float MatLen
		,const char _MaskDirection);

	///////////////////////////////////////////////////////////////////////////////////

	bool Hit2DDecision(
		const D3DXMATRIX *_Obj1Mat
		, const D3DXMATRIX *_Obj2Mat
		, const LpChTex *_Obj1Tex
		, const LpChTex *_Obj2Tex);

	///////////////////////////////////////////////////////////////////////////////////

	void LookObjectAxis(
		D3DXVECTOR3 *_OutVec
		, const D3DXMATRIX *_OffsetMat
		, const D3DXMATRIX *_ObjectMat);

	///////////////////////////////////////////////////////////////////////////////////

}ChObjCon, *LPChObjCon;

#endif // !Ch_D3D9_Ob_h
//CopyRight Chronoss0518 2018/08
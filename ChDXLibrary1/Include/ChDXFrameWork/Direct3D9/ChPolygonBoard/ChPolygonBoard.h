#ifndef Ch_D3D9_PB_h
#define Ch_D3D9_PB_h

#include"../../CGameIncludeFile.h"



typedef struct ChVERTEXpctsn{
	D3DXVECTOR3 pos;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
	//D3DCOLOR specular;
	//D3DXVECTOR3 normal;
}ChVertex,*LpChVertex;


typedef class ChPolygonBoard {
private:
	bool AlphaFlg;
	//bool UpDateFlg = NULL;
	static const unsigned char VertexMaxCnt = 4;
	LPDIRECT3DDEVICE9 Device;
public:

	///////////////////////////////////////////////////////////////////////////////////

	ChVertex Ver[VertexMaxCnt];

	///////////////////////////////////////////////////////////////////////////////////

	void SetAlphaFlg(bool _Flg) { AlphaFlg = _Flg; }

	///////////////////////////////////////////////////////////////////////////////////

	//���ݒ���s��Ȃ��ꍇ�ADefolt�l�̍����(1.0f,1.0f,0.0f)�������l�Ƃ���2�Â��ꂽ������XY�ǂ��Z�b�g����B
	ChPolygonBoard(LPDIRECT3DDEVICE9 _Dv);

	///////////////////////////////////////////////////////////////////////////////////

	//�X�y�L�������Ȃǂ��܂ނ��܂܂Ȃ���
	//void SetUpDateFlg(const bool _Flg) { UpDateFlg = _Flg; }

	///////////////////////////////////////////////////////////////////////////////////

	//�����D3DXVECTOR3���擾���A��������̕��������v�Z���o�͂��Ă����B
	//XY�����̔|���S���̃|�W�V�����w��
	void SetXYPosition(const D3DXVECTOR3 *_LeftTopPos,const float _W,const float _H);

	///////////////////////////////////////////////////////////////////////////////////

	//YZ�����̔|���S���̃|�W�V�����w��
	void SetYZPosition(const D3DXVECTOR3 *_LeftTopPos, const float _W, const float _H);

	///////////////////////////////////////////////////////////////////////////////////

	//ZX�����̔|���S���̃|�W�V�����w��
	void SetZXPosition(const D3DXVECTOR3 *_LeftTopPos, const float _W, const float _H);

	///////////////////////////////////////////////////////////////////////////////////

	//�Ώۂ�Vertex���I���W�i���̈ʒu�֎����Ă������Ƃ��ł���B
	void SetPositionVector(const D3DXVECTOR3 _Pos, const char _PosNo)
	{
		if (_PosNo > VertexMaxCnt)return;
		Ver[_PosNo].pos = _Pos;
	}

	///////////////////////////////////////////////////////////////////////////////////

	//�Ώۂ�Vertex�̐F�����Z�b�g�ł���
	void SetColor(const D3DCOLOR _Col, const unsigned char _PosNo) 
	{ 
		if (_PosNo > VertexMaxCnt)return;
		Ver[_PosNo].col = _Col;
	}

	///////////////////////////////////////////////////////////////////////////////////

	//�Ώۂ�Vertex��Texture�`��n�_(�X�N���[�����W�n)�̐ݒ���s�����Ƃ��ł���B
	void SetTex(const D3DXVECTOR2 _Tex, const unsigned char _PosNo)
	{
		if (_PosNo > VertexMaxCnt)return;
		Ver[_PosNo].tex = _Tex;
	}

	///////////////////////////////////////////////////////////////////////////////////

	//�Ώۂ�VerTex�̖@�����Z�b�g�ł���B
	void SetNormal(const D3DXVECTOR3 _Normal, const char _PosNo)
	{
		if (_PosNo > VertexMaxCnt)return;
		//Ver[_PosNo].normal = _Normal;
	}

	///////////////////////////////////////////////////////////////////////////////////

	void Draw(const LpChTex _Tex, const LPD3DXMATRIX _Mat);

}ChPoBo;




#endif
//CopyRight Chronoss0518 2018/08
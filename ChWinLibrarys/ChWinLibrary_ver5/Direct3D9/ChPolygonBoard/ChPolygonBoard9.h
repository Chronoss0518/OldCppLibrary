#ifndef Ch_D3D9_PB_h
#define Ch_D3D9_PB_h

namespace ChTex
{
	typedef class BaseTexture9 Texture9;

	//�|���S���Ǘ��p�N���X//
	class PolygonBoard9:public ChCp::Initializer
	{
	public:

		//�|���S���ŗ��p���钸�_���//
		struct ChVertex9
		{
			ChVec3_9 pos;
			D3DCOLOR col;
			D3DXVECTOR2 tex;
		};

		ChVertex9& operator[](int _size)
		{
			return this->ver[_size];
		}

		ChVertex9 operator[](const int _size)const
		{
			return this->ver[_size];
		}

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(const LPDIRECT3DDEVICE9& _dv);

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//���߂����邩�����Ȃ����̃t���O//
		void SetAlphaFlg(bool _flg) { alphaFlg = _flg; }

		//�X�y�L�������Ȃǂ��܂ނ��܂܂Ȃ���//
		//void SetUpDateFlg(const bool _Flg) { UpDateFlg = _Flg; }

		//�����D3DXVECTOR3���擾���A��������̕��������v�Z���o�͂��Ă����B//
		//XY�����̔|���S���̃|�W�V�����w��//
		void SetXYPosition(const ChVec3_9& _leftTopPos, const float _w, const float _h);

		//YZ�����̔|���S���̃|�W�V�����w��//
		void SetYZPosition(const ChVec3_9& _leftTopPos, const float _w, const float _h);

		//ZX�����̔|���S���̃|�W�V�����w��//
		void SetZXPosition(const ChVec3_9& _leftTopPos, const float _w, const float _h);

		//�Ώۂ�Vertex���I���W�i���̈ʒu�֎����Ă������Ƃ��ł���B//
		void SetPositionVector(const D3DXVECTOR3* _pos, const char _posNo);

		//�Ώۂ�Vertex�̐F�����Z�b�g�ł���//
		void SetColor(const D3DCOLOR _col, const unsigned char _posNo);

		//�Ώۂ�Vertex��Texture�`��n�_(�X�N���[�����W�n)�̐ݒ���s�����Ƃ��ł���B//
		void SetTex(const D3DXVECTOR2 _tex, const unsigned char _posNo);

		//�������ɂ́A�I���W�i���T�C�Y���猩���s�N�Z���T�C�Y�B//
		//��O�����ɂ́A�摜�̍���摜�ʒu�B//
		void SetRectTex(
			const ChPtr::Shared<BaseTexture9> _tex
			, const RECT& _rect
			, const unsigned char _sPosNo);

		//�Ώۂ�VerTex�̖@�����Z�b�g�ł���B//
		//void SetNormal(const D3DXVECTOR3 _Normal, const char _PosNo);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		const inline ChVertex9* GetPosVertex(unsigned char _vertexCnt)
		{
			if (vertexMaxCnt < _vertexCnt)return nullptr;
			return &ver[_vertexCnt];
		}

		///////////////////////////////////////////////////////////////////////////////////

		void Draw(
			const ChPtr::Shared<BaseTexture9>& _Tex
			, const LPD3DXMATRIX& _Mat);

	protected:



		ChStd::Bool alphaFlg;

		static const unsigned char vertexMaxCnt = 4;

		LPDIRECT3DDEVICE9 device;

		union
		{
			struct
			{
				ChVertex9 _1,_2,_3,_4;
			};

			ChVertex9 ver[vertexMaxCnt];

		};

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		//���ݒ���s��Ȃ��ꍇ�ADefolt�l�̍����(1.0f,1.0f,0.0f)//
		//�������l�Ƃ���2�Â��ꂽ������XY�ǂ��Z�b�g����B//
		PolygonBoard9() {};


	public:

		inline static PolygonBoard9& GetIns()
		{
			static PolygonBoard9 ins;
			return ins;
		}

	};

	static const std::function<PolygonBoard9&()> PoBo9 = PolygonBoard9::GetIns;

}

#endif
//CopyRight Chronoss0518 2018/08
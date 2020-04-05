
#ifndef Ch_D3D9_DXCo_h
#define Ch_D3D9_DXCo_h


namespace ChD3D9
{

	//�K�v�Ɗ�����l�����ׂĂ킩��₷����������
	namespace FVF
	{
		const unsigned long XYZ = D3DFVF_XYZ;
		const unsigned long DIFFUSE = D3DFVF_DIFFUSE;
		const unsigned long TEX = D3DFVF_TEX1;
		const unsigned long NORMAL = D3DFVF_NORMAL;
	}

	enum class CULL { NONE = 1, CW, CCW };

	//Direct3D9�𗘗p���邽�߂ɍ��ꂽ�N���X//
	//D3DX����������Ă���//
	class DirectX3D9:public ChCpp::ChCp::InitPack
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndReleas//

		void Init(
			const HWND _hWnd
			, const bool _FullScreenFlg
			, const unsigned short _ScrW
			, const unsigned short _ScrH);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�Œ�@�\�`�������ۂɗ��p���郉�C�g�f�[�^���Z�b�g//
		inline void SetLight(const ChStd::DataNo _SetNo, const D3DLIGHT9 *_Light)
		{
			Device->SetLight((DWORD)_SetNo, _Light);
		}

		//�Œ�@�\�`�������ۂɗ��p����J�����O�f�[�^���Z�b�g//
		inline void SetCullMode(const CULL _CULL)
		{
			Device->SetRenderState(D3DRS_CULLMODE, ChStd::EnumCast(_CULL));
		}

		//�Œ�@�\�`�������ۂɗ��p����e�N�X�`���`����@���Z�b�g//
		inline void SetFilter(
			_D3DTEXTUREFILTERTYPE _Mip
			, _D3DTEXTUREFILTERTYPE _Min
			, _D3DTEXTUREFILTERTYPE _Mag)
		{
			Device->SetSamplerState(0, D3DSAMP_MIPFILTER, _Mip);
			Device->SetSamplerState(0, D3DSAMP_MINFILTER, _Min);
			Device->SetSamplerState(0, D3DSAMP_MAGFILTER, _Mag);
		}

		//�`����s�����߂̃o�b�N�o�b�t�@�Z�b�g//
		inline void SetBackBuffer()
		{
			Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &BackBuffer);
		}

		//���_�𗘗p�����|���S���̕`��Ɋւ���f�[�^�̃Z�b�g//
		inline void SetFVF(unsigned long _FVF)
		{
			Device->SetFVF(_FVF);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Direct3D9�������ǂ�f�o�C�X�̎擾//
		inline LPDIRECT3DDEVICE9 GetDevice()
		{
			return Device;
		}

		//�Ώۂ̃}�g���b�N�X�ɑ΂��ĉ�ʏ�ł̈ʒu���擾//
		ChVec3_9 GetOnViewPos(const ChMat_9& _Mat);

		//�����p�����[�^�̎擾//
		inline D3DPRESENT_PARAMETERS GetInitParam()
		{
			return Param;
		}

		//�ˉe�s��̎擾//
		inline const ChMat_9 GetCamPMat()
		{
			ChMat_9 Proj;
			Device->GetTransform(D3DTS_PROJECTION, &Proj);
			return Proj;
		}

		//�r���[�s��̎擾//
		inline const ChMat_9 GetCamVMat()
		{
			ChMat_9 View;
			Device->GetTransform(D3DTS_VIEW, &View);
			return View;

		}

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�Œ�@�\�`��\�m�F//
		inline ChStd::Bool IsDraw()
		{
			return DFlg;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//UseFlgFunction//

		//Z�o�b�t�@(�[�x��ǂݍ��ރo�b�t�@)�𗘗p���邩�ۂ��̃t���O//
		inline void ZBufferUseFlg(const ChStd::Bool _Flg)
		{
			_Flg == ChStd::True ? Device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE)
				: Device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

			Device->SetRenderState(D3DRS_ZWRITEENABLE, _Flg);
		}

		//�Œ�@�\�ŃA���t�@�u�����h(���ߍ���)�𗘗p���邩�ۂ��̃t���O//
		inline void AlphaBlendUseFlg(const ChStd::Bool _Flg)
		{
			Device->SetRenderState(D3DRS_ALPHABLENDENABLE, _Flg);
			Device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, _Flg);
		}

		//�Œ�@�\�ł��ꂼ���Light�𗘗p���邩�ۂ��̃t���O
		inline void LightUseFlg(const ChStd::DataNo _SetNo, const ChStd::Bool _Flg)
		{
			Device->LightEnable((DWORD)_SetNo, _Flg);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SettingFunction//

		//�Œ�@�\�ŕ`�掞�Ƀ��C�g�v�Z���s�����ۂ��̃t���O//
		inline void LightSetting(const ChStd::Bool _Flg)
		{
			Device->SetRenderState(D3DRS_LIGHTING, _Flg);
		}

		//�Œ�@�\�ŃA���t�@�u�����h(����Z����)�̐ݒ�//
		inline void AlphaBlendSetting()
		{
			Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}

		//�Œ�@�\�ŃA���t�@�u�����h(���Z����)�̐ݒ�//
		inline void AddBlendSetting()
		{
			Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		//�Œ�@�\�őS�̂̕`��ݒ�//
		inline void RenderSetting()
		{
			// �����_�����O���̃A���t�@�l�̌v�Z���@�̐ݒ�//
			Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			// �e�N�X�`���̐F���g�p//
			Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			// ���_�̐F���g�p//
			Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
			// �����_�����O���̐F�̌v�Z���@�̐ݒ�//
			Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		}

		///////////////////////////////////////////////////////////////////////////////////

		//Device�������@//
		ChStd::Bool CreateD3DXDevice(const HWND _hWnd
			, D3DPRESENT_PARAMETERS *_d3dpp);

		///////////////////////////////////////////////////////////////////////////////////

		//�f�o�C�X�����݂��邩���Ȃ����̊m�F//
		inline ChStd::Bool CheckInstanse()
		{
			if (ChPtr::NullCheck(D3D9))return ChStd::False;
			if (ChPtr::NullCheck(Device))return ChStd::False;
			return ChStd::True;
		}

		///////////////////////////////////////////////////////////////////////////////////

		//�`��J�n���ɌĂԊ֐�//
		void DrawStart(const D3DCOLOR& _BackColor = D3DCOLOR_ARGB(255, 255, 255, 255));

		///////////////////////////////////////////////////////////////////////////////////

		//�`��I�����ɌĂԊ֐�//
		//�����_�[�^�[�Q�b�g���p�����ۂ�Flg��True�ɂ���//
		void DrawEnd(const ChStd::Bool& _RTFlg = false);

		///////////////////////////////////////////////////////////////////////////////////

	private:

		LPDIRECT3D9 D3D9 = nullptr;
		LPDIRECT3DDEVICE9 Device = nullptr;
		LPDIRECT3DSURFACE9 BackBuffer = nullptr;

		ChStd::Bool DFlg = false;

		int adapter = 0;
		D3DPRESENT_PARAMETERS Param;

		///////////////////////////////////////////////////////////////////////////////////
		//SetSingleton
		///////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		inline DirectX3D9() {}

		inline ~DirectX3D9()
		{
			Release();
		}

	public:

		static DirectX3D9& GetInstans()
		{
			static DirectX3D9 Ins;
			return Ins;
		}


	};

	const static std::function<DirectX3D9&()> D3D9API = DirectX3D9::GetInstans;

	const static std::function<LPDIRECT3DDEVICE9()> D3D9Device
		= []()->LPDIRECT3DDEVICE9 
	{
		return DirectX3D9::GetInstans().GetDevice();
	};
}

#endif
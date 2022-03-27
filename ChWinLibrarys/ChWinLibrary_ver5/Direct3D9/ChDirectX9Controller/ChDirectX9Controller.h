
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
	class DirectX3D9:public ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndReleas//

		void Init(
			const HWND _hWnd
			, const bool _fullScreenFlg
			, const unsigned short _scrW
			, const unsigned short _scrH);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�Œ�@�\�`�������ۂɗ��p���郉�C�g�f�[�^���Z�b�g//
		inline void SetLight(const ChStd::DataNo _setNo, const D3DLIGHT9 *_light)
		{
			device->SetLight((DWORD)_setNo, _light);
		}

		//�Œ�@�\�`�������ۂɗ��p����J�����O�f�[�^���Z�b�g//
		inline void SetCullMode(const CULL _cull)
		{
			device->SetRenderState(D3DRS_CULLMODE, ChStd::EnumCast(_cull));
		}

		//�Œ�@�\�`�������ۂɗ��p����e�N�X�`���`����@���Z�b�g//
		inline void SetFilter(
			_D3DTEXTUREFILTERTYPE _mip
			, _D3DTEXTUREFILTERTYPE _min
			, _D3DTEXTUREFILTERTYPE _mag)
		{
			device->SetSamplerState(0, D3DSAMP_MIPFILTER, _mip);
			device->SetSamplerState(0, D3DSAMP_MINFILTER, _min);
			device->SetSamplerState(0, D3DSAMP_MAGFILTER, _mag);
		}

		//�`����s�����߂̃o�b�N�o�b�t�@�Z�b�g//
		inline void SetBackBuffer()
		{
			device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
		}

		//���_�𗘗p�����|���S���̕`��Ɋւ���f�[�^�̃Z�b�g//
		inline void SetFVF(unsigned long _FVF)
		{
			device->SetFVF(_FVF);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Direct3D9�������ǂ�f�o�C�X�̎擾//
		inline LPDIRECT3DDEVICE9 GetDevice()
		{
			return device;
		}

		//�Ώۂ̃}�g���b�N�X�ɑ΂��ĉ�ʏ�ł̈ʒu���擾//
		ChVec3_9 GetOnViewPos(const ChMat_9& _mat);

		//�����p�����[�^�̎擾//
		inline D3DPRESENT_PARAMETERS GetInitParam()
		{
			return param;
		}

		//�ˉe�s��̎擾//
		inline const ChMat_9 GetCamPMat()
		{
			ChMat_9 proj;
			device->GetTransform(D3DTS_PROJECTION, &proj);
			return proj;
		}

		//�r���[�s��̎擾//
		inline const ChMat_9 GetCamVMat()
		{
			ChMat_9 view;
			device->GetTransform(D3DTS_VIEW, &view);
			return view;

		}

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�Œ�@�\�`��\�m�F//
		inline ChStd::Bool IsDraw()
		{
			return dFlg;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//UseFlgFunction//

		//Z�o�b�t�@(�[�x��ǂݍ��ރo�b�t�@)�𗘗p���邩�ۂ��̃t���O//
		inline void ZBufferUseFlg(const ChStd::Bool _flg)
		{
			_flg ? device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE)
				: device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

			device->SetRenderState(D3DRS_ZWRITEENABLE, _flg);
		}

		//�Œ�@�\�ŃA���t�@�u�����h(���ߍ���)�𗘗p���邩�ۂ��̃t���O//
		inline void AlphaBlendUseFlg(const ChStd::Bool _flg)
		{
			device->SetRenderState(D3DRS_ALPHABLENDENABLE, _flg);
			device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, _flg);
		}

		//�Œ�@�\�ł��ꂼ���Light�𗘗p���邩�ۂ��̃t���O
		inline void LightUseFlg(const ChStd::DataNo _setNo, const ChStd::Bool _flg)
		{
			device->LightEnable((DWORD)_setNo, _flg);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SettingFunction//

		//�Œ�@�\�ŕ`�掞�Ƀ��C�g�v�Z���s�����ۂ��̃t���O//
		inline void LightSetting(const ChStd::Bool _flg)
		{
			device->SetRenderState(D3DRS_LIGHTING, _flg);
		}

		//�Œ�@�\�ŃA���t�@�u�����h(����Z����)�̐ݒ�//
		inline void AlphaBlendSetting()
		{
			device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}

		//�Œ�@�\�ŃA���t�@�u�����h(���Z����)�̐ݒ�//
		inline void AddBlendSetting()
		{
			device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		//�Œ�@�\�őS�̂̕`��ݒ�//
		inline void RenderSetting()
		{
			// �����_�����O���̃A���t�@�l�̌v�Z���@�̐ݒ�//
			device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			// �e�N�X�`���̐F���g�p//
			device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			// ���_�̐F���g�p//
			device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
			// �����_�����O���̐F�̌v�Z���@�̐ݒ�//
			device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		}

		///////////////////////////////////////////////////////////////////////////////////

		//Device�������@//
		ChStd::Bool CreateD3DXDevice(const HWND _hWnd
			, D3DPRESENT_PARAMETERS *_d3dpp);

		///////////////////////////////////////////////////////////////////////////////////

		//�f�o�C�X�����݂��邩���Ȃ����̊m�F//
		inline ChStd::Bool CheckInstanse()
		{
			if (ChPtr::NullCheck(d3d9))return false;
			if (ChPtr::NullCheck(device))return false;
			return true;
		}

		///////////////////////////////////////////////////////////////////////////////////

		//�`��J�n���ɌĂԊ֐�//
		void DrawStart(const D3DCOLOR& _backColor = D3DCOLOR_ARGB(255, 255, 255, 255));

		///////////////////////////////////////////////////////////////////////////////////

		//�`��I�����ɌĂԊ֐�//
		//�����_�[�^�[�Q�b�g���p�����ۂ�Flg��True�ɂ���//
		void DrawEnd(const ChStd::Bool& _rtFlg = false);

		///////////////////////////////////////////////////////////////////////////////////

	private:

		LPDIRECT3D9 d3d9 = nullptr;
		LPDIRECT3DDEVICE9 device = nullptr;
		LPDIRECT3DSURFACE9 backBuffer = nullptr;

		ChStd::Bool dFlg = false;

		int adapter = 0;
		D3DPRESENT_PARAMETERS param;

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
			static DirectX3D9 ins;
			return ins;
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
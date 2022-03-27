#ifndef Ch_D3D9_CamCon_h
#define Ch_D3D9_CamCon_h

namespace ChD3D9
{
	class CameraController;

	typedef struct CameraObject
	{
		D3DXVECTOR3 Pos = ChVec3_9(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 Look = ChVec3_9(0.0f, 0.0f, 1.0f);
		D3DXVECTOR3 Head = ChVec3_9(0.0f, 1.0f, 0.0f);

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�`�悷�鋗�����m�F���Ȃ���Z�b�g����֐�//
		inline void SetLookLenMinMax(
			const float _Min = 0.0f
			, const float _Max = 1000.0f)
		{
			if (_Min < 0.0f)return;
			if (_Min >= _Max)return;
			LMin = _Min;
			LMax = _Max;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�����鋗���̍ō�����//
		float GetLookMax() { return LMax; }

		//�����鋗���̍Œ዗��//
		float GetLookMin() { return LMin; }

		///////////////////////////////////////////////////////////////////////////////////
		
		friend CameraController;

	private:

		float LMin = 0.0f, LMax =1000.0f;

	}CamObj;

	class CameraController:public::ChCpp::ChCp::Initializer
	{
	public:


		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Init(const LPDIRECT3DDEVICE9 _Dev) { Device = _Dev; SetInitFlg(true); }

		inline void Release() { SetInitFlg(false); };

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//
		
		//DirectX�̌Œ�@�\�ɃJ�����ϊ��s����Z�b�g����//
		inline void SetViewMat(const D3DXMATRIX& _VMat)
		{
			Device->SetTransform(D3DTS_VIEW, &_VMat);
		}

		//DirectX�̌Œ�@�\�ɍŌ�ɍ쐬�����J�����ϊ��s����Z�b�g����//
		inline void SetViewMat()
		{
			Device->SetTransform(D3DTS_VIEW, &ViewMat);
		}

		//DirectX�̌Œ�@�\�Ɏˉe�ϊ��s����Z�b�g����//
		inline void SetProMat(const D3DXMATRIX& _PMat)
		{
			Device->SetTransform(D3DTS_PROJECTION, &_PMat);
		}

		//DirectX�̌Œ�@�\�ɍŌ�ɍ쐬�����J�����ϊ��s����Z�b�g����//
		inline void SetProMat()
		{
			Device->SetTransform(D3DTS_PROJECTION, &ProjectionMat);
		}

		//DirectX�̌Œ�@�\�ɍŌ�ɍ쐬���ꂽ�f�[�^�����ɃJ�����f�[�^���Z�b�g����//
		inline void SetView()
		{
			Device->SetTransform(D3DTS_VIEW, &ViewMat);
			Device->SetTransform(D3DTS_PROJECTION, &ProjectionMat);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�Ō�ɃZ�b�g�����f�[�^���擾
		inline CamObj GetLastCamData() { return LastCamData; }

		//DirectX�̌Œ�@�\�ɃJ�����ϊ��s����擾����//
		inline D3DXMATRIX GetViewMatForDevice()
		{
			ChMat_9 TmpMat;

			Device->GetTransform(D3DTS_VIEW, &TmpMat);

			return TmpMat;
		}

		//�Ō�ɍ쐬�����J�����ϊ��s����擾����//
		inline D3DXMATRIX GetViewMat()
		{
			return ViewMat;
		}

		//DirectX�̌Œ�@�\�ɓo�^����Ă���ˉe�ϊ��s����擾����//
		inline D3DXMATRIX GetProMatForDevice()
		{
			ChMat_9 TmpMat;

			Device->GetTransform(D3DTS_PROJECTION, &TmpMat);

			return TmpMat;
		}

		//�Ō�ɍ쐬�����ˉe�ϊ��s����擾����//
		inline D3DXMATRIX GetProMat()
		{
			return ProjectionMat;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//MakeFunction//

		D3DXMATRIX MakeViewMatrix(const CamObj& _Cam);

		D3DXMATRIX MakeViewMatrix(
			const D3DXVECTOR3& _CamPos = ChVec3_9(0.0f, 0.0f, 0.0f)
			, const D3DXVECTOR3& _CamLook = ChVec3_9(0.0f, 0.0f, 1.0f)
			, const D3DXVECTOR3& _CamHead = ChVec3_9(0.0f, 1.0f, 0.0f));

		D3DXMATRIX MakeProjectionMatrix(
			const CamObj& _Cam
			, const float _WindWidth = 1280.0f
			, const float _WindHeight = 720.0f
			, const float _ViewAngDeg = 60.0f);

		D3DXMATRIX MakeProjectionMatrix(
			const float _LookNear = 1.0f
			, const float _LookDistant = 1000.0f
			, const float _WindWidth = 1280.0f
			, const float _WindHeight = 720.0f
			, const float _ViewAngDeg = 60.0f);

		///////////////////////////////////////////////////////////////////////////////////

	private:

		LPDIRECT3DDEVICE9 Device;

		ChMat_9 ProjectionMat;
		ChMat_9 ViewMat;

		CamObj LastCamData;

		///////////////////////////////////////////////////////////////////////////////////
		//SetSingleton
		///////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		CameraController(){}

		~CameraController(){}

		public:

		static CameraController& GetIns()
		{
			static CameraController Ins;
			return Ins;
		}

	};

	const static std::function<CameraController&()>CamCon = CameraController::GetIns;
}

#endif
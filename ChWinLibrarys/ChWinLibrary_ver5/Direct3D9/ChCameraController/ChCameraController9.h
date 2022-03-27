#ifndef Ch_D3D9_CamCon_h
#define Ch_D3D9_CamCon_h

namespace ChD3D9
{
	class CameraController;

	typedef struct CameraObject
	{
		D3DXVECTOR3 pos = ChVec3_9(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 look = ChVec3_9(0.0f, 0.0f, 1.0f);
		D3DXVECTOR3 head = ChVec3_9(0.0f, 1.0f, 0.0f);

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//描画する距離を確認しながらセットする関数//
		inline void SetLookLenMinMax(
			const float _min = 0.0f
			, const float _max = 1000.0f)
		{
			if (_min < 0.0f)return;
			if (_min >= _max)return;
			lMin = _min;
			lMax = _max;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//見える距離の最高距離//
		float GetLookMax() { return lMax; }

		//見える距離の最低距離//
		float GetLookMin() { return lMin; }

		///////////////////////////////////////////////////////////////////////////////////
		
		friend CameraController;

	private:

		float lMin = 0.0f, lMax =1000.0f;

	}CamObj;

	class CameraController:public ChCp::Initializer,public ChCp::Releaser
	{
	public:


		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Init(const LPDIRECT3DDEVICE9 _dev) { device = _dev; SetInitFlg(true); }

		inline void Release()override { SetInitFlg(false); };

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//
		
		//DirectXの固定機能にカメラ変換行列をセットする//
		inline void SetViewMat(const D3DXMATRIX& _vMat)
		{
			device->SetTransform(D3DTS_VIEW, &_vMat);
		}

		//DirectXの固定機能に最後に作成したカメラ変換行列をセットする//
		inline void SetViewMat()
		{
			device->SetTransform(D3DTS_VIEW, &viewMat);
		}

		//DirectXの固定機能に射影変換行列をセットする//
		inline void SetProMat(const D3DXMATRIX& _pMat)
		{
			device->SetTransform(D3DTS_PROJECTION, &_pMat);
		}

		//DirectXの固定機能に最後に作成したカメラ変換行列をセットする//
		inline void SetProMat()
		{
			device->SetTransform(D3DTS_PROJECTION, &projectionMat);
		}

		//DirectXの固定機能に最後に作成されたデータを元にカメラデータをセットする//
		inline void SetView()
		{
			device->SetTransform(D3DTS_VIEW, &viewMat);
			device->SetTransform(D3DTS_PROJECTION, &projectionMat);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//最後にセットしたデータを取得
		inline CamObj GetLastCamData() { return lastCamData; }

		//DirectXの固定機能にカメラ変換行列を取得する//
		inline D3DXMATRIX GetViewMatForDevice()
		{
			ChMat_9 tmpMat;

			device->GetTransform(D3DTS_VIEW, &tmpMat);

			return tmpMat;
		}

		//最後に作成したカメラ変換行列を取得する//
		inline D3DXMATRIX GetViewMat()
		{
			return viewMat;
		}

		//DirectXの固定機能に登録されている射影変換行列を取得する//
		inline D3DXMATRIX GetProMatForDevice()
		{
			ChMat_9 tmpMat;

			device->GetTransform(D3DTS_PROJECTION, &tmpMat);

			return tmpMat;
		}

		//最後に作成した射影変換行列を取得する//
		inline D3DXMATRIX GetProMat()
		{
			return projectionMat;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//MakeFunction//

		D3DXMATRIX MakeViewMatrix(const CamObj& _cam);

		D3DXMATRIX MakeViewMatrix(
			const D3DXVECTOR3& _camPos = ChVec3_9(0.0f, 0.0f, 0.0f)
			, const D3DXVECTOR3& _camLook = ChVec3_9(0.0f, 0.0f, 1.0f)
			, const D3DXVECTOR3& _camHead = ChVec3_9(0.0f, 1.0f, 0.0f));

		D3DXMATRIX MakeProjectionMatrix(
			const CamObj& _cam
			, const float _windWidth = 1280.0f
			, const float _windHeight = 720.0f
			, const float _viewAngDeg = 60.0f);

		D3DXMATRIX MakeProjectionMatrix(
			const float _lookNear = 1.0f
			, const float _lookDistant = 1000.0f
			, const float _windWidth = 1280.0f
			, const float _windHeight = 720.0f
			, const float _viewAngDeg = 60.0f);

		///////////////////////////////////////////////////////////////////////////////////

	private:

		LPDIRECT3DDEVICE9 device;

		ChMat_9 projectionMat;
		ChMat_9 viewMat;

		CamObj lastCamData;

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
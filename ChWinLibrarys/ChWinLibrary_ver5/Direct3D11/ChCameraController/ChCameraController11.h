#ifndef Ch_D3D11_Cam_h
#define Ch_D3D11_Cam_h

namespace ChD3D11
{
	class CameraController11
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//ViewMatrix���쐬����ۂɁA�����ŏ�������v�Z���Ȃ��B//
		ChMat_11 GetViewMat(
			const ChVec3_11& _pos
			, const ChVec3_11& _dir
			, const ChVec3_11& _up);

		//ViewMatrix���쐬����ۂɁA�����ŏ�������v�Z����B//
		ChMat_11 GetViewMat(
			const ChVec3_11& _pos
			, const ChVec3_11& _dir);

		//ViewMatrix���쐬����ۂɁA�����ŏ�������v�Z����B//
		ChMat_11 GetViewMat(
			const ChVec3_11& _pos
			, const ChQua_11& _rot);

		//�O��g�����f�[�^���g���܂킷//
		inline ChMat_11 GetViewMat()
		{
			return camMat;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//Singleton//

		static CameraController11& GetIns()
		{
			static CameraController11 ins;

			return ins;
		}

	protected:

		CameraController11(){}
		
		~CameraController11(){}

		ChMat_11 camMat;

	};

	static const std::function< CameraController11& ()>CamCon
		= CameraController11::GetIns;

}

#endif
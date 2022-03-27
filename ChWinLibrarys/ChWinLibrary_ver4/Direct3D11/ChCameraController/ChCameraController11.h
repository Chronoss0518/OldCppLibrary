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
			const ChVec3_11& _Pos
			, const ChVec3_11& _Dir
			, const ChVec3_11& _Up);

		//ViewMatrix���쐬����ۂɁA�����ŏ�������v�Z����B//
		ChMat_11 GetViewMat(
			const ChVec3_11& _Pos
			, const ChVec3_11& _Dir);

		//ViewMatrix���쐬����ۂɁA�����ŏ�������v�Z����B//
		ChMat_11 GetViewMat(
			const ChVec3_11& _Pos
			, const ChQua_11& _Rot);

		//�O��g�����f�[�^���g���܂킷//
		inline ChMat_11 GetViewMat()
		{
			return CamMat;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//Singleton//

		static CameraController11& GetIns()
		{
			static CameraController11 Ins;

			return Ins;
		}

	protected:

		CameraController11(){}
		
		~CameraController11(){}

		ChMat_11 CamMat;

	};

	static const std::function< CameraController11& ()>CamCon
		= CameraController11::GetIns;

}

#endif
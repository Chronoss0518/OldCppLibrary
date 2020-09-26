
#ifndef Ch_D3D11_DXCo_h
#define Ch_D3D11_DXCo_h

namespace ChD3D11
{

	//Direct3D9�𗘗p���邽�߂ɍ��ꂽ�N���X//
	//D3DX����������Ă���//
	class DirectX3D11:public ChCpp::ChCp::InitPack
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



		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Direct3D11�������ǂ�f�o�C�X�̎擾//
		inline const ID3D11Device* const GetDevice()
		{
			return Device;
		}

		//�`��������ǂ�f�o�C�X�̎擾//
		inline const ID3D11DeviceContext* const GetDC()
		{
			return DContext;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�f�o�C�X�����݂��邩���Ȃ����̊m�F//
		inline ChStd::Bool IsInstanse()
		{
			if (ChPtr::NullCheck(Device))return false;
			if (ChPtr::NullCheck(DContext))return false;
			if (ChPtr::NullCheck(Window))return false;
			return true;

		}

		///////////////////////////////////////////////////////////////////////////////////

	private:

		///////////////////////////////////////////////////////////////////////////////////

		void CreateDevice(
			const HWND _hWnd
			, const unsigned short _ScrW
			, const unsigned short _ScrH);

		///////////////////////////////////////////////////////////////////////////////////

		//��{�I�u�W�F�N�g�������ǂ�f�o�C�X//
		ID3D11Device* Device = nullptr;

		//�`��p�f�o�C�X//
		ID3D11DeviceContext* DContext = nullptr;

		//�ێ�����Window�f�[�^//
		IDXGISwapChain* Window;

		ChStd::Bool DFlg = false;

		

		///////////////////////////////////////////////////////////////////////////////////
		//SetSingleton
		///////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		inline DirectX3D11() {}

		inline ~DirectX3D11()
		{
			Release();
		}

	public:

		static DirectX3D11& GetInstans()
		{
			static DirectX3D11 Ins;
			return Ins;
		}


	};

	const static std::function<DirectX3D11&()> D3D11API = DirectX3D11::GetInstans;

	const static std::function<const ID3D11Device*()> D3D11Device
		= []()->const ID3D11Device* const
	{
		return DirectX3D11::GetInstans().GetDevice();
	};


	const static std::function<const ID3D11DeviceContext* const()> D3D11DC
		= []()->const ID3D11DeviceContext* const
	{
		return DirectX3D11::GetInstans().GetDC();
	};
}

#endif
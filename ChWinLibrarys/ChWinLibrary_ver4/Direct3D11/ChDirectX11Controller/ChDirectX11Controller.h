
#ifndef Ch_D3D11_DXCo_h
#define Ch_D3D11_DXCo_h

namespace ChD3D11
{

	//Direct3D11�𗘗p���邽�߂ɍ��ꂽ�N���X//
	class DirectX3D11:public ChCpp::ChCp::Initializer,ChCpp::ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndReleas//

		void Init(
			HWND _hWnd
			, const ChStd::Bool _FullScreenFlg
			, const unsigned short _ScrW
			, const unsigned short _ScrH
			, const unsigned short _ScrX = 5
			, const unsigned short _ScrY = 5);

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//



		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Direct3D11�������ǂ�f�o�C�X�̎擾//
		inline ID3D11Device* const GetDevice()
		{
			return Device;
		}

		//�`��������ǂ�f�o�C�X�̎擾//
		inline ID3D11DeviceContext* const GetDC()
		{
			return DContext;
		}

		inline IDXGISwapChain* const GetSC()
		{
			return Window;
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

	protected:

		///////////////////////////////////////////////////////////////////////////////////

		void CreateDevice(
			HWND _hWnd
			, const unsigned short _ScrW
			, const unsigned short _ScrH);

		///////////////////////////////////////////////////////////////////////////////////

		//��{�I�u�W�F�N�g�������ǂ�f�o�C�X//
		ID3D11Device* Device = nullptr;

		//�`��p�f�o�C�X//
		ID3D11DeviceContext* DContext = nullptr;

		//�ێ�����Window�f�[�^//
		IDXGISwapChain* Window = nullptr;

		ChStd::Bool DFlg = false;

		///////////////////////////////////////////////////////////////////////////////////
		//SetSingleton
		///////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		inline DirectX3D11() {}

	public:

		static DirectX3D11& GetInstans()
		{
			static DirectX3D11 Ins;
			return Ins;
		}


	};

	const static std::function<DirectX3D11&()> D3D11API = DirectX3D11::GetInstans;

	const static std::function<ID3D11Device*()> D3D11Device
		= []()->ID3D11Device* 
	{
		return DirectX3D11::GetInstans().GetDevice();
	};


	const static std::function<ID3D11DeviceContext*()> D3D11DC
		= []()->ID3D11DeviceContext*
	{
		return DirectX3D11::GetInstans().GetDC();
	};
}

#endif
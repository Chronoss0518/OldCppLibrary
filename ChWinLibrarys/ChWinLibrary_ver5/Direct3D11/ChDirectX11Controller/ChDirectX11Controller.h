
#ifndef Ch_D3D11_DXCo_h
#define Ch_D3D11_DXCo_h

namespace ChD3D11
{

	//Direct3D11�𗘗p���邽�߂ɍ��ꂽ�N���X//
	class DirectX3D11:public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndReleas//

		void Init(
			HWND _hWnd
			, const ChStd::Bool _fullScreenFlg
			, const unsigned short _scrW
			, const unsigned short _scrH
			, const unsigned short _scrX = 5
			, const unsigned short _scrY = 5);

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//



		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//Direct3D11�������ǂ�f�o�C�X�̎擾//
		inline ID3D11Device* const GetDevice()
		{
			return device;
		}

		//�`��������ǂ�f�o�C�X�̎擾//
		inline ID3D11DeviceContext* const GetDC()
		{
			return dContext;
		}

		inline IDXGISwapChain* const GetSC()
		{
			return window;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�f�o�C�X�����݂��邩���Ȃ����̊m�F//
		inline ChStd::Bool IsInstanse()
		{
			if (ChPtr::NullCheck(device))return false;
			if (ChPtr::NullCheck(dContext))return false;
			if (ChPtr::NullCheck(window))return false;
			return true;

		}

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		///////////////////////////////////////////////////////////////////////////////////

		void CreateDevice(
			HWND _hWnd
			, const unsigned short _scrW
			, const unsigned short _scrH);

		///////////////////////////////////////////////////////////////////////////////////

		//��{�I�u�W�F�N�g�������ǂ�f�o�C�X//
		ID3D11Device* device = nullptr;

		//�`��p�f�o�C�X//
		ID3D11DeviceContext* dContext = nullptr;

		//�ێ�����Window�f�[�^//
		IDXGISwapChain* window = nullptr;

		///////////////////////////////////////////////////////////////////////////////////
		//SetSingleton
		///////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		inline DirectX3D11() {}

	public:

		static DirectX3D11& GetInstans()
		{
			static DirectX3D11 ins;
			return ins;
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
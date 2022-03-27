#ifndef Ch_D3D9_ReTa_h
#define Ch_D3D9_ReTa_h

namespace ChD3D9
{
	class ShaderController;
}

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//�����_�[�^�[�Q�b�g��ݒ肷��N���X//
	class RenderTargetManager9:public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(
			const LPDIRECT3DDEVICE9& _dv
			, const unsigned short _windWidth
			, const unsigned short _windHeight
			, const ChD3D9::ShaderController* _shader = nullptr);

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�����_�[�^�[�Q�b�g�p�̃e�N�X�`����ݒ�//
		//�������ŉ�ʂ��N���A����F�w��//
		//ChD3D9::Shader::DrawStart�ƕ��p�ł��܂���//
		void SetRT(
			const std::string& _dataName
			, const D3DCOLOR _backCol = D3DCOLOR_ARGB(0, 0, 0, 0));

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�쐬�����e�N�X�`�����擾//
		inline ChPtr::Shared<Texture9> GetRTTexture(const std::string& _dataName)
		{
			if (rtList.find(_dataName) == rtList.end())return nullptr;
			return rtList[_dataName];
		}

		///////////////////////////////////////////////////////////////////////////////////

		//�o�^����Ă�e�N�X�`����I�����ď���//
		inline void DeleteRTTexture(const std::string& _dataName)
		{
			if (rtList.empty())return;
			if (rtList.find(_dataName) == rtList.end())return;

			rtList.erase(_dataName);

		}

		///////////////////////////////////////////////////////////////////////////////////

		//�o�^���Ă��邷�ׂẴ����_�[�^�[�Q�b�g�e�N�X�`�������//
		inline void ClearRT()
		{
			if (rtList.empty())return;
			rtList.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////

		//�����_�[�^�[�Q�b�g�ƂȂ�e�N�X�`�����쐬:�o�^//
		void CreateRT(
			const std::string& _dataName
			, const UINT _rtWidth = 1280
			, const UINT _rtHeight = 720
			, const _D3DFORMAT _format = D3DFMT_A8R8G8B8);

		///////////////////////////////////////////////////////////////////////////////////

		//�����_�[�^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂�//
		void ReturnRT();

	private:

		///////////////////////////////////////////////////////////////////////////////////

		LPDIRECT3DDEVICE9 device;

		std::map<std::string, ChPtr::Shared<BaseTexture9>>rtList;

		ChPtr::Shared<BaseTexture9>dbData;

		ChD3D9::ShaderController* uShader = nullptr;

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		RenderTargetManager9() {};


	public:

		static RenderTargetManager9& GetInc()
		{
			static RenderTargetManager9 ins;
			return ins;
		}

	};

	static const std::function<RenderTargetManager9&()> RTManager9 = RenderTargetManager9::GetInc;

}

#endif
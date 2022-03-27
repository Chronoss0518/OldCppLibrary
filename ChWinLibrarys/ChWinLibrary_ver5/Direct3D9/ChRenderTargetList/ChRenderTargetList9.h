#ifndef Ch_D3D9_RTList_h
#define Ch_D3D9_RTList_h

namespace ChD3D9
{
	class ShaderController;
}

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//�����_�[�^�[�Q�b�g��ݒ肷��N���X//
	typedef class RenderTargetList9 :public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		RenderTargetList9() {};

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
			const ChStd::DataNo _dataNum
			, const D3DCOLOR _backCol = D3DCOLOR_ARGB(0,0,0,0));

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�쐬�����e�N�X�`�����擾//
		inline ChPtr::Shared<Texture9> GetRTTexture(const ChStd::DataNo _dataNum)
		{
			if (rtList.find(_dataNum) == rtList.end())return nullptr;
			return rtList[_dataNum];
		}

		///////////////////////////////////////////////////////////////////////////////////

		//�o�^����Ă�e�N�X�`����I�����ď���//
		inline void DeleteRTTexture(const ChStd::DataNo _dataNum)
		{
			if (rtList.empty())return;
			if (rtList.find(_dataNum) == rtList.end())return;

			rtList.erase(_dataNum);

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
			const ChStd::DataNo _dataNum
			, const UINT _rtWidth = 1280
			, const UINT _rtHeight = 720
			, const _D3DFORMAT _FMT = D3DFMT_A8R8G8B8);

		///////////////////////////////////////////////////////////////////////////////////

		//�����_�[�^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂�//
		void ReturnRT();

	private:

		///////////////////////////////////////////////////////////////////////////////////

		LPDIRECT3DDEVICE9 device;

		std::map<ChStd::DataNo, ChPtr::Shared<BaseTexture9>>rtList;

		ChPtr::Shared<BaseTexture9>dbData = nullptr;

		ChD3D9::ShaderController* uShader = nullptr;

	}ChRTList9;

}

#endif
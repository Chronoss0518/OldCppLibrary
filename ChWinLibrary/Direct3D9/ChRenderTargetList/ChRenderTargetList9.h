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
	typedef class RenderTargetList9 :public ChCpp::ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		RenderTargetList9() {};

		~RenderTargetList9() { Release(); }

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(
			const LPDIRECT3DDEVICE9& _Dv
			, const unsigned short _WW
			, const unsigned short _WH
			, const ChD3D9::ShaderController* _Shader = nullptr);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�����_�[�^�[�Q�b�g�p�̃e�N�X�`����ݒ�//
		//�������ŉ�ʂ��N���A����F�w��//
		//ChD3D9::Shader::DrawStart�ƕ��p�ł��܂���//
		void SetRT(
			const ChStd::DataNo _DataNum
			, const D3DCOLOR _BackCol = D3DCOLOR_ARGB(0,0,0,0));

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�쐬�����e�N�X�`�����擾//
		inline ChPtr::Shared<Texture9> GetRTTexture(const ChStd::DataNo _DataNum)
		{
			if (RTList.find(_DataNum) == RTList.end())return nullptr;
			return RTList[_DataNum];
		}

		///////////////////////////////////////////////////////////////////////////////////

		//�o�^����Ă�e�N�X�`����I�����ď���//
		inline void DeleteRTTexture(const ChStd::DataNo _DataNum)
		{
			if (RTList.empty())return;
			if (RTList.find(_DataNum) == RTList.end())return;

			RTList.erase(_DataNum);

		}

		///////////////////////////////////////////////////////////////////////////////////

		//�o�^���Ă��邷�ׂẴ����_�[�^�[�Q�b�g�e�N�X�`�������//
		inline void ClearRT()
		{
			if (RTList.empty())return;
			RTList.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////

		//�����_�[�^�[�Q�b�g�ƂȂ�e�N�X�`�����쐬:�o�^//
		void CreateRT(
			const ChStd::DataNo _DataNum
			, const UINT _RTW = 1280
			, const UINT _RTH = 720
			, const _D3DFORMAT _FMT = D3DFMT_A8R8G8B8);

		///////////////////////////////////////////////////////////////////////////////////

		//�����_�[�^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂�//
		void ReturnRT();

	private:

		///////////////////////////////////////////////////////////////////////////////////

		LPDIRECT3DDEVICE9 Device;

		std::map<ChStd::DataNo, ChPtr::Shared<BaseTexture9>>RTList;

		ChPtr::Shared<BaseTexture9>DBData = nullptr;

		ChD3D9::ShaderController* UShader = nullptr;

	}ChRTList9;

}

#endif
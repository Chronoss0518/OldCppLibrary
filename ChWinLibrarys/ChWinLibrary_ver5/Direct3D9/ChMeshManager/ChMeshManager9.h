#ifndef Ch_D3D9_MeMa_h
#define Ch_D3D9_MeMa_h

class ChAnimationObject9;

namespace ChTex
{
	typedef class BaseTexture9 Texture9;
}

namespace ChMesh 
{

	typedef class BaseMesh9 Mesh9;

#ifndef _ChMesh9
#define _ChMesh9

	//���b�V���̒��_�f�[�^//
	struct MeshVertex9
	{
		ChVec3_9 pos;
		ChVec3_9 normal;
		D3DXVECTOR2 tex;
	};

	struct MeshFace9
	{
		unsigned long vertexNum[3];
		ChVec3_9 normal;
		ChVec3_9 centerPos;
	};

#endif

	class SkinMesh9;

	//�S�̂ŗ��p�����V���O���g���������ꂽ���b�V���}�l�[�W���[//
	//�S�̊Ǘ����s���Ă��邽�߁A�K�x��Clear���Ȃ���΂Ȃ�Ȃ�//
	class MeshManager9:public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		virtual void Init(const LPDIRECT3DDEVICE9 _de);

		virtual void Release()override;

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�g�p����f�B���N�g���̓o�^//
		void SetDirectoryPath(const std::string& _directoryPath
			, const std::string& _useDirectoryPashName);

		//�o�^�����f�B���N�g�����Mesh�̓o�^//
		void SetMesh(const std::string& _meshName
			, const std::string& _dataName
			, const std::string& _usePashName);

		//���o�^�ł���SkinMesh���܂��������Ă��Ȃ�//
		//�o�^�����f�B���N�g�����Mesh�̓o�^//
		void SetSkinMesh(const std::string& _meshName
			, const std::string& _dataName
			, const std::string& _usePashName);

		//�o�^����Ă���e�N�X�`�����擾//
		void SetTexture(
			const std::string& _dataName
			, const unsigned long _texNum
			, const ChPtr::Shared<ChTex::Texture9> _tex);

		//SkinMesh��p//
		//XFile���A�j���[�V�������擾//
		void SetAnimation(
			const std::string& _meshName
			, const std::string& _aniamtionName
			, const std::string& _xFileName);

		//SkinMesh��p//
		//�O���ō쐬�����A�j���[�V�������Z�b�g//
		void SetAnimation(
			const std::string& _meshName
			, const std::string& _aniamtionName
			, const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _animes);

		//SkinMesh��p//
		//�A�j���[�V���������t���[���ŏI�����邩��ݒ�//
		void SetAnimationTime(
			const std::string& _meshName
			, const std::string& _aniamtionName
			, const float _playAniTime);

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�O���ŗ��p����Mesh�̎擾//
		inline ChPtr::Shared<BaseMesh9> GetMesh(
			const std::string& _dataName)
		{
			if (meshList.empty())return nullptr;
			if (meshList.find(_dataName) == meshList.end())return nullptr;
			return meshList[_dataName];
		}

		//Mesh�ɓo�^����Ă���}�e���A���f�[�^���ׂĂ��擾//
		std::vector<ChPtr::Shared<ChMaterial_9>>& GetMeshMaterials(
			const std::string& _dataName);

		//���ݓo�^����Ă���f�B���N�g���p�X�̐�//
		inline size_t GetPathCnt() { return pathList.size(); }

		//���ݓo�^����Ă���Mesh�̐�//
		inline size_t GetMeshCnt() { return meshList.size(); }

		//�o�^����Ă���Mesh�̑I�������ʂ̖@���̎擾//
		MeshFace9 GetEasyFace(
			const std::string& _dataName
			, const unsigned long _faseNum);

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�o�^����Ă���p�X�����݂��邩�̊m�F//
		//���������ꍇ��true��Ԃ�//
		inline ChStd::Bool IsPath(const std::string& _find)
		{
			return pathList.find(_find) != pathList.end(); 
		}

		//�o�^����Ă���Mesh���X�g�擾//
		//���������ꍇ��true��Ԃ�//
		inline ChStd::Bool IsMesh(const std::string& _find)
		{
			return meshList.find(_find) != meshList.end();
		}

		///////////////////////////////////////////////////////////////////////////////////////

		//GetFaseBaseNormal�𗘗p����ې�ɌĂԕK�v������֐�//
		//�e�ʂɑ΂��Ă̖@�����쐬����//
		void CreateEasyFace(
			const std::string& _dataName
			, const unsigned short _baseMatNum);

		///////////////////////////////////////////////////////////////////////////////////////

		//�I������XFile���������//
		void ClearData(const std::string& _dataName);

		///////////////////////////////////////////////////////////////////////////////////////

		//�o�^����Ă���XFile���Œ�@�\�ŕ`�悷��//
		void DrawMesh(
			const ChMat_9& _mat
			, const std::string& _dataName
			, const long _subNum = -1);

	protected:

		static MeshFace9 nFace;

		static std::vector<ChPtr::Shared<ChMaterial_9>> nMaterial;

		std::map<std::string, ChPtr::Shared<ChMesh::BaseMesh9>> meshList;

		std::map<std::string, ChPtr::Shared<std::string>> pathList;

		LPDIRECT3DDEVICE9 device;

		///////////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		MeshManager9() {}

	public:

		static MeshManager9& GetInstance()
		{
			static MeshManager9 ins;
			return ins;
		}

	};

	static const std::function<MeshManager9&()>MeManager9 = MeshManager9::GetInstance;

}

#endif
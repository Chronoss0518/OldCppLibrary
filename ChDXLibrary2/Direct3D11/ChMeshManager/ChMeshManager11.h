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
		ChVec3_9 Pos;
		ChVec3_9 Normal;
		D3DXVECTOR2 Tex;
	};

	struct MeshFace9
	{
		unsigned long VertexNum[3];
		ChVec3_9 Normal;
		ChVec3_9 CenterPos;
	};

#endif

	class SkinMesh9;

	//�S�̂ŗ��p�����V���O���g���������ꂽ���b�V���}�l�[�W���[//
	//�S�̊Ǘ����s���Ă��邽�߁A�K�x��Clear���Ȃ���΂Ȃ�Ȃ�//
	class MeshManager9
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		virtual void Init(const LPDIRECT3DDEVICE9 _De);

		virtual void Release();

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//�g�p����f�B���N�g���̓o�^//
		void SetDirectoryPath(const std::string& _DirectoryPath
			, const std::string& _UseDirectoryPashName);

		//�o�^�����f�B���N�g�����Mesh�̓o�^//
		void SetMesh(const std::string& _MeshName
			, const std::string& _DataName
			, const std::string& _UsePashName);

		//���o�^�ł���SkinMesh���܂��������Ă��Ȃ�//
		//�o�^�����f�B���N�g�����Mesh�̓o�^//
		void SetSkinMesh(const std::string& _MeshName
			, const std::string& _DataName
			, const std::string& _UsePashName);

		//�o�^����Ă���e�N�X�`�����擾//
		void SetTexture(
			const std::string& _DataName
			, const unsigned long _TexNum
			, const ChPtr::Shared<ChTex::Texture9> _Tex);

		//SkinMesh��p//
		//XFile���A�j���[�V�������擾//
		void SetAnimation(
			const std::string& _MeshName
			, const std::string& _AniamtionName
			, const std::string& _XFileName);

		//SkinMesh��p//
		//�O���ō쐬�����A�j���[�V�������Z�b�g//
		void SetAnimation(
			const std::string& _MeshName
			, const std::string& _AniamtionName
			, const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _Animes);

		//SkinMesh��p//
		//�A�j���[�V���������t���[���ŏI�����邩��ݒ�//
		void SetAnimationTime(
			const std::string& _MeshName
			, const std::string& _AniamtionName
			, const float _PlayAniTime);

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�O���ŗ��p����Mesh�̎擾//
		inline ChPtr::Shared<BaseMesh9> GetMesh(
			const std::string& _DataName)
		{
			if (MeshList.empty())return nullptr;
			if (MeshList.find(_DataName) == MeshList.end())return nullptr;
			return MeshList[_DataName];
		}

		//Mesh�ɓo�^����Ă���}�e���A���f�[�^���ׂĂ��擾//
		std::vector<ChPtr::Shared<ChMaterial_9>>& GetMeshMaterials(
			const std::string& _DataName);

		//���ݓo�^����Ă���f�B���N�g���p�X�̐�//
		inline size_t GetPathCnt() { return PathList.size(); }

		//���ݓo�^����Ă���Mesh�̐�//
		inline size_t GetMeshCnt() { return MeshList.size(); }

		//�o�^����Ă���Mesh�̑I�������ʂ̖@���̎擾//
		MeshFace9 GetEasyFace(
			const std::string& _DataName
			, const unsigned long _FaseNum);

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�o�^����Ă���p�X�����݂��邩�̊m�F//
		//���������ꍇ��true��Ԃ�//
		inline ChStd::Bool IsPath(const std::string& _Find)
		{
			return PathList.find(_Find) != PathList.end(); 
		}

		//�o�^����Ă���Mesh���X�g�擾//
		//���������ꍇ��true��Ԃ�//
		inline ChStd::Bool IsMesh(const std::string& _Find)
		{
			return MeshList.find(_Find) != MeshList.end();
		}

		///////////////////////////////////////////////////////////////////////////////////////

		//GetFaseBaseNormal�𗘗p����ې�ɌĂԕK�v������֐�//
		//�e�ʂɑ΂��Ă̖@�����쐬����//
		void CreateEasyFace(
			const std::string& _DataName
			, const unsigned short _BaseMatNum);

		///////////////////////////////////////////////////////////////////////////////////////

		//�I������XFile���������//
		void ClearData(const std::string& _DataName);

		///////////////////////////////////////////////////////////////////////////////////////

		//�o�^����Ă���XFile���Œ�@�\�ŕ`�悷��//
		void DrawMesh(
			const ChMat_9& _Mat
			, const std::string& _DataName
			, const long _SubNum = -1);

	protected:

		static MeshFace9 NFace;

		static std::vector<ChPtr::Shared<ChMaterial_9>> NMaterial;

		std::map<std::string, ChPtr::Shared<ChMesh::BaseMesh9>> MeshList;

		std::map<std::string, ChPtr::Shared<std::string>> PathList;

		LPDIRECT3DDEVICE9 Device;

		///////////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		MeshManager9() {}

		~MeshManager9() { Release(); }

	public:

		static MeshManager9& GetInstance()
		{
			static MeshManager9 Ins;
			return Ins;
		}

	};

	static const std::function<MeshManager9&()>MeManager9 = MeshManager9::GetInstance;

}

#endif
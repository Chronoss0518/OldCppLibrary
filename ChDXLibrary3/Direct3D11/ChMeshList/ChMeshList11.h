#ifndef Ch_D3D9_MeLi_h
#define Ch_D3D9_MeLi_h

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

	//SmpXFile��p��enum class������āASetSmpXFile�̑������ɓ����B//
	//�ȍ~�������ɓ��ꂽ�������g����SmpXFile�𑀍삷��B//
	typedef class MeshList9 {
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//OperatorList//

		MeshList9& operator =(const MeshList9& _XList)
		{
			return *this;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		~MeshList9();

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//�����AXFile�t�H���_�[�Ȃǂ�����Ă��Ȃ��ꍇ�͑�������""������B//
		inline void Init(
			const LPDIRECT3DDEVICE9 _Dv
			, const std::string& _FileInDirectoryPath)
		{
			Device = _Dv;
			DirectoryPath = _FileInDirectoryPath;
		}

		inline void Release()
		{
			if (MeshList.empty())return;
			MeshList.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//Mesh�̓o�^(DataName���g����3D���f����I������)//
		void SetMesh(
			const std::string& _MeshName
			, const ChStd::DataNo DataNum);

		//���o�^�ł���SkinMesh���܂��������Ă��Ȃ�//
		//SkinMesh�̓o�^(DataName���g����3D���f����I������)//
		void SetSkinMesh(
			const std::string& _MeshName
			, const ChStd::DataNo _DataNum);

		//�o�^����Ă���Mesh�̉摜���ꕔ�ύX//
		void SetTexture(
			const ChStd::DataNo _DataNum
			, const unsigned long _TexNum
			, const ChPtr::Shared<ChTex::Texture9> _Tex);

		//SkinMesh��p//
		//XFile���A�j���[�V�������擾//
		void SetAnimation(
			const ChStd::DataNo _DataNum
			, const std::string& _AniamtionName
			, const std::string& _XFileName);

		//SkinMesh��p//
		//�O���ō쐬�����A�j���[�V�������Z�b�g//
		void SetAnimation(
			const ChStd::DataNo _DataNum
			, const std::string& _AniamtionName
			, const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _Animes);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�I������Mesh�̑I�������ʂ̃x�[�X�ƂȂ�@��//
		MeshFace9 GetEasyFace(
			const ChStd::DataNo _DataNum
			, const unsigned long _FaseNum);

		//�o�^����Ă���Mesh�̐�//
		inline const ChStd::DataNo GetMeshSize()
		{
			return (ChStd::DataNo)MeshList.size();
		}

		//�o�^����Ă���Mesh�̃}�e���A�����擾//
		std::vector<ChPtr::Shared<ChMaterial_9>>& GetMeshMaterials(
			const ChStd::DataNo _DataNum);

		//�`�掞�Ȃǂɗ��p�����Mesh���o��//
		inline ChPtr::Shared<BaseMesh9> GetMesh(const ChStd::DataNo DataNum)
		{
			if (MeshList.size() <= DataNum)return nullptr;

			return MeshList[DataNum];
		}

		///////////////////////////////////////////////////////////////////////////////////

		//���̊֐����ĂԂƊe�ʂɉ�������s�����߂̖@�������������B
		void CreateEasyFace(
			const ChStd::DataNo _DataNum
			, const unsigned short _BaseMatNum);

		///////////////////////////////////////////////////////////////////////////////////

		//�o�^����Ă���XFile��SubSet���Ƃɕ`�悷��//
		void DrawMesh(
			const ChMat_9 &_Mat
			, const ChStd::DataNo _DataNum
			, const long _SubNum = -1);

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		LPDIRECT3DDEVICE9 Device;

		std::string DirectoryPath;


		static MeshFace9 NFase;

		static std::vector<ChPtr::Shared<ChMaterial_9>> NMaterial;

		std::map<ChStd::DataNo, ChPtr::Shared<BaseMesh9>>MeshList;

	}ChMeshList9;

}

#endif
//CopyRight Chronoss0518 2018/08
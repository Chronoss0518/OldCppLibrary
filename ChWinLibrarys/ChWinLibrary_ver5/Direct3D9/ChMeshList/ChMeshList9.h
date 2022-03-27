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

	//SmpXFile��p��enum class������āASetSmpXFile�̑������ɓ����B//
	//�ȍ~�������ɓ��ꂽ�������g����SmpXFile�𑀍삷��B//
	typedef class MeshList9:public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//OperatorList//

		MeshList9& operator =(const MeshList9& _xList)
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
			const LPDIRECT3DDEVICE9 _dv
			, const std::string& _fileInDirectoryPath)
		{
			device = _dv;
			directoryPath = _fileInDirectoryPath;
			SetInitFlg(true);
		}

		inline void Release()override
		{
			if (meshList.empty())return;
			meshList.clear();
			SetInitFlg(false);
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//Mesh�̓o�^(DataName���g����3D���f����I������)//
		void SetMesh(
			const std::string& _meshName
			, const ChStd::DataNo _dataNum);

		//���o�^�ł���SkinMesh���܂��������Ă��Ȃ�//
		//SkinMesh�̓o�^(DataName���g����3D���f����I������)//
		void SetSkinMesh(
			const std::string& _meshName
			, const ChStd::DataNo _dataNum);

		//�o�^����Ă���Mesh�̉摜���ꕔ�ύX//
		void SetTexture(
			const ChStd::DataNo _dataNum
			, const unsigned long _texNum
			, const ChPtr::Shared<ChTex::Texture9> _tex);

		//SkinMesh��p//
		//XFile���A�j���[�V�������擾//
		void SetAnimation(
			const ChStd::DataNo _dataNum
			, const std::string& _aniamtionName
			, const std::string& _xFileName);

		//SkinMesh��p//
		//�O���ō쐬�����A�j���[�V�������Z�b�g//
		void SetAnimation(
			const ChStd::DataNo _dataNum
			, const std::string& _aniamtionName
			, const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _animes);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//�I������Mesh�̑I�������ʂ̃x�[�X�ƂȂ�@��//
		MeshFace9 GetEasyFace(
			const ChStd::DataNo _dataNum
			, const unsigned long _faseNum);

		//�o�^����Ă���Mesh�̐�//
		inline const ChStd::DataNo GetMeshSize()
		{
			return (ChStd::DataNo)meshList.size();
		}

		//�o�^����Ă���Mesh�̃}�e���A�����擾//
		std::vector<ChPtr::Shared<ChMaterial_9>>& GetMeshMaterials(
			const ChStd::DataNo _dataNum);

		//�`�掞�Ȃǂɗ��p�����Mesh���o��//
		inline ChPtr::Shared<BaseMesh9> GetMesh(const ChStd::DataNo _dataNum)
		{
			if (meshList.size() <= _dataNum)return nullptr;

			return meshList[_dataNum];
		}

		///////////////////////////////////////////////////////////////////////////////////

		//���̊֐����ĂԂƊe�ʂɉ�������s�����߂̖@�������������B
		void CreateEasyFace(
			const ChStd::DataNo _dataNum
			, const unsigned short _baseMatNum);

		///////////////////////////////////////////////////////////////////////////////////

		//�o�^����Ă���XFile��SubSet���Ƃɕ`�悷��//
		void DrawMesh(
			const ChMat_9 &_mat
			, const ChStd::DataNo _dataNum
			, const long _subNum = -1);

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		LPDIRECT3DDEVICE9 device;

		std::string directoryPath;


		static MeshFace9 nFace;

		static std::vector<ChPtr::Shared<ChMaterial_9>> nMaterial;

		std::map<ChStd::DataNo, ChPtr::Shared<BaseMesh9>>meshList;

	}ChMeshList9;

}

#endif
//CopyRight Chronoss0518 2018/08
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

	//メッシュの頂点データ//
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

	//全体で利用されるシングルトン生成されたメッシュマネージャー//
	//全体管理を行っているため、適度にClearしなければならない//
	class MeshManager9:public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		virtual void Init(const LPDIRECT3DDEVICE9 _de);

		virtual void Release()override;

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//使用するディレクトリの登録//
		void SetDirectoryPath(const std::string& _directoryPath
			, const std::string& _useDirectoryPashName);

		//登録したディレクトリよりMeshの登録//
		void SetMesh(const std::string& _meshName
			, const std::string& _dataName
			, const std::string& _usePashName);

		//※登録できるSkinMeshがまだ完成していない//
		//登録したディレクトリよりMeshの登録//
		void SetSkinMesh(const std::string& _meshName
			, const std::string& _dataName
			, const std::string& _usePashName);

		//登録されているテクスチャを取得//
		void SetTexture(
			const std::string& _dataName
			, const unsigned long _texNum
			, const ChPtr::Shared<ChTex::Texture9> _tex);

		//SkinMesh専用//
		//XFileよりアニメーションを取得//
		void SetAnimation(
			const std::string& _meshName
			, const std::string& _aniamtionName
			, const std::string& _xFileName);

		//SkinMesh専用//
		//外部で作成したアニメーションをセット//
		void SetAnimation(
			const std::string& _meshName
			, const std::string& _aniamtionName
			, const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _animes);

		//SkinMesh専用//
		//アニメーションが何フレームで終了するかを設定//
		void SetAnimationTime(
			const std::string& _meshName
			, const std::string& _aniamtionName
			, const float _playAniTime);

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//外部で利用するMeshの取得//
		inline ChPtr::Shared<BaseMesh9> GetMesh(
			const std::string& _dataName)
		{
			if (meshList.empty())return nullptr;
			if (meshList.find(_dataName) == meshList.end())return nullptr;
			return meshList[_dataName];
		}

		//Meshに登録されているマテリアルデータすべてを取得//
		std::vector<ChPtr::Shared<ChMaterial_9>>& GetMeshMaterials(
			const std::string& _dataName);

		//現在登録されているディレクトリパスの数//
		inline size_t GetPathCnt() { return pathList.size(); }

		//現在登録されているMeshの数//
		inline size_t GetMeshCnt() { return meshList.size(); }

		//登録されているMeshの選択した面の法線の取得//
		MeshFace9 GetEasyFace(
			const std::string& _dataName
			, const unsigned long _faseNum);

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//登録されているパスが存在するかの確認//
		//見つかった場合はtrueを返す//
		inline ChStd::Bool IsPath(const std::string& _find)
		{
			return pathList.find(_find) != pathList.end(); 
		}

		//登録されているMeshリスト取得//
		//見つかった場合はtrueを返す//
		inline ChStd::Bool IsMesh(const std::string& _find)
		{
			return meshList.find(_find) != meshList.end();
		}

		///////////////////////////////////////////////////////////////////////////////////////

		//GetFaseBaseNormalを利用する際先に呼ぶ必要がある関数//
		//各面に対しての法線を作成する//
		void CreateEasyFace(
			const std::string& _dataName
			, const unsigned short _baseMatNum);

		///////////////////////////////////////////////////////////////////////////////////////

		//選択したXFileを解放する//
		void ClearData(const std::string& _dataName);

		///////////////////////////////////////////////////////////////////////////////////////

		//登録されているXFileを固定機能で描画する//
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
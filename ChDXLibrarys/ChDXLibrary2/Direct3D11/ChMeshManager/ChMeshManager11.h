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

	//全体で利用されるシングルトン生成されたメッシュマネージャー//
	//全体管理を行っているため、適度にClearしなければならない//
	class MeshManager9
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		virtual void Init(const LPDIRECT3DDEVICE9 _De);

		virtual void Release();

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//使用するディレクトリの登録//
		void SetDirectoryPath(const std::string& _DirectoryPath
			, const std::string& _UseDirectoryPashName);

		//登録したディレクトリよりMeshの登録//
		void SetMesh(const std::string& _MeshName
			, const std::string& _DataName
			, const std::string& _UsePashName);

		//※登録できるSkinMeshがまだ完成していない//
		//登録したディレクトリよりMeshの登録//
		void SetSkinMesh(const std::string& _MeshName
			, const std::string& _DataName
			, const std::string& _UsePashName);

		//登録されているテクスチャを取得//
		void SetTexture(
			const std::string& _DataName
			, const unsigned long _TexNum
			, const ChPtr::Shared<ChTex::Texture9> _Tex);

		//SkinMesh専用//
		//XFileよりアニメーションを取得//
		void SetAnimation(
			const std::string& _MeshName
			, const std::string& _AniamtionName
			, const std::string& _XFileName);

		//SkinMesh専用//
		//外部で作成したアニメーションをセット//
		void SetAnimation(
			const std::string& _MeshName
			, const std::string& _AniamtionName
			, const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _Animes);

		//SkinMesh専用//
		//アニメーションが何フレームで終了するかを設定//
		void SetAnimationTime(
			const std::string& _MeshName
			, const std::string& _AniamtionName
			, const float _PlayAniTime);

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//外部で利用するMeshの取得//
		inline ChPtr::Shared<BaseMesh9> GetMesh(
			const std::string& _DataName)
		{
			if (MeshList.empty())return nullptr;
			if (MeshList.find(_DataName) == MeshList.end())return nullptr;
			return MeshList[_DataName];
		}

		//Meshに登録されているマテリアルデータすべてを取得//
		std::vector<ChPtr::Shared<ChMaterial_9>>& GetMeshMaterials(
			const std::string& _DataName);

		//現在登録されているディレクトリパスの数//
		inline size_t GetPathCnt() { return PathList.size(); }

		//現在登録されているMeshの数//
		inline size_t GetMeshCnt() { return MeshList.size(); }

		//登録されているMeshの選択した面の法線の取得//
		MeshFace9 GetEasyFace(
			const std::string& _DataName
			, const unsigned long _FaseNum);

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//登録されているパスが存在するかの確認//
		//見つかった場合はtrueを返す//
		inline ChStd::Bool IsPath(const std::string& _Find)
		{
			return PathList.find(_Find) != PathList.end(); 
		}

		//登録されているMeshリスト取得//
		//見つかった場合はtrueを返す//
		inline ChStd::Bool IsMesh(const std::string& _Find)
		{
			return MeshList.find(_Find) != MeshList.end();
		}

		///////////////////////////////////////////////////////////////////////////////////////

		//GetFaseBaseNormalを利用する際先に呼ぶ必要がある関数//
		//各面に対しての法線を作成する//
		void CreateEasyFace(
			const std::string& _DataName
			, const unsigned short _BaseMatNum);

		///////////////////////////////////////////////////////////////////////////////////////

		//選択したXFileを解放する//
		void ClearData(const std::string& _DataName);

		///////////////////////////////////////////////////////////////////////////////////////

		//登録されているXFileを固定機能で描画する//
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
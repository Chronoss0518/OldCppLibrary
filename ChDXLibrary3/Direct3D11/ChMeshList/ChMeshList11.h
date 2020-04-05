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

	//SmpXFile専用のenum classを作って、SetSmpXFileの第二引数に入れる。//
	//以降第二引数に入れた数字を使ってSmpXFileを操作する。//
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

		//もし、XFileフォルダーなどを作っていない場合は第二引数に""を入れる。//
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

		//Meshの登録(DataNameを使って3Dモデルを選択する)//
		void SetMesh(
			const std::string& _MeshName
			, const ChStd::DataNo DataNum);

		//※登録できるSkinMeshがまだ完成していない//
		//SkinMeshの登録(DataNameを使って3Dモデルを選択する)//
		void SetSkinMesh(
			const std::string& _MeshName
			, const ChStd::DataNo _DataNum);

		//登録されているMeshの画像を一部変更//
		void SetTexture(
			const ChStd::DataNo _DataNum
			, const unsigned long _TexNum
			, const ChPtr::Shared<ChTex::Texture9> _Tex);

		//SkinMesh専用//
		//XFileよりアニメーションを取得//
		void SetAnimation(
			const ChStd::DataNo _DataNum
			, const std::string& _AniamtionName
			, const std::string& _XFileName);

		//SkinMesh専用//
		//外部で作成したアニメーションをセット//
		void SetAnimation(
			const ChStd::DataNo _DataNum
			, const std::string& _AniamtionName
			, const std::map<std::string, ChPtr::Shared<ChAnimationObject9>>& _Animes);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//選択したMeshの選択した面のベースとなる法線//
		MeshFace9 GetEasyFace(
			const ChStd::DataNo _DataNum
			, const unsigned long _FaseNum);

		//登録されているMeshの数//
		inline const ChStd::DataNo GetMeshSize()
		{
			return (ChStd::DataNo)MeshList.size();
		}

		//登録されているMeshのマテリアルを取得//
		std::vector<ChPtr::Shared<ChMaterial_9>>& GetMeshMaterials(
			const ChStd::DataNo _DataNum);

		//描画時などに利用されるMeshを出力//
		inline ChPtr::Shared<BaseMesh9> GetMesh(const ChStd::DataNo DataNum)
		{
			if (MeshList.size() <= DataNum)return nullptr;

			return MeshList[DataNum];
		}

		///////////////////////////////////////////////////////////////////////////////////

		//この関数を呼ぶと各面に横滑りを行うための法線が生成される。
		void CreateEasyFace(
			const ChStd::DataNo _DataNum
			, const unsigned short _BaseMatNum);

		///////////////////////////////////////////////////////////////////////////////////

		//登録されているXFileをSubSetごとに描画する//
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
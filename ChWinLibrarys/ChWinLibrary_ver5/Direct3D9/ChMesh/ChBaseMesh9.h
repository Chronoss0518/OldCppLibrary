
#ifndef Ch_D3D9_BMe_h
#define Ch_D3D9_BMe_h


namespace ChTex
{
	typedef class BaseTexture9 Texture9;
}

class ChObjectController9;

namespace ChMesh
{

	class MeshManager9;
	class MeshList9;

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

	//D3DXMeshを操る基底クラス//
	typedef class BaseMesh9:public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		virtual void SetSkin(){}

		void SetMaterialName(const std::string& _fileName);

		inline void SetMaterialCol(
			const unsigned long _Num
			,const ChVec4& _Dif) 
		{
			if (material.size() <= _Num)return;

			material[_Num]->Diffuse.a = _Dif.a;
			material[_Num]->Diffuse.r = _Dif.r;
			material[_Num]->Diffuse.g = _Dif.g;
			material[_Num]->Diffuse.b = _Dif.b;

		}

		inline void SetMaterialMatrix(
			const unsigned long _Num
			, const ChLMat& _Mat)
		{
			if (material.size() <= _Num)return;

			material[_Num]->mat = _Mat;

		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline const LPD3DXMESH GetMesh() const { return mesh; }

		inline std::vector<ChPtr::Shared<ChVec3_9>> GetVertexList()const
		{ 
			return offsetVertexList; 
		}

		inline std::vector<ChPtr::Shared<ChMaterial_9>> GetMaterials() const { return material; }

		inline std::vector<ChPtr::Shared<ChTex::BaseTexture9>> GetTex() const { return texList; }

		inline std::vector<ChPtr::Shared<ChTex::BaseTexture9>> GetNormalTex() const { return normalTex; }

		inline std::vector<ChPtr::Shared<MeshFace9>> GetFace() const { return easyFaceList; }
		
		virtual inline ChMat_9 GetBoneMat(const std::string& _str){ return ChMat_9(); }

		///////////////////////////////////////////////////////////////////////////////////

		void CreateEasyFaceList();

		///////////////////////////////////////////////////////////////////////////////////

		virtual void Draw(
			const ChMat_9& _mat
			, const LPDIRECT3DDEVICE9& _dev
			, const long _subNum = -1);

		///////////////////////////////////////////////////////////////////////////////////

		void CreateMesh(
			const std::string& _fileName
			, const std::string& _pathName
			, const LPDIRECT3DDEVICE9& _dev);

		///////////////////////////////////////////////////////////////////////////////////

		static ChPtr::Shared<BaseMesh9> MeshType(
			const std::string& _fileName);

		///////////////////////////////////////////////////////////////////////////////////

		static ChPtr::Shared<BaseMesh9> SkinMeshType(
			const std::string& _fileName);

		friend MeshManager9;
		friend MeshList9;
		friend ChObjectController9;

	protected:

		///////////////////////////////////////////////////////////////////////////////////

		virtual void OpenFile(
			const std::string& _fileName
			, const std::string& _pathName
			, const LPDIRECT3DDEVICE9& _dev) {}

		///////////////////////////////////////////////////////////////////////////////////
		//InsFunction//

		virtual LPD3DXMESH InsMesh() { return mesh; }

		std::vector<ChPtr::Shared<ChMaterial_9>>& InsMaterials() { return material; }

		std::vector<ChPtr::Shared<ChTex::BaseTexture9>>& InsTex() { return texList; }

		std::vector<ChPtr::Shared<ChTex::BaseTexture9>>& InsNormalTex() { return normalTex; }

		std::vector<ChPtr::Shared<MeshFace9>>& InsFace() { return easyFaceList; }

		///////////////////////////////////////////////////////////////////////////////////

		virtual void SetOffsetVertex();

		///////////////////////////////////////////////////////////////////////////////////

		LPD3DXMESH mesh = nullptr;//メッシュの形状//
		std::vector<ChPtr::Shared<ChMaterial_9>> material;//マテリアルの内容//
		std::vector<ChPtr::Shared<ChTex::BaseTexture9>> texList;//テクスチャーの内容//
		std::vector<ChPtr::Shared<ChTex::BaseTexture9>> normalTex;//法線マッピング//

		std::vector<ChPtr::Shared<ChVec3_9>>optimalVertexList;//最適化した頂点//
		std::vector<ChPtr::Shared<MeshFace9>>easyFaceList;//最適化した頂点//

		std::vector<ChPtr::Shared<ChVec3_9>>offsetVertexList;//初期の頂点位置//
		size_t vertexNum = 0;


	}Mesh9;



}

#endif
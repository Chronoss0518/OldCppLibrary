
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

	//D3DXMeshを操る基底クラス//
	typedef class BaseMesh9
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		BaseMesh9() {};

		virtual ~BaseMesh9() { Release(); }

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		virtual void SetSkin(){}

		void SetMaterialName(const std::string& _FileName);

		inline void SetMaterialCol(
			const unsigned long _Num
			,const ChVec4& _Dif) 
		{
			if (Material.size() <= _Num)return;

			Material[_Num]->Diffuse.a = _Dif.a;
			Material[_Num]->Diffuse.r = _Dif.r;
			Material[_Num]->Diffuse.g = _Dif.g;
			Material[_Num]->Diffuse.b = _Dif.b;

		}

		inline void SetMaterialMatrix(
			const unsigned long _Num
			, const ChLMat& _Mat)
		{
			if (Material.size() <= _Num)return;

			Material[_Num]->Mat = _Mat;

		}

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline const LPD3DXMESH GetMesh() const { return Mesh; }

		inline std::vector<ChPtr::Shared<ChVec3_9>> GetVertexList()const
		{ 
			return OffsetVertexList; 
		}

		inline std::vector<ChPtr::Shared<ChMaterial_9>> GetMaterials() const { return Material; }

		inline std::vector<ChPtr::Shared<ChTex::BaseTexture9>> GetTex() const { return TexList; }

		inline std::vector<ChPtr::Shared<ChTex::BaseTexture9>> GetNormalTex() const { return NormalTex; }

		inline std::vector<ChPtr::Shared<MeshFace9>> GetFace() const { return EasyFaceList; }
		
		virtual inline ChMat_9 GetBoneMat(const std::string& _Str){ return ChMat_9(); }

		///////////////////////////////////////////////////////////////////////////////////

		void CreateEasyFaceList();

		///////////////////////////////////////////////////////////////////////////////////

		virtual void Draw(
			const ChMat_9& _Mat
			, const LPDIRECT3DDEVICE9& _Dev
			, const long _SubNum = -1);

		///////////////////////////////////////////////////////////////////////////////////

		void CreateMesh(
			const std::string& _FileName
			, const std::string& _PathName
			, const LPDIRECT3DDEVICE9& _Dev);

		///////////////////////////////////////////////////////////////////////////////////

		static ChPtr::Shared<BaseMesh9> MeshType(
			const std::string& _FileName);

		///////////////////////////////////////////////////////////////////////////////////

		static ChPtr::Shared<BaseMesh9> SkinMeshType(
			const std::string& _FileName);

		friend MeshManager9;
		friend MeshList9;
		friend ChObjectController9;

	protected:

		///////////////////////////////////////////////////////////////////////////////////

		virtual void OpenFile(
			const std::string& _FileName
			, const std::string& _PathName
			, const LPDIRECT3DDEVICE9& _Dev) {}

		///////////////////////////////////////////////////////////////////////////////////
		//InsFunction//

		virtual LPD3DXMESH InsMesh() { return Mesh; }

		std::vector<ChPtr::Shared<ChMaterial_9>>& InsMaterials() { return Material; }

		std::vector<ChPtr::Shared<ChTex::BaseTexture9>>& InsTex() { return TexList; }

		std::vector<ChPtr::Shared<ChTex::BaseTexture9>>& InsNormalTex() { return NormalTex; }

		std::vector<ChPtr::Shared<MeshFace9>>& InsFace() { return EasyFaceList; }

		///////////////////////////////////////////////////////////////////////////////////

		virtual void SetOffsetVertex();

		///////////////////////////////////////////////////////////////////////////////////

		LPD3DXMESH Mesh = nullptr;//メッシュの形状//
		std::vector<ChPtr::Shared<ChMaterial_9>> Material;//マテリアルの内容//
		std::vector<ChPtr::Shared<ChTex::BaseTexture9>> TexList;//テクスチャーの内容//
		std::vector<ChPtr::Shared<ChTex::BaseTexture9>> NormalTex;//法線マッピング//

		std::vector<ChPtr::Shared<ChVec3_9>>OptimalVertexList;//最適化した頂点//
		std::vector<ChPtr::Shared<MeshFace9>>EasyFaceList;//最適化した頂点//

		std::vector<ChPtr::Shared<ChVec3_9>>OffsetVertexList;//初期の頂点位置//
		size_t VertexNum = 0;


	}Mesh9;



}

#endif
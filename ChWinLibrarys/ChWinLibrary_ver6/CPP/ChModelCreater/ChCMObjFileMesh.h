#ifndef Ch_CPP_ObjMesh_h
#define Ch_CPP_ObjMesh_h

#ifndef Ch_CPP_CMesh_h
#include"ChModelCreater.h"
#endif

namespace ChCpp
{

	class TextObject;

	class CMObjFile :public ModelCreater
	{
	protected:

		struct ObjFileMaterialData
		{
			ChVec3 Ambient;
			ChVec3 Diffuse;
			ChVec3 Specular;

			float SpePow = 1.0f;
			float Alpha = 1.0f;
			float ODensity = 1.0f;

			std::string AmbientMap = "";
			std::string DiffuseMap = "";
			std::string SpecularMap = "";
			std::string SpecularHighLightMap = "";
			std::string BumpMap = "";
			std::string MetallicMap = "";
			std::string AlphaMap = "";
			std::string NormalMap = "";
		};

		struct ObjFileModelData
		{
			struct MeshData
			{

				struct Data
				{
					unsigned long VertexNum;
					unsigned long NormalNum;
					unsigned long UVNum;
				};

				std::string TargetMaterialName = "";
				std::vector<ChPtr::Shared<Data>> Values;
			};

			//std::vector<ChPtr::Shared<ObjFileModelData>> ChildObjects;
			//ChPtr::Shared<ObjFileModelData> ParentObject = nullptr;

			std::vector<ChPtr::Shared<MeshData>> MeshDatas;
		};

		///////////////////////////////////////////////////////////////////////////////////////

		//モデルデータの読み込み口//
		void CreateModel(const std::string& _FilePath)override;

		void CreateObject(const std::string& _ObjectName);

		void CreateMaterials(const std::string& _FileName);

		void CreateMaterial(const std::string& _MatName);

		void CreateChFrame(ChPtr::Shared<ChCpp::ModelFrame::Frame>& _Frame);

		///////////////////////////////////////////////////////////////////////////////////////

		void OutModelFile(const std::string& _FilePath)override;

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetVertex(const std::string& _Line);

		void SetUV(const std::string& _Line);

		void SetNormal(const std::string& _Line);

		void SetFace(const std::string& _Line);

		void SetMateBlock(const std::string& _Line);

		void SetMatAmbient(const std::string& _Line);

		void SetMatDiffuse(const std::string& _Line);

		void SetMatSpecular(const std::string& _Line);

		void SetMatSpecularHighLight(const std::string& _Line);

		//Alpha値//
		void SetMatDissolve(const std::string& _Line);

		//屈折率//
		void SetMatODensity(const std::string& _Line);

		void SetMatAmbientMap(const std::string& _Line);

		void SetMatDiffuseMap(const std::string& _Line);

		void SetMatSpecularMap(const std::string& _Line);

		void SetMatSpecularHighLightMap(const std::string& _Line);

		void SetMatBumpMap(const std::string& _Line);
		void SetMatBumpMap2(const std::string& _Line);

		void SetMatMetallicMap(const std::string& _Line);
		void SetMatMetallicMap2(const std::string& _Line);

		void SetMatNormalMap(const std::string& _Line);

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		///////////////////////////////////////////////////////////////////////////////////////
		//LoadFunction//

		std::string LoadTextureName(const std::string& _Line);

		///////////////////////////////////////////////////////////////////////////////////////

		std::map<std::string, ChPtr::Shared<ObjFileModelData>>ObjectMaps;
		std::map<std::string, ChPtr::Shared<ObjFileMaterialData>>MaterialMaps;

		std::string BlockMaterial = "";

		std::vector<ChPtr::Shared<ChVec3>> VertexDatas;
		std::vector<ChPtr::Shared<ChVec2>> UVDatas;
		std::vector<ChPtr::Shared<ChVec3>> NormalDatas;

		ChPtr::Shared<ObjFileModelData>MakeObject = nullptr;
		ChPtr::Shared<ObjFileMaterialData>TargetMaterial = nullptr;

		///////////////////////////////////////////////////////////////////////////////////////
		//Tags//
		
		const char CommentTags = '#';

		//ObjFileData//
		const char UseMaterialFileNameTags[6] = { 'm','t','l','l','i','b' };

		const char MaterialBlockTags[6] = { 'u','s','e','m','t','l' };

		const char ObjectBlockTags = 'o';

		//const char GroupBlockTags = 'g';

		//const std::string SmouthShadingBlockTags = "s ";

		const char VertexTags = 'v';

		const char UVTags[2] = { 'v','t' };

		const char NormalTags[2] = { 'v','n' };

		const char MeshTags = 'f';

		//const std::string LineTags = "l ";

		//const std::string ParamVertexTags = "vp ";

		//ObjFileMaterialData//
		const char MatMaterialBlockTags[6] = { 'n','e','w','m','t','l' };

		const char MatAmbientTags[2] = { 'K','a' };
			  
		const char MatDiffuseTags[2] = { 'K','d' };
			  
		const char MatSpecularTags[2] = { 'K','s' };

		const char MatSpecularHighLightTags[2] = { 'N','s' };
			  
		const char MatDissolveTags = 'd';
		
		//const std::string MatUnDissolveTags = "Tr ";

		//屈折率//
		const char MatODensityTags[2] = { 'N','i' };

		//const std::string MatLightObjectTags = "illum ";

		//MaterialMapTags//
		const char MatAmbientMapTags[6] = { 'm','a','p','_','K','a' };

		const char MatDiffuseMapTags[6] = { 'm','a','p','_','K','d' };

		const char MatSpecularMapTags[6] = { 'm','a','p','_','K','s' };

		const char MatSpecularHighLightMapTags[6] = { 'm','a','p','_','N','s' };

		const char MatDissolveMapTags[5] = { 'm','a','p','_','d' };

		const char MatBumpMapTags[8] =  { 'm','a','p','_','b','u','m','p' };
		const char MatBumpMapTags2[4] = { 'b','u','m','p'};

		//const std::string MatDisplateMapTags = "disp ";

		//const std::string MatDecalMapTags = "decal ";

		//const char MatRoughnessMapTags[2][6] = { { 'm','a','p','_','P','r' },{ 'P','r',0,0,0} };

		const char MatMetallicMapTags[6] = { 'm','a','p','_','P','m' };
		const char MatMetallicMapTags2[2] = { 'P','m'};

		//const std::string MatSheenMapTags[2] = { "map_Ps","Ps" };

		//const std::string MatClearcoatThicknessMapTags = "Pc ";

		//const std::string MatClearcoatRoughnessMapTags = "Pcr ";

		//const std::string MatRadiationMapTags[2] = { "map_Ke" ,"Ke" };

		//const std::string MatAnisotropyMapTags = "aniso ";

		//const std::string MatAnisotropyRotateMapTags = "anisor ";

		const char MatNormalMapTags[4] = { 'n','o','r','m' };

	};

}

#endif
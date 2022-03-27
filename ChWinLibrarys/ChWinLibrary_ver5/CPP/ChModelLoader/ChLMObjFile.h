#ifndef Ch_CPP_ObjMesh_h
#define Ch_CPP_ObjMesh_h

#ifndef Ch_CPP_MLoader_h
#include"ChModelLoader.h"
#endif

namespace ChCpp
{
	class TextObject;

	namespace ModelLoader
	{

		class ObjFile :public ModelLoaderBase
		{
		protected:

			struct ObjFileMaterialData
			{
				ChVec3 ambient;
				ChVec3 diffuse;
				ChVec3 specular;

				float spePow = 1.0f;
				float alpha = 1.0f;
				float ODensity = 1.0f;

				std::string ambientMap = "";
				std::string diffuseMap = "";
				std::string specularMap = "";
				std::string specularHighLightMap = "";
				std::string bumpMap = "";
				std::string metallicMap = "";
				std::string alphaMap = "";
				std::string normalMap = "";
			};

			struct ObjFileModelData
			{
				struct MeshData
				{

					struct Data
					{
						unsigned long vertexNum;
						unsigned long normalNum;
						unsigned long uvNum;
					};

					std::string targetMaterialName = "";
					std::vector<ChPtr::Shared<Data>> values;
				};

				std::vector<ChPtr::Shared<ChVec3>> vertexDatas;
				std::vector<ChPtr::Shared<ChVec2>> uvDatas;
				std::vector<ChPtr::Shared<ChVec3>> normalDatas;

				unsigned long sVertex = 0;
				unsigned long sUV = 0;
				unsigned long sNormal = 0;

				//std::vector<ChPtr::Shared<ObjFileModelData>> ChildObjects;
				//ChPtr::Shared<ObjFileModelData> ParentObject = nullptr;

				std::vector<ChPtr::Shared<MeshData>> meshDatas;
				std::string objectName;
			};

			///////////////////////////////////////////////////////////////////////////////////////

			//モデルデータの読み込み口//
			void CreateModel(const std::string& _filePath)override;

			void CreateObject(const std::string& _objectName);

			void CreateMaterials(const std::string& _fileName);

			void CreateMaterial(const std::string& _aatName);

			void CreateChFrame(ChPtr::Shared<ChCpp::ModelFrame::Frame>& _frame);

			///////////////////////////////////////////////////////////////////////////////////////

			void OutModelFile(const std::string& _filePath)override;

			///////////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetVertex(const std::string& _line);

			void SetUV(const std::string& _line);

			void SetNormal(const std::string& _line);

			void SetFace(const std::string& _line);

			void SetMateBlock(const std::string& _line);

			void SetMatAmbient(const std::string& _line);

			void SetMatDiffuse(const std::string& _line);

			void SetMatSpecular(const std::string& _line);

			void SetMatSpecularHighLight(const std::string& _line);

			//Alpha値//
			void SetMatDissolve(const std::string& _line);

			//屈折率//
			void SetMatODensity(const std::string& _line);

			void SetMatAmbientMap(const std::string& _line);

			void SetMatDiffuseMap(const std::string& _line);

			void SetMatSpecularMap(const std::string& _line);

			void SetMatSpecularHighLightMap(const std::string& _line);

			void SetMatBumpMap(const std::string& _line);
			void SetMatBumpMap2(const std::string& _line);

			void SetMatMetallicMap(const std::string& _line);
			void SetMatMetallicMap2(const std::string& _line);

			void SetMatNormalMap(const std::string& _line);

			///////////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			///////////////////////////////////////////////////////////////////////////////////////
			//LoadFunction//

			std::string LoadTextureName(const std::string& _line);

			///////////////////////////////////////////////////////////////////////////////////////

			std::string folderPath = "";

			std::vector<ChPtr::Shared<ObjFileModelData>>objects;

			//std::map<std::string, ChPtr::Shared<ObjFileModelData>>ObjectMaps;
			std::map<std::string, ChPtr::Shared<ObjFileMaterialData>>materialMaps;

			std::string blockMaterial = "";

			ChPtr::Shared<ObjFileModelData>makeObject = nullptr;
			ChPtr::Shared<ObjFileMaterialData>targetMaterial = nullptr;

			///////////////////////////////////////////////////////////////////////////////////////
			//Tags//

			const char commentTags = '#';

			//ObjFileData//
			const char useMaterialFileNameTags[6] = { 'm','t','l','l','i','b' };

			const char materialBlockTags[6] = { 'u','s','e','m','t','l' };

			const char objectBlockTags = 'o';

			//const char GroupBlockTags = 'g';

			//const std::string SmouthShadingBlockTags = "s ";

			const char vertexTags = 'v';

			const char uvTags[2] = { 'v','t' };

			const char normalTags[2] = { 'v','n' };

			const char meshTags = 'f';

			//const std::string LineTags = "l ";

			//const std::string ParamVertexTags = "vp ";

			//ObjFileMaterialData//
			const char matMaterialBlockTags[6] = { 'n','e','w','m','t','l' };

			const char matAmbientTags[2] = { 'K','a' };

			const char matDiffuseTags[2] = { 'K','d' };

			const char matSpecularTags[2] = { 'K','s' };

			const char matSpecularHighLightTags[2] = { 'N','s' };

			const char matDissolveTags = 'd';

			//const std::string MatUnDissolveTags = "Tr ";

			//屈折率//
			const char matODensityTags[2] = { 'N','i' };

			//const std::string MatLightObjectTags = "illum ";

			//MaterialMapTags//
			const char matAmbientMapTags[6] = { 'm','a','p','_','K','a' };

			const char matDiffuseMapTags[6] = { 'm','a','p','_','K','d' };

			const char matSpecularMapTags[6] = { 'm','a','p','_','K','s' };

			const char matSpecularHighLightMapTags[6] = { 'm','a','p','_','N','s' };

			const char matDissolveMapTags[5] = { 'm','a','p','_','d' };

			const char matBumpMapTags[8] = { 'm','a','p','_','b','u','m','p' };
			const char matBumpMapTags2[4] = { 'b','u','m','p' };

			//const std::string MatDisplateMapTags = "disp ";

			//const std::string MatDecalMapTags = "decal ";

			//const char MatRoughnessMapTags[2][6] = { { 'm','a','p','_','P','r' },{ 'P','r',0,0,0} };

			const char matMetallicMapTags[6] = { 'm','a','p','_','P','m' };
			const char matMetallicMapTags2[2] = { 'P','m' };

			//const std::string MatSheenMapTags[2] = { "map_Ps","Ps" };

			//const std::string MatClearcoatThicknessMapTags = "Pc ";

			//const std::string MatClearcoatRoughnessMapTags = "Pcr ";

			//const std::string MatRadiationMapTags[2] = { "map_Ke" ,"Ke" };

			//const std::string MatAnisotropyMapTags = "aniso ";

			//const std::string MatAnisotropyRotateMapTags = "anisor ";

			const char matNormalMapTags[4] = { 'n','o','r','m' };

		};
	}
}

#endif
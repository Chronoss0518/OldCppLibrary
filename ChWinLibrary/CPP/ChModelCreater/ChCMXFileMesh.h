#ifndef Ch_CPP_XMesh_h
#define Ch_CPP_XMesh_h

#include"ChModelCreater.h"

namespace ChCpp
{
	class CMXFile :public ModelCreater
	{
	protected:

		struct TemplateRange
		{
			size_t Bigen;
			size_t End;
			std::vector<ChPtr::Shared<TemplateRange>> Nest;
		};

		//モデルデータの読み込み口//
		void CreateMesh(const std::string& _FilePath)override;

		///////////////////////////////////////////////////////////////////////////////////////

		void OutMeshFile(const std::string& _FilePath)override;

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetFrame(
			ChPtr::Shared<BaseModel::Frame>& _Frames
			, const ChPtr::Shared<TemplateRange>& _TargetTemplate
			, unsigned long& _TemplateNo
			, const std::string& _Text);

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		ChStd::Bool IsTags(
			size_t& _OutTagPos
			, const std::string& _TagName
			, const ChPtr::Shared<TemplateRange> _LookTemplate
			, const std::string& _Text);

		///////////////////////////////////////////////////////////////////////////////////////

		void LoadToTemplates(
			const size_t& _Offset
			, const std::string& _Text);

		///////////////////////////////////////////////////////////////////////////////////////

		void SetToTemplate(
			ChPtr::Shared<TemplateRange> _Tmp
			, size_t& _BCnt
			, size_t& _ECnt
			, const std::vector<size_t>& _STemplateTags
			, const std::vector<size_t>& _ETemplateTags);

		///////////////////////////////////////////////////////////////////////////////////////
		//Structers//

		struct XVertex
		{
			ChVec3 Pos;
			ChVec3 Normal;
			ChVec2 UVPos;
		};

		struct XMaterial
		{
			std::string MaterialName;

			ChVec4 Diffuse;
			float SpecularPower;
			ChVec3 Specular;
			ChVec3 Ammbient;

			std::vector<std::string>TetureNameList;

		};

		struct XFace
		{
			std::vector<unsigned long> VertexNos;
			unsigned long MateNo;
		};

		struct XSkinWeight
		{
			std::string ArmatureName;
			std::map<unsigned long, float> WeightPow;
			ChLMat OffsetMatrix;
		};

		struct XMesh
		{

			std::vector<ChPtr::Shared<XVertex>>VertexList;
			std::vector<ChPtr::Shared<XMaterial>>MaterialList;
			std::vector<ChPtr::Shared<XFace>>FaceList;
			std::vector<ChPtr::Shared<XSkinWeight>>SkinWeightDatas;

		};

		struct XFrame
		{
			std::string FName;
			ChPtr::Shared<XMesh> Meshs;
			std::vector<ChPtr::Shared<XFrame>>Next;
		};

		ChStd::Bool exceptionFlg = false;

		ChPtr::Shared<TemplateRange> Templates;

		const std::string FrameTags = "Frame ";

		const std::string FrameTransformMatrixTags = "FrameTransformMatrix ";

		const std::string MeshTags = "Mesh ";

		const std::string GetNormalTags = "MeshNormals ";

		const std::string MaterialTags = "MeshMaterialList ";

		const std::string SkinWeightsTags = "SkinWeights ";

		const std::string UVTags = "MeshTextureCoords ";

	};

}

#endif
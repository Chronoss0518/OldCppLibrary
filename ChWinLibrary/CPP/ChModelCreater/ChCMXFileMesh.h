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
			ChPtr::Shared<BaseModel::Frame> &_Frames
			, size_t& _TextPos
			, const std::string& _Text);

		void SetMesh(
			ChPtr::Shared<BaseModel::Frame> &_Frames
			, size_t& _TextPos
			, const std::string& _Text);

		void SetVertexPos(
			ChPtr::Shared<BaseModel::Mesh>& _Meshs
			, size_t& _TextPos
			, const std::string& _Text);

		void SetVertexNormal(
			ChPtr::Shared<BaseModel::Mesh>& _Meshs
			, size_t& _TextPos
			, const std::string& _Text);

		void SetFace(
			ChPtr::Shared<BaseModel::Mesh> &_Meshs
			, size_t& _TextPos
			, const std::string& _Text);

		void SetMaterials(
			ChPtr::Shared<BaseModel::Mesh> &_Meshs
			, size_t& _TextPos
			, const std::string& _Text);

		void SetMaterial(
			ChPtr::Shared<BaseModel::Mesh>& _Meshs
			, size_t& _TextPos
			, const std::string& _Text);

		void SetUVMaps(
			ChPtr::Shared<BaseModel::Mesh>& _Meshs
			, size_t& _TextPos
			, const std::string& _Text);

		void SetWeight(
			ChPtr::Shared<BaseModel::Mesh>& _Meshs
			, size_t& _TextPos
			, const std::string& _Text);

		void SetVector3s(
			std::vector<ChVec3>& _Vector3s
			, size_t& _TextPos
			, const std::string& _Text
			, const std::string _EndChars = ";;"
			, const std::string _CutChars = ",");

		void SetVector2s(
			std::vector<ChVec2>& _Vector3s
			, size_t& _TextPos
			, const std::string& _Text
			, const std::string _EndChars = ";;"
			, const std::string _CutChars = ",");

		void SetValues(
			std::vector<std::vector<unsigned long>>& _Values
			, size_t& _TextPos
			, const std::string& _Text
			, const std::string _EndChars = ";;"
			, const std::string _CutChars = ",");

		void SetNums(
			std::vector<unsigned long>& _Values
			, size_t& _TextPos
			, const std::string& _Text
			, const std::string _EndChars = ";;"
			, const std::string _CutChars = ",");

		void SetFloats(
			std::vector<float>& _Values
			, size_t& _TextPos
			, const std::string& _Text
			, const std::string _EndChars = ";;"
			, const std::string _CutChars = ",");

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		std::string GetFrameTags()
		{
			return "Frame ";
		}

		std::string GetFrameTransformMatrixTags()
		{
			return "FrameTransformMatrix ";
		}

		std::string GetMeshTags()
		{
			return "Mesh ";
		}

		std::string GetNormalTags()
		{
			return "MeshNormals ";
		}

		std::string GetMaterialTags()
		{
			return "MeshMaterialList ";
		}

		std::string GetSkinWeightsTags()
		{
			return "SkinWeights ";
		}

		std::string GetUVTags()
		{
			return "MeshTextureCoords ";
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		ChStd::Bool IsException(const size_t& _val)
		{
			if (_val == std::string::npos)
			{
				exceptionFlg = true;
				return true;
			}

			return  false;
		}

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

		ChStd::Bool exceptionFlg = false;

		std::vector<ChPtr::Shared<TemplateRange>> Templates;

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
			unsigned long VertexNos[3];
			unsigned long MateNo;
		};

		struct XSkinWeight
		{
			unsigned long XVertexNo;
			float WeightPow;
		};

		struct XMesh
		{

			std::vector<ChPtr::Shared<XVertex>>VertexList;
			std::vector<ChPtr::Shared<XMaterial>>MaterialList;
			std::vector<ChPtr::Shared<XFace>>FaceList;
			std::map<std::string, ChPtr::Shared<XSkinWeight>>SkinWeightDatas;

		};

		struct XFrame
		{
			std::string FName;
			ChPtr::Shared<XMesh> Meshs;
			std::vector<ChPtr::Shared<XFrame>>Next;
		};

	};

}

#endif
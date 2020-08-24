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
			size_t Begin;
			size_t End;
		};

		//モデルデータの読み込み口//
		void CreateMesh(const std::string& _FilePath)override;

		///////////////////////////////////////////////////////////////////////////////////////

		void OutMeshFile(const std::string& _FilePath)override;

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//


		

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

		void ThroughTemplate(
			size_t& _TextPos
			, const std::string& _Text);

		///////////////////////////////////////////////////////////////////////////////////////

		ChStd::Bool exceptionFlg = false;

	};

}

#endif
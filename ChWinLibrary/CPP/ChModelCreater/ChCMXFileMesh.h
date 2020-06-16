#ifndef Ch_CPP_XMesh_h
#define Ch_CPP_XMesh_h

#include"ChModelCreater.h"

namespace ChCpp
{
	class CMXFileModel:public ModelCreater
	{
	protected:

		const std::string N_Frame = "Frame";

		const std::string N_TFrame = "FrameTransformMatrix {";

		const std::string N_Mesh = "Mesh {";

		const std::string N_MNormal = "MeshNormals {";

		const std::string N_MMaterials = "MeshMaterialList {";

		const std::string N_Material = "Material ";

		const std::string N_SkinWeights = "SkinWeight";

		const std::string N_AniTicks = "AnimTicksPerSecond {";

		const std::string N_AniSet = "AnimationSet ";

		const std::string N_Ani = "Animation {";

		const std::string N_AniFrameName = "{";

		const std::string N_AniKey = "AniamtionKey {";

		void CreateMesh(const std::string& _FilePath, ModelObject* _Model)override;

		///////////////////////////////////////////////////////////////////////////////////////

		void OutMeshFile(const std::string& _FilePath, const ModelObject* _Model)override;

		///////////////////////////////////////////////////////////////////////////////////////

		void SetFrame(size_t& _TextPos,const std::string& _Text);

		///////////////////////////////////////////////////////////////////////////////////////

		void SetMesh(size_t& _TextPos, ChPtr::Shared<Model::Frame> _Frames, const std::string& _Text);

		///////////////////////////////////////////////////////////////////////////////////////

		void SetVertex(size_t& _TextPos, ChPtr::Shared<Model::Mesh> _Meshs, const std::string& _Text);

		///////////////////////////////////////////////////////////////////////////////////////

		void SetFace(size_t& _TextPos, const std::string& _Text);

		///////////////////////////////////////////////////////////////////////////////////////

		void SetMaterial(size_t& _TextPos, const std::string& _Text);

	};

}

#endif
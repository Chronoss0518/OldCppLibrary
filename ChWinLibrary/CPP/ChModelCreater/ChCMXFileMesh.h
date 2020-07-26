#ifndef Ch_CPP_XMesh_h
#define Ch_CPP_XMesh_h

#include"ChModelCreater.h"

namespace ChCpp
{
	class CMXFile :public ModelCreater
	{
	protected:

		void CreateMesh(const std::string& _FilePath)override;

		///////////////////////////////////////////////////////////////////////////////////////

		void OutMeshFile(const std::string& _FilePath)override;

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetFrame(size_t& _TextPos, const std::string& _Text);

		void SetMesh(size_t& _TextPos, ChPtr::Shared<BaseModel::Frame> _Frames, const std::string& _Text);

		void SetVertex(size_t& _TextPos, ChPtr::Shared<BaseModel::Mesh> _Meshs, const std::string& _Text);

		void SetFace(size_t& _TextPos, const std::string& _Text);

		void SetMaterial(size_t& _TextPos, const std::string& _Text);

	};

}

#endif
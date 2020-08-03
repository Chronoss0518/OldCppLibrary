#ifndef Ch_CPP_XMesh_h
#define Ch_CPP_XMesh_h

#include"ChModelCreater.h"

namespace ChCpp
{
	class CMXFile :public ModelCreater
	{
	protected:

		//モデルデータの読み込み口//
		void CreateMesh(const std::string& _FilePath)override;

		///////////////////////////////////////////////////////////////////////////////////////

		void OutMeshFile(const std::string& _FilePath)override;

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetFrame(
			ChPtr::Shared<BaseModel::Frame> _Frames
			, size_t& _TextPos
			, const std::string& _Text);

		void SetMesh(
			ChPtr::Shared<BaseModel::Frame> _Frames
			, size_t& _TextPos
			, const std::string& _Text);

		void SetVertex(
			ChPtr::Shared<BaseModel::Mesh> _Meshs
			, size_t& _TextPos
			, const std::string& _Text);

		void SetFace(
			ChPtr::Shared<BaseModel::SurFace> _Meshs
			, size_t& _TextPos
			, const std::string& _Text);

		void SetMaterial(
			ChPtr::Shared<BaseModel::SurFace> _Meshs
			, size_t& _TextPos
			, const std::string& _Text);

		///////////////////////////////////////////////////////////////////////////////////////

		ChStd::Bool SuccesFlgs = false;

	};

}

#endif
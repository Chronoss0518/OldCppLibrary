#include"../../BaseIncluder/ChBase.h"

#include"../ChModel/ChModel.h"
#include"../ChModel/ChModelObject.h"

#include"ChModelCreater.h"
#include"ChCMXFileMesh.h"

using namespace ChCpp;

void ChCpp::ModelCreater::Init(ModelObject *_Model)
{
	Model = _Model;
}

///////////////////////////////////////////////////////////////////////////////////////
//ChXFileMesh Method//
///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::CreateMesh(const std::string& _FilePath)
{
	if (_FilePath.size() <= 0)return;
	if (_FilePath.rfind(".") == std::string::npos)return;

	std::string Text;

	{

		ChFIO::File Files;

		Files.FileOpen(_FilePath);

		Files.FileRead(Text);

		Files.FileClose();

		if (Text.length() <= 0)
		{
			std::remove(_FilePath.c_str());
			return;
		}
	}

	if (Text.find("xof") != 0)return;

	size_t TextPos = Text.find("xof");

	{
		std::string Tmp = "template Frame";
		size_t TmpLen = Text.find(Tmp);

		if (TmpLen != Tmp.npos) {
			TextPos = TmpLen;
			TextPos += Tmp.length();
		}
	}

	

	
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::OutMeshFile(const std::string& _FilePath)
{

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetFrame(size_t& _TextPos, const std::string& _Text)
{



}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetMesh(size_t& _TextPos, ChPtr::Shared<BaseModel::Frame> _Frames, const std::string& _Text)
{

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetVertex(
	size_t& _TextPos
	, ChPtr::Shared<BaseModel::Mesh> _Meshs
	, const std::string& _Text)
{

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetFace(size_t& _TextPos, const std::string& _Text)
{

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetMaterial(size_t& _TextPos, const std::string& _Text)
{

}

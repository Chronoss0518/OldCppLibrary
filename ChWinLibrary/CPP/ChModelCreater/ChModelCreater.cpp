#include"../../BaseIncluder/ChBase.h"

#include"../ChModel/ChModel.h"
#include"../ChModel/ChModelObject.h"

#include"ChModelCreater.h"
#include"ChCMXFileMesh.h"

using namespace ChCpp;

void ChCpp::ModelCreater::Init(BaseModel *_Model)
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
		size_t TmpLen = Text.find(Tmp,TextPos);

		if (TmpLen != Tmp.npos) {
			TextPos = TmpLen;
			TextPos += Tmp.length();
		}
	}

	size_t TmpLen = Text.find("Frame", TextPos);

	if (TmpLen == Text.npos)return;

	ChPtr::Shared<BaseModel> OutModels = nullptr;

	if (!SuccesFlgs)return;

	Model->ModelData = OutModels;

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::OutMeshFile(const std::string& _FilePath)
{

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetFrame(
	ChPtr::Shared<BaseModel::Frame> _Frames
	, size_t& _TextPos
	, const std::string& _Text)
{

	size_t TmpLen = _Text.find("Frame", _TextPos);

	std::string FrameTag = "Frame";

	_TextPos = TmpLen;
	_TextPos += FrameTag.length();

	TmpLen = _Text.find("{", _TextPos);

	if (TmpLen == _Text.npos)return;

	TmpLen -= 1;

	_Frames = ChPtr::Make_S<BaseModel::Frame>();

	_Frames->MyName = ChStd::RemoveToWhiteSpaceChars(_Text.substr(_TextPos, TmpLen - _TextPos));

	_TextPos = TmpLen;

	while (1)
	{
		TmpLen = _Text.find("{", _TextPos);

		if (_Text.npos == TmpLen)return;


	}


	//_Frames->BaseMat.Deserialize();



}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetMesh(
	ChPtr::Shared<BaseModel::Frame> _Frames
	, size_t& _TextPos
	, const std::string& _Text)
{

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetVertex(
	ChPtr::Shared<BaseModel::Mesh> _Meshs
	, size_t& _TextPos
	, const std::string& _Text)
{

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetFace(
	ChPtr::Shared<BaseModel::SurFace> _Meshs
	, size_t& _TextPos
	, const std::string& _Text)
{

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetMaterial(
	ChPtr::Shared<BaseModel::SurFace> _Meshs
	, size_t& _TextPos
	, const std::string& _Text)
{

}

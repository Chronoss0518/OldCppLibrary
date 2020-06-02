#include"../../BaseIncluder/ChBase.h"

#include"../ChModel/ChModel.h"
#include"ChModelCreater.h"
#include"ChCMXFileMesh.h"

void ChCpp::ModelCreater::Init(ModelObject *_Model)
{
	Model = _Model;
}


///////////////////////////////////////////////////////////////////////////////////////
//ChXFileMesh Method//
///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFileModel::CreateMesh(const std::string& _FilePath, ModelObject* _Model)
{
	if (_FilePath.size() <= 0)return;
	if (_FilePath.rfind(".") == std::string::npos)return;

	ChFIO::FileObject Text;

	{

		ChFIO::File Files;

		Files.FileOpen(_FilePath);

		Files.FileRead(Text);

		Files.FileClose();

		if (Text.GetText().length() <= 0)
		{
			std::remove(_FilePath.c_str());
			return;
		}
	}

	if (Text.GetText().find("xof") != 0)return;

	size_t TextPos = Text.GetText().find("xof");

	{
		std::string Tmp = "template Frame";
		size_t TmpLen = Text.GetText().find(Tmp);

		if (TmpLen != Tmp.npos) {
			TextPos = TmpLen;
			TextPos += Tmp.length();
		}
	}

	SetFrame(TextPos, Text);

	if (ModelDataIns().size() <= 0)return;

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFileModel::OutMeshFile(const std::string& _FilePath, const ModelObject* _Model)
{

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFileModel::SetFrame(size_t& _TextPos, const ChFIO::FileObject& _Text)
{

	{

		size_t FrameTagTestPos = 0;

		size_t FrameTransformMatrixTagTest = 0;

		{
			std::string Tmp;

			Tmp = "Frame ";

			FrameTagTestPos = _Text.FindLine(Tmp, _TextPos);

			if (FrameTagTestPos == 0)return;
			FrameTagTestPos += Tmp.length();

			Tmp = "FrameTransformMatrix {";

			FrameTransformMatrixTagTest = _Text.FindLine(Tmp, FrameTagTestPos);

			if (FrameTagTestPos == std::string::npos)return;

			FrameTransformMatrixTagTest += Tmp.length();

			auto frame = ChPtr::Make_S<Model::Frame>();

			size_t Test;

			Test = _Text.FindLine("}", FrameTransformMatrixTagTest);

			Tmp = _Text.SubStr(FrameTransformMatrixTagTest, Test + 1);

			frame->BaseMat.Deserialize(Tmp);

			_TextPos = Test + 1;

			SetMesh(_TextPos, frame, _Text);


		}

	}

	while (_Text.find("Frame ", _TextPos) != _Text.npos)
	{
		SetFrame(_TextPos, _Text);
	}




}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFileModel::SetMesh(size_t& _TextPos, ChPtr::Shared<Model::Frame> _Frames, const std::string& _Text)
{
	if (_Text.find("Mesh {", _TextPos) == _Text.npos)return;
	if (_Text.find("Mesh {", _TextPos) >= _Text.find("}", _TextPos))return;

	_Frames->Meshs = ChPtr::Make_S<Model::Mesh>();

	_TextPos = _Text.find("Mesh {", _TextPos);
	_TextPos = _Text.find("\n", _TextPos);

	SetVertex(_TextPos, _Frames->Meshs, _Text);

	SetFace(_TextPos, _Text);



}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFileModel::SetVertex(
	size_t& _TextPos
	, ChPtr::Shared<Model::Mesh> _Meshs
	, const std::string& _Text)
{

	std::string TmpText;
	unsigned long Num = 0;

	{
		std::string Tmp;

		size_t TmpNum = _Text.find(";", _TextPos);
		TmpNum -= _TextPos;
		Tmp = _Text.substr(_TextPos, TmpNum);

		Num = std::atoi(Tmp.c_str());

		_TextPos += TmpNum;
	}

	for (unsigned long i = 0; i < Num - 1; i++)
	{
		auto Ver = ChPtr::Make_S<Model::VertexData>();
		Ver->Pos.Deserialize(_Text, _TextPos, ";", ";,");
		_TextPos = _Text.find(";,", _TextPos);
		_Meshs->VertexList.push_back(Ver);
	}
	auto Ver = ChPtr::Make_S<Model::VertexData>();
	Ver->Pos.Deserialize(_Text, _TextPos, ";", ";;");
	_TextPos = _Text.find(";;", _TextPos);
	_Meshs->VertexList.push_back(Ver);


}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFileModel::SetFace(size_t& _TextPos, const std::string& _Text)
{

	unsigned long Num = 0;
	{
		std::string Tmp;

		size_t TmpNum = _Text.find(";", _TextPos);
		TmpNum -= _TextPos;
		Tmp = _Text.substr(_TextPos, TmpNum);

		Num = std::atoi(Tmp.c_str());

		_TextPos += TmpNum;
	}



}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFileModel::SetMaterial(size_t& _TextPos, const std::string& _Text)
{

}

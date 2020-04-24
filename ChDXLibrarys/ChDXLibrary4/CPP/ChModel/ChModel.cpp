
#include"../../ChInclude/ChGameBI.h"

#include"../ChTexture/ChBaseTexture.h"
#include"ChModel.h"
#include"ChXFileMesh.h"

using namespace ChCpp;

Model::Frame Model::Non;

std::map<
	std::string
	, std::function
	<ChPtr::Shared<ModelCreater>(const std::string& _FineName)>>
	Model::CreaterList;


///////////////////////////////////////////////////////////////////////////////////////
//Modelメソッド//
///////////////////////////////////////////////////////////////////////////////////////

void Model::Release()
{
	SetInitFlg(true);
	ModelData.clear();

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////////
//
//template<class T>
//void Model::SetMyModelCreater(const typename std::enable_if<std::is_base_of<ModelCreater, T>::value, std::string&>::type _ModelName)
//{
//
//	if (CreaterList.find(_ModelName) != CreaterList.end())return;
//
//	CreaterList[_ModelName] = 
//		[](const std::string& _FineName)->ChPtr::Shared<ModelCreater>
//	{
//
//		ChPtr::Shared<ModelCreater> Tmp;
//		Tmp = ChPtr::Make_S<T>();
//		return Tmp;
//	};
//
//	return;
//
//}template void Model::SetMyModelCreater<ModelCreater>(const typename std::enable_if<std::is_base_of<ModelCreater, ModelCreater>::value, std::string&>::type _ModelName);
//
//template<class T>
//void Model::SetMyModelCreater(const typename std::enable_if<!std::is_base_of<ModelCreater, T>::value, std::string&>::type _ModelName)
//{
//
//	return;
//
//}template void Model::SetMyModelCreater<int>(const typename std::enable_if<!std::is_base_of<ModelCreater, int>::value, std::string&>::type _ModelName);


///////////////////////////////////////////////////////////////////////////////////////

void Model::CreateModel(const std::string& _FilePath)
{

}

///////////////////////////////////////////////////////////////////////////////////////

void Model::OutModelFile(const std::string& _FilePath)
{

}

///////////////////////////////////////////////////////////////////////////////////////
//XFileMeshメソッド//
///////////////////////////////////////////////////////////////////////////////////////

void CXFileModel::CreateMesh(const std::string& _FilePath)
{
	if (_FilePath.size() <= 0)return;
	if (_FilePath.rfind(".") == std::string::npos)return;

	std::string Text;

	{

		ChFIO::File Files;

		Files.FileOpen(_FilePath);

		Text = Files.FileRead();

		Files.FileClose();

		if (Text.size() <= 0)
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

		if (TmpLen != Text.npos) {
			TextPos = TmpLen;
			TextPos += Tmp.length();
		}
	}

	SetFrame(TextPos, Text);

	if (ModelDataIns().size() <= 0)return;

}

///////////////////////////////////////////////////////////////////////////////////////

void CXFileModel::OutMeshFile(const std::string& _FilePath)
{

}

///////////////////////////////////////////////////////////////////////////////////////

void CXFileModel::SetFrame(size_t& _TextPos, const std::string& _Text)
{

	{

		size_t FrameTagTestPos = 0;

		size_t FrameTransformMatrixTagTest = 0;

		{
			std::string Tmp;

			Tmp = "Frame ";

			FrameTagTestPos = _Text.find(Tmp, _TextPos);

			if (FrameTagTestPos == std::string::npos)return;
			FrameTagTestPos += Tmp.length();

			Tmp = "FrameTransformMatrix {";

			FrameTransformMatrixTagTest = _Text.find(Tmp, FrameTagTestPos);

			if (FrameTagTestPos == std::string::npos)return;

			FrameTransformMatrixTagTest += Tmp.length();

			auto frame = ChPtr::Make_S<Model::Frame>();

			size_t Test;

			Test = _Text.find("}", FrameTransformMatrixTagTest);

			Tmp = _Text.substr(FrameTransformMatrixTagTest, Test + 1);

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

void CXFileModel::SetMesh(size_t& _TextPos, ChPtr::Shared<Model::Frame> _Frames, const std::string& _Text)
{
	if (_Text.find("Mesh {", _TextPos) == _Text.npos)return;
	if (_Text.find("Mesh {", _TextPos) >= _Text.find("}", _TextPos))return;

	_Frames->Meshs = ChPtr::Make_S<Model::Mesh>();

	_TextPos = _Text.find("Mesh {", _TextPos);
	_TextPos = _Text.find("\n", _TextPos);

	SetVertex(_TextPos, _Frames->Meshs, _Text);

	SetVertex(_TextPos, _Frames->Meshs, _Text);



}

///////////////////////////////////////////////////////////////////////////////////////

void CXFileModel::SetVertex(
	size_t& _TextPos
	, ChPtr::Shared<Model::Mesh> _Meshs
	, const std::string& _Text)
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

void CXFileModel::SetFace(size_t& _TextPos, const std::string& _Text)
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
/*
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
*/
}

///////////////////////////////////////////////////////////////////////////////////////

void CXFileModel::SetMaterial(size_t& _TextPos, const std::string& _Text)
{

}

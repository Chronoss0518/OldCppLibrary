#include"../../BaseIncluder/ChBase.h"

#include"../ChModel/ChModelObject.h"

#include"ChModelCreater.h"
#include"ChCMXFileMesh.h"

void ChCpp::ModelCreater::Init(ModelObject* _Model)
{
	Model = _Model;
}


void ChCpp::ModelCreater::SetModel(ChPtr::Shared<BaseModel> _Models)
{
	Model->Model = _Models;
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
		size_t TmpLen = Text.find(Tmp, TextPos);

		if (TmpLen != Tmp.npos) {
			TextPos = TmpLen;
			TextPos += Tmp.length();
		}
	}

	size_t TmpLen = Text.find("Frame", TextPos);
	if (TmpLen == Text.npos)return;

	TmpLen = Text.find("}", TmpLen);
	if (TmpLen == Text.npos)return;

	ChPtr::Shared<BaseModel> OutModels = nullptr;

	OutModels = ChPtr::Make_S<BaseModel>();

	SetFrame(OutModels->ModelData, TextPos, Text);

	if (exceptionFlg)return;

	SetModel(OutModels);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::OutMeshFile(const std::string& _FilePath)
{

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetFrame(
	ChPtr::Shared<BaseModel::Frame>& _Frames
	, size_t& _TextPos
	, const std::string& _Text)
{

	if (exceptionFlg)return;

	size_t TmpLen = _Text.find(GetFrameTags(), _TextPos);


	_TextPos = TmpLen;
	_TextPos += GetFrameTags().length();

	TmpLen = _Text.find("{", _TextPos);
	if (IsException(TmpLen))return;

	TmpLen -= 1;

	_Frames = ChPtr::Make_S<BaseModel::Frame>();

	_Frames->MyName = ChStd::RemoveToWhiteSpaceChars(_Text.substr(_TextPos, TmpLen - _TextPos));

	_TextPos = TmpLen + 1;



	while (1)
	{

		if (exceptionFlg)return;

		TmpLen = _Text.find("}", _TextPos);
		if (IsException(TmpLen))return;

		size_t TestPos = 0;

		//Set Normal Test//
		TestPos = _Text.find(GetFrameTags(), _TextPos);
		if (TestPos < TmpLen)
		{
			ChPtr::Shared<BaseModel::Frame>tmpFrame;

			SetFrame(tmpFrame, _TextPos, _Text);

			_Frames->ChildFrames.push_back(tmpFrame);


			continue;

		}


		//Set FrameTransformMatrix Test//
		TestPos = _Text.find(GetFrameTransformMatrixTags(), _TextPos);
		if (TestPos < TmpLen)
		{

			_TextPos = TestPos;

			_TextPos += GetFrameTransformMatrixTags().length() + 2;;


			_Frames->BaseMat.Deserialize(_Text, _TextPos);

			_TextPos = TmpLen + 1;


			continue;
		}

		//Set Mesh Test//
		TestPos = _Text.find(GetMeshTags(), _TextPos);
		if (TestPos < TmpLen)
		{
			_TextPos = TestPos;
			_TextPos += GetMeshTags().length() + 2;

			SetMesh(_Frames, _TextPos, _Text);
			continue;
		}

		break;
	}

	_TextPos = TmpLen;



}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetMesh(
	ChPtr::Shared<BaseModel::Frame>& _Frames
	, size_t& _TextPos
	, const std::string& _Text)
{
	if (exceptionFlg)return;


	ChPtr::Shared<BaseModel::Mesh> Meshs
		= ChPtr::Make_S<BaseModel::Mesh>();

	SetVertexPos(Meshs, _TextPos, _Text);

	SetFace(Meshs, _TextPos, _Text);

	size_t TmpLen = _Text.find(";", _TextPos);
	if (IsException(TmpLen))return;

	_TextPos = TmpLen + 1;

	while (1)
	{

		if (exceptionFlg)return;

		TmpLen = _Text.find("}", _TextPos);
		if (IsException(TmpLen))return;

		size_t TestPos = 0;

		//Set Normals//
		TestPos = _Text.find(GetNormalTags(), _TextPos);
		if (TestPos < TmpLen)
		{

			SetVertexNormal(Meshs, _TextPos, _Text);

			continue;
		}

		//Set MeshMaterialList//
		TestPos = _Text.find(GetMaterialTags(), _TextPos);
		if (TestPos < TmpLen)
		{

			SetMaterial(Meshs, _TextPos, _Text);

			continue;
		}

		//Set SkinWeights//
		TestPos = _Text.find(GetSkinWeightsTags(), _TextPos);
		if (TestPos < TmpLen)
		{

			SetWeight(Meshs, _TextPos, _Text);

			continue;
		}

		break;


	}



	_Frames->Meshs = Meshs;


}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetVertexPos(
	ChPtr::Shared<BaseModel::Mesh>& _Meshs
	, size_t& _TextPos
	, const std::string& _Text)
{

	if (exceptionFlg)return;

	{
		size_t TmpLen = _Text.find(";", _TextPos);
		if (IsException(TmpLen))return;

		_TextPos = TmpLen + 1;
	}

	std::vector<ChVec3>Poss;

	SetVector3s(Poss, _TextPos, _Text);

	if (exceptionFlg)return;

	for (auto Pos : Poss)
	{
		ChPtr::Shared<BaseModel::VertexData> Ver
			= ChPtr::Make_S<BaseModel::VertexData>();

		Ver->Pos = Pos;

		_Meshs->VertexList.push_back(Ver);
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetVertexNormal(
	ChPtr::Shared<BaseModel::Mesh>& _Meshs
	, size_t& _TextPos
	, const std::string& _Text)
{

	if (exceptionFlg)return;

	std::vector<ChVec3>Normals;

	std::map<unsigned long, unsigned long>VertexCount;


	if (exceptionFlg)return;

	{
		size_t TmpLen = _Text.find(";", _TextPos);
		if (IsException(TmpLen))return;

		_TextPos = TmpLen + 1;
	}

	SetVector3s(Normals, _TextPos, _Text);

	if (exceptionFlg)return;

	{
		size_t TmpLen = _Text.find(";", _TextPos);
		if (IsException(TmpLen))return;

		_TextPos = TmpLen + 1;
	}

	std::vector<std::vector<unsigned long>>Values;

	SetValues(Values, _TextPos, _Text);


	if (exceptionFlg)return;




}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetFace(
	ChPtr::Shared<BaseModel::Mesh>& _Meshs
	, size_t& _TextPos
	, const std::string& _Text)
{
	if (exceptionFlg)return;
	
	{
		size_t TmpLen = _Text.find(";", _TextPos);
		if (IsException(TmpLen))return;

		_TextPos = TmpLen + 1;
	}

	std::vector<std::vector<unsigned long>>Values;

	SetValues(Values, _TextPos, _Text);

	if (exceptionFlg)return;

	for (auto lis : Values)
	{

		ChPtr::Shared<BaseModel::SurFace>Fases
			= ChPtr::Make_S<BaseModel::SurFace>();

		for (auto No : lis)
		{

			Fases->VertexNo.push_back(No);
		}

		_Meshs->FaceList.push_back(Fases);
	}



}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetMaterial(
	ChPtr::Shared<BaseModel::Mesh>& _Meshs
	, size_t& _TextPos
	, const std::string& _Text)
{
	if (exceptionFlg)return;




}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetWeight(
	ChPtr::Shared<BaseModel::Mesh>& _Meshs
	, size_t& _TextPos
	, const std::string& _Text)
{
	if (exceptionFlg)return;

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetVector3s(
	std::vector<ChVec3>& _Vector3s
	, size_t& _TextPos
	, const std::string& _Text)
{

	if (exceptionFlg)return;

	size_t TmpLen = _Text.find(";;", _TextPos);
	if (IsException(TmpLen))return;

	std::string TmpText = _Text.substr(_TextPos, TmpLen - _TextPos);

	TmpText = ChStd::RemoveToWhiteSpaceChars(TmpText);

	size_t TmpSPos = 0;

	size_t TmpEPos = TmpText.find(";,", TmpSPos);

	while (TmpEPos <= TmpLen)
	{
		ChVec3 Normal;

		Normal.Deserialize(TmpText, TmpSPos, ";", ";,");

		TmpSPos = TmpEPos + 2;

		TmpEPos = TmpText.find(";,", TmpSPos);

		_Vector3s.push_back(Normal);

	}

	ChVec3 Normal;

	Normal.Deserialize(TmpText, TmpSPos, ";", ";;");

	TmpEPos = TmpText.find(";,", TmpSPos);

	_Vector3s.push_back(Normal);

	_TextPos = TmpLen + 2;


}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetValues(
	std::vector<std::vector<unsigned long>>& _Values
	, size_t& _TextPos
	, const std::string& _Text)
{

	if (exceptionFlg)return;

	size_t TmpLen = _Text.find(";", _TextPos);
	if (IsException(TmpLen))return;

	_TextPos = TmpLen;

	TmpLen = _Text.find(";;", TmpLen + 1);
	if (IsException(TmpLen))return;

	std::string TmpText = _Text.substr(_TextPos, TmpLen - _TextPos);

	TmpText = ChStd::RemoveToWhiteSpaceChars(TmpText);

	_TextPos = TmpLen + 2;

	TmpLen = TmpText.length();

	size_t TmpEPos = TmpText.find(";,", 1);
	if (IsException(TmpEPos))return;

	size_t TmpSPos = 0;

	while (TmpEPos <= TmpLen)
	{

		TmpSPos = TmpText.find(";", TmpSPos);
		if (IsException(TmpSPos))return;

		std::vector<unsigned long> TmpValues;

		while (TmpSPos <= TmpEPos)
		{

			size_t Tmp = TmpText.find(",", TmpSPos + 1);

			std::string TmpStr = TmpText.substr(TmpSPos + 1, Tmp - (TmpSPos + 1));

			long VerTexNo = std::atol(TmpStr.c_str());
			
			TmpValues.push_back(VerTexNo);


			TmpSPos = Tmp;

		}


		_Values.push_back(TmpValues);

		TmpEPos = TmpText.find(";,", TmpEPos + 1);
		TmpSPos += 1;

	}

	TmpSPos = TmpText.find(";", TmpSPos);
	TmpEPos = TmpText.length();

	std::vector<unsigned long> TmpValues;

	while (TmpSPos <= TmpEPos)
	{

		size_t Tmp = TmpText.find(",", TmpSPos + 1);

		std::string TmpStr = TmpText.substr(TmpSPos + 1, Tmp - (TmpSPos + 1));

		long VerTexNo = std::atol(TmpStr.c_str());

		TmpValues.push_back(VerTexNo);


		TmpSPos = Tmp;

	}



	_Values.push_back(TmpValues);

}
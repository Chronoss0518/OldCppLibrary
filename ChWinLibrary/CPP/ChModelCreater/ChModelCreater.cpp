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


		TestPos = _Text.find("{", _TextPos);
		if (TestPos >= TmpLen)
		{
			break;
		}

		_TextPos = TestPos + 1;
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

			SetMaterials(Meshs, _TextPos, _Text);

			continue;
		}

		//Set SkinWeights//
		TestPos = _Text.find(GetSkinWeightsTags(), _TextPos);
		if (TestPos < TmpLen)
		{

			SetWeight(Meshs, _TextPos, _Text);

			continue;
		}



		TestPos = _Text.find("{", _TextPos);
		if (TestPos >= TmpLen)
		{
			break;
		}

		_TextPos = TestPos + 1;

	}


	_TextPos = TmpLen + 1;

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

	_TextPos = _Text.find(GetNormalTags(), _TextPos)
		+ GetNormalTags().length();

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


	size_t TmpLen = _Text.find("}", _TextPos);
	if (IsException(TmpLen))return;

	_TextPos = TmpLen + 1;

	unsigned long FaseNo = 0;

	for (auto Value : Values)
	{

		if (Value.size() != _Meshs->FaceList[FaseNo]->VertexNo.size())
		{
			exceptionFlg = true;
			return;
		}

		for (unsigned long i = 0; i < Value.size(); i++)
		{
			if (VertexCount.find(_Meshs->FaceList[FaseNo]->VertexNo[i])
				== VertexCount.end())
				VertexCount[_Meshs->FaceList[FaseNo]->VertexNo[i]] = 0;
			unsigned long VerNo = _Meshs->FaceList[FaseNo]->VertexNo[i];
			VertexCount[VerNo] += 1;
			_Meshs->VertexList[VerNo]->Normal += Normals[Value[i]];
		}

		FaseNo++;

	}


	for (unsigned long i = 0; i < _Meshs->VertexList.size(); i++)
	{
		_Meshs->VertexList[i]->Normal /= VertexCount[i];
	}


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

void ChCpp::CMXFile::SetMaterials(
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

	std::vector<unsigned long> lValues;

	SetNums(lValues, _TextPos, _Text,";",",");
	
	if (lValues.size() != _Meshs->FaceList.size())
	{
		exceptionFlg = true;
		return;
	}

	{
		auto& Faces = _Meshs->FaceList;

		for (unsigned long i = 0; i < _Meshs->FaceList.size(); i++)
		{
			Faces[i]->Materials = lValues[i];
		}
	}


	//MaterialSet//
	while (1)
	{

	}



}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetMaterial(
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

	std::vector<unsigned long> lValues;

	SetNums(lValues, _TextPos, _Text, ";", ",");

	if (lValues.size() != _Meshs->FaceList.size())
	{
		exceptionFlg = true;
		return;
	}

	{
		auto& Faces = _Meshs->FaceList;

		for (unsigned long i = 0; i < _Meshs->FaceList.size(); i++)
		{
			Faces[i]->Materials = lValues[i];
		}
	}


	//MaterialSet//
	while (1)
	{

	}



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
	, const std::string& _Text
	, const std::string _EndChars
	, const std::string _CutChars)
{

	if (exceptionFlg)return;

	size_t TmpLen = _Text.find(_EndChars, _TextPos);
	if (IsException(TmpLen))return;

	std::string TmpText = _Text.substr(_TextPos, TmpLen - _TextPos);

	TmpText = ChStd::RemoveToWhiteSpaceChars(TmpText);

	size_t TmpSPos = 0;

	size_t TmpEPos = TmpText.find(";,", TmpSPos);

	while (TmpEPos <= TmpLen)
	{
		ChVec3 Vec;

		Vec.Deserialize(TmpText, TmpSPos, _CutChars, ";,");

		TmpSPos = TmpEPos + 2;

		TmpEPos = TmpText.find(";,", TmpSPos);

		_Vector3s.push_back(Vec);

	}

	ChVec3 Vec;

	Vec.Deserialize(TmpText, TmpSPos, _CutChars, _EndChars);

	TmpEPos = TmpText.find(";,", TmpSPos);

	_Vector3s.push_back(Vec);

	_TextPos = TmpLen + _EndChars.length();


}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetValues(
	std::vector<std::vector<unsigned long>>& _Values
	, size_t& _TextPos
	, const std::string& _Text
	, const std::string _EndChars
	, const std::string _CutChars)
{

	if (exceptionFlg)return;

	size_t TmpLen = _Text.find(";", _TextPos);
	if (IsException(TmpLen))return;

	_TextPos = TmpLen;

	TmpLen = _Text.find(_EndChars, TmpLen + 1);
	if (IsException(TmpLen))return;

	std::string TmpText = _Text.substr(_TextPos, TmpLen - _TextPos);

	TmpText = ChStd::RemoveToWhiteSpaceChars(TmpText);

	_TextPos = TmpLen + _EndChars.length();

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

			size_t Tmp = TmpText.find(_CutChars, TmpSPos + 1);

			std::string TmpStr = TmpText.substr(TmpSPos + 1, Tmp - (TmpSPos + 1));

			long Num = std::atol(TmpStr.c_str());

			TmpValues.push_back(Num);


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

		size_t Tmp = TmpText.find(_CutChars, TmpSPos + 1);

		std::string TmpStr = TmpText.substr(TmpSPos + 1, Tmp - (TmpSPos + 1));

		long Num = std::atol(TmpStr.c_str());

		TmpValues.push_back(Num);


		TmpSPos = Tmp;

	}



	_Values.push_back(TmpValues);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetNums(
	std::vector<unsigned long>& _Values
	, size_t& _TextPos
	, const std::string& _Text
	, const std::string _EndChars
	, const std::string _CutChars)
{

	if (exceptionFlg)return;

	size_t TmpLen = _Text.find(";", _TextPos);
	if (IsException(TmpLen))return;

	_TextPos = TmpLen;

	TmpLen = _Text.find(_EndChars, TmpLen + 1);
	if (IsException(TmpLen))return;

	std::string TmpText = _Text.substr(_TextPos + 1, TmpLen - _TextPos);

	TmpText = ChStd::RemoveToWhiteSpaceChars(TmpText);

	_TextPos = TmpLen + _EndChars.length();

	TmpLen = TmpText.length();


	size_t TmpPos = 0;

	size_t Test = TmpText.find(_CutChars, TmpPos);;


	while (Test <= TmpLen)
	{


		std::string TmpStr = TmpText.substr(TmpPos, Test - TmpPos - 1);

		long Tmp = std::atol(TmpStr.c_str());

		_Values.push_back(Tmp);

		TmpPos = Test + 1;

		Test = TmpText.find(_CutChars, TmpPos);

	}


	std::string TmpStr = TmpText.substr(TmpPos + 1, TmpLen - TmpPos - 1);

	long Tmp = std::atol(TmpStr.c_str());

	_Values.push_back(Tmp);





}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetFloats(
	std::vector<float>& _Values
	, size_t& _TextPos
	, const std::string& _Text
	, const std::string _EndChars
	, const std::string _CutChars)
{

	if (exceptionFlg)return;

	size_t TmpLen = _Text.find(";", _TextPos);
	if (IsException(TmpLen))return;

	_TextPos = TmpLen;

	TmpLen = _Text.find(_EndChars, TmpLen + 1);
	if (IsException(TmpLen))return;

	std::string TmpText = _Text.substr(_TextPos + 1, TmpLen - _TextPos);

	TmpText = ChStd::RemoveToWhiteSpaceChars(TmpText);

	_TextPos = TmpLen + _EndChars.length();

	TmpLen = TmpText.length();


	size_t TmpPos = 0;

	size_t Test = TmpText.find(_CutChars, TmpPos);;


	while (Test <= TmpLen)
	{


		std::string TmpStr = TmpText.substr(TmpPos, Test - TmpPos - 1);

		float Tmp = std::atof(TmpStr.c_str());

		_Values.push_back(Tmp);

		TmpPos = Test + 1;

		Test = TmpText.find(_CutChars, TmpPos);

	}


	std::string TmpStr = TmpText.substr(TmpPos + 1, TmpLen - TmpPos - 1);

	float Tmp = std::atof(TmpStr.c_str());

	_Values.push_back(Tmp);



}

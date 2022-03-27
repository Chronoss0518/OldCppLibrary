#include"../../BaseIncluder/ChBase.h"

#include"../ChTextObject/ChTextObject.h"
#include"../ChModel/ChModelObject.h"

#include"ChModelCreater.h"
#include"ChCMXFileMesh.h"
#include"ChCMObjFileMesh.h"

void ChCpp::ModelCreater::Init(ModelObject* _Model)
{
	OModel = _Model;
}


void ChCpp::ModelCreater::SetModel(ChPtr::Shared<ModelFrame> _Models)
{
	OModel->Model = _Models;
}

///////////////////////////////////////////////////////////////////////////////////////
//ChXFileMesh Method//
///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::CreateModel(const std::string& _FilePath)
{
	if (_FilePath.size() <= 0)return;

	std::string Text;
	{

		ChFIO::File Files;

		Files.FileOpen(_FilePath);

		Files.FileRead(Text);

		Files.FileClose();

		if (Text.length() <= 0)
		{
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

	ChPtr::Shared<TemplateRange> Templates = ChPtr::Make_S<TemplateRange>();

	LoadToTemplates(Templates, TextPos, Text);

	auto XModel = ChPtr::Make_S<XFileModelFrame>();

	for (auto&& Temp : Templates->Nest)
	{

		SetFrame(XModel->ModelData, Temp, Text);

		SetMesh(XModel->ModelData, Temp, Text);

	}

	if (exceptionFlg)return;

	ChPtr::Shared<ModelFrame> OutModels = nullptr;

	OutModels = ChPtr::Make_S<ModelFrame>();

	OutModels->ModelName = _FilePath;

	XFrameToChFrame(OutModels->ModelData, XModel->ModelData);

	SetModel(OutModels);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::OutModelFile(const std::string& _FilePath)
{

}

/////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetFrame(
	ChPtr::Shared<XFileModelFrame::XFrame>& _Frames
	, const ChPtr::Shared<TemplateRange>& _TargetTemplate
	, const std::string& _Text)
{
	if (exceptionFlg)return false;

	size_t FramePos;

	if (!IsTags(FramePos, FrameTags, _TargetTemplate, _Text))return false;

	FramePos += FrameTags.length();

	auto TmpFrame = ChPtr::Make_S<XFileModelFrame::XFrame>();

	TmpFrame->FName = _Text.substr(FramePos, _TargetTemplate->Bigen - FramePos);

	TmpFrame->FName = ChStr::RemoveToWhiteSpaceChars(TmpFrame->FName);

	for (auto&& Temp : _TargetTemplate->Nest)
	{
		if (SetFremeTransformMatrix(TmpFrame, Temp, _Text)) continue;

		{
			ChPtr::Shared<XFileModelFrame::XFrame> Obj = nullptr;

			if (SetFrame(Obj, Temp, _Text))
			{

				TmpFrame->Next.push_back(Obj);

				continue;
			}
		}

		if (SetMesh(TmpFrame, Temp, _Text)) continue;
	}

	_Frames = TmpFrame;

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetFremeTransformMatrix(
	ChPtr::Shared<XFileModelFrame::XFrame>& _Frames
	, const ChPtr::Shared<TemplateRange>& _TargetTemplate
	, const std::string& _Text)
{

	if (exceptionFlg)return false;

	if (!IsTags(FrameTransformMatrixTags, _TargetTemplate, _Text))return false;

	std::string UseText;

	{
		size_t TextLen = _TargetTemplate->End - _TargetTemplate->Bigen - 1;

		UseText = _Text.substr(_TargetTemplate->Bigen + 1, TextLen);
	}

	_Frames->frameMatrix.Deserialize(UseText, 0, ",", ";;");

	return true;

}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetMesh(
	ChPtr::Shared<XFileModelFrame::XFrame>& _Frames
	, const ChPtr::Shared<TemplateRange>& _TargetTemplate
	, const std::string& _Text)
{
	if (exceptionFlg)return false;

	if (!IsTags(MeshTags, _TargetTemplate, _Text))return false;

	if (_Frames == nullptr)
	{
		_Frames = ChPtr::Make_S<XFileModelFrame::XFrame>();
		_Frames->FName = "Root";
	}

	size_t TmpPos = _TargetTemplate->Bigen;

	TmpPos += 1;

	auto Meshs = ChPtr::Make_S<XFileModelFrame::XMesh>();

	{

		auto Values = GetArrayValues<XVECTOR>(_Text, TmpPos, ";,", ";;");

		for (auto&& Poss : Values)
		{
			auto Vertex = ChPtr::Make_S<XFileModelFrame::XVertex>();

			Vertex->Pos = Poss->value;

			Meshs->VertexList.push_back(Vertex);

		}

	}

	TmpPos = _Text.find(";;", TmpPos);
	TmpPos += 2;

	{
		auto Values = GetArrayValues<XMESHFACE>(_Text, TmpPos, ";,", ";;");

		for (auto&& Poss : Values)
		{
			auto Face = ChPtr::Make_S<XFileModelFrame::XFace>();

			for (auto&& No : Poss->value)
			{
				Face->VertexNos.push_back(No);
			}

			Meshs->FaceList.push_back(Face);

		}
	}

	_Frames->Meshs = Meshs;

	for (auto&& Temp : _TargetTemplate->Nest)
	{

		if (SetMeshNormal(_Frames, Temp, _Text)) continue;

		if (SetMeshTextureCoords(_Frames, Temp, _Text)) continue;

		if (SetMeshMaterialList(_Frames, Temp, _Text)) continue;

		if (SetSkinWeights(_Frames, Temp, _Text)) continue;

	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetMeshNormal(
	ChPtr::Shared<XFileModelFrame::XFrame>& _Frames
	, const ChPtr::Shared<TemplateRange>& _TargetTemplate
	, const std::string& _Text)
{
	if (exceptionFlg)return false;

	if (!IsTags(NormalTags, _TargetTemplate, _Text))return false;

	size_t TmpPos = _TargetTemplate->Bigen;

	TmpPos += 1;

	auto Normals = GetArrayValues<XVECTOR>(_Text, TmpPos, ";,", ";;");

	TmpPos = _Text.find(";;", TmpPos);
	TmpPos += 2;

	auto Faces = GetArrayValues<XMESHFACE>(_Text, TmpPos, ";,", ";;");

	for (unsigned long i = 0; i < Faces.size(); i++)
	{
		auto Mesh = _Frames->Meshs->FaceList[i];

		for (unsigned long j = 0; j < Mesh->VertexNos.size(); j++)
		{

			_Frames->Meshs->VertexList[Mesh->VertexNos[j]]->Normal +=
				Normals[Faces[i]->value[j]]->value;

		}
	}
	for (auto&& Vertex : _Frames->Meshs->VertexList)
	{
		if (Vertex->Normal.Len() == 1.00000000f)continue;
		Vertex->Normal.Normalize();
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetMeshTextureCoords(
	ChPtr::Shared<XFileModelFrame::XFrame>& _Frames
	, const ChPtr::Shared<TemplateRange>& _TargetTemplate
	, const std::string& _Text)
{
	if (exceptionFlg)return false;

	if (!IsTags(UVTags, _TargetTemplate, _Text))return false;

	size_t TmpPos = _TargetTemplate->Bigen;

	TmpPos += 1;

	auto UVs = GetArrayValues<XCOODS2D>(_Text, TmpPos, ";,", ";;");

	TmpPos = _Text.find(";;", TmpPos);
	TmpPos += 2;

	auto& VertexList = _Frames->Meshs->VertexList;

	for (unsigned long i = 0; i < VertexList.size(); i++)
	{
		VertexList[i]->UVPos = UVs[i]->value;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetMeshMaterialList(
	ChPtr::Shared<XFileModelFrame::XFrame>& _Frames
	, const ChPtr::Shared<TemplateRange>& _TargetTemplate
	, const std::string& _Text)
{
	if (exceptionFlg)return false;

	if (!IsTags(MaterialListTags, _TargetTemplate, _Text))return false;

	size_t TmpPos = _TargetTemplate->Bigen;

	TmpPos += 1;

	TmpPos = _Text.find(";", TmpPos);

	TmpPos += 1;

	auto MateNo = GetArrayValues<XDWORD>(_Text, TmpPos, ",", ";;");

	auto& Faces = _Frames->Meshs->FaceList;

	for (unsigned long i = 0; i < Faces.size(); i++)
	{
		Faces[i]->MateNo = MateNo[i]->value;
	}

	for (auto&& Temp : _TargetTemplate->Nest)
	{
		SetMaterial(_Frames, Temp, _Text);
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetMaterial(
	ChPtr::Shared<XFileModelFrame::XFrame>& _Frames
	, const ChPtr::Shared<TemplateRange>& _TargetTemplate
	, const std::string& _Text)
{
	if (exceptionFlg)return false;

	size_t MatePos;

	if (!IsTags(MatePos, MaterialTags, _TargetTemplate, _Text))return false;

	std::string MaterialName = "";

	MatePos += MaterialTags.length();

	MaterialName = _Text.substr(MatePos, _TargetTemplate->Bigen - MatePos);

	MaterialName = ChStr::RemoveToWhiteSpaceChars(MaterialName);

	size_t TmpPos = _TargetTemplate->Bigen;

	TmpPos += 1;

	ColorRGBA Diffuse;

	{
		std::string UseText = "";

		size_t tmpEnd = _Text.find(";;", TmpPos);
		tmpEnd += 2;

		UseText = _Text.substr(TmpPos, tmpEnd - TmpPos);

		TmpPos = tmpEnd;

		Diffuse.Desirialise(UseText, 0, ";;");
	}

	XFLOAT SpePow;

	{
		std::string UseText = "";

		size_t tmpEnd = _Text.find(";", TmpPos);
		tmpEnd += 1;

		UseText = _Text.substr(TmpPos, tmpEnd - TmpPos);

		TmpPos = tmpEnd;

		SpePow.Desirialise(UseText, 0, ";");
	}

	ColorRGB Specular;

	{
		std::string UseText = "";

		size_t tmpEnd = _Text.find(";;", TmpPos);
		tmpEnd += 2;

		UseText = _Text.substr(TmpPos, tmpEnd - TmpPos);

		TmpPos = tmpEnd;

		Specular.Desirialise(UseText, 0, ";;");
	}

	ColorRGB Ambient;

	{
		std::string UseText = "";

		size_t tmpEnd = _Text.find(";;", TmpPos);
		tmpEnd += 2;

		UseText = _Text.substr(TmpPos, tmpEnd - TmpPos);

		TmpPos = tmpEnd;

		Ambient.Desirialise(UseText, 0, ";;");
	}

	auto Mate = ChPtr::Make_S<XFileModelFrame::XMaterial>();

	Mate->MaterialName = MaterialName;
	Mate->Diffuse = Diffuse.value;
	Mate->SpecularPower = SpePow.value;
	Mate->Specular = Specular.value;
	Mate->Ambient = Ambient.value;

	for (auto&& Temp : _TargetTemplate->Nest)
	{

		if (!IsTags(TextureFilenameTag, Temp, _Text))continue;

		size_t Start = _Text.find("\"", Temp->Bigen);

		if (Start >= Temp->End)continue;

		size_t End = _Text.find("\"", Start + 1);

		if (End >= Temp->End)continue;

		std::string TexturePath = _Text.substr(Start + 1, End - Start - 1);

		Mate->TextureNameList.push_back(TexturePath);

	}

	_Frames->Meshs->MaterialList.push_back(Mate);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetSkinWeights(
	ChPtr::Shared<XFileModelFrame::XFrame>& _Frames
	, const ChPtr::Shared<TemplateRange>& _TargetTemplate
	, const std::string& _Text)
{

	if (exceptionFlg)return false;

	if (!IsTags(SkinWeightsTag, _TargetTemplate, _Text))return false;

	size_t TmpPos = _TargetTemplate->Bigen;

	TmpPos += 1;

	std::string BoneName;

	{
		size_t TmpStart = _Text.find("\"", TmpPos);

		size_t TmpEnd = _Text.find("\";", TmpPos);

		if (TmpStart > _TargetTemplate->End
			|| TmpEnd > _TargetTemplate->End)return true;


		BoneName = _Text.substr(TmpStart + 1, TmpEnd - TmpStart - 1);

		TmpPos = TmpEnd + 2;
	}

	TmpPos = _Text.find(";", TmpPos);
	TmpPos += 1;


	auto VertexNo = GetArrayValuesNC<XDWORD>(_Text, TmpPos, ",", ";");

	TmpPos = _Text.find(";", TmpPos);
	TmpPos += 1;

	auto WeightPow = GetArrayValuesNC<XFLOAT>(_Text, TmpPos, ",", ";");

	TmpPos = _Text.find(";", TmpPos);
	TmpPos += 1;

	ChLMat TmpOffMat;

	TmpOffMat.Deserialize(_Text, TmpPos, ",", ";;");

	auto SkinWeight = ChPtr::Make_S<XFileModelFrame::XSkinWeights>();

	SkinWeight->BoneOffset = TmpOffMat;

	SkinWeight->TargetFrameName = BoneName;

	{
		size_t WeightingCount = VertexNo.size();

		if (WeightingCount > WeightPow.size())WeightingCount = WeightPow.size();

		for (unsigned long i = 0; i < WeightingCount; i++)
		{
			SkinWeight->WeitPow[VertexNo[i]->value] = WeightPow[i]->value;
		}
	}

	_Frames->SkinWeightDatas.push_back(SkinWeight);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::IsTags(
	size_t& _OutTagPos
	, const std::string& _TagName
	, const ChPtr::Shared<TemplateRange> _LookTemplate
	, const std::string& _Text)
{

	size_t CheckStartPos
		= _Text.rfind("\n", _LookTemplate->Bigen);


	if (CheckStartPos == _Text.npos)
	{
		exceptionFlg = true;
		return false;
	}

	std::string tmp = _Text.substr(
		CheckStartPos
		, _LookTemplate->Bigen - CheckStartPos);

	size_t Checked = tmp.find(_TagName);

	if (Checked == _Text.npos)return false;

	_OutTagPos = _Text.find(_TagName, CheckStartPos);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::LoadToTemplates(
	ChPtr::Shared<TemplateRange>& _Templates
	, const size_t& _Offset
	, const std::string& _Text)
{
	std::vector<size_t>TemplateTags[2];
	char Tags[] = { '{','}' };

	for (size_t i = 0; i < 2; i++)
	{

		size_t offset = _Offset;

		while (1)
		{
			offset = _Text.find(Tags[i], offset + 1);

			if (offset >= _Text.npos)break;

			TemplateTags[i].push_back(offset);

		}
	}


	if (TemplateTags[0].size() != TemplateTags[1].size())
	{
		exceptionFlg = true;
		return;
	}


	size_t TempCount = TemplateTags[0].size();

	size_t BeginCount = 0;
	size_t EndCount = 0;

	_Templates = ChPtr::Make_S<TemplateRange>();

	_Templates->Bigen = 0;
	_Templates->End = 0;

	while (1)
	{

		if (BeginCount >= TemplateTags[0].size())
		{
			break;
		}

		SetToTemplate(
			_Templates
			, BeginCount
			, EndCount
			, TemplateTags[0]
			, TemplateTags[1]);

	}



}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetToTemplate(
	ChPtr::Shared<TemplateRange>& _Tmp
	, size_t& _BCnt
	, size_t& _ECnt
	, const std::vector<size_t>& _STemplateTags
	, const std::vector<size_t>& _ETemplateTags)
{

	if (_ECnt >= _ETemplateTags.size())
	{
		exceptionFlg = true;
		return;
	}

	auto Temp = ChPtr::Make_S<TemplateRange>();

	Temp->Bigen = _STemplateTags[_BCnt];

	_Tmp->Nest.push_back(Temp);

	_BCnt++;

	while (1)
	{

		if (_BCnt >= _STemplateTags.size())
		{

			Temp->End = _ETemplateTags[_ECnt];
			_ECnt++;
			break;
		}

		if (_STemplateTags[_BCnt] > _ETemplateTags[_ECnt])
		{
			Temp->End = _ETemplateTags[_ECnt];
			_ECnt++;
			break;
		}

		SetToTemplate(
			Temp
			, _BCnt
			, _ECnt
			, _STemplateTags
			, _ETemplateTags);


	}


}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::XFrameToChFrame(
	ChPtr::Shared<ModelFrame::Frame>& _ChFrame
	, const ChPtr::Shared<XFileModelFrame::XFrame>& _XFrame)
{


	_ChFrame = ChPtr::Make_S<ModelFrame::Frame>();

	_ChFrame->BaseMat = _XFrame->frameMatrix;
	_ChFrame->MyName = _XFrame->FName;


	for (auto&& Frame : _XFrame->Next)
	{
		ChPtr::Shared<ModelFrame::Frame> ChFrame = nullptr;

		XFrameToChFrame(ChFrame, Frame);

		_ChFrame->ChildFrames.push_back(ChFrame);

		ChFrame->Parent = _ChFrame;
	}

	std::map<unsigned long, unsigned long>SummarizeVertex;

	auto Meshs = ChPtr::Make_S<ModelFrame::Mesh>();

	if (_XFrame->Meshs == nullptr)return;
	//SetVertexList//
	{
		auto& XVertexList = _XFrame->Meshs->VertexList;

		auto& ChVertexList = Meshs->VertexList;

		for (unsigned long i = 0; i < XVertexList.size(); i++)
		{
			ChStd::Bool LookFlg = false;

			for (unsigned long j = 0; j < ChVertexList.size(); j++)
			{

				if (ChVertexList[j]->Pos != XVertexList[i]->Pos)continue;

				SummarizeVertex[i] = j;

				ChVertexList[j]->Normal += XVertexList[i]->Normal;

				LookFlg = true;

				break;

			}

			if (LookFlg)continue;


			SummarizeVertex[i] = ChVertexList.size();

			auto ChVertex = ChPtr::Make_S<ModelFrame::VertexData>();

			ChVertex->Pos = XVertexList[i]->Pos;
			ChVertex->Normal += XVertexList[i]->Normal;

			ChVertexList.push_back(ChVertex);

		}

		for (auto&& ChVertex : ChVertexList)
		{
			ChVertex->Normal.Normalize();
		}

	}

	//SetFaceList//
	{
		auto& XVertexList = _XFrame->Meshs->VertexList;

		auto& XFaceList = _XFrame->Meshs->FaceList;

		auto& ChFaceList = Meshs->FaceList;

		for (auto&& XFace : XFaceList)
		{
			unsigned long Counters[3];
			Counters[0] = 0;
			Counters[1] = 1;
			Counters[2] = XFace->VertexNos.size() - 1;

			ChStd::Bool UpperFlg = true;

			for (unsigned long i = 0; i < XFace->VertexNos.size() - 2; i++)
			{
				auto ChFace = ChPtr::Make_S<ModelFrame::SurFace>();

				for (unsigned long j = 0; j < 3; j++)
				{

					auto ChVertexData = ChPtr::Make_S<ModelFrame::SurFace::SurFaceVertex>();

					unsigned long VertexNo = SummarizeVertex[XFace->VertexNos[Counters[j]]];

					ChVertexData->VertexNo = VertexNo;
					ChVertexData->UVPos = XVertexList[XFace->VertexNos[Counters[j]]]->UVPos;


					ChFace->VertexData[j].UVPos = ChVertexData->UVPos;
					ChFace->VertexData[j].VertexNo = ChVertexData->VertexNo;
				}


				if (UpperFlg)
				{
					Counters[0] = Counters[1];
					Counters[1] = Counters[2] - 1;
				}
				else
				{
					Counters[2] = Counters[1];
					Counters[1] = Counters[0] + 1;
				}

				UpperFlg = !UpperFlg;

				ChFace->Materials = XFace->MateNo;

				ChFaceList.push_back(ChFace);
			}
		}


	}

	//SetMaterial//

	{
		auto& ChMateList = Meshs->MaterialList;
		auto& ChMateNos = Meshs->MaterialNo;

		unsigned long i = 0;

		for (auto&& XMate : _XFrame->Meshs->MaterialList)
		{
			auto ChMate = ChPtr::Make_S<ModelFrame::Material>();

			ChMate->Diffuse = XMate->Diffuse;
			ChMate->MaterialName = XMate->MaterialName;
			ChMate->Specular = XMate->Specular;
			ChMate->SpePow = XMate->SpecularPower;
			ChMate->AmbientPow = XMate->Ambient.Len() / 4.0f;

			for (unsigned long i = 0; i < XMate->TextureNameList.size(); i++)
			{
				switch (i)
				{
				case 0:ChMate->DiffuseMap = XMate->TextureNameList[i]; break;
				case 1:ChMate->NormalMap = XMate->TextureNameList[i]; break;
				case 2:ChMate->AmbientMap = XMate->TextureNameList[i]; break;
				case 3:ChMate->SpecularMap = XMate->TextureNameList[i]; break;
				case 4:ChMate->SpecularPowMap = XMate->TextureNameList[i]; break;
				case 5:ChMate->BumpMap = XMate->TextureNameList[i]; break;
				case 6:ChMate->AlphaMap = XMate->TextureNameList[i]; break;
				case 7:ChMate->MetallicMap = XMate->TextureNameList[i]; break;
				default:
					break;
				}

			}

			ChMateNos[ChMate->MaterialName] = i;

			ChMateList.push_back(ChMate);

			i++;

		}

	}

	_ChFrame->Meshs = Meshs;

}


///////////////////////////////////////////////////////////////////////////////////////
//ChCMObjeFile Method//
///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::CreateModel(const std::string& _FilePath)
{
	if (_FilePath.size() <= 0)return;

	ChCpp::TextObject Text;

	{
		std::string Tmp;

		ChFIO::File Files;

		Files.FileOpen(_FilePath);

		Files.FileRead(Tmp);

		Files.FileClose();

		if (Tmp.length() <= 0)
		{
			return;
		}

		Text.SetText(Tmp);
	}

	for (unsigned long i = 0; i < Text.LineCount(); i++)
	{
		if (Text[i].length() <= 0)continue;
		if (Text[i][0] == CommentTags)continue;

		CreateMaterials(Text[i]);

		CreateObject(Text[i]);
		SetVertex(Text[i]);
		SetUV(Text[i]);
		SetNormal(Text[i]);
		SetFace(Text[i]);
		SetMateBlock(Text[i]);
	}

	if (ObjectMaps.size() <= 0)return;

	auto OutModels = ChPtr::Make_S<ModelFrame>();

	OutModels->ModelName = _FilePath;

	OutModels->ModelData = ChPtr::Make_S<ModelFrame::Frame>();

	OutModels->ModelData->MyName = "Root";

	CreateChFrame(OutModels->ModelData);

	SetModel(OutModels);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::CreateObject(const std::string& _ObjectName)
{
	if (_ObjectName[0] != ObjectBlockTags)return;

	auto Name = _ObjectName.substr(2);

	MakeObject = nullptr;

	MakeObject = ChPtr::Make_S<ObjFileModelData>();
	ObjectMaps[Name] = MakeObject;

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::CreateMaterials(const std::string& _FileName)
{
	if (_FileName.size() < 8)return;
	if (_FileName[0] != UseMaterialFileNameTags[0])return;
	if (_FileName[1] != UseMaterialFileNameTags[1])return;
	if (_FileName[2] != UseMaterialFileNameTags[2])return;
	if (_FileName[3] != UseMaterialFileNameTags[3])return;
	if (_FileName[4] != UseMaterialFileNameTags[4])return;
	if (_FileName[5] != UseMaterialFileNameTags[5])return;

	std::string FileName = &_FileName[7];

	ChCpp::TextObject Text;

	{
		std::string Tmp;

		ChFIO::File Files;

		Files.FileOpen(FileName);

		Files.FileRead(Tmp);

		Files.FileClose();

		if (Tmp.length() <= 0)
		{
			return;
		}

		Text.SetText(Tmp);
	}

	for (unsigned long i = 0; i < Text.LineCount(); i++)
	{
		if (Text[i].length() <= 0)continue;
		if (Text[i][0] == CommentTags)continue;

		CreateMaterial(Text[i]);
		SetMatAmbient(Text[i]);
		SetMatDiffuse(Text[i]);
		SetMatSpecular(Text[i]);
		SetMatSpecularHighLight(Text[i]);
		SetMatDissolve(Text[i]);
		SetMatODensity(Text[i]);
		SetMatAmbientMap(Text[i]);
		SetMatDiffuseMap(Text[i]);
		SetMatSpecularMap(Text[i]);
		SetMatSpecularHighLightMap(Text[i]);
		SetMatBumpMap(Text[i]);
		SetMatMetallicMap(Text[i]);
		SetMatNormalMap(Text[i]);
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::CreateMaterial(const std::string& _MatName)
{

	if (_MatName.size() < 7)return;
	if (_MatName[0] != MatMaterialBlockTags[0])return;
	if (_MatName[1] != MatMaterialBlockTags[1])return;
	if (_MatName[2] != MatMaterialBlockTags[2])return;
	if (_MatName[3] != MatMaterialBlockTags[3])return;
	if (_MatName[4] != MatMaterialBlockTags[4])return;
	if (_MatName[5] != MatMaterialBlockTags[5])return;

	TargetMaterial = nullptr;

	TargetMaterial = ChPtr::Make_S<ObjFileMaterialData>();

	MaterialMaps[&_MatName[7]] = TargetMaterial;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::CreateChFrame(ChPtr::Shared<ChCpp::ModelFrame::Frame>& _Frame)
{

	for (auto&& Obj : ObjectMaps)
	{
		unsigned long MaterialNo = 0;

		auto Meshs = ChPtr::Make_S<ChCpp::ModelFrame::Mesh>();

		for (auto&& Vertexs : VertexDatas)
		{
			auto Ver = ChPtr::Make_S<ChCpp::ModelFrame::VertexData>();

			Ver->Pos = *Vertexs;

			Meshs->VertexList.push_back(Ver);

		}

		for (auto&& Face : Obj.second->MeshDatas)
		{

			if (Meshs->MaterialNo.find(Face->TargetMaterialName) == Meshs->MaterialNo.end())
			{

				Meshs->MaterialNo[Face->TargetMaterialName] = MaterialNo;

				auto Mate = ChPtr::Make_S<ChCpp::ModelFrame::Material>();

				auto TmpMate = MaterialMaps[Face->TargetMaterialName];

				Mate->MaterialName = Face->TargetMaterialName;

				Mate->Diffuse = TmpMate->Diffuse;
				Mate->Diffuse.a = TmpMate->Alpha;

				Mate->Specular = TmpMate->Specular;

				Mate->SpePow = TmpMate->SpePow;

				Mate->AmbientPow = TmpMate->Ambient.r + TmpMate->Ambient.g + TmpMate->Ambient.b;

				Mate->AmbientPow /= 3;

				Mate->DiffuseMap = TmpMate->DiffuseMap;
				Mate->AmbientMap = TmpMate->AmbientMap;
				Mate->SpecularMap = TmpMate->SpecularMap;
				Mate->SpecularPowMap = TmpMate->SpecularHighLightMap;
				Mate->BumpMap = TmpMate->BumpMap;
				Mate->AlphaMap = TmpMate->AlphaMap;
				Mate->NormalMap = TmpMate->NormalMap;
				Mate->MetallicMap = TmpMate->MetallicMap;

				Meshs->MaterialList.push_back(Mate);

				MaterialNo++;
			}

			std::vector<ChPtr::Shared<ChCpp::ModelFrame::SurFace::SurFaceVertex>>FVList;

			for (auto&& Values : Face->Values)
			{

				if (NormalDatas.size() <= Values->NormalNum - 1)
				{
					continue;
				}

				if (Meshs->VertexList.size() <= Values->VertexNum - 1)continue;

				auto faceVertex = ChPtr::Make_S<ChCpp::ModelFrame::SurFace::SurFaceVertex>();
				
				faceVertex->VertexNo = Values->VertexNum - 1;
				if(UVDatas.size() > Values->UVNum - 1)faceVertex->UVPos = *UVDatas[Values->UVNum - 1];

				FVList.push_back(faceVertex);

				Meshs->VertexList[Values->VertexNum - 1]->Normal += *NormalDatas[Values->NormalNum - 1];
			}

			if (FVList.size() >= 2)
			{
				unsigned long Counters[3];
				Counters[0] = 0;
				Counters[1] = 1;
				Counters[2] = FVList.size() - 1;

				ChStd::Bool UpperFlg = true;

				for (unsigned long i = 0; i < FVList.size() - 2; i++)
				{

					auto face = ChPtr::Make_S<ChCpp::ModelFrame::SurFace>();

					face->VertexData[0] = *FVList[Counters[2]];
					face->VertexData[1] = *FVList[Counters[1]];
					face->VertexData[2] = *FVList[Counters[0]];

					if (UpperFlg)
					{
						Counters[0] = Counters[1];
						Counters[1] = Counters[2] - 1;
					}
					else
					{
						Counters[2] = Counters[1];
						Counters[1] = Counters[0] + 1;
					}

					UpperFlg = !UpperFlg;

					Meshs->FaceList.push_back(face);
				}

			}


			for (auto&& Ver : Meshs->VertexList)
			{
				Ver->Normal.Normalize();
			}

		}

		auto Frame = ChPtr::Make_S< ChCpp::ModelFrame::Frame>();

		Frame->MyName = Obj.first;
		Frame->Parent = _Frame;
		Frame->Meshs = Meshs;

		_Frame->ChildFrames.push_back(Frame);
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::OutModelFile(const std::string& _FilePath)
{
	if (_FilePath.size() <= 0)return;
	if (_FilePath.rfind(".") == std::string::npos)return;

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetVertex(const std::string& _Line)
{
	if (_Line[0] != VertexTags)return;

	auto Pos = ChPtr::Make_S<ChVec3>();

	Pos->Deserialize(_Line, 2, " ");

	VertexDatas.push_back(Pos);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetUV(const std::string& _Line)
{
	if (_Line.size() < 3)return;
	if (_Line[0] != UVTags[0])return;
	if (_Line[1] != UVTags[1])return;

	auto UV = ChPtr::Make_S<ChVec2>();

	UV->Deserialize(_Line, 3, " ");

	UVDatas.push_back(UV);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetNormal(const std::string& _Line)
{
	if (_Line.size() < 3)return;
	if (_Line[0] != NormalTags[0])return;
	if (_Line[1] != NormalTags[1])return;

	auto Normal = ChPtr::Make_S<ChVec3>();

	Normal->Deserialize(_Line, 3, " ");

	NormalDatas.push_back(Normal);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetFace(const std::string& _Line)
{
	if (_Line[0] != MeshTags)return;

	unsigned long Pos = _Line.find(' ');

	unsigned long TmpPos = Pos;

	unsigned long End = 0;

	auto data = ChPtr::Make_S < ChCpp::CMObjFile::ObjFileModelData::MeshData>();

	data->TargetMaterialName = BlockMaterial;

	MakeObject->MeshDatas.push_back(data);

	ChStd::Bool EndFlg = false;

	while (1)
	{

		TmpPos = _Line.find(' ', Pos + 1);

		if (_Line.size() < TmpPos)
		{
			EndFlg = true;
			TmpPos = _Line.size();
		}

		auto Mdata = ChPtr::Make_S<ChCpp::CMObjFile::ObjFileModelData::MeshData::Data>();


		std::string Tmp = _Line.substr(Pos, TmpPos - Pos);

		unsigned long Val[3] = { 0xffffffff,0xffffffff ,0xffffffff };

		//SrashCount//
		unsigned long SCount = 0;

		unsigned long Start = 0;

		while (1)
		{
			End = Tmp.find('/', Start);

			if (Tmp.size() <= End)End = Tmp.size();

			std::string ST = Tmp.substr(Start, End - Start);

			if (Tmp[Start] != '/')
			{
				Val[SCount] = ChStr::GetIntegialFromText<unsigned long>(Tmp.substr(Start, End - Start));
			}

			if (Tmp.size() <= End)break;

			SCount++;
			Start = End + 1;
		}

		Pos += Tmp.length();

		Mdata->VertexNum = Val[0];
		Mdata->UVNum = Val[1];
		Mdata->NormalNum = Val[2];

		data->Values.push_back(Mdata);
		if (EndFlg)break;

		End = 0;

	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMateBlock(const std::string& _Line)
{

	if (_Line.size() < 7)return;
	if (_Line[0] != MaterialBlockTags[0])return;
	if (_Line[1] != MaterialBlockTags[1])return;
	if (_Line[2] != MaterialBlockTags[2])return;
	if (_Line[3] != MaterialBlockTags[3])return;
	if (_Line[4] != MaterialBlockTags[4])return;
	if (_Line[5] != MaterialBlockTags[5])return;

	BlockMaterial = &_Line[7];

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatAmbient(const std::string& _Line)
{
	if (_Line.size() < 3)return;
	if (_Line[0] != MatAmbientTags[0])return;
	if (_Line[1] != MatAmbientTags[1])return;

	TargetMaterial->Ambient.Deserialize(&_Line[3], 0, " ");
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatDiffuse(const std::string& _Line)
{

	if (_Line.size() < 3)return;
	if (_Line[0] != MatDiffuseTags[0])return;
	if (_Line[1] != MatDiffuseTags[1])return;

	TargetMaterial->Diffuse.Deserialize(&_Line[3], 0, " ");

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatSpecular(const std::string& _Line)
{

	if (_Line.size() < 3)return;
	if (_Line[0] != MatSpecularTags[0])return;
	if (_Line[1] != MatSpecularTags[1])return;

	TargetMaterial->Specular.Deserialize(&_Line[3], 0, " ");

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatSpecularHighLight(const std::string& _Line)
{

	if (_Line.size() < 3)return;
	if (_Line[0] != MatSpecularHighLightTags[0])return;
	if (_Line[1] != MatSpecularHighLightTags[1])return;

	TargetMaterial->SpePow = ChStr::GetFloatingFromText<float>(&_Line[3], 0);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatDissolve(const std::string& _Line)
{

	if (_Line.size() < 2)return;
	if (_Line[0] != MatDissolveTags)return;

	TargetMaterial->Alpha = ChStr::GetFloatingFromText<float>(&_Line[2], 0);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatODensity(const std::string& _Line)
{
	if (_Line.size() < 3)return;

	if (_Line[0] != MatODensityTags[0])return;
	if (_Line[1] != MatODensityTags[1])return;

	TargetMaterial->ODensity = ChStr::GetFloatingFromText<float>(&_Line[3], 0);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatAmbientMap(const std::string& _Line)
{
	if (_Line.size() < 7)return;

	if (_Line[0] != MatAmbientMapTags[0])return;
	if (_Line[1] != MatAmbientMapTags[1])return;
	if (_Line[2] != MatAmbientMapTags[2])return;
	if (_Line[3] != MatAmbientMapTags[3])return;
	if (_Line[4] != MatAmbientMapTags[4])return;
	if (_Line[5] != MatAmbientMapTags[5])return;

	TargetMaterial->AmbientMap = LoadTextureName(&_Line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatDiffuseMap(const std::string& _Line)
{

	if (_Line.size() < 7)return;

	if (_Line[0] != MatDiffuseMapTags[0])return;
	if (_Line[1] != MatDiffuseMapTags[1])return;
	if (_Line[2] != MatDiffuseMapTags[2])return;
	if (_Line[3] != MatDiffuseMapTags[3])return;
	if (_Line[4] != MatDiffuseMapTags[4])return;
	if (_Line[5] != MatDiffuseMapTags[5])return;

	TargetMaterial->DiffuseMap = LoadTextureName(&_Line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatSpecularMap(const std::string& _Line)
{

	if (_Line.size() < 7)return;

	if (_Line[0] != MatSpecularMapTags[0])return;
	if (_Line[1] != MatSpecularMapTags[1])return;
	if (_Line[2] != MatSpecularMapTags[2])return;
	if (_Line[3] != MatSpecularMapTags[3])return;
	if (_Line[4] != MatSpecularMapTags[4])return;
	if (_Line[5] != MatSpecularMapTags[5])return;

	TargetMaterial->SpecularMap = LoadTextureName(&_Line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatSpecularHighLightMap(const std::string& _Line)
{

	if (_Line.size() < 7)return;

	if (_Line[0] != MatSpecularHighLightMapTags[0])return;
	if (_Line[1] != MatSpecularHighLightMapTags[1])return;
	if (_Line[2] != MatSpecularHighLightMapTags[2])return;
	if (_Line[3] != MatSpecularHighLightMapTags[3])return;
	if (_Line[4] != MatSpecularHighLightMapTags[4])return;
	if (_Line[5] != MatSpecularHighLightMapTags[5])return;

	TargetMaterial->SpecularHighLightMap = LoadTextureName(&_Line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatBumpMap(const std::string& _Line)
{

	if (_Line.size() < 9)return;

	if (_Line[0] != MatBumpMapTags[0])return;
	if (_Line[1] != MatBumpMapTags[1])return;
	if (_Line[2] != MatBumpMapTags[2])return;
	if (_Line[3] != MatBumpMapTags[3])return;
	if (_Line[4] != MatBumpMapTags[4])return;
	if (_Line[5] != MatBumpMapTags[5])return;
	if (_Line[6] != MatBumpMapTags[6])return;
	if (_Line[7] != MatBumpMapTags[7])return;

	TargetMaterial->BumpMap = LoadTextureName(&_Line[9]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatBumpMap2(const std::string& _Line)
{
	if (_Line.size() < 5)return;

	if (_Line[0] != MatBumpMapTags2[0])return;
	if (_Line[1] != MatBumpMapTags2[1])return;
	if (_Line[2] != MatBumpMapTags2[2])return;
	if (_Line[3] != MatBumpMapTags2[3])return;

	TargetMaterial->BumpMap = LoadTextureName(&_Line[5]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatMetallicMap(const std::string& _Line)
{

	if (_Line.size() < 7)return;

	if (_Line[0] != MatMetallicMapTags[0])return;
	if (_Line[1] != MatMetallicMapTags[1])return;
	if (_Line[2] != MatMetallicMapTags[2])return;
	if (_Line[3] != MatMetallicMapTags[3])return;
	if (_Line[4] != MatMetallicMapTags[4])return;
	if (_Line[5] != MatMetallicMapTags[5])return;

	TargetMaterial->MetallicMap = LoadTextureName(&_Line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatMetallicMap2(const std::string& _Line)
{

	if (_Line.size() < 3)return;

	if (_Line[0] != MatMetallicMapTags2[0])return;
	if (_Line[1] != MatMetallicMapTags2[1])return;

	TargetMaterial->MetallicMap = LoadTextureName(&_Line[3]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMObjFile::SetMatNormalMap(const std::string& _Line)
{

	if (_Line.size() < 5)return;

	if (_Line[0] != MatNormalMapTags[0])return;
	if (_Line[1] != MatNormalMapTags[1])return;
	if (_Line[2] != MatNormalMapTags[2])return;
	if (_Line[3] != MatNormalMapTags[3])return;

	TargetMaterial->NormalMap = LoadTextureName(&_Line[5]);

}

///////////////////////////////////////////////////////////////////////////////////////

std::string ChCpp::CMObjFile::LoadTextureName(const std::string& _Line)
{

	ChStd::Bool LoadFlg = false;
	std::string Name = "";

	size_t NowPos = 0;
	size_t NowEndPos = 0;

	while (1)
	{
		NowPos = NowEndPos;
		NowEndPos = _Line.find(' ', NowPos + 1);

		if (NowEndPos == _Line.npos)NowEndPos = _Line.length();

		if (_Line[NowPos + 1] == '-')
		{

			NowPos = NowEndPos;
			NowEndPos = _Line.find(' ', NowPos + 1);

			continue;
		}

		Name = _Line.substr(NowPos, NowEndPos - NowPos);
		break;
	}

	return Name;
}
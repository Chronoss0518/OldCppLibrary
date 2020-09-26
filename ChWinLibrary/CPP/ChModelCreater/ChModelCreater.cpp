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

	ChPtr::Shared<TemplateRange> Templates = ChPtr::Make_S<TemplateRange>();

	LoadToTemplates(Templates, TextPos, Text);

	ChPtr::Shared<XFrame>XModel = nullptr;

	for (auto&& Temp : Templates->Nest)
	{

		SetFrame(XModel, Temp, Text);

	}

	if (exceptionFlg)return;

	ChPtr::Shared<BaseModel> OutModels = nullptr;

	OutModels = ChPtr::Make_S<BaseModel>();

	OutModels->ModelName = _FilePath;
	OutModels->ModelData = ChPtr::Make_S<BaseModel::Frame>();

	XModelToChModel(OutModels, XModel);

	SetModel(OutModels);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::OutMeshFile(const std::string& _FilePath)
{

}

/////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetFrame(
	ChPtr::Shared<XFrame>& _Frames
	, const ChPtr::Shared<TemplateRange>& _TargetTemplate
	, const std::string& _Text)
{

	if (exceptionFlg)return false;

	size_t FramePos;

	if (!IsTags(FramePos, FrameTags, _TargetTemplate, _Text))return false;

	FramePos += FrameTags.length();

	auto TmpFrame = ChPtr::Make_S<XFrame>();

	TmpFrame->FName = _Text.substr(FramePos, _TargetTemplate->Bigen - FramePos);

	TmpFrame->FName = ChStd::RemoveToWhiteSpaceChars(TmpFrame->FName);

	for (auto&& Temp : _TargetTemplate->Nest)
	{

		if (SetFremeTransformMatrix(TmpFrame, Temp, _Text)) continue;

		{
			ChPtr::Shared<XFrame> Obj = nullptr;

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
	ChPtr::Shared<XFrame>& _Frames
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
	ChPtr::Shared<XFrame>& _Frames
	, const ChPtr::Shared<TemplateRange>& _TargetTemplate
	, const std::string& _Text)
{
	if (exceptionFlg)return false;

	if (!IsTags(MeshTags, _TargetTemplate, _Text))return false;

	size_t TmpPos = _TargetTemplate->Bigen;

	TmpPos += 1;

	auto Meshs = ChPtr::Make_S<XMesh>();

	{

		auto Values = GetArrayValues<XVECTOR>(_Text, TmpPos, ";,", ";;");


		for (auto&& Poss : Values)
		{
			auto Vertex = ChPtr::Make_S<XVertex>();

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
			auto Face = ChPtr::Make_S<XFace>();

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

	}
	return true;

}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::CMXFile::SetMeshNormal(
	ChPtr::Shared<XFrame>& _Frames
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
	ChPtr::Shared<XFrame>& _Frames
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
	ChPtr::Shared<XFrame>& _Frames
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
	ChPtr::Shared<XFrame>& _Frames
	, const ChPtr::Shared<TemplateRange>& _TargetTemplate
	, const std::string& _Text)
{
	if (exceptionFlg)return false;

	size_t MatePos;

	if (!IsTags(MatePos, MaterialTags, _TargetTemplate, _Text))return false;

	std::string MaterialName = "";

	MatePos += MaterialTags.length();

	MaterialName = _Text.substr(MatePos, _TargetTemplate->Bigen - MatePos);

	MaterialName = ChStd::RemoveToWhiteSpaceChars(MaterialName);

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

	auto Mate = ChPtr::Make_S<XMaterial>();

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

		Mate->TetureNameList.push_back(TexturePath);

	}

	_Frames->Meshs->MaterialList.push_back(Mate);

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

void ChCpp::CMXFile::XModelToChModel(
	ChPtr::Shared<BaseModel>& _ChModel
	, const ChPtr::Shared<XFrame>& _XModel)
{

	_ChModel->ModelData->MyName = _XModel->FName;
	_ChModel->ModelData->BaseMat = _XModel->frameMatrix;

	for (auto&& frame : _XModel->Next)
	{
		ChPtr::Shared<BaseModel::Frame>chFrame = nullptr;

		XFrameToChFrame(chFrame, frame);

		_ChModel->ModelData->ChildFrames.push_back(chFrame);

		chFrame->Parent = _ChModel->ModelData;

	}




}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::XFrameToChFrame(
	ChPtr::Shared<BaseModel::Frame>& _ChFrame
	, const ChPtr::Shared<XFrame>& _XFrame)
{


	_ChFrame = ChPtr::Make_S<BaseModel::Frame>();

	_ChFrame->BaseMat = _XFrame->frameMatrix;
	_ChFrame->MyName = _XFrame->FName;


	for (auto&& Frame : _XFrame->Next)
	{
		ChPtr::Shared<BaseModel::Frame> ChFrame = nullptr;

		XFrameToChFrame(ChFrame, Frame);

		_ChFrame->ChildFrames.push_back(ChFrame);

		ChFrame->Parent = _ChFrame;
	}

	std::map<unsigned long, unsigned long>SummarizeVertex;

	auto Meshs = ChPtr::Make_S<BaseModel::Mesh>();

	//SetVertexList//
	{
		auto& XVertexList = _XFrame->Meshs->VertexList;

		auto& ChVertexList = Meshs->VertexList;

		for (unsigned long i = 0; i < XVertexList.size(); i++)
		{
			ChStd::Bool LookFlg = false;

			for (unsigned long j = 0; j < ChVertexList.size(); j++)
			{

				ChVec3 Tmp = ChVertexList[j]->Pos - XVertexList[i]->Pos;

				if (Tmp.Len() > 0.0000001f)continue;

				SummarizeVertex[i] = j;

				ChVertexList[j]->Normal += XVertexList[i]->Normal;

				LookFlg = true;

				break;

			}

			if (LookFlg)continue;

			SummarizeVertex[i] = i;

			auto ChVertex = ChPtr::Make_S<BaseModel::VertexData>();

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

		for (unsigned long i = 0; i < XFaceList.size(); i++)
		{
			auto ChFace = ChPtr::Make_S<BaseModel::SurFace>();

			for (unsigned long j = 0; j < XFaceList[i]->VertexNos.size(); j++)
			{

				auto ChVertexDatas = ChPtr::Make_S<BaseModel::SurFace::SurFaceVertex>();

				unsigned long VertexNo = SummarizeVertex[XFaceList[i]->VertexNos[j]];

				ChVertexDatas->VertexNo = VertexNo;
				ChVertexDatas->UVPos = XVertexList[XFaceList[i]->VertexNos[j]]->UVPos;

				ChFace->VertexData.push_back(ChVertexDatas);
			}

			ChFace->Materials = XFaceList[i]->MateNo;

			ChFaceList.push_back(ChFace);
		}

	}

	//SetMaterial//
	{
		auto& ChMateList = Meshs->MaterialList;
		auto& ChMateNos = Meshs->MaterialNo;

		unsigned long i = 0;

		for (auto&& XMate : _XFrame->Meshs->MaterialList)
		{
			auto ChMate = ChPtr::Make_S<BaseModel::Material>();

			ChMate->Diffuse = XMate->Diffuse;
			ChMate->MaterialName = XMate->MaterialName;
			ChMate->Specular = XMate->Specular;
			ChMate->SpePow = XMate->SpecularPower;
			ChMate->AmbientPow = XMate->Ambient.Len() / 4.0f;

			for (auto&& TexName : XMate->TetureNameList)
			{
				ChMate->TextureNames.push_back(TexName.c_str());
			}

			ChMateNos[ChMate->MaterialName] = i;

			ChMateList.push_back(ChMate);

			i++;

		}

	}

	_ChFrame->Meshs = Meshs;

}

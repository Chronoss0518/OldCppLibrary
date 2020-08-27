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

	LoadToTemplates(TextPos, Text);

	unsigned long TmpCnt = 0;

	for (auto&& Temp : Templates->Nest)
	{

		SetFrame(OutModels->ModelData, Temp, TmpCnt, Text);
	}


	if (exceptionFlg)return;

	OutModels->ModelName = _FilePath;

	SetModel(OutModels);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::OutMeshFile(const std::string& _FilePath)
{

}

/////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetFrame(
	ChPtr::Shared<BaseModel::Frame>& _Frames
	, const ChPtr::Shared<TemplateRange>& _TargetTemplate
	, unsigned long& _TemplateNo
	, const std::string& _Text)
{

	if (exceptionFlg)return;

	size_t FramePos;

	if(!IsTags(FramePos,FrameTags, _TargetTemplate,_Text))return;

	FramePos += FrameTags.length();

	auto TmpFrame = ChPtr::Make_S<BaseModel::Frame>();

	TmpFrame->MyName = _Text.substr(FramePos, _TargetTemplate->Bigen - FramePos);

	TmpFrame->MyName = ChStd::RemoveToWhiteSpaceChars(TmpFrame->MyName);

	for(auto&& Temp : _TargetTemplate->Nest)
	{

	}

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

	size_t Checked = _Text.substr(
		CheckStartPos
		, _LookTemplate->Bigen - CheckStartPos)
		.find(_TagName);

	if (Checked == _Text.npos)return false;

	_OutTagPos = Checked;

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::LoadToTemplates(
	const size_t& _Offset
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

	Templates = ChPtr::Make_S<TemplateRange>();

	Templates->Bigen = 0;
	Templates->End = 0;

	while (1)
	{

		if (BeginCount >= TemplateTags[0].size())
		{
			break;
		}

		SetToTemplate(
			Templates
			, BeginCount
			, EndCount
			, TemplateTags[0]
			, TemplateTags[1]);

	}



}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::CMXFile::SetToTemplate(
	ChPtr::Shared<TemplateRange> _Tmp
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
			,_BCnt
			,_ECnt
			, _STemplateTags
			, _ETemplateTags);


	}


}
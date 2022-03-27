#include"../../BaseIncluder/ChBase.h"

#include"../ChFile/ChFile.h"

#include"../ChModel/ChModelObject.h"

#include"ChModelLoader.h"
#include"ChLMXFile.h"

///////////////////////////////////////////////////////////////////////////////////////
//ChXFileMesh Method//
///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::XFile::CreateModel(const std::string& _filePath)
{
	if (_filePath.size() <= 0)return;

	std::string text;
	{

		ChCpp::File<> files;

		files.FileOpen(_filePath);

		text = files.FileReadText();

		files.FileClose();

		if (text.length() <= 0)
		{
			return;
		}
	}

	if (text.find("xof") != 0)return;

	size_t textPos = text.find("xof");

	{
		std::string tmp = "template Frame";
		size_t tmpLen = text.find(tmp, textPos);

		if (tmpLen != tmp.npos) {
			textPos = tmpLen;
			textPos += tmp.length();
		}
	}

	size_t tmpLen = text.find("Frame", textPos);
	if (tmpLen == text.npos)return;

	tmpLen = text.find("}", tmpLen);
	if (tmpLen == text.npos)return;

	ChPtr::Shared<TemplateRange> templates = ChPtr::Make_S<TemplateRange>();

	LoadToTemplates(templates, textPos, text);

	auto xModel = ChPtr::Make_S<XFileModelFrame>();

	for (auto&& tmp : templates->nest)
	{

		SetFrame(xModel->modelData, tmp, text);

		SetMesh(xModel->modelData, tmp, text);

	}

	if (exceptionFlg)return;

	ChPtr::Shared<ModelFrame> outModels = nullptr;

	outModels = ChPtr::Make_S<ModelFrame>();

	outModels->modelName = _filePath;

	XFrameToChFrame(outModels->modelData, xModel->modelData);

	SetModel(outModels);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::XFile::OutModelFile(const std::string& _filePath)
{

}

/////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::ModelLoader::XFile::SetFrame(
	ChPtr::Shared<XFileModelFrame::XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::string& _text)
{
	if (exceptionFlg)return false;

	size_t framePos;

	if (!IsTags(framePos, frameTags, _targetTemplate, _text))return false;

	framePos += frameTags.length();

	auto tmpFrame = ChPtr::Make_S<XFileModelFrame::XFrame>();

	tmpFrame->fName = _text.substr(framePos, _targetTemplate->begin - framePos);

	tmpFrame->fName = ChStr::RemoveToWhiteSpaceChars(tmpFrame->fName);

	for (auto&& tmp : _targetTemplate->nest)
	{
		if (SetFremeTransformMatrix(tmpFrame, tmp, _text)) continue;

		{
			ChPtr::Shared<XFileModelFrame::XFrame> obj = nullptr;

			if (SetFrame(obj, tmp, _text))
			{

				tmpFrame->next.push_back(obj);

				continue;
			}
		}

		if (SetMesh(tmpFrame, tmp, _text)) continue;
	}

	_frames = tmpFrame;

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::ModelLoader::XFile::SetFremeTransformMatrix(
	ChPtr::Shared<XFileModelFrame::XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::string& _text)
{

	if (exceptionFlg)return false;

	if (!IsTags(frameTransformMatrixTags, _targetTemplate, _text))return false;

	std::string useText;

	{
		size_t textLen = _targetTemplate->end - _targetTemplate->begin - 1;

		useText = _text.substr(_targetTemplate->begin + 1, textLen);
	}

	_frames->frameMatrix.Deserialize(useText, 0, ",", ";;");

	return true;

}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::ModelLoader::XFile::SetMesh(
	ChPtr::Shared<XFileModelFrame::XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::string& _text)
{
	if (exceptionFlg)return false;

	if (!IsTags(meshTags, _targetTemplate, _text))return false;

	if (_frames == nullptr)
	{
		_frames = ChPtr::Make_S<XFileModelFrame::XFrame>();
		_frames->fName = "Root";
	}

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	auto mesh = ChPtr::Make_S<XFileModelFrame::XMesh>();

	{

		auto values = GetArrayValues<XVECTOR>(_text, tmpPos, ";,", ";;");

		for (auto&& poss : values)
		{
			auto vertex = ChPtr::Make_S<XFileModelFrame::XVertex>();

			vertex->pos = poss->value;

			mesh->vertexList.push_back(vertex);

		}

	}

	tmpPos = _text.find(";;", tmpPos);
	tmpPos += 2;

	{
		auto values = GetArrayValues<XMESHFACE>(_text, tmpPos, ";,", ";;");

		for (auto&& Poss : values)
		{
			auto face = ChPtr::Make_S<XFileModelFrame::XFace>();

			for (auto&& no : Poss->value)
			{
				face->vertexNos.push_back(no);
			}

			mesh->faceList.push_back(face);

		}
	}

	_frames->mesh = mesh;

	for (auto&& tmp : _targetTemplate->nest)
	{

		if (SetMeshNormal(_frames, tmp, _text)) continue;

		if (SetMeshTextureCoords(_frames, tmp, _text)) continue;

		if (SetMeshMaterialList(_frames, tmp, _text)) continue;

		if (SetSkinWeights(_frames, tmp, _text)) continue;

	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::ModelLoader::XFile::SetMeshNormal(
	ChPtr::Shared<XFileModelFrame::XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::string& _text)
{
	if (exceptionFlg)return false;

	if (!IsTags(normalTags, _targetTemplate, _text))return false;

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	auto normals = GetArrayValues<XVECTOR>(_text, tmpPos, ";,", ";;");

	tmpPos = _text.find(";;", tmpPos);
	tmpPos += 2;

	auto faces = GetArrayValues<XMESHFACE>(_text, tmpPos, ";,", ";;");

	for (unsigned long i = 0; i < faces.size(); i++)
	{
		auto Mesh = _frames->mesh->faceList[i];

		for (unsigned long j = 0; j < Mesh->vertexNos.size(); j++)
		{

			_frames->mesh->vertexList[Mesh->vertexNos[j]]->normal +=
				normals[faces[i]->value[j]]->value;

		}
	}
	for (auto&& vertex : _frames->mesh->vertexList)
	{
		if (vertex->normal.Len() == 1.00000000f)continue;
		vertex->normal.Normalize();
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::ModelLoader::XFile::SetMeshTextureCoords(
	ChPtr::Shared<XFileModelFrame::XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::string& _text)
{
	if (exceptionFlg)return false;

	if (!IsTags(uvTags, _targetTemplate, _text))return false;

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	auto UVs = GetArrayValues<XCOODS2D>(_text, tmpPos, ";,", ";;");

	tmpPos = _text.find(";;", tmpPos);
	tmpPos += 2;

	auto& vertexList = _frames->mesh->vertexList;

	for (unsigned long i = 0; i < vertexList.size(); i++)
	{
		vertexList[i]->uvPos = UVs[i]->value;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::ModelLoader::XFile::SetMeshMaterialList(
	ChPtr::Shared<XFileModelFrame::XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::string& _text)
{
	if (exceptionFlg)return false;

	if (!IsTags(materialListTags, _targetTemplate, _text))return false;

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	tmpPos = _text.find(";", tmpPos);

	tmpPos += 1;

	auto mateNo = GetArrayValues<XDWORD>(_text, tmpPos, ",", ";;");

	auto& faces = _frames->mesh->faceList;

	for (unsigned long i = 0; i < faces.size(); i++)
	{
		faces[i]->mateNo = mateNo[i]->value;
	}

	for (auto&& tmp : _targetTemplate->nest)
	{
		SetMaterial(_frames, tmp, _text);
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::ModelLoader::XFile::SetMaterial(
	ChPtr::Shared<XFileModelFrame::XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::string& _text)
{
	if (exceptionFlg)return false;

	size_t matePos;

	if (!IsTags(matePos, materialTags, _targetTemplate, _text))return false;

	std::string materialName = "";

	matePos += materialTags.length();

	materialName = _text.substr(matePos, _targetTemplate->begin - matePos);

	materialName = ChStr::RemoveToWhiteSpaceChars(materialName);

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	ColorRGBA diffuse;

	{
		std::string useText = "";

		size_t tmpEnd = _text.find(";;", tmpPos);
		tmpEnd += 2;

		useText = _text.substr(tmpPos, tmpEnd - tmpPos);

		tmpPos = tmpEnd;

		diffuse.Desirialise(useText, 0, ";;");
	}

	XFLOAT spePow;

	{
		std::string useText = "";

		size_t tmpEnd = _text.find(";", tmpPos);
		tmpEnd += 1;

		useText = _text.substr(tmpPos, tmpEnd - tmpPos);

		tmpPos = tmpEnd;

		spePow.Desirialise(useText, 0, ";");
	}

	ColorRGB specular;

	{
		std::string useText = "";

		size_t tmpEnd = _text.find(";;", tmpPos);
		tmpEnd += 2;

		useText = _text.substr(tmpPos, tmpEnd - tmpPos);

		tmpPos = tmpEnd;

		specular.Desirialise(useText, 0, ";;");
	}

	ColorRGB ambient;

	{
		std::string useText = "";

		size_t tmpEnd = _text.find(";;", tmpPos);
		tmpEnd += 2;

		useText = _text.substr(tmpPos, tmpEnd - tmpPos);

		tmpPos = tmpEnd;

		ambient.Desirialise(useText, 0, ";;");
	}

	auto mate = ChPtr::Make_S<XFileModelFrame::XMaterial>();

	mate->materialName = materialName;
	mate->diffuse = diffuse.value;
	mate->specularPower = spePow.value;
	mate->specular = specular.value;
	mate->ambient = ambient.value;

	for (auto&& tmp : _targetTemplate->nest)
	{

		if (!IsTags(textureFileNameTag, tmp, _text))continue;

		size_t start = _text.find("\"", tmp->begin);

		if (start >= tmp->end)continue;

		size_t end = _text.find("\"", start + 1);

		if (end >= tmp->end)continue;

		std::string texturePath = _text.substr(start + 1, end - start - 1);

		mate->textureNameList.push_back(texturePath);

	}

	_frames->mesh->materialList.push_back(mate);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::ModelLoader::XFile::SetSkinWeights(
	ChPtr::Shared<XFileModelFrame::XFrame>& _frames
	, const ChPtr::Shared<TemplateRange>& _targetTemplate
	, const std::string& _text)
{

	if (exceptionFlg)return false;

	if (!IsTags(skinWeightsTag, _targetTemplate, _text))return false;

	size_t tmpPos = _targetTemplate->begin;

	tmpPos += 1;

	std::string boneName;

	{
		size_t tmpStart = _text.find("\"", tmpPos);

		size_t tmpEnd = _text.find("\";", tmpPos);

		if (tmpStart > _targetTemplate->end
			|| tmpEnd > _targetTemplate->end)return true;


		boneName = _text.substr(tmpStart + 1, tmpEnd - tmpStart - 1);

		tmpPos = tmpEnd + 2;
	}

	tmpPos = _text.find(";", tmpPos);
	tmpPos += 1;


	auto vertexNo = GetArrayValuesNC<XDWORD>(_text, tmpPos, ",", ";");

	tmpPos = _text.find(";", tmpPos);
	tmpPos += 1;

	auto weightPow = GetArrayValuesNC<XFLOAT>(_text, tmpPos, ",", ";");

	tmpPos = _text.find(";", tmpPos);
	tmpPos += 1;

	ChLMat tmpOffMat;

	tmpOffMat.Deserialize(_text, tmpPos, ",", ";;");

	auto skinWeight = ChPtr::Make_S<XFileModelFrame::XSkinWeights>();

	skinWeight->boneOffset = tmpOffMat;

	skinWeight->targetFrameName = boneName;

	{
		size_t weightingCount = vertexNo.size();

		if (weightingCount > weightPow.size())weightingCount = weightPow.size();

		for (unsigned long i = 0; i < weightingCount; i++)
		{
			skinWeight->weitPow[vertexNo[i]->value] = weightPow[i]->value;
		}
	}

	_frames->skinWeightDatas.push_back(skinWeight);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

ChStd::Bool ChCpp::ModelLoader::XFile::IsTags(
	size_t& _outTagPos
	, const std::string& _TagName
	, const ChPtr::Shared<TemplateRange> _LookTemplate
	, const std::string& _text)
{

	size_t checkStartPos
		= _text.rfind("\n", _LookTemplate->begin);


	if (checkStartPos == _text.npos)
	{
		exceptionFlg = true;
		return false;
	}

	std::string tmp = _text.substr(
		checkStartPos
		, _LookTemplate->begin - checkStartPos);

	size_t checked = tmp.find(_TagName);

	if (checked == _text.npos)return false;

	_outTagPos = _text.find(_TagName, checkStartPos);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::XFile::LoadToTemplates(
	ChPtr::Shared<TemplateRange>& _templates
	, const size_t& _offset
	, const std::string& _text)
{
	std::vector<size_t>templateTags[2];
	char tags[] = { '{','}' };

	for (size_t i = 0; i < 2; i++)
	{

		size_t offset = _offset;

		while (1)
		{
			offset = _text.find(tags[i], offset + 1);

			if (offset >= _text.npos)break;

			templateTags[i].push_back(offset);

		}
	}


	if (templateTags[0].size() != templateTags[1].size())
	{
		exceptionFlg = true;
		return;
	}


	size_t tempCount = templateTags[0].size();

	size_t beginCount = 0;
	size_t endCount = 0;

	_templates = ChPtr::Make_S<TemplateRange>();

	_templates->begin = 0;
	_templates->end = 0;

	while (1)
	{

		if (beginCount >= templateTags[0].size())
		{
			break;
		}

		SetToTemplate(
			_templates
			, beginCount
			, endCount
			, templateTags[0]
			, templateTags[1]);

	}



}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::XFile::SetToTemplate(
	ChPtr::Shared<TemplateRange>& _tmp
	, size_t& _bCnt
	, size_t& _eCnt
	, const std::vector<size_t>& _sTemplateTags
	, const std::vector<size_t>& _eTemplateTags)
{

	if (_eCnt >= _eTemplateTags.size())
	{
		exceptionFlg = true;
		return;
	}

	auto tmp = ChPtr::Make_S<TemplateRange>();

	tmp->begin = _sTemplateTags[_bCnt];

	_tmp->nest.push_back(tmp);

	_bCnt++;

	while (1)
	{

		if (_bCnt >= _sTemplateTags.size())
		{

			tmp->end = _eTemplateTags[_eCnt];
			_eCnt++;
			break;
		}

		if (_sTemplateTags[_bCnt] > _eTemplateTags[_eCnt])
		{
			tmp->end = _eTemplateTags[_eCnt];
			_eCnt++;
			break;
		}

		SetToTemplate(
			tmp
			, _bCnt
			, _eCnt
			, _sTemplateTags
			, _eTemplateTags);


	}


}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::XFile::XFrameToChFrame(
	ChPtr::Shared<ModelFrame::Frame>& _chFrame
	, const ChPtr::Shared<XFileModelFrame::XFrame>& _xFrame)
{


	_chFrame = ChPtr::Make_S<ModelFrame::Frame>();

	_chFrame->baseMat = _xFrame->frameMatrix;
	_chFrame->myName = _xFrame->fName;


	for (auto&& frame : _xFrame->next)
	{
		ChPtr::Shared<ModelFrame::Frame> chFrame = nullptr;

		XFrameToChFrame(chFrame, frame);

		_chFrame->childFrames.push_back(chFrame);

		chFrame->parent = _chFrame;
	}

	std::map<unsigned long, unsigned long>summarizeVertex;

	auto mesh = ChPtr::Make_S<ModelFrame::Mesh>();

	if (_xFrame->mesh == nullptr)return;
	//SetVertexList//
	{
		auto& xVertexList = _xFrame->mesh->vertexList;

		auto& chVertexList = mesh->vertexList;

		for (unsigned long i = 0; i < xVertexList.size(); i++)
		{
			ChStd::Bool lookFlg = false;

			for (unsigned long j = 0; j < chVertexList.size(); j++)
			{

				if (chVertexList[j]->pos != xVertexList[i]->pos)continue;

				summarizeVertex[i] = j;

				chVertexList[j]->normal += xVertexList[i]->normal;

				lookFlg = true;

				break;

			}

			if (lookFlg)continue;


			summarizeVertex[i] = chVertexList.size();

			auto chVertex = ChPtr::Make_S<ModelFrame::VertexData>();

			chVertex->pos = xVertexList[i]->pos;
			chVertex->normal += xVertexList[i]->normal;

			chVertexList.push_back(chVertex);

		}

		for (auto&& chVertex : chVertexList)
		{
			chVertex->normal.Normalize();
		}

	}

	//SetFaceList//
	{
		auto& xVertexList = _xFrame->mesh->vertexList;

		auto& xFaceList = _xFrame->mesh->faceList;

		auto& chFaceList = mesh->faceList;

		for (auto&& xFace : xFaceList)
		{
			unsigned long counters[3];
			counters[0] = 0;
			counters[1] = 1;
			counters[2] = xFace->vertexNos.size() - 1;

			ChStd::Bool upperFlg = true;

			for (unsigned long i = 0; i < xFace->vertexNos.size() - 2; i++)
			{
				auto chFace = ChPtr::Make_S<ModelFrame::SurFace>();

				for (unsigned long j = 0; j < 3; j++)
				{

					auto chVertexData = ChPtr::Make_S<ModelFrame::SurFace::SurFaceVertex>();

					unsigned long VertexNo = summarizeVertex[xFace->vertexNos[counters[j]]];

					chVertexData->vertexNo = VertexNo;
					chVertexData->uvPos = xVertexList[xFace->vertexNos[counters[j]]]->uvPos;


					chFace->vertexData[j].uvPos = chVertexData->uvPos;
					chFace->vertexData[j].vertexNo = chVertexData->vertexNo;

					chFace->normal += xVertexList[xFace->vertexNos[counters[j]]]->normal;
				}

				chFace->normal.Normalize();

				if (upperFlg)
				{
					counters[0] = counters[1];
					counters[1] = counters[2] - 1;
				}
				else
				{
					counters[2] = counters[1];
					counters[1] = counters[0] + 1;
				}

				upperFlg = !upperFlg;

				chFace->materialNo = xFace->mateNo;

				chFaceList.push_back(chFace);
			}
		}


	}

	//SetMaterial//

	{
		auto& chMateList = mesh->materialList;
		auto& chMateNos = mesh->materialNo;

		unsigned long i = 0;

		for (auto&& xMate : _xFrame->mesh->materialList)
		{
			auto chMate = ChPtr::Make_S<ModelFrame::Material>();

			chMate->diffuse = xMate->diffuse;
			chMate->materialName = xMate->materialName;
			chMate->specular = xMate->specular;
			chMate->spePow = xMate->specularPower;
			chMate->ambientPow = xMate->ambient.Len() / 4.0f;

			for (unsigned long i = 0; i < xMate->textureNameList.size(); i++)
			{
				chMate->textureNames.push_back(xMate->textureNameList[i]);

				//switch (i)
				//{
				//case 0:ChMate->diffuseMap = XMate->TextureNameList[i]; break;
				//case 1:ChMate->NormalMap = XMate->TextureNameList[i]; break;
				//case 2:ChMate->AmbientMap = XMate->TextureNameList[i]; break;
				//case 3:ChMate->specularMap = XMate->TextureNameList[i]; break;
				//case 4:ChMate->specularPowMap = XMate->TextureNameList[i]; break;
				//case 5:ChMate->BumpMap = XMate->TextureNameList[i]; break;
				//case 6:ChMate->alphaMap = XMate->TextureNameList[i]; break;
				//case 7:ChMate->MetallicMap = XMate->TextureNameList[i]; break;
				//default:
				//	break;
				//}

			}

			chMateNos[chMate->materialName] = i;

			chMateList.push_back(chMate);

			i++;

		}

	}

	_chFrame->mesh = mesh;

}

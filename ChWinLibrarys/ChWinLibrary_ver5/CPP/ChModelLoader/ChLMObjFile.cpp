#include"../../BaseIncluder/ChBase.h"

#include"../ChFile/ChFile.h"

#include"../ChTextObject/ChTextObject.h"
#include"../ChModel/ChModelObject.h"

#include"ChModelLoader.h"
#include"ChLMObjFile.h"


///////////////////////////////////////////////////////////////////////////////////////
//ChCMObjeFile Method//
///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::CreateModel(const std::string& _filePath)
{
	if (_filePath.size() <= 0)return;

	ChCpp::TextObject text;

	{
		std::string tmp;

		ChCpp::File<> files;

		files.FileOpen(_filePath);

		tmp = files.FileReadText();

		files.FileClose();

		if (tmp.length() <= 0)
		{
			return;
		}

		text.SetText(tmp);

	}

	folderPath = GetRoutePath(_filePath);

	for (unsigned long i = 0; i < text.LineCount(); i++)
	{
		if (text[i].length() <= 0)continue;
		if (text[i][0] == commentTags)continue;

		CreateMaterials(text[i]);

		CreateObject(text[i]);
		SetVertex(text[i]);
		SetUV(text[i]);
		SetNormal(text[i]);
		SetFace(text[i]);
		SetMateBlock(text[i]);
	}

	//if (ObjectMaps.size() <= 0)return;
	if (objects.size() <= 0)return;

	auto outModels = ChPtr::Make_S<ModelFrame>();

	outModels->modelName = _filePath;

	outModels->modelData = ChPtr::Make_S<ModelFrame::Frame>();

	outModels->modelData->myName = "Root";

	CreateChFrame(outModels->modelData);

	SetModel(outModels);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::CreateObject(const std::string& _objectName)
{
	if (_objectName.size() < 3)return;
	if (_objectName[1] != ' ')return;
	if (_objectName[0] != objectBlockTags)return;

	auto name = _objectName.substr(2);

	auto obj = ChPtr::Make_S<ObjFileModelData>();

	obj->sVertex = makeObject != nullptr ? makeObject->sVertex + makeObject->vertexDatas.size() : 0;
	obj->sUV = makeObject != nullptr ? makeObject->sUV + makeObject->uvDatas.size() : 0;
	obj->sNormal = makeObject != nullptr ? makeObject->sNormal + makeObject->normalDatas.size() : 0;

	makeObject = nullptr;

	makeObject = obj;
	//ObjectMaps[Name] = MakeObject;
	makeObject->objectName = name;
	objects.push_back(makeObject);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::CreateMaterials(const std::string& _fileName)
{
	if (_fileName.size() < 8)return;
	if (_fileName[6] != ' ')return;
	if (_fileName[5] != useMaterialFileNameTags[5])return;
	if (_fileName[4] != useMaterialFileNameTags[4])return;
	if (_fileName[3] != useMaterialFileNameTags[3])return;
	if (_fileName[2] != useMaterialFileNameTags[2])return;
	if (_fileName[1] != useMaterialFileNameTags[1])return;
	if (_fileName[0] != useMaterialFileNameTags[0])return;

	std::string fileName = &_fileName[7];

	ChCpp::TextObject text;

	{
		std::string tmp;

		ChCpp::File<> files;

		files.FileOpen(folderPath + fileName);

		tmp = files.FileReadText();

		files.FileClose();

		if (tmp.length() <= 0)
		{
			return;
		}

		text.SetText(tmp);
	}

	for (unsigned long i = 0; i < text.LineCount(); i++)
	{
		if (text[i].length() <= 0)continue;
		if (text[i][0] == commentTags)continue;

		CreateMaterial(text[i]);
		SetMatAmbient(text[i]);
		SetMatDiffuse(text[i]);
		SetMatSpecular(text[i]);
		SetMatSpecularHighLight(text[i]);
		SetMatDissolve(text[i]);
		SetMatODensity(text[i]);
		SetMatAmbientMap(text[i]);
		SetMatDiffuseMap(text[i]);
		SetMatSpecularMap(text[i]);
		SetMatSpecularHighLightMap(text[i]);
		SetMatBumpMap(text[i]);
		SetMatMetallicMap(text[i]);
		SetMatNormalMap(text[i]);
	}

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::CreateMaterial(const std::string& _matName)
{

	if (_matName.size() < 7)return;
	if (_matName[6] != ' ')return;
	if (_matName[5] != matMaterialBlockTags[5])return;
	if (_matName[4] != matMaterialBlockTags[4])return;
	if (_matName[3] != matMaterialBlockTags[3])return;
	if (_matName[2] != matMaterialBlockTags[2])return;
	if (_matName[1] != matMaterialBlockTags[1])return;
	if (_matName[0] != matMaterialBlockTags[0])return;

	targetMaterial = nullptr;

	targetMaterial = ChPtr::Make_S<ObjFileMaterialData>();

	materialMaps[&_matName[7]] = targetMaterial;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::CreateChFrame(ChPtr::Shared<ChCpp::ModelFrame::Frame>& _frame)
{

	//for (auto&& Obj : ObjectMaps)
	for (auto&& obj : objects)
	{
		unsigned long materialNo = 0;

		auto mesh = ChPtr::Make_S<ChCpp::ModelFrame::Mesh>();

		//for (auto&& Vertexs : Obj.second->VertexDatas)
		for (auto&& vertexs : obj->vertexDatas)
		{
			auto ver = ChPtr::Make_S<ChCpp::ModelFrame::VertexData>();

			ver->pos = *vertexs;

			mesh->vertexList.push_back(ver);

		}

		//for (auto&& Face : Obj.second->MeshDatas)
		for (auto&& face : obj->meshDatas)
		{

			if (mesh->materialNo.find(face->targetMaterialName) == mesh->materialNo.end())
			{

				mesh->materialNo[face->targetMaterialName] = materialNo;

				auto mate = ChPtr::Make_S<ChCpp::ModelFrame::Material>();

				auto& tmpMate = materialMaps[face->targetMaterialName];

				mate->materialName = face->targetMaterialName;

				mate->diffuse = tmpMate->diffuse;
				mate->diffuse.a = tmpMate->alpha;

				mate->specular = tmpMate->specular;

				mate->spePow = tmpMate->spePow;

				mate->ambientPow = tmpMate->ambient.r + tmpMate->ambient.g + tmpMate->ambient.b;

				mate->ambientPow /= 3;

				mate->textureNames.push_back(tmpMate->diffuseMap);
				mate->textureNames.push_back(tmpMate->ambientMap);
				mate->textureNames.push_back(tmpMate->specularMap);
				mate->textureNames.push_back(tmpMate->specularHighLightMap);
				mate->textureNames.push_back(tmpMate->bumpMap);
				mate->textureNames.push_back(tmpMate->alphaMap);
				mate->textureNames.push_back(tmpMate->normalMap);
				mate->textureNames.push_back(tmpMate->metallicMap);

				//mate->diffuseMap = tmpMate->diffuseMap;
				//mate->AmbientMap = tmpMate->AmbientMap;
				//mate->specularMap = tmpMate->specularMap;
				//mate->specularPowMap = tmpMate->specularHighLightMap;
				//mate->BumpMap = tmpMate->BumpMap;
				//mate->alphaMap = tmpMate->alphaMap;
				//mate->NormalMap = tmpMate->NormalMap;
				//mate->MetallicMap = tmpMate->MetallicMap;

				mesh->materialList.push_back(mate);

				materialNo++;
			}

			std::vector<ChPtr::Shared<ChCpp::ModelFrame::SurFace::SurFaceVertex>>fVList;

			for (auto&& values : face->values)
			{

				//unsigned long NVertex = Values->VertexNum - Obj.second->SVertex - 1;
				//unsigned long NUV = Values->UVNum - Obj.second->SUV - 1;
				//unsigned long NNormal = Values->NormalNum - Obj.second->SNormal - 1;
				unsigned long nVertex = values->vertexNum - obj->sVertex - 1;
				unsigned long nUV = values->uvNum - obj->sUV - 1;
				unsigned long nNormal = values->normalNum - obj->sNormal - 1;

				auto faceVertex = ChPtr::Make_S<ChCpp::ModelFrame::SurFace::SurFaceVertex>();

				faceVertex->vertexNo = nVertex;
				//if(Obj.second->UVDatas.size() > NUV)faceVertex->UVPos = *Obj.second->UVDatas[NUV];
				if (obj->uvDatas.size() > nUV)faceVertex->uvPos = *obj->uvDatas[nUV];

				fVList.push_back(faceVertex);

				//mesh->VertexList[NVertex]->Normal += *Obj.second->NormalDatas[NNormal];
				mesh->vertexList[nVertex]->normal += *obj->normalDatas[nNormal];
			}

			if (fVList.size() >= 3)
			{

				unsigned long counters[3];
				counters[0] = 0;
				counters[1] = 1;
				counters[2] = fVList.size() - 1;

				ChStd::Bool upperFlg = true;


				for (unsigned long i = 0; i < fVList.size() - 2; i++)
				{

					auto face = ChPtr::Make_S<ChCpp::ModelFrame::SurFace>();

					face->vertexData[0] = *fVList[counters[2]];
					face->vertexData[1] = *fVList[counters[1]];
					face->vertexData[2] = *fVList[counters[0]];

					//face->VertexData[0] = *FVList[i];
					//face->VertexData[1] = *FVList[i + 1];
					//face->VertexData[2] = *FVList[i + 2];

					face->materialNo = materialNo - 1;

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

					mesh->faceList.push_back(face);
				}

			}


			for (auto&& ver : mesh->vertexList)
			{
				ver->normal.Normalize();
			}

		}

		auto frame = ChPtr::Make_S< ChCpp::ModelFrame::Frame>();

		//Frame->MyName = Obj.first;
		frame->myName = obj->objectName;
		frame->parent = _frame;
		frame->mesh = mesh;


		_frame->childFrames.push_back(frame);

	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::OutModelFile(const std::string& _filePath)
{
	if (_filePath.size() <= 0)return;
	if (_filePath.rfind(".") == std::string::npos)return;

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetVertex(const std::string& _line)
{
	if (_line.size() < 2)return;
	if (_line[1] != ' ')return;
	if (_line[0] != vertexTags)return;

	auto pos = ChPtr::Make_S<ChVec3>();

	pos->Deserialize(_line, 2, " ");

	makeObject->vertexDatas.push_back(pos);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetUV(const std::string& _line)
{
	if (_line.size() < 3)return;
	if (_line[2] != ' ')return;
	if (_line[1] != uvTags[1])return;
	if (_line[0] != uvTags[0])return;

	auto uv = ChPtr::Make_S<ChVec2>();

	uv->Deserialize(_line, 3, " ");

	makeObject->uvDatas.push_back(uv);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetNormal(const std::string& _line)
{
	if (_line.size() < 3)return;
	if (_line[2] != ' ')return;
	if (_line[1] != normalTags[1])return;
	if (_line[0] != normalTags[0])return;

	auto normal = ChPtr::Make_S<ChVec3>();

	normal->Deserialize(_line, 3, " ");

	makeObject->normalDatas.push_back(normal);
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetFace(const std::string& _line)
{
	if (_line.size() < 2)return;
	if (_line[1] != ' ')return;
	if (_line[0] != meshTags)return;

	unsigned long pos = _line.find(' ');

	unsigned long tmpPos = pos;

	unsigned long end = 0;

	auto data = ChPtr::Make_S<ChCpp::ModelLoader::ObjFile::ObjFileModelData::MeshData>();

	data->targetMaterialName = blockMaterial;

	makeObject->meshDatas.push_back(data);

	ChStd::Bool endFlg = false;

	while (1)
	{

		tmpPos = _line.find(' ', pos + 1);

		if (_line.size() < tmpPos)
		{
			endFlg = true;
			tmpPos = _line.size();
		}

		auto mdata = ChPtr::Make_S<ChCpp::ModelLoader::ObjFile::ObjFileModelData::MeshData::Data>();


		std::string tmp = _line.substr(pos, tmpPos - pos);

		unsigned long val[3] = { 0xffffffff,0xffffffff ,0xffffffff };

		//SrashCount//
		unsigned long sCount = 0;

		unsigned long start = 0;

		while (1)
		{
			end = tmp.find('/', start);

			if (tmp.size() <= end)end = tmp.size();

			std::string ST = tmp.substr(start, end - start);

			if (tmp[start] != '/')
			{
				val[sCount] = ChStr::GetIntegialFromText<unsigned long>(tmp.substr(start, end - start));
			}

			if (tmp.size() <= end)break;

			sCount++;
			start = end + 1;
		}

		pos += tmp.length();

		mdata->vertexNum = val[0];
		mdata->uvNum = val[1];
		mdata->normalNum = val[2];

		data->values.push_back(mdata);
		if (endFlg)break;

		end = 0;

	}
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMateBlock(const std::string& _line)
{

	if (_line.size() < 7)return;
	if (_line[6] != ' ')return;
	if (_line[5] != materialBlockTags[5])return;
	if (_line[4] != materialBlockTags[4])return;
	if (_line[3] != materialBlockTags[3])return;
	if (_line[2] != materialBlockTags[2])return;
	if (_line[1] != materialBlockTags[1])return;
	if (_line[0] != materialBlockTags[0])return;

	blockMaterial = &_line[7];

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatAmbient(const std::string& _line)
{
	if (_line.size() < 3)return;
	if (_line[2] != ' ')return;
	if (_line[1] != matAmbientTags[1])return;
	if (_line[0] != matAmbientTags[0])return;

	targetMaterial->ambient.Deserialize(&_line[3], 0, " ");
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatDiffuse(const std::string& _line)
{

	if (_line.size() < 3)return;
	if (_line[2] != ' ')return;
	if (_line[1] != matDiffuseTags[1])return;
	if (_line[0] != matDiffuseTags[0])return;

	targetMaterial->diffuse.Deserialize(&_line[3], 0, " ");

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatSpecular(const std::string& _line)
{

	if (_line.size() < 3)return;
	if (_line[2] != ' ')return;
	if (_line[1] != matSpecularTags[1])return;
	if (_line[0] != matSpecularTags[0])return;

	targetMaterial->specular.Deserialize(&_line[3], 0, " ");

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatSpecularHighLight(const std::string& _line)
{

	if (_line.size() < 3)return;
	if (_line[2] != ' ')return;
	if (_line[1] != matSpecularHighLightTags[1])return;
	if (_line[0] != matSpecularHighLightTags[0])return;

	targetMaterial->spePow = ChStr::GetFloatingFromText<float>(&_line[3], 0);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatDissolve(const std::string& _line)
{

	if (_line.size() < 2)return;
	if (_line[1] != ' ')return;
	if (_line[0] != matDissolveTags)return;

	targetMaterial->alpha = ChStr::GetFloatingFromText<float>(&_line[2], 0);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatODensity(const std::string& _line)
{
	if (_line.size() < 3)return;

	if (_line[2] != ' ')return;
	if (_line[1] != matODensityTags[1])return;
	if (_line[0] != matODensityTags[0])return;

	targetMaterial->ODensity = ChStr::GetFloatingFromText<float>(&_line[3], 0);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatAmbientMap(const std::string& _line)
{
	if (_line.size() < 7)return;

	if (_line[6] != ' ')return;
	if (_line[5] != matAmbientMapTags[5])return;
	if (_line[4] != matAmbientMapTags[4])return;
	if (_line[3] != matAmbientMapTags[3])return;
	if (_line[2] != matAmbientMapTags[2])return;
	if (_line[1] != matAmbientMapTags[1])return;
	if (_line[0] != matAmbientMapTags[0])return;

	targetMaterial->ambientMap = LoadTextureName(&_line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatDiffuseMap(const std::string& _line)
{

	if (_line.size() < 7)return;

	if (_line[6] != ' ')return;
	if (_line[5] != matDiffuseMapTags[5])return;
	if (_line[4] != matDiffuseMapTags[4])return;
	if (_line[3] != matDiffuseMapTags[3])return;
	if (_line[2] != matDiffuseMapTags[2])return;
	if (_line[1] != matDiffuseMapTags[1])return;
	if (_line[0] != matDiffuseMapTags[0])return;

	targetMaterial->diffuseMap = LoadTextureName(&_line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatSpecularMap(const std::string& _line)
{

	if (_line.size() < 7)return;

	if (_line[6] != ' ')return;
	if (_line[5] != matSpecularMapTags[5])return;
	if (_line[4] != matSpecularMapTags[4])return;
	if (_line[3] != matSpecularMapTags[3])return;
	if (_line[2] != matSpecularMapTags[2])return;
	if (_line[1] != matSpecularMapTags[1])return;
	if (_line[0] != matSpecularMapTags[0])return;

	targetMaterial->specularMap = LoadTextureName(&_line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatSpecularHighLightMap(const std::string& _line)
{

	if (_line.size() < 7)return;

	if (_line[6] != ' ')return;
	if (_line[5] != matSpecularHighLightMapTags[5])return;
	if (_line[4] != matSpecularHighLightMapTags[4])return;
	if (_line[3] != matSpecularHighLightMapTags[3])return;
	if (_line[2] != matSpecularHighLightMapTags[2])return;
	if (_line[1] != matSpecularHighLightMapTags[1])return;
	if (_line[0] != matSpecularHighLightMapTags[0])return;

	targetMaterial->specularHighLightMap = LoadTextureName(&_line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatBumpMap(const std::string& _line)
{

	if (_line.size() < 9)return;

	if (_line[8] != ' ')return;
	if (_line[7] != matBumpMapTags[7])return;
	if (_line[6] != matBumpMapTags[6])return;
	if (_line[5] != matBumpMapTags[5])return;
	if (_line[4] != matBumpMapTags[4])return;
	if (_line[3] != matBumpMapTags[3])return;
	if (_line[2] != matBumpMapTags[2])return;
	if (_line[1] != matBumpMapTags[1])return;
	if (_line[0] != matBumpMapTags[0])return;

	targetMaterial->bumpMap = LoadTextureName(&_line[9]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatBumpMap2(const std::string& _line)
{
	if (_line.size() < 5)return;

	if (_line[4] != ' ')return;
	if (_line[3] != matBumpMapTags2[3])return;
	if (_line[2] != matBumpMapTags2[2])return;
	if (_line[1] != matBumpMapTags2[1])return;
	if (_line[0] != matBumpMapTags2[0])return;

	targetMaterial->bumpMap = LoadTextureName(&_line[5]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatMetallicMap(const std::string& _line)
{

	if (_line.size() < 7)return;

	if (_line[6] != ' ')return;
	if (_line[5] != matMetallicMapTags[5])return;
	if (_line[4] != matMetallicMapTags[4])return;
	if (_line[3] != matMetallicMapTags[3])return;
	if (_line[2] != matMetallicMapTags[2])return;
	if (_line[1] != matMetallicMapTags[1])return;
	if (_line[0] != matMetallicMapTags[0])return;

	targetMaterial->metallicMap = LoadTextureName(&_line[7]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatMetallicMap2(const std::string& _line)
{

	if (_line.size() < 3)return;

	if (_line[2] != ' ')return;
	if (_line[1] != matMetallicMapTags2[1])return;
	if (_line[0] != matMetallicMapTags2[0])return;

	targetMaterial->metallicMap = LoadTextureName(&_line[3]);

}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoader::ObjFile::SetMatNormalMap(const std::string& _line)
{

	if (_line.size() < 5)return;

	if (_line[4] != ' ')return;
	if (_line[3] != matNormalMapTags[3])return;
	if (_line[2] != matNormalMapTags[2])return;
	if (_line[1] != matNormalMapTags[1])return;
	if (_line[0] != matNormalMapTags[0])return;

	targetMaterial->normalMap = LoadTextureName(&_line[5]);

}

///////////////////////////////////////////////////////////////////////////////////////

std::string ChCpp::ModelLoader::ObjFile::LoadTextureName(const std::string& _line)
{

	ChStd::Bool loadFlg = false;
	std::string name = "";

	size_t nowPos = 0;
	size_t nowEndPos = 0;

	while (1)
	{
		nowPos = nowEndPos;
		nowEndPos = _line.find(' ', nowPos + 1);

		if (nowEndPos == _line.npos)nowEndPos = _line.length();

		if (_line[nowPos + 1] == '-')
		{

			nowPos = nowEndPos;
			nowEndPos = _line.find(' ', nowPos + 1);

			continue;
		}

		name = _line.substr(nowPos, nowEndPos - nowPos);
		break;
	}

	return name;
}
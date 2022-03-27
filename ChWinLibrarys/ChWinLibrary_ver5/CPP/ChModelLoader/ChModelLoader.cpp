#include"../../BaseIncluder/ChBase.h"

#include"../ChTextObject/ChTextObject.h"
#include"../ChModel/ChModelObject.h"

#include"ChModelLoader.h"

///////////////////////////////////////////////////////////////////////////////////////
//ChModelLoader Method//
///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoaderBase::Init(ModelObject* _model)
{
	oModel = _model;
}

///////////////////////////////////////////////////////////////////////////////////////

void ChCpp::ModelLoaderBase::SetModel(ChPtr::Shared<ModelFrame> _models)
{
	oModel->model = _models;
}

///////////////////////////////////////////////////////////////////////////////////////

std::string ChCpp::ModelLoaderBase::GetRoutePath(const std::string& _filePath)
{

	if (_filePath.find("\\") == _filePath.find("/"))return "";

	std::string tmpPath = ChStr::StrReplase(_filePath, "\\", "/");

	unsigned long tmp = tmpPath.rfind("/");

	return tmpPath.substr(0, tmp + 1);

}

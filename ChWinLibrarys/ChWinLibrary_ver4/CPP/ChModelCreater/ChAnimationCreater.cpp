#include"../../BaseIncluder/ChBase.h"

#include"../ChModel/ChModelObject.h"
#include"ChAnimationCreater.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//ModelAniCreater Method//
///////////////////////////////////////////////////////////////////////////////////////

void AnimationCreater::Init(ModelObject* _Model)
{
	Model = _Model;
}

///////////////////////////////////////////////////////////////////////////////////////

std::string& AnimationCreater::ModelNameIns()
{
	return Model->Model->ModelName;
}

///////////////////////////////////////////////////////////////////////////////////////

void AnimationCreater::SetModel(ChPtr::Shared<ModelFrame> _Models)
{
	Model->Model = _Models;
}
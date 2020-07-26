
#include"../../BaseIncluder/ChBase.h"

#include"../ChTexture/ChBaseTexture.h"

#include"ChModel.h"
#include"ChModelObject.h"

using namespace ChCpp;

std::map<
	std::string
	, ModelObject::Animation>
	ModelObject::AnimatorList;

///////////////////////////////////////////////////////////////////////////////////////
//ChModel Method//
///////////////////////////////////////////////////////////////////////////////////////

void ModelObject::Release()
{

	SetInitFlg(false);
}

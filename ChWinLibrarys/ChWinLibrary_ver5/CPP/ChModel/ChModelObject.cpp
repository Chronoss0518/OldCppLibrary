
#include"../../BaseIncluder/ChBase.h"

//#include"../ChTexture/ChBaseTexture.h"

#include"ChModelObject.h"

using namespace ChCpp;

std::map<
	std::string
	, ModelObject::Animation>
	ModelObject::animatorList;

///////////////////////////////////////////////////////////////////////////////////////
//ChModel Method//
///////////////////////////////////////////////////////////////////////////////////////

void ModelObject::Release()
{
	model = nullptr;

	if(!animatorNames.empty())animatorNames.clear();

}

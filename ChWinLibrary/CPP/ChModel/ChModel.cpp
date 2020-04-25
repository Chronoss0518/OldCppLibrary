
#include"../../BaseIncluder/ChBase.h"

#include"../ChTexture/ChBaseTexture.h"

#include"ChModel.h"

using namespace ChCpp;

Model::Frame Model::Non;

std::map<
	ChPtr::Shared<ModelObject>
	, Model::Animation>
	Model::AnimatorList;

std::map<
	std::string
	, std::function
	<ChPtr::Shared<ModelCreater>(const std::string& _FineName)>>
	Model::CreaterList;


///////////////////////////////////////////////////////////////////////////////////////
//ChModel Method//
///////////////////////////////////////////////////////////////////////////////////////

void Model::Release()
{
	SetInitFlg(true);
	ModelData.clear();

	SetInitFlg(false);
}

///////////////////////////////////////////////////////////////////////////////////////
//
//template<class T>
//void Model::SetMyModelCreater(const typename std::enable_if<std::is_base_of<ModelCreater, T>::value, std::string&>::type _ModelName)
//{
//
//	if (CreaterList.find(_ModelName) != CreaterList.end())return;
//
//	CreaterList[_ModelName] = 
//		[](const std::string& _FineName)->ChPtr::Shared<ModelCreater>
//	{
//
//		ChPtr::Shared<ModelCreater> Tmp;
//		Tmp = ChPtr::Make_S<T>();
//		return Tmp;
//	};
//
//	return;
//
//}template void Model::SetMyModelCreater<ModelCreater>(const typename std::enable_if<std::is_base_of<ModelCreater, ModelCreater>::value, std::string&>::type _ModelName);
//
//template<class T>
//void Model::SetMyModelCreater(const typename std::enable_if<!std::is_base_of<ModelCreater, T>::value, std::string&>::type _ModelName)
//{
//
//	return;
//
//}template void Model::SetMyModelCreater<int>(const typename std::enable_if<!std::is_base_of<ModelCreater, int>::value, std::string&>::type _ModelName);

///////////////////////////////////////////////////////////////////////////////////////

void Model::CreateModel(const std::string& _FilePath)
{

}

///////////////////////////////////////////////////////////////////////////////////////

void Model::OutModelFile(const std::string& _FilePath)
{

}

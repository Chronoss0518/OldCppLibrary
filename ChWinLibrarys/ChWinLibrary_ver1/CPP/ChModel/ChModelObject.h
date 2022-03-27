#ifndef Ch_CPP_MObj_h
#define Ch_CPP_MObj_h

#include"../ChModel/ChModel.h"
#include"../ChModelCreater/ChModelCreater.h"
#include"../ChModelCreater/ChAnimationCreater.h"


namespace ChCpp
{

	class ModelObject :public  ChCpp::ChCp::InitPack
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		inline virtual ~ModelObject() {}

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Init() {};

		virtual void Release();

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//



		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//


		///////////////////////////////////////////////////////////////////////////////////////
		//InsFunction//

		///////////////////////////////////////////////////////////////////////////////////////

		template<class T>
		auto CreateModel(const std::string& _FilePath)->typename std::enable_if<
			std::is_base_of<ModelCreater, T>::value, void>::type
		{
			ChPtr::Shared<ModelCreater> creater;
			creater = ChPtr::Make_S<T>();

			creater->Init(this);

			creater->CreateMesh(_FilePath);
		}

		///////////////////////////////////////////////////////////////////////////////////////

		template<class T>
		auto OutModelFile(const std::string& _FilePath)->typename std::enable_if<
			std::is_base_of<ModelCreater, T>::value, void>::type
		{

		}

		friend ModelCreater;
		friend AnimationCreater;

	protected:

		ChPtr::Shared<BaseModel>Model = nullptr;

		std::vector<std::string>AnimatorNames;

	private:

		using Animation = std::map<std::string, ChPtr::Shared<ModelAnimator>>;

		static	std::map<
			std::string
			, Animation>
			AnimatorList;



	};





}

#endif
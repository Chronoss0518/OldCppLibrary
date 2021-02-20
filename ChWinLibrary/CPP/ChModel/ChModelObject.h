#ifndef Ch_CPP_MObj_h
#define Ch_CPP_MObj_h

#include"../ChModel/ChModel.h"
#include"../ChModelCreater/ChModelCreater.h"
#include"../ChModelCreater/ChAnimationCreater.h"


namespace ChCpp
{

	class ModelObject :public  ChCpp::ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Init() {};

		virtual void Release()override;

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		ChPtr::Shared<ModelFrame> GetModel()const
		{
			return Model;
		}

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

			creater->CreateModel(_FilePath);
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

		ChPtr::Shared<ModelFrame>Model = nullptr;

		std::vector<std::string>AnimatorNames;

	private:

		using FrameName = std::string;
		using  AnimationName = std::string;

		using Animation = std::map<AnimationName, ChPtr::Shared<ModelAnimator>>;

		static	std::map<FrameName, Animation>AnimatorList;

	};





}

#endif
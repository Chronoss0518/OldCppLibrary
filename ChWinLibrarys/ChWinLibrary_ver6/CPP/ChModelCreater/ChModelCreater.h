
#ifndef Ch_CPP_CMesh_h
#define Ch_CPP_CMesh_h

namespace ChCpp
{

	class ModelObject;
	struct ModelFrame;

	class ModelCreater
	{

	public:


		///////////////////////////////////////////////////////////////////////////////////////

		inline virtual void CreateModel(const std::string& _FilePath) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		inline virtual void OutModelFile(const std::string& _FilePath) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		friend ModelObject;

	protected:
		
		void Init(ModelObject * _Model);

		void SetModel(ChPtr::Shared<ModelFrame> _Models);

		ChStd::Bool exceptionFlg = false;

	private:

		ModelObject* OModel;

	};
}


#endif

#ifndef Ch_CPP_CMesh_h
#define Ch_CPP_CMesh_h

namespace ChCpp
{

	class ModelObject;

	class ModelCreater
	{

	public:


		///////////////////////////////////////////////////////////////////////////////////////

		inline virtual void CreateMesh(const std::string& _FilePath) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		inline virtual void OutMeshFile(const std::string& _FilePath) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		friend ModelObject;

	protected:
		
		void Init(ModelObject * _Model);

		void SetModel(ChPtr::Shared<BaseModel> _Models);

		ModelObject* Model;

	};
}


#endif
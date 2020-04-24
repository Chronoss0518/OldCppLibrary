
#ifndef Ch_CPP_AMesh_h
#define Ch_CPP_AMesh_h

namespace ChCpp
{

	class ModelObject;

	class ModelAniCreater
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////////

		inline std::string& ModelNameIns()
		{
			return Model->ModelName;
		}

		///////////////////////////////////////////////////////////////////////////////////////

		inline virtual void CreateMesh(const std::string& _FilePath, ModelObject* _Model) {};

		///////////////////////////////////////////////////////////////////////////////////////

		inline virtual void OutMeshFile(const std::string& _FilePath, const ModelObject* _Model) {};

		///////////////////////////////////////////////////////////////////////////////////////

		friend ModelObject;

	private:

		inline void Init(const ModelObject* _Model) { Model = const_cast<ModelObject*>(_Model); }

		ModelObject* Model;

	};
}



#endif
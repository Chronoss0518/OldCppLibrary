#ifndef Ch_CPP_Mesh_h
#define Ch_CPP_Mesh_h


namespace ChCpp
{
	class Mesh
	{

	private:



	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetModel(ChPtr::Shared<Ch3D::Frame<Ch3D::MeshVertex>>& _model);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		ChPtr::Shared<Ch3D::Frame<Ch3D::MeshVertex>> GetModel();

		
		///////////////////////////////////////////////////////////////////////////////////
		

	private:

		ChPtr::Shared<Ch3D::Frame<Ch3D::MeshVertex>>model;

		std::map<std::string, unsigned long>frameNames;

		std::vector<ChPtr::Shared<Ch3D::Frame<Ch3D::MeshVertex>>>frames;

	};
}

#endif

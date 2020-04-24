#ifndef Ch_CPP_Mesh_h
#define Ch_CPP_Mesh_h

namespace ChCpp
{
	class ModelCreater;

	 typedef class ModelObject :public  ChCpp::ChCp::InitPack
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//MeshDataStruct//

		struct VertexData
		{
			ChVec3 Pos;
			ChVec3 Normal;
			ChVec2 UVPos;
		};

		struct Material
		{
			std::string MaterialName = "";
			ChVec4 Diffuse = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
			ChVec4 Specular = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
			ChVec4 Ambient = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
			float SpePow = 1.0f;
			std::string TextureName = "";
		};

		struct SurFace
		{
			std::vector<unsigned long>Vertexs;
			unsigned long Materials;
			ChVec3 Normal;

			inline ~SurFace()
			{
				Vertexs.clear();
			}
		};

		struct Mesh
		{
			std::vector<ChPtr::Shared<VertexData>>VertexList;
			std::vector<ChPtr::Shared<Material>>MaterialList;
			std::map<std::string, unsigned long> MaterialNo;
			std::vector<ChPtr::Shared<SurFace>>FaceList;

			inline ~Mesh()
			{
				FaceList.clear();

				VertexList.clear();

				MaterialList.clear();
			}
		};

		struct Frame
		{
			ChMatrix BaseMat;
			std::string MyName;
			ChPtr::Shared<Mesh>Meshs;
			std::string Parent;

			~Frame() { Meshs = nullptr; }
		};

		///////////////////////////////////////////////////////////////////////////////////////
		//Operator//

		inline const ChPtr::Shared<Frame> operator[](unsigned int _Num)const
		{
			if (*this)return nullptr;
			if (ModelData.size() <= 0)return nullptr;
			if (ModelData.size() <= _Num)return nullptr;

			return ModelData[_Num];
		}

		inline Frame& operator[](unsigned int _Num)
		{
			if (*this)return Non;
			if (ModelData.size() <= 0)return Non;
			if (ModelData.size() <= _Num)return Non;


			return *ModelData[_Num];
		}

		///////////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		inline virtual ~ModelObject(){}

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		inline void Init() {};

		virtual void Release();

		///////////////////////////////////////////////////////////////////////////////////////
		//GetFunction//


		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//ユーザーが独自のモデルを読み込む際に利用できる。//
		//ChCpp::ModelCreaterを継承する必要がある//
		template<class T>
		inline void SetMyModelCreater
		(const typename std::enable_if
			<std::is_base_of<ModelCreater, T>::value, std::string&>::type
			_ModelName)
		{

			if (CreaterList.find(_ModelName) != CreaterList.end())return;

			CreaterList[_ModelName] =
				[](const std::string& _FineName)->ChPtr::Shared<ModelCreater>
			{

				return ChPtr::Make_S<T>();
			};

			return;

		}

		template<class T>
		inline void SetMyModelCreater
		(const typename std::enable_if
			<!std::is_base_of<ModelCreater, T>::value, std::string&>::type
			_ModelName)
		{
			return;
		}
			

		///////////////////////////////////////////////////////////////////////////////////////
		//InsFunction//


		///////////////////////////////////////////////////////////////////////////////////////

		void CreateModel(const std::string& _FilePath);

		///////////////////////////////////////////////////////////////////////////////////////

		void OutModelFile(const std::string& _FilePath);

		friend ModelCreater;

	protected:

		ChPtr::Shared<ModelCreater>Creater = nullptr;

		std::vector<ChPtr::Shared<Frame>>ModelData;
		std::string ModelName;

		static std::map<
			std::string
			,std::function
			<ChPtr::Shared<ModelCreater>(const std::string& _FineName)>
		>CreaterList;

	private:

		static Frame Non;

	}Model;

	 class ModelCreater
	{

	public:


		inline std::vector<ChPtr::Shared<Model::Frame>>& ModelDataIns()
		{
			return Model->ModelData;
		}

		///////////////////////////////////////////////////////////////////////////////////////

		inline std::string& ModelNameIns()
		{
			return Model->ModelName;
		}

		///////////////////////////////////////////////////////////////////////////////////////

		inline virtual void CreateMesh(const std::string& _FilePath) {};

		///////////////////////////////////////////////////////////////////////////////////////

		inline virtual void OutMeshFile(const std::string& _FilePath) {};

		///////////////////////////////////////////////////////////////////////////////////////

		friend ModelObject;

	private:

		inline void Init(const ModelObject* _Model) { Model = const_cast<ModelObject*>(_Model); }

		ModelObject* Model;

	};

}

#endif
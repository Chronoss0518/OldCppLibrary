#ifndef Ch_CPP_3D_h
#define Ch_CPP_3D_h

namespace Ch3D
{

	struct BaseVertex
	{
		ChVec3 Pos;
		ChVec2 UV;
		ChVec4 Color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	struct PolyVertex : public BaseVertex
	{
		ChVec3 Normal = ChVec3(0.0f, 0.0f, -1.0f);
	};

	struct MeshVertex : public PolyVertex
	{
		ChVec3 FaceNormal = ChVec3(0.0f, 0.0f, -1.0f);
		ChUIMat BlendIndex;
		ChLMat BlendPow;
		unsigned long BlendNum = 0;
	};

	//‘ÎÛ‚Ì’¸“_‚ğŠÇ—‚·‚é//
	template<class vertex>
	struct TriPolygon
	{
		 typename std::enable_if<std::is_base_of<BaseVertex,vertex>::value,vertex>::type vertexs[3];
		 unsigned long VertexNo[3];
	};

	struct Material
	{
		ChVec4 Diffuse;
		ChVec4 Ambient;
		ChVec3 Specular;
		float SpecularPower;
	};

	struct MaterialData
	{
		Material Mate;
	};

	//Material‚É‘Î‰‚·‚é–Ê‚ğŠÇ—‚·‚é//
	template<class vertex = BaseVertex,class Mate = MaterialData>
	struct Primitive
	{
		std::vector<vertex*> TriPolygons;
		vertex* VertexList = nullptr;

		Mate mate;

	};

	template<class vertex = BaseVertex,class primitive = Primitive<vertex>>
	struct Frame
	{

		std::string FrameName;

		std::map<std::string,ChPtr::Shared<primitive>>PrimitiveDatas;

		std::vector<primitive*> polyDatas;
		std::map<std::string, unsigned long>mateNames;


		std::vector<ChPtr::Shared<Frame>>ChildFrame;

		ChPtr::Shared<Frame> ParentFrame;

	};


}

#endif
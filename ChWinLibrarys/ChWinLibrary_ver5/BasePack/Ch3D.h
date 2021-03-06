#ifndef Ch_CPP_3D_h
#define Ch_CPP_3D_h

#include"../BaseIncluder/ChBase.h"

namespace Ch3D
{

	struct Vertex
	{
		ChVec3 pos;
		ChVec2 uv;
		ChVec4 color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	struct PolyVertex : public Vertex
	{
		ChVec3 normal = ChVec3(0.0f, 0.0f, -1.0f);
	};

	struct MeshVertex : public PolyVertex
	{
		ChVec3 faceNormal = ChVec3(0.0f, 0.0f, -1.0f);
		ChUIMat blendIndex;
		ChLMat blendPow;
		unsigned long blendNum = 0;
	};

	//対象の頂点を管理する//
	template<class vertex>
	struct TriPolygon
	{
		 typename std::enable_if<std::is_base_of<Vertex,vertex>::value,vertex>::type vertexs[3];
		 unsigned long vertexNo[3];
	};

	struct Material
	{
		ChVec4 diffuse;
		ChVec3 specular;
		float specilarPower;
		ChVec3 ambient;

	};

	struct MaterialStatus
	{
		Material mate;

		std::string texture;
		std::string normalMap;
		std::string damegeMap;
	};

	//Materialに対応する面を管理する//
	template<class vertex = Vertex>
	struct Primitive
	{
		std::vector<ChPtr::Shared<TriPolygon<Vertex>>> triPolygons = nullptr;
		Vertex* vertexList = nullptr;

		ChPtr::Shared<MaterialStatus>mate = nullptr;

	};

	template<class vertex = Vertex,class primitive = Primitive<vertex>>
	struct Frame
	{

		std::vector<ChPtr::Shared<primitive>> polyDatas = nullptr;
		std::map<std::string, unsigned long>mateNames;

		std::vector<ChPtr::Shared<Frame<Vertex>>> parent;

	};


	template<class vertex = Vertex>
	struct MeshBuffer
	{
		
	};


}

#endif
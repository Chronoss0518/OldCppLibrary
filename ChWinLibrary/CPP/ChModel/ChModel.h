#ifndef Ch_CPP_Model_h
#define Ch_CPP_Model_h

namespace ChCpp
{
	class ModelAnimator
	{
	protected:

		float Speed = 0.1f;

		unsigned long AllAnimationCount;

		struct AniDatas
		{
			ChVec3 Pos;
			ChQua Rot;
			ChVec3 Scal;
		};

		struct AnimationData
		{
			AniDatas Start;
			AniDatas End;
			unsigned long AnimationFrameCount;
		};

		std::vector<ChPtr::Shared<AnimationData>>Animation;

	};

	struct BaseModel
	{

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
			float AmbientPow = 0.0f;
			float SpePow = 1.0f;
			std::vector<std::string>TextureName;
		};

		struct SurFace
		{
			std::vector<unsigned long>VertexNo;
			unsigned long Materials;
			ChVec3 Normal;

			inline ~SurFace()
			{
				VertexNo.clear();
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
			ChLMatrix BaseMat;
			std::string MyName;
			ChPtr::Shared<Mesh>Meshs;
			std::string Parent;

			~Frame()
			{
				Meshs = nullptr;
				ChildFrames.clear();
			}

			std::vector<ChPtr::Shared<Frame>>ChildFrames;

		};

		ChPtr::Shared<Frame>ModelData = nullptr;
		std::string ModelName;

	};


}
#endif

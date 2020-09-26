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
		};

		struct Material
		{
			std::string MaterialName = "";
			ChVec4 Diffuse = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
			ChVec3 Specular = ChVec3(1.0f, 1.0f, 1.0f);
			float AmbientPow = 0.0f;
			float SpePow = 1.0f;
			std::vector<std::string>TextureNames;
		};

		struct SurFace
		{

			struct SurFaceVertex
			{
				size_t VertexNo;
				ChVec2 UVPos;
			};

			const unsigned long VertexRotations[2][3] = { {0,1,2},{0,2,3} };

			std::vector<ChPtr::Shared<SurFaceVertex>>VertexData;
			unsigned long Materials;
			ChVec3 Normal;
			
			inline ~SurFace()
			{
				VertexData.clear();
			}
		};

		struct WeightData
		{
			ChLMat OffsetMat;

			std::map<unsigned long, float> VertexDatas;
		};

		struct Mesh
		{
			std::vector<ChPtr::Shared<VertexData>>VertexList;
			std::vector<ChPtr::Shared<Material>>MaterialList;
			std::map<std::string, unsigned long> MaterialNo;
			std::vector<ChPtr::Shared<SurFace>>FaceList;
			std::map<std::string, ChPtr::Shared<WeightData>>SkinWeightDatas;

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
			ChPtr::Shared<Frame>Parent;
			std::vector<ChPtr::Shared<Frame>>ChildFrames;

			~Frame()
			{
				Meshs = nullptr;
				ChildFrames.clear();
			}

		};

		ChPtr::Shared<Frame>ModelData = nullptr;
		std::string ModelName;

	};

}
#endif

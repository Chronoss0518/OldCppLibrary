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

	struct ModelFrame
	{
		///////////////////////////////////////////////////////////////////////////////////////
		//MeshDataStruct//

		struct VertexData
		{
			ChVec3 Pos;
			ChVec3 Normal;
			ChUIMat BoneNo;
			ChLMat	BlendPow;
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


			SurFaceVertex VertexData[3];
			unsigned long Materials;
			ChVec3 Normal;
			
			inline ~SurFace()
			{

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
			ChPtr::Shared<Frame>Parent;
			std::vector<ChPtr::Shared<Frame>>ChildFrames;

			~Frame()
			{
				Meshs = nullptr;
				ChildFrames.clear();
			}

		};


		struct BoneTrees
		{

			ChLMat BaseMat;
			ChPtr::Shared<BoneTrees> ParentBone = nullptr;
			std::vector<ChPtr::Shared<BoneTrees>>ChildBones;
		};

		std::map<std::string, unsigned long>BoneNames;
		std::vector<ChPtr::Shared<BoneTrees>>BoneList;

		ChPtr::Shared<Frame>ModelData = nullptr;
		std::string ModelName;

	};

}
#endif

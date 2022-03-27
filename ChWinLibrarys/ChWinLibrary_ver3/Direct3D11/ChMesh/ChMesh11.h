#ifndef Ch_D3D11_Model_h
#define Ch_D3D11_Model_h

#include"../../CPP/ChModel/ChModelObject.h"
#include"../ChShaderStructures.h"

namespace ChD3D11
{

	class Texture11;

	struct FrameData11
	{
		std::map<std::string,ChPtr::Shared<PrimitiveData11<PrimitiveVertex11>>>PrimitiveDatas;

		std::string FrameName;

		ChMat_11 BaseMat;

		ChPtr::Shared<FrameData11> ParentFrame;

		std::vector<ChPtr::Shared<FrameData11>>ChildFrame;


		unsigned long PrimitiveCount = 0;

	};

	class Mesh11:public ShaderObject<PrimitiveVertex11>
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(const ID3D11Device* _Device);

		void Init();

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		inline ChStd::Bool IsMesh() const { return ModelData != nullptr; }

		///////////////////////////////////////////////////////////////////////////////////////
		//Creater//

		virtual void Create(const ChCpp::ModelFrame& _BaseModels);

		///////////////////////////////////////////////////////////////////////////////////////

		void SetDrawData(ID3D11DeviceContext* _DC)override;

		void SetDrawData(ID3D11DeviceContext* _DC,const std::string& _FrameName);

	protected:

		///////////////////////////////////////////////////////////////////////////////////////

		void CreateFrames(
			ChPtr::Shared<FrameData11>& _Frames
			, const ChCpp::ModelFrame::Frame& _BaseModels);

		void CreatePrimitiveData(
			ChPtr::Shared<FrameData11>& _Frames
			, const ChCpp::ModelFrame::Frame& _BaseModels);

		std::vector<std::vector<ChPtr::Shared<ChCpp::ModelFrame::SurFace>>>
			CreateSurfaceList(
			const ChCpp::ModelFrame::Frame& _BaseModels);

		///////////////////////////////////////////////////////////////////////////////////////

		void UpdateFrame();

		///////////////////////////////////////////////////////////////////////////////////////

		using FrameName = std::string;
		using MaterialNo = unsigned long;
		using MaterialName = std::string;

		std::map<std::string,ChPtr::Shared<FrameData11>>FrameNames;

		std::vector<ChPtr::Shared<FrameData11>>FrameList;

		ChPtr::Shared<FrameData11> ModelData = nullptr;

		ChMat_11* BoneList = nullptr;

	};

}

#endif
#ifndef Ch_D3D11_Model_h
#define Ch_D3D11_Model_h

#include"../../CPP/ChModel/ChModelObject.h"
#include"../ChShaderStructures11.h"

namespace ChD3D11
{

	class Texture11;

	struct FrameData11
	{
		std::map<std::string,ChPtr::Shared<PrimitiveData11<PrimitiveVertex11>>>primitiveDatas;

		std::string frameName;

		ChMat_11 baseMat;

		ChPtr::Shared<FrameData11> parentFrame;

		std::vector<ChPtr::Shared<FrameData11>>childFrame;

		unsigned long primitiveCount = 0;

	};

	class Mesh11:public ShaderObject<PrimitiveVertex11>
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(ID3D11Device* _device);

		void Init();

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		inline ChStd::Bool IsMesh() const { return modelData != nullptr; }

		///////////////////////////////////////////////////////////////////////////////////////
		//Creater//

		virtual void Create(const ChCpp::ModelObject& _baseModels);

		///////////////////////////////////////////////////////////////////////////////////////

		void SetDrawData(ID3D11DeviceContext* _dc)override;

		void SetDrawData(ID3D11DeviceContext* _dc,const std::string& _frameName);

	protected:

		///////////////////////////////////////////////////////////////////////////////////////

		void CreateFrames(
			ChPtr::Shared<FrameData11>& _frames
			, const ChCpp::ModelFrame::Frame& _baseModels);

		void CreatePrimitiveData(
			ChPtr::Shared<FrameData11>& _frames
			, const ChCpp::ModelFrame::Frame& _baseModels);

		std::vector<std::vector<ChPtr::Shared<ChCpp::ModelFrame::SurFace>>>
			CreateSurfaceList(
			const ChCpp::ModelFrame::Frame& _baseModels);

		///////////////////////////////////////////////////////////////////////////////////////

		void UpdateFrame();

		///////////////////////////////////////////////////////////////////////////////////////

		using FrameName = std::string;
		using MaterialNo = unsigned long;
		using MaterialName = std::string;

		std::map<std::string,ChPtr::Shared<FrameData11>>frameNames;

		std::vector<ChPtr::Shared<FrameData11>>frameList;

		ChPtr::Shared<FrameData11> modelData = nullptr;

		ChMat_11* boneList = nullptr;


	private:

		ChPtr::Shared<Texture11>whiteTex = nullptr;
		ChPtr::Shared<Texture11>normalTex = nullptr;

	};

}

#endif
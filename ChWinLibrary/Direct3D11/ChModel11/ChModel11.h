#ifndef Ch_D3D11_Model_h
#define Ch_D3D11_Model_h

#include"../../CPP/ChModel/ChModelObject.h"

namespace ChD3D11
{
	class Texture11;

	class Model11 :public ChCpp::ModelObject
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//
		
		void SetTextures();

		void SetTextures(const ID3D11Device* _Device);


	protected:

		///////////////////////////////////////////////////////////////////////////////////////

		void SetTextures(ChPtr::Shared<ChCpp::BaseModel::Frame> _Frames
			, const ID3D11Device* _Device);

		using FrameName = std::string;
		using MaterialName = std::string;
		using TextureName = std::string;
		
		using MateTextures = std::map<MaterialName, ChPtr::Shared<Texture11>>;

		std::map<FrameName, MateTextures>MaterialNames;




	};

}

#endif

#ifndef Ch_CPP_Com_Trans_h
#define Ch_CPP_Com_Trans_h

namespace ChCpp
{
	typedef class TransformComponent:ChCpp::BaseComponent
	{

	public:

		ChVec3 Position;

		ChQua Rotation;

		ChVec3 Scaling = ChVec3(1.0f, 1.0f, 1.0f);


	}TransformCom;

}



#endif
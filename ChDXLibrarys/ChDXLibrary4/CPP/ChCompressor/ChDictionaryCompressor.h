#ifndef Ch_CPP_Cmp_Dic_h
#define Ch_CPP_Cmp_Dic_h

#include"ChBaseCompressor.h"

namespace ChCpp
{
	namespace Cmp
	{
		 typedef class Dictionary:public BaseComp
		{
		public:

			std::string Press(const std::string& _PressBase)override;

			std::string Thaw(const std::string& _PressBase)override;

		}Dic;

	}
}

#endif

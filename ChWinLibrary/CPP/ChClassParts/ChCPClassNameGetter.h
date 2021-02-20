

#ifndef Ch_CPP_CP_CNGet_h
#define Ch_CPP_CP_CNGet_h

namespace ChCpp
{
	namespace ChCp
	{
		//�p�����ė��p����//
		//���g�̃N���X�l�[���y�уN���X���g�̌^���擾�ł���//
		class ClassNameGetter
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			template<class T>
			inline std::string GetName() 
			{
				std::string Tmp;
				
#ifdef __GNUC__

				Tmp = typeid(T).name();

#else

				Tmp = typeid(T).raw_name();

#endif
				return Tmp;
			}

		protected:

			ClassNameGetter(){}

		};

		using CNGetter = ClassNameGetter;

	}
}

#endif

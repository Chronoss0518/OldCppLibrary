

#ifndef Ch_CPP_CP_CNGet_h
#define Ch_CPP_CP_CNGet_h

namespace ChCpp
{
	namespace ChCp
	{
		//�p�����ė��p����//
		//���g�̃N���X�l�[���y�уN���X���g�̌^���擾�ł���//
		template<class T>
		class ClassNameGetter
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			inline std::string GetName() 
			{
				std::string Tmp = typeid(T).name;
				
					size_t TmpNum = Tmp.find(" ", 0);
					TmpNum = TmpNum == std::string::npos ? 0 : TmpNum;
				

				Tmp = &Tmp[TmpNum];
				return Tmp;
			}

		};

		template<class T>
		using CNGetter = ClassNameGetter<T>;

	}
}

#endif

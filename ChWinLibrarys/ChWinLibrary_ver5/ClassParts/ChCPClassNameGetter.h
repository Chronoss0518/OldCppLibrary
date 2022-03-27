

#ifndef Ch_CPP_CP_CNGet_h
#define Ch_CPP_CP_CNGet_h

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
			std::string tmp;

#ifdef __GNUC__

			tmp = typeid(T).name();

#else

			tmp = typeid(T).raw_name();

#endif
			return tmp;
		}

	protected:

		ClassNameGetter() {}

	};

	using CNGetter = ClassNameGetter;

}

#endif

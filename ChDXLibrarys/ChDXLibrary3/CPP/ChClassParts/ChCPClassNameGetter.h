

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

			T* Tmp = nullptr;

		public:

			///////////////////////////////////////////////////////////////////////////////////

			T GetType() { return T(); }

			///////////////////////////////////////////////////////////////////////////////////

			std::string GetName() { return typeid(T).Name; }

		};

		template<class T>
		using CNGetter = ClassNameGetter<T>;

	}
}

#endif



#ifndef Ch_CPP_CP_CNGet_h
#define Ch_CPP_CP_CNGet_h

namespace ChCpp
{
	namespace ChCp
	{
		//継承して利用する//
		//自身のクラスネーム及びクラス自身の型を取得できる//
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

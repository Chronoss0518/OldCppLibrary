

#ifndef Ch_CPP_CP_CNGet_h
#define Ch_CPP_CP_CNGet_h

namespace ChCp
{
	//継承して利用する//
	//自身のクラスネーム及びクラス自身の型を取得できる//
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

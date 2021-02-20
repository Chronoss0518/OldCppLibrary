

#ifndef Ch_CPP_CP_CNGet_h
#define Ch_CPP_CP_CNGet_h

namespace ChCpp
{
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



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

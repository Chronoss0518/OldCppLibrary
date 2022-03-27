
#ifndef Ch_CPP_CP_Rel_h
#define Ch_CPP_CP_Rel_h

namespace ChCpp
{
	namespace ChCp
	{

		//継承して利用する//
		//メモリ開放が行われる際に必ずRelease関数を呼ばれる//
		//Release関数をオーバーライドする必要がある//
		class Releaser
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			virtual void Release() {};

			///////////////////////////////////////////////////////////////////////////////////
			//ConstructorDestructor//

		protected:

			virtual ~Releaser()
			{
				Release();
			}

		};


	}
}
#endif

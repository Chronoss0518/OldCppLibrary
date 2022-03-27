
#ifndef Ch_CPP_CParts_h
#define Ch_CPP_CParts_h

namespace ChCpp
{
	namespace CP
	{

		class CPBase :public std::enable_shared_from_this<CPBase>
		{

		};


		class UpdateStart :public CPBase
		{
		public:

			virtual void Function() = 0;

		};

		class Update :public CPBase
		{
		public:

			virtual void Function() = 0;

		};

		class UpdateEnd :public CPBase
		{
		public:

			virtual void Function() = 0;

		};

		class MoveStart :public CPBase
		{
		public:

			virtual void Function() = 0;

		};

		class Move :public CPBase
		{
		public:

			virtual void Function() = 0;

		};

		class MoveEnd :public CPBase
		{
		public:

			virtual void Function() = 0;

		};

		class DrawStart :public CPBase
		{
		public:

			virtual void Function() = 0;

		};

		class Draw2D :public CPBase
		{
		public:

			virtual void Function() = 0;

		};

		class Draw3D :public CPBase
		{
		public:

			virtual void Function() = 0;

		};

		class DrawEnd :public CPBase
		{
		public:

			virtual void Function() = 0;

		};
		
	}
}

#endif
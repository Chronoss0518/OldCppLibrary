
#ifndef Ch_CPP_OParts_h
#define Ch_CPP_OParts_h

namespace ChCpp
{
	namespace OP
	{
		class OPBase :public std::enable_shared_from_this<OPBase>
		{

		};

		class UpdateStart :public OPBase
		{
		public:

			virtual void Function() = 0;

		};

		class Update :public OPBase
		{
		public:

			virtual void Function() = 0;

		};

		class UpdateEnd :public OPBase
		{
		public:

			virtual void Function() = 0;

		};

		class MoveStart :public OPBase
		{
		public:

			virtual void Function() = 0;

		};

		class Move :public OPBase
		{
		public:

			virtual void Function() = 0;

		};

		class MoveEnd :public OPBase
		{
		public:

			virtual void Function() = 0;

		};

		class DrawStart :public OPBase
		{
		public:

			virtual void Function() = 0;

		};

		class Draw2D :public OPBase
		{
		public:

			virtual void Function() = 0;

		};

		class Draw3D :public OPBase
		{
		public:

			virtual void Function() = 0;

		};

		class DrawEnd :public OPBase
		{
		public:

			virtual void Function() = 0;

		};

		class UseTransForm :public OPBase
		{
		public:

			

		};

	}
}

#endif
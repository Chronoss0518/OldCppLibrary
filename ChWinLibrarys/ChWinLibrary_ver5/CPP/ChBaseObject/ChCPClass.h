
#ifndef Ch_CPP_CParts_h
#define Ch_CPP_CParts_h

namespace ChCpp
{
	namespace ClassPerts
	{

		class CPBase{};


		class CPUpdateStart :public CPBase
		{
		public:

			virtual void UpdateStart() = 0;

		};

		class CPUpdate :public CPBase
		{
		public:

			virtual void Update() = 0;

		};

		class CPUpdateEnd :public CPBase
		{
		public:

			virtual void UpdateEnd() = 0;

		};

		class CPMoveStart :public CPBase
		{
		public:

			virtual void MoveStart() = 0;

		};

		class CPMove :public CPBase
		{
		public:

			virtual void Move() = 0;

		};

		class CPMoveEnd :public CPBase
		{
		public:

			virtual void MoveEnd() = 0;

		};

		class CPDrawStart :public CPBase
		{
		public:

			virtual void DrawStart() = 0;

		};

		class CPDraw2D :public CPBase
		{
		public:

			virtual void Draw2D() = 0;

		};

		class CPDraw3D :public CPBase
		{
		public:

			virtual void Draw3D() = 0;

		};

		class CPDrawEnd :public CPBase
		{
		public:

			virtual void DrawEnd() = 0;

		};
		
	}
}

#endif
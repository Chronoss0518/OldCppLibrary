
#ifndef Ch_CPP_OParts_h
#define Ch_CPP_OParts_h

namespace ChCpp
{
	//OP:ObjectPartsの略//
	//BaseComponentを作成する際に継承して使用//
	//各オブジェクトにメソッドを所持させる事が出来る//
	class OP_Update
	{
	public:

		virtual void UpdateBegin() {};

		virtual void Update() = 0;

		virtual void UpdateEnd() {};

	};

	//OP:ObjectPartsの略//
	//BaseComponentを作成する際に継承して使用//
	//各オブジェクトにメソッドを所持させる事が出来る//
	class OP_Move
	{
	public:

		virtual void MoveBegin() {};

		virtual void Move() = 0;

		virtual void MoveEnd() {};

	};

	//OP:ObjectPartsの略//
	//BaseComponentを作成する際に継承して使用//
	//各オブジェクトにメソッドを所持させる事が出来る//
	class OP_Draw
	{
	public:

		virtual void DrawBegin() {}

		virtual void Draw3D() {}

		virtual void Draw2D() {}

		virtual void DrawEnd() {}

	};


}

#endif
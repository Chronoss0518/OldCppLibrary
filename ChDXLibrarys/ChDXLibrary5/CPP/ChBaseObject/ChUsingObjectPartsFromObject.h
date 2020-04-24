
#ifndef Ch_CPP_UsingOPs_Obj_h
#define Ch_CPP_UsingOPs_Obj_h

namespace ChCpp
{


	class BU_Object : public BaseObject, public OP_UpdateBegin
	{

	};

	class U_Object : public BaseObject, public OP_Update
	{

	};

	class EU_Object : public BaseObject, public OP_UpdateEnd
	{

	};

	class BM_Object : public BaseObject, public OP_MoveBegin
	{

	};

	class M_Object : public BaseObject, public OP_Move
	{

	};

	class EM_Object : public BaseObject, public OP_MoveEnd
	{

	};

	class BD_Object : public BaseObject, public OP_DrawBegin
	{

	};

	class D3_Object : public BaseObject, public OP_Draw3D
	{

	};

	class D2_Object : public BaseObject, public OP_Draw2D
	{

	};

	class ED_Object : public BaseObject, public OP_DrawEnd
	{

	};

}

#endif
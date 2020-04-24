
#ifndef Ch_CPP_UsingOPs_h
#define Ch_CPP_UsingOPs_h

namespace ChCpp
{

	class BU_Component : public BaseComponent, public OP_UpdateBegin
	{

	};

	class U_Component : public BaseComponent, public OP_Update
	{

	};

	class EU_Component : public BaseComponent, public OP_UpdateEnd
	{

	};

	class BM_Component : public BaseComponent, public OP_MoveBegin
	{

	};

	class M_Component : public BaseComponent, public OP_Move
	{

	};

	class EM_Component : public BaseComponent, public OP_MoveEnd
	{

	};

	class BD_Component : public BaseComponent, public OP_DrawBegin
	{

	};

	class D3_Component : public BaseComponent, public OP_Draw3D
	{

	};

	class D2_Component : public BaseComponent, public OP_Draw2D
	{

	};

	class ED_Component : public BaseComponent, public OP_DrawEnd
	{

	};



}


#endif
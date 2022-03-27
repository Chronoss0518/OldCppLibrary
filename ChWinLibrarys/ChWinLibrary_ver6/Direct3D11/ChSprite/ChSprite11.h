#ifndef Ch_D3D11_Sprite_h
#define Ch_D3D11_Sprite_h

#ifndef Ch_D3D11_SStruct_h
#include"../ChShaderStructures11.h"
#endif

namespace ChD3D11
{

	enum class SpritePositionName : unsigned char
	{
		LeftTop,RightTop,RightDown, LeftDown
	};

	class Sprite11 :public ShaderObject<Vertex11>
	{

	public:

		Sprite11& operator=(const Sprite11& _Sp)
		{
			for (unsigned char i = 0; i < 4; i++)
			{
				Position[i] = _Sp.Position[i];
				UVPoss[i] = _Sp.UVPoss[i];
			}

			UpdateFlg = true;

			return *this;

		}

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init();

		void Init(const ID3D11Device* _Device);

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPos(const SpritePositionName _PosNames, const  ChVec2& _PosData)
		{
			SetPos(ChStd::EnumCast(_PosNames), _PosData);
		}

		void SetPos(const unsigned char _PosNames, const  ChVec2& _PosData);

		inline void SetUVPos(const SpritePositionName _PosNames, const ChVec2& _PosData)
		{
			SetUVPos(ChStd::EnumCast(_PosNames), _PosData);
		}

		void SetUVPos(const unsigned char _PosNames, const  ChVec2& _PosData);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//


		inline ChVec2 GetPos(const SpritePositionName _PosNames)
		{
			return Position[ChStd::EnumCast(_PosNames)];
		}

		inline ChVec2 GetPos(const unsigned char _Num)
		{
			if (_Num >= 4)return ChVec2();

			return Position[_Num];
		}

		inline ChVec2 GetPosUVPos(const SpritePositionName _PosNames)
		{
			return UVPoss[ChStd::EnumCast(_PosNames)];
		}

		ChVec2 GetPosUVPos(const unsigned char _Num)
		{
			if (_Num >= 4)return ChVec2();

			return UVPoss[_Num];
		}

		///////////////////////////////////////////////////////////////////////////////////
		
		inline void Move(const ChVec2& _Vec) { Move(_Vec.x, _Vec.y); }

		void Move(const float _x,const float _y);

		inline void MoveX(const float _x) { Move(_x, 0.0f); }

		inline void MoveY(const float _y) { Move(0.0f, _y); }

		///////////////////////////////////////////////////////////////////////////////////

		void SetDrawData(ID3D11DeviceContext* _DC)override;

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		void UpdateVertex();

		///////////////////////////////////////////////////////////////////////////////////

		//ChVec2 Position[4] = 
		//{
		//	ChVec2(-1.0f,-1.0f)	//LeftTop//
		//	,ChVec2(1.0f,-1.0f)	//RightTop//
		//	,ChVec2(1.0f,1.0f)	//RightDown//
		//	,ChVec2(-1.0f,1.0f)	//LeftDown//
		//};

		ChVec2 Position[4] =
		{
			ChVec2(-1.0f,1.0f)	//LeftTop//
			,ChVec2(1.0f,1.0f)	//RightTop//
			,ChVec2(1.0f,-1.0f)	//RightDown//
			,ChVec2(-1.0f,-1.0f)	//LeftDown//
		};

		ChVec2 UVPoss[4] =
		{
			ChVec2(0.0f,0.0f)	//LeftTop//
			,ChVec2(1.0f,0.0f)	//RightTop//
			,ChVec2(1.0f,1.0f)	//RightDown//
			,ChVec2(0.0f,1.0f)	//LeftDown//
		};

		ChStd::Bool UpdateFlg = true;

		PrimitiveData11<Vertex11> Primitives;

	};

}

#endif
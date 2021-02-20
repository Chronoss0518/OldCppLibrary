#ifndef Ch_D3D11_Sprite_h
#define Ch_D3D11_Sprite_h

#include"../ChShaderStructures11.h"

namespace ChD3D11
{

	enum class SpritePositionName : unsigned char
	{
		LeftTop,RightDown,RightTop, LeftDown
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

		inline ChVec2 GetPos(const unsigned char _Num)
		{
			if (_Num >= 4)return ChVec2();

			return Position[_Num];

		}

		inline ChVec2 GetUVPos(const unsigned char _Num)
		{
			if (_Num >= 4)return ChVec2();

			return UVPoss[_Num];

		}


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
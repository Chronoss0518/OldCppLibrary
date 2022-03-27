#ifndef Ch_D3D11_Sprite_h
#define Ch_D3D11_Sprite_h

#include"../ChShaderStructures11.h"

namespace ChD3D11
{

	enum class SpritePositionName : unsigned char
	{
		LeftTop,RightTop,RightDown, LeftDown
	};

	class Sprite11 :public ShaderObject<Vertex11>
	{

	public:

		Sprite11& operator=(const Sprite11& _sp)
		{
			for (unsigned char i = 0; i < 4; i++)
			{
				poss[i] = _sp.poss[i];
				uvPoss[i] = _sp.uvPoss[i];
			}

			updateFlg = true;

			return *this;

		}

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init();

		void Init(const ID3D11Device* _device);

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		inline void SetPos(const SpritePositionName _posNames, const  ChVec2& _posData)
		{
			SetPos(ChStd::EnumCast(_posNames), _posData);
		}

		void SetPos(const unsigned char _posNames, const  ChVec2& _posData);

		inline void SetUVPos(const SpritePositionName _posNames, const ChVec2& _posData)
		{
			SetUVPos(ChStd::EnumCast(_posNames), _posData);
		}

		void SetUVPos(const unsigned char _posNames, const  ChVec2& _posData);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//


		inline ChVec2 GetPos(const SpritePositionName _posNames)
		{
			return poss[ChStd::EnumCast(_posNames)];
		}

		inline ChVec2 GetPos(const unsigned char _num)
		{
			if (_num >= 4)return ChVec2();

			return poss[_num];
		}

		inline ChVec2 GetPosUVPos(const SpritePositionName _posNames)
		{
			return uvPoss[ChStd::EnumCast(_posNames)];
		}

		ChVec2 GetPosUVPos(const unsigned char _num)
		{
			if (_num >= 4)return ChVec2();

			return uvPoss[_num];
		}

		///////////////////////////////////////////////////////////////////////////////////
		
		inline void Move(const ChVec2& _vec) { Move(_vec.x, _vec.y); }

		void Move(const float _x,const float _y);

		inline void MoveX(const float _x) { Move(_x, 0.0f); }

		inline void MoveY(const float _y) { Move(0.0f, _y); }

		///////////////////////////////////////////////////////////////////////////////////

		void SetDrawData(ID3D11DeviceContext* _dc)override;

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

		ChVec2 poss[4] =
		{
			ChVec2(-1.0f,1.0f)	//LeftTop//
			,ChVec2(1.0f,1.0f)	//RightTop//
			,ChVec2(1.0f,-1.0f)	//RightDown//
			,ChVec2(-1.0f,-1.0f)	//LeftDown//
		};

		ChVec2 uvPoss[4] =
		{
			ChVec2(0.0f,0.0f)	//LeftTop//
			,ChVec2(1.0f,0.0f)	//RightTop//
			,ChVec2(1.0f,1.0f)	//RightDown//
			,ChVec2(0.0f,1.0f)	//LeftDown//
		};

		ChStd::Bool updateFlg = true;

		PrimitiveData11<Vertex11> primitives;

	};

}

#endif
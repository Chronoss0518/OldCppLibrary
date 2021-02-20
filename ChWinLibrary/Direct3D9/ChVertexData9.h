
namespace ChD3D9
{
#ifndef _DVer9
#define _DVer9

	//Shaderにて板ポリゴンに画像を張り付けて描画を行う際に利用する型//
	struct VertexData
	{

		struct Vertex
		{
			ChVec3_9 Pos;
			ChVec4 Col;
			ChVec2 UV;

			Vertex();

			Vertex(
				const ChVec3_9 _Pos
				, const ChVec4 _Col
				, const ChVec2 _UV
			)
			{
				Pos = _Pos;
				Col = _Col;
				UV = _UV;
			}

		};

		Vertex operator[](const int _n)const
		{
			return Ver[_n];
		}

		Vertex& operator[](const int _n)
		{
			return Ver[_n];
		}

		VertexData& operator=(const VertexData& _Ver)
		{
			for (unsigned char i = 0; i < 4; i++)
			{
				Ver[i] = _Ver.Ver[i];
			}

			return *this;
		}

		VertexData()
		{
			_1 = { ChVec3_9(-1.0f,-1.0f,0.0f),ChVec4(1.0f,1.0f,1.0f,1.0f),ChVec2(0.0f,0.0f) };
			_2 = { ChVec3_9(1.0f,-1.0f,0.0f),ChVec4(1.0f,1.0f,1.0f,1.0f),ChVec2(1.0f,0.0f) };
			_3 = { ChVec3_9(1.0f,1.0f,0.0f),ChVec4(1.0f,1.0f,1.0f,1.0f),ChVec2(1.0f,1.0f) };
			_4 = { ChVec3_9(-1.0f,1.0f,0.0f),ChVec4(1.0f,1.0f,1.0f,1.0f),ChVec2(0.0f,1.0f) };
		};

		VertexData(const Vertex _v1
			, const Vertex _v2
			, const Vertex _v3
			, const Vertex _v4)
		{
			Ver[0] = _v1;
			Ver[1] = _v2;
			Ver[2] = _v3;
			Ver[3] = _v4;
		}

		VertexData(const VertexData& _Ver)
		{
			*this = _Ver;
		}

		union
		{

			struct
			{
				Vertex _1, _2, _3, _4;
			};

			Vertex Ver[4];
		};


	};

	//Z軸を利用しない//
	//Shaderにてスプライト描画を行う際に利用する型//
	struct SpriteData
	{
		SpriteData() 
		{
			SpData = VertexData(
				VertexData::Vertex( ChVec3_9(0.0f,0.0f,0.0f),ChVec4(1.0f,1.0f,1.0f,1.0f),ChVec2(0.0f,0.0f) )
				,
				VertexData::Vertex(ChVec3_9(1280.0f,0.0f,0.0f),ChVec4(1.0f,1.0f,1.0f,1.0f), ChVec2(1.0f,0.0f) )
				,
				VertexData::Vertex(ChVec3_9(1280.0f,720.0f,0.0f),ChVec4(1.0f,1.0f,1.0f,1.0f), ChVec2(1.0f,1.0f) )
				,
				VertexData::Vertex(ChVec3_9(0.0f,720.0f,0.0f),ChVec4(1.0f,1.0f,1.0f,1.0f), ChVec2(0.0f,1.0f) )
			);
		}

		SpriteData(const SpriteData& _SpData)
		{

			SpData = _SpData.SpData;
		}

		SpriteData(const VertexData& _VerData)
		{

			SpData = _VerData;
		}

		SpriteData(const ChVec2& _Pos
			, const ChVec2& _Size)
		{
			SpData.Ver[0].Pos = ChVec3_9(_Pos.x, _Pos.y, 0.0f);
			SpData.Ver[1].Pos = ChVec3_9(_Pos.x + _Size.w, _Pos.y, 0.0f);
			SpData.Ver[2].Pos = ChVec3_9(_Pos.x + _Size.w, _Pos.y + _Size.h, 0.0f);
			SpData.Ver[3].Pos = ChVec3_9(_Pos.x, _Pos.y + _Size.h, 0.0f);
		}

		SpriteData(const  ChVec4& _Rect)
		{
			SpData.Ver[0].Pos = ChVec3_9(_Rect.x, _Rect.y, 0.0f);
			SpData.Ver[1].Pos = ChVec3_9(_Rect.x + _Rect.w, _Rect.y, 0.0f);
			SpData.Ver[2].Pos = ChVec3_9(_Rect.x + _Rect.w, _Rect.y + _Rect.h, 0.0f);
			SpData.Ver[3].Pos = ChVec3_9(_Rect.x, _Rect.y + _Rect.h, 0.0f);
		}

		SpriteData& operator = (const VertexData& _VD)
		{
			SpData = _VD;
			return *this;
		}

		void TextureInvers()
		{
			SpData.Ver[0].UV = SpData.Ver[1].UV + SpData.Ver[0].UV;
			SpData.Ver[1].UV = SpData.Ver[0].UV - SpData.Ver[1].UV;
			SpData.Ver[0].UV = SpData.Ver[0].UV - SpData.Ver[1].UV;

			SpData.Ver[2].UV = SpData.Ver[3].UV + SpData.Ver[2].UV;
			SpData.Ver[3].UV = SpData.Ver[2].UV - SpData.Ver[3].UV;
			SpData.Ver[2].UV = SpData.Ver[2].UV - SpData.Ver[3].UV;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		VertexData SpData;

	};

#endif
}

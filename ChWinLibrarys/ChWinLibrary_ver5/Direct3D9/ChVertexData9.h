
namespace ChD3D9
{
#ifndef _DVer9
#define _DVer9

	//Shaderにて板ポリゴンに画像を張り付けて描画を行う際に利用する型//
	struct VertexData
	{

		struct Vertex
		{
			ChVec3_9 pos;
			ChVec4 col;
			ChVec2 uv;

			Vertex();

			Vertex(
				const ChVec3_9 _pos
				, const ChVec4 _col
				, const ChVec2 _uv
			)
			{
				pos = _pos;
				col = _col;
				uv = _uv;
			}

		};

		Vertex operator[](const int _n)const
		{
			return ver[_n];
		}

		Vertex& operator[](const int _n)
		{
			return ver[_n];
		}

		VertexData& operator=(const VertexData& _ver)
		{
			for (unsigned char i = 0; i < 4; i++)
			{
				ver[i] = _ver.ver[i];
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
			ver[0] = _v1;
			ver[1] = _v2;
			ver[2] = _v3;
			ver[3] = _v4;
		}

		VertexData(const VertexData& _ver)
		{
			*this = _ver;
		}

		union
		{

			struct
			{
				Vertex _1, _2, _3, _4;
			};

			Vertex ver[4];
		};


	};

	//Z軸を利用しない//
	//Shaderにてスプライト描画を行う際に利用する型//
	struct SpriteData
	{
		SpriteData() 
		{
			spData = VertexData(
				VertexData::Vertex( ChVec3_9(0.0f,0.0f,0.0f),ChVec4(1.0f,1.0f,1.0f,1.0f),ChVec2(0.0f,0.0f) )
				,
				VertexData::Vertex(ChVec3_9(1280.0f,0.0f,0.0f),ChVec4(1.0f,1.0f,1.0f,1.0f), ChVec2(1.0f,0.0f) )
				,
				VertexData::Vertex(ChVec3_9(1280.0f,720.0f,0.0f),ChVec4(1.0f,1.0f,1.0f,1.0f), ChVec2(1.0f,1.0f) )
				,
				VertexData::Vertex(ChVec3_9(0.0f,720.0f,0.0f),ChVec4(1.0f,1.0f,1.0f,1.0f), ChVec2(0.0f,1.0f) )
			);
		}

		SpriteData(const SpriteData& _spData)
		{

			spData = _spData.spData;
		}

		SpriteData(const VertexData& _verData)
		{

			spData = _verData;
		}

		SpriteData(const ChVec2& _pos
			, const ChVec2& _size)
		{
			spData.ver[0].pos = ChVec3_9(_pos.x, _pos.y, 0.0f);
			spData.ver[1].pos = ChVec3_9(_pos.x + _size.w, _pos.y, 0.0f);
			spData.ver[2].pos = ChVec3_9(_pos.x + _size.w, _pos.y + _size.h, 0.0f);
			spData.ver[3].pos = ChVec3_9(_pos.x, _pos.y + _size.h, 0.0f);
		}

		SpriteData(const  ChVec4& _Rect)
		{
			spData.ver[0].pos = ChVec3_9(_Rect.left, _Rect.top, 0.0f);
			spData.ver[1].pos = ChVec3_9(_Rect.left + _Rect.right, _Rect.top, 0.0f);
			spData.ver[2].pos = ChVec3_9(_Rect.left + _Rect.right, _Rect.top + _Rect.down, 0.0f);
			spData.ver[3].pos = ChVec3_9(_Rect.left, _Rect.top + _Rect.down, 0.0f);
		}

		SpriteData& operator = (const VertexData& _VD)
		{
			spData = _VD;
			return *this;
		}

		void TextureInvers()
		{
			spData.ver[0].uv = spData.ver[1].uv + spData.ver[0].uv;
			spData.ver[1].uv = spData.ver[0].uv - spData.ver[1].uv;
			spData.ver[0].uv = spData.ver[0].uv - spData.ver[1].uv;
				   					  					 
			spData.ver[2].uv = spData.ver[3].uv + spData.ver[2].uv;
			spData.ver[3].uv = spData.ver[2].uv - spData.ver[3].uv;
			spData.ver[2].uv = spData.ver[2].uv - spData.ver[3].uv;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		VertexData spData;

	};

#endif
}

#ifndef Ch_D3D11_PolyBoard_h
#define Ch_D3D11_PolyBoard_h

#include"../ChShaderStructures11.h"

namespace ChD3D11
{


	class PolygonBoard11 :public ShaderObject<MeshVertex11>
	{

		public:

			///////////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			void Init();

			void Init(ID3D11Device* _Device);

			void Release()override;

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetPos(const unsigned char _PosNo, const ChVec3& _PosData);

			void SetUVPos(const unsigned char _PosNo, const ChVec2& _PosData);

			///////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			inline ChVec3 GetPos(const unsigned char _Num)
			{
				if (_Num >= 4)return ChVec3();

				return Primitives.VertexArray[_Num].Pos;

			}

			inline ChVec2 GetUVPos(const unsigned char _Num)
			{
				if (_Num >= 4)return ChVec2();

				return Primitives.VertexArray[_Num].UVPos;

			}


			///////////////////////////////////////////////////////////////////////////////////

			void SetDrawData(ID3D11DeviceContext* _CD)override;

			///////////////////////////////////////////////////////////////////////////////////

		protected:

			void UpdateVertex();

			///////////////////////////////////////////////////////////////////////////////////

			ChStd::Bool UpdateFlg = true;

			PrimitiveData11<MeshVertex11> Primitives;
	};
}

#endif

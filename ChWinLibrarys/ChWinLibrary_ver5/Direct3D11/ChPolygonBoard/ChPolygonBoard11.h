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

			void Init(ID3D11Device* _device);

			void Release()override;

			///////////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			void SetPos(const unsigned char _posNo, const ChVec3& _posData);

			void SetUVPos(const unsigned char _posNo, const ChVec2& _posData);

			///////////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			inline ChVec3 GetPos(const unsigned char _num)
			{
				if (_num >= 4)return ChVec3();

				return primitives.vertexArray[_num].pos;

			}

			inline ChVec2 GetUVPos(const unsigned char _num)
			{
				if (_num >= 4)return ChVec2();

				return primitives.vertexArray[_num].uvPos;

			}


			///////////////////////////////////////////////////////////////////////////////////

			void SetDrawData(ID3D11DeviceContext* _CD)override;

			///////////////////////////////////////////////////////////////////////////////////

		protected:

			void UpdateVertex();

			///////////////////////////////////////////////////////////////////////////////////

			ChStd::Bool updateFlg = true;

			PrimitiveData11<MeshVertex11> primitives;
	};
}

#endif

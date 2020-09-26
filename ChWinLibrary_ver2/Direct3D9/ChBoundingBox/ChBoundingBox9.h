#ifndef Ch_D3D9_BBox_h
#define Ch_D3D9_BBox_h

namespace ChMesh
{
	typedef class BaseMesh9 Mesh9;


	//(改良中)//
	//メッシュを作成時に生成されるバウンディングボックス、バウンディングスフィア専用クラス//
	//主にボックスを利用するため名前はバウンディングボックス//
	typedef class BoundingBox9
	{

	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		BoundingBox9() {}

		BoundingBox9(const BoundingBox9& _Box)
		{
			*this = _Box;
		}

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//XFileより生成されるバウンディングボックス//
		void SetBBox(const ChPtr::Shared<ChMesh::Mesh9>& _Mesh);

		//XFileより生成されるバウンディングスフィア//
		void SetBSphere(const ChPtr::Shared<ChMesh::Mesh9>& _Mesh);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//最小単位となる位置//
		inline const ChVec3_9* GetBasePos() { return &Main; }

		//最大単位-最小単位で計算された位置
		inline const ChVec3_9* GetDepth() { return &Depth; }

		std::vector<ChPtr::Shared<ChVec3_9>> GetPosition();

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//点と箱の当たり判定//
		ChStd::Bool IsHitToPos(
			const ChMat_9* _Mat
			, const ChVec3_9* _Pos);

		//箱と箱の当たり判定(未完成)//
		ChStd::Bool IsHitToB_Box(
			const ChMat_9* _Mat
			, const BoundingBox9* _Pos);

		//球と箱の当たり判定//
		ChStd::Bool IsHitToBull(
			const ChMat_9* _Mat
			, const ChVec3_9* _Pos
			, const float _R);

	private:

		ChVec3_9 Main;
		ChVec3_9 Depth;
		float Radius;

	}ChB_Box9;

}

#endif
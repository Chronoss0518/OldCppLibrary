
#ifndef Ch_D3D9_XMe_h
#define Ch_D3D9_XMe_h

#include"ChBaseMesh9.h"

namespace ChMesh
{

	class XFileMesh9 :public BaseMesh9
	{
	public:

		void OpenFile(
			const std::string& _fileName
			, const std::string& _pathName
			, const LPDIRECT3DDEVICE9& _dev)override;


	};


}


#endif
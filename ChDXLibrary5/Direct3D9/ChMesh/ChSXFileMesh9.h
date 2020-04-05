
#ifndef Ch_D3D9_SXMe_h
#define Ch_D3D9_SXMe_h

#include"ChSkinMesh9.h"

namespace ChMesh
{

	//������//
	class SXFileMesh9 :public SkinMesh9
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////

		void OpenFile(
			const std::string& _FileName
			, const std::string& _PathName
			, const LPDIRECT3DDEVICE9& _Dev)override;

		///////////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetBone(const std::string& _FileName);

		void SetBoneVertex(const std::string& _FStr);

		///////////////////////////////////////////////////////////////////////////////////////

		void CreateBoneTree(
			const std::string& _FStr
			, size_t& _FPos
			, const ChPtr::Shared<Bone>& _Bone = nullptr);

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		///////////////////////////////////////////////////////////////////////////////////

		static const std::string FreamMat;
		static const std::string SkinWaights;


	};


}


#endif
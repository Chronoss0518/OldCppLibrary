#ifndef Ch_D3D9_RTList_h
#define Ch_D3D9_RTList_h

namespace ChD3D9
{
	class ShaderController;
}

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//レンダーターゲットを設定するクラス//
	typedef class RenderTargetList9 :public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		RenderTargetList9() {};

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(
			const LPDIRECT3DDEVICE9& _dv
			, const unsigned short _windWidth
			, const unsigned short _windHeight
			, const ChD3D9::ShaderController* _shader = nullptr);

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//レンダーターゲット用のテクスチャを設定//
		//第二引数で画面をクリアする色指定//
		//ChD3D9::Shader::DrawStartと併用できません//
		void SetRT(
			const ChStd::DataNo _dataNum
			, const D3DCOLOR _backCol = D3DCOLOR_ARGB(0,0,0,0));

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//作成したテクスチャを取得//
		inline ChPtr::Shared<Texture9> GetRTTexture(const ChStd::DataNo _dataNum)
		{
			if (rtList.find(_dataNum) == rtList.end())return nullptr;
			return rtList[_dataNum];
		}

		///////////////////////////////////////////////////////////////////////////////////

		//登録されてるテクスチャを選択して消去//
		inline void DeleteRTTexture(const ChStd::DataNo _dataNum)
		{
			if (rtList.empty())return;
			if (rtList.find(_dataNum) == rtList.end())return;

			rtList.erase(_dataNum);

		}

		///////////////////////////////////////////////////////////////////////////////////

		//登録してあるすべてのレンダーターゲットテクスチャを解放//
		inline void ClearRT()
		{
			if (rtList.empty())return;
			rtList.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////

		//レンダーターゲットとなるテクスチャを作成:登録//
		void CreateRT(
			const ChStd::DataNo _dataNum
			, const UINT _rtWidth = 1280
			, const UINT _rtHeight = 720
			, const _D3DFORMAT _FMT = D3DFMT_A8R8G8B8);

		///////////////////////////////////////////////////////////////////////////////////

		//レンダーターゲットをバックバッファに戻す//
		void ReturnRT();

	private:

		///////////////////////////////////////////////////////////////////////////////////

		LPDIRECT3DDEVICE9 device;

		std::map<ChStd::DataNo, ChPtr::Shared<BaseTexture9>>rtList;

		ChPtr::Shared<BaseTexture9>dbData = nullptr;

		ChD3D9::ShaderController* uShader = nullptr;

	}ChRTList9;

}

#endif
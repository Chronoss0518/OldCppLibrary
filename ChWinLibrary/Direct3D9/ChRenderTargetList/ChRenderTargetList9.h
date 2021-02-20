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
	typedef class RenderTargetList9 :public ChCpp::ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		RenderTargetList9() {};

		~RenderTargetList9() { Release(); }

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(
			const LPDIRECT3DDEVICE9& _Dv
			, const unsigned short _WW
			, const unsigned short _WH
			, const ChD3D9::ShaderController* _Shader = nullptr);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//レンダーターゲット用のテクスチャを設定//
		//第二引数で画面をクリアする色指定//
		//ChD3D9::Shader::DrawStartと併用できません//
		void SetRT(
			const ChStd::DataNo _DataNum
			, const D3DCOLOR _BackCol = D3DCOLOR_ARGB(0,0,0,0));

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//作成したテクスチャを取得//
		inline ChPtr::Shared<Texture9> GetRTTexture(const ChStd::DataNo _DataNum)
		{
			if (RTList.find(_DataNum) == RTList.end())return nullptr;
			return RTList[_DataNum];
		}

		///////////////////////////////////////////////////////////////////////////////////

		//登録されてるテクスチャを選択して消去//
		inline void DeleteRTTexture(const ChStd::DataNo _DataNum)
		{
			if (RTList.empty())return;
			if (RTList.find(_DataNum) == RTList.end())return;

			RTList.erase(_DataNum);

		}

		///////////////////////////////////////////////////////////////////////////////////

		//登録してあるすべてのレンダーターゲットテクスチャを解放//
		inline void ClearRT()
		{
			if (RTList.empty())return;
			RTList.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////

		//レンダーターゲットとなるテクスチャを作成:登録//
		void CreateRT(
			const ChStd::DataNo _DataNum
			, const UINT _RTW = 1280
			, const UINT _RTH = 720
			, const _D3DFORMAT _FMT = D3DFMT_A8R8G8B8);

		///////////////////////////////////////////////////////////////////////////////////

		//レンダーターゲットをバックバッファに戻す//
		void ReturnRT();

	private:

		///////////////////////////////////////////////////////////////////////////////////

		LPDIRECT3DDEVICE9 Device;

		std::map<ChStd::DataNo, ChPtr::Shared<BaseTexture9>>RTList;

		ChPtr::Shared<BaseTexture9>DBData = nullptr;

		ChD3D9::ShaderController* UShader = nullptr;

	}ChRTList9;

}

#endif
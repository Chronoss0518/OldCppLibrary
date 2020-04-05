#ifndef Ch_D3D9_ReTa_h
#define Ch_D3D9_ReTa_h

namespace ChTex
{

	typedef class BaseTexture9 Texture9;

	//レンダーターゲットを設定するクラス//
	class RenderTargetManager9
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(
			const LPDIRECT3DDEVICE9& _Dv
			, const unsigned short _WW
			, const unsigned short _WH);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//レンダーターゲット用のテクスチャを設定//
		void SetRT(const std::string& _DataName);

		///////////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		//作成したテクスチャを取得//
		inline ChPtr::Shared<Texture9> GetRTTexture(const std::string& _DataName)
		{
			if (RTList.find(_DataName) == RTList.end())return nullptr;
			return RTList[_DataName];
		}

		///////////////////////////////////////////////////////////////////////////////////

		//登録されてるテクスチャを選択して消去//
		inline void DeleteRTTexture(const std::string& _DataName)
		{
			if (RTList.empty())return;
			if (RTList.find(_DataName) == RTList.end())return;

			RTList.erase(_DataName);

		}

		///////////////////////////////////////////////////////////////////////////////////

		//登録してあるすべてのレンダーターゲットテクスチャを解放//
		inline void ClearRT()
		{
			if (RTList.empty())return;
			RTList.clear();
		}

		///////////////////////////////////////////////////////////////////////////////////

		inline void SetClearColor(const ChStd::COLOR255& _Col)
		{
			ClearColor = _Col;
		}

		///////////////////////////////////////////////////////////////////////////////////

		inline void SetClearColor(const D3DCOLOR& _Col)
		{
			ClearColor.a = (unsigned char)((_Col >> 24) & 0xff);
			ClearColor.r = (unsigned char)((_Col >> 16) & 0xff);
			ClearColor.g = (unsigned char)((_Col >> 8) & 0xff);
			ClearColor.b = (unsigned char)((_Col) & 0xff);
		}

		///////////////////////////////////////////////////////////////////////////////////

		//レンダーターゲットとなるテクスチャを作成:登録//
		void CreateRT(
			const std::string& _DataName
			, const UINT _RTW = 1280
			, const UINT _RTH = 720
			, const _D3DFORMAT _FMT = D3DFMT_A8R8G8B8);

		///////////////////////////////////////////////////////////////////////////////////

		//レンダーターゲットをバックバッファに戻す//
		void ReturnRT();

	private:

		///////////////////////////////////////////////////////////////////////////////////

		LPDIRECT3DDEVICE9 Device;

		std::map<std::string, ChPtr::Shared<BaseTexture9>>RTList;

		ChPtr::Shared<BaseTexture9>DBData;

		ChStd::COLOR255 ClearColor = ChStd::COLOR255(0, 0, 0, 0);

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		RenderTargetManager9() {};

		~RenderTargetManager9() { Release(); }

	public:

		static RenderTargetManager9& GetInc()
		{
			static RenderTargetManager9 Ins;
			return Ins;
		}

	};

	static const std::function<RenderTargetManager9&()> RTManager9 = RenderTargetManager9::GetInc;

}

#endif
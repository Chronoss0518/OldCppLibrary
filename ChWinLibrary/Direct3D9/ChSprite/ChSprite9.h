#pragma once
#ifndef Ch_D3D9_Sp_h
#define Ch_D3D9_Sp_h

namespace ChTex
{
	typedef class BaseTexture9 Texture9;

	//(シングルトンに対して改良中)
	//スプライト描画を行うクラス//
	class Sprite9 {
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(const LPDIRECT3DDEVICE9 _d);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////

		//第三引数がNULL又はnullptrだった場合,画面サイズと同じになる。//
		virtual void DrawSprite(
			const ChPtr::Shared<Texture9> _tex
			, const ChMat_9& _Mat
			, const ChVec3_9& _CenterPos
			, const RECT& _AnimationRect = { 0,0,0,0 });

		///////////////////////////////////////////////////////////////////////////////////

	protected:


		LPD3DXSPRITE Sp;
		LPDIRECT3DDEVICE9 Device;

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		Sprite9() {};

		virtual ~Sprite9() {
			Release();
		};

	private:

		ChStd::Bool InitFlg = false;

	public:

		inline ChStd::Bool IsInit() { return InitFlg; }

		inline static Sprite9& GetIns()
		{
			static Sprite9 Ins;
			return Ins;
		}

	};

	static const std::function<Sprite9&()>DrawSp9 = Sprite9::GetIns;

}

#endif
//CopyRight Chronoss0518 2018/08

#ifndef Ch_D3D9_Sp_h
#define Ch_D3D9_Sp_h

namespace ChTex
{
	typedef class BaseTexture9 Texture9;

	//(シングルトンに対して改良中)
	//スプライト描画を行うクラス//
	class Sprite9 :public ChCp::Initializer,public ChCp::Releaser
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(const LPDIRECT3DDEVICE9 _d);

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////////

		//第三引数がNULL又はnullptrだった場合,画面サイズと同じになる。//
		virtual void DrawSprite(
			const ChPtr::Shared<Texture9> _tex
			, const ChMat_9& _mat
			, const ChVec3_9& _centerPos
			, const RECT& _animationRect = { 0,0,0,0 });

		///////////////////////////////////////////////////////////////////////////////////

	protected:


		LPD3DXSPRITE sp;
		LPDIRECT3DDEVICE9 device;

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		Sprite9() {};

	public:

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
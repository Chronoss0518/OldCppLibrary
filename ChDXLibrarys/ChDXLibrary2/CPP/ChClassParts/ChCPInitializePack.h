
#ifndef Ch_CPP_CP_Init_h
#define Ch_CPP_CP_Init_h

namespace ChCpp
{
	namespace ChCp
	{
		//継承して利用する//
		//初期化が完了しているか確認できるようになる//
		//初期化をするときにSetInitFlg(true);を//
		//解放するときにはSetInitFlg(false);を呼ぶ事//
		typedef class InitializePack
		{
		private:

			ChStd::Bool InitFlg = false;

		protected:

			inline void SetInitFlg(const ChStd::Bool _Flg) { InitFlg = _Flg; }

		public:

			explicit operator bool()const { return InitFlg; }

			inline ChStd::Bool IsInit() { return InitFlg; }

		}InitPack;


	}
}

#endif

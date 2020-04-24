
#ifndef Ch_CPP_CP_Init_h
#define Ch_CPP_CP_Init_h

namespace ChCpp
{
	namespace ChCp
	{
		//Œp³‚µ‚Ä—˜—p‚·‚é//
		//‰Šú‰»‚ªŠ®—¹‚µ‚Ä‚¢‚é‚©Šm”F‚Å‚«‚é‚æ‚¤‚É‚È‚é//
		//‰Šú‰»‚ğ‚·‚é‚Æ‚«‚ÉSetInitFlg(true);‚ğ//
		//‰ğ•ú‚·‚é‚Æ‚«‚É‚ÍSetInitFlg(false);‚ğŒÄ‚Ô–//
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

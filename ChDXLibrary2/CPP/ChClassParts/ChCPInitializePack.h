
#ifndef Ch_CPP_CP_Init_h
#define Ch_CPP_CP_Init_h

namespace ChCpp
{
	namespace ChCp
	{
		//�p�����ė��p����//
		//���������������Ă��邩�m�F�ł���悤�ɂȂ�//
		//������������Ƃ���SetInitFlg(true);��//
		//�������Ƃ��ɂ�SetInitFlg(false);���ĂԎ�//
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
